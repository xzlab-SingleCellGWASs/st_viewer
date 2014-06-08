/*
    Copyright (C) 2012  Spatial Transcriptomics AB,
    read LICENSE for licensing terms.
    Contact : Jose Fernandez Navarro <jose.fernandez.navarro@scilifelab.se>

*/

#ifndef GENESWIDGET_H
#define GENESWIDGET_H

#include <QWidget>

#include "data/DataProxy.h"

class ColorPickerPopup;
class QPushButton;
class QLineEdit;
class GenesTableView;
class GeneFeatureItemModel;
class QSortFilterProxyModel;

class GenesWidget : public QWidget
{
    Q_OBJECT

public:

    explicit GenesWidget(QWidget *parent = 0);
    virtual ~GenesWidget();

signals:

    void signalSelectionChanged(DataProxy::GeneList);
    void signalColorChanged(DataProxy::GeneList);

public slots:

    void slotSetColorAllSelected(const QColor &color);
    void slotSetVisibilityForSelectedRows(bool visible);

    void slotLoadModel();
    void slotClearModel();

private slots:

    void slotHideAllSelected();
    void slotShowAllSelected();

 private:

    QSortFilterProxyModel *getProxyModel();
    GeneFeatureItemModel *getModel();

    ColorPickerPopup *m_colorPickerPopup;
    QPushButton *m_selectionMenu;
    QPushButton *m_actionMenu;
    QLineEdit *m_lineEdit;
    GenesTableView *m_genes_tableview;

    Q_DISABLE_COPY(GenesWidget)
};

#endif // GENESWIDGET_H
