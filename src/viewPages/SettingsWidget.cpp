#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"

static const int INTENSITY_MIN = 1;
static const int INTENSITY_MAX = 10;
static const int SIZEMIN = 5;
static const int SIZEMAX = 30;
static const float SIZE_DEFAULT = 0.5;
static const float INTENSITY_DEFAULT = 1.0;

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::SettingsWidget)
{
    m_ui->setupUi(this);

    // Reset elemements to default
    reset();

    // Make connections (propagate signals)
    connect(m_ui->genes_threshold,
            &QSlider::valueChanged, this, &SettingsWidget::slotGenesTreshold);
    connect(m_ui->reads_threshold,
            &QSlider::valueChanged, this, &SettingsWidget::slotReadsTreshold);
    connect(m_ui->individual_reads_threshold,
            &QSlider::valueChanged, this, &SettingsWidget::slotIndReadsTreshold);
    connect(m_ui->spots_intensity,
            &QSlider::valueChanged, this, &SettingsWidget::slotIntensity);
    connect(m_ui->spots_size,
            &QSlider::valueChanged, this, &SettingsWidget::slotSize);

    connect(m_ui->show_image, &QCheckBox::stateChanged, this, &SettingsWidget::signalShowImage);
    connect(m_ui->show_spots, &QCheckBox::stateChanged, this, &SettingsWidget::signalShowSpots);
    connect(m_ui->legend, &QCheckBox::stateChanged, this, &SettingsWidget::signalShowLegend);
    connect(m_ui->gene_cutoff, &QCheckBox::stateChanged, this, &SettingsWidget::slotGeneCutoff);

    connect(m_ui->normalization_raw, &QRadioButton::clicked, this,
            [=]() {slotNormalization(NormalizationMode::RAW);});
    connect(m_ui->normalization_tpm, &QRadioButton::clicked, this,
            [=]() {slotNormalization(NormalizationMode::TPM);});
    connect(m_ui->normalization_rel, &QRadioButton::clicked, this,
            [=]() {slotNormalization(NormalizationMode::REL);});
    connect(m_ui->normalization_deseq, &QRadioButton::clicked, this,
            [=]() {slotNormalization(NormalizationMode::DESEQ);});
    connect(m_ui->normalization_scran, &QRadioButton::clicked, this,
            [=]() {slotNormalization(NormalizationMode::SCRAN);});

    connect(m_ui->visual_reads, &QRadioButton::clicked, this,
            [=]() {slotVisualMode(Reads);});
    connect(m_ui->visual_reads_log, &QRadioButton::clicked, this,
            [=]() {slotVisualMode(ReadsLog);});
    connect(m_ui->visual_genes, &QRadioButton::clicked, this,
            [=]() {slotVisualMode(Genes);});
    connect(m_ui->visual_genes_log, &QRadioButton::clicked, this,
            [=]() {slotVisualMode(GenesLog);});

    connect(m_ui->visual_normal, &QRadioButton::clicked, this,
            [=]() {slotVisualMode(Normal);});
    connect(m_ui->visual_dynamic_range, &QRadioButton::clicked, this,
            [=]() {slotVisualMode(DynamicRange);});
    connect(m_ui->visual_heatmap, &QRadioButton::clicked, this,
            [=]() {slotVisualMode(HeatMap);});
    connect(m_ui->visual_color_range, &QRadioButton::clicked, this,
            [=]() {slotVisualMode(ColorRange);});
}

SettingsWidget::~SettingsWidget()
{
}

void SettingsWidget::reset()
{
    m_ui->spots_intensity->setMinimum(INTENSITY_MIN);
    m_ui->spots_intensity->setMaximum(INTENSITY_MAX);
    m_ui->spots_size->setMinimum(SIZEMIN);
    m_ui->spots_size->setMaximum(SIZEMAX);
    m_ui->show_image->setChecked(true);
    m_ui->show_spots->setChecked(true);
    m_ui->legend->setChecked(false);
    m_ui->gene_cutoff->setChecked(false);
    m_ui->normalization_raw->setChecked(true);
    m_ui->visual_reads->setChecked(true);
    m_ui->visual_normal->setChecked(true);
    m_rendering_settings.intensity = INTENSITY_DEFAULT;
    m_rendering_settings.size = SIZE_DEFAULT;
    m_rendering_settings.gene_cutoff = false;
    m_rendering_settings.genes_threshold = 0;
    m_rendering_settings.reads_threshold = 0;
    m_rendering_settings.ind_reads_threshold = 0;
    m_rendering_settings.normalization_mode = SettingsWidget::RAW;
    m_rendering_settings.visual_mode = SettingsWidget::Normal;
    m_rendering_settings.visual_type_mode = SettingsWidget::Reads;
}

const SettingsWidget::Rendering &SettingsWidget::renderingSettings() const
{
    return m_rendering_settings;
}

void SettingsWidget::resetReadsThreshold(int min, int max)
{
    m_ui->individual_reads_threshold->setMinimum(min);
    m_ui->individual_reads_threshold->setMaximum(max);
}

void SettingsWidget::resetTotalReadsThreshold(int min, int max)
{
    m_ui->reads_threshold->setMinimum(min);
    m_ui->reads_threshold->setMaximum(max);
}

void SettingsWidget::resetTotalGenesThreshold(int min, int max)
{
    m_ui->genes_threshold->setMinimum(min);
    m_ui->genes_threshold->setMaximum(max);
}

void SettingsWidget::slotGenesTreshold(int value)
{
    if (m_rendering_settings.genes_threshold != value) {
        m_rendering_settings.genes_threshold = value;
        emit signalSpotRendering();
    }
}

void SettingsWidget::slotReadsTreshold(int value)
{
    if (m_rendering_settings.reads_threshold != value) {
        m_rendering_settings.reads_threshold = value;
        emit signalSpotRendering();
    }
}

void SettingsWidget::slotIndReadsTreshold(int value)
{
    if (m_rendering_settings.ind_reads_threshold != value) {
        m_rendering_settings.ind_reads_threshold = value;
        emit signalSpotRendering();
    }
}

void SettingsWidget::slotIntensity(int value)
{
    if (m_rendering_settings.intensity != value) {
        m_rendering_settings.intensity = value;
        emit signalSpotRendering();
    }
}

void SettingsWidget::slotSize(int value)
{
    if (m_rendering_settings.size != value) {
        m_rendering_settings.size = value;
        emit signalSpotRendering();
    }
}

void SettingsWidget::slotGeneCutoff(bool value)
{
    if (m_rendering_settings.gene_cutoff != value) {
        m_rendering_settings.gene_cutoff = value;
        emit signalSpotRendering();
    }
}

void SettingsWidget::slotNormalization(NormalizationMode mode)
{
    if (m_rendering_settings.normalization_mode != mode) {
        m_rendering_settings.normalization_mode = mode;
        emit signalSpotRendering();
    }
}

void SettingsWidget::slotVisualMode(VisualMode mode)
{
    if (m_rendering_settings.visual_mode != mode) {
        m_rendering_settings.visual_mode = mode;
        emit signalSpotRendering();
    }
}

void SettingsWidget::slotVisualMode(VisualTypeMode mode)
{
    if (m_rendering_settings.visual_type_mode != mode) {
        m_rendering_settings.visual_type_mode = mode;
        emit signalSpotRendering();
    }
}
