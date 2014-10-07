/*
    Copyright (C) 2012  Spatial Transcriptomics AB,
    read LICENSE for licensing terms.
    Contact : Jose Fernandez Navarro <jose.fernandez.navarro@scilifelab.se>

*/
#ifndef SPINBOXSLIDER_H
#define SPINBOXSLIDER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPointer>

#include "qxtspanslider.h"

//Wrapper around QxtSpanSlider
//to add two spin boxes one on each side

// double bar slider is DISABLED at the moment
class SpinBoxSlider : public QWidget
{
    Q_OBJECT

public:
    
    explicit SpinBoxSlider(QWidget *parent = 0);
    virtual ~SpinBoxSlider();

    void setToolTip(const QString &str);
    void setMaximumValue(const int max);
    void setMinimumValue(const int min);
    void setTickInterval(const int interval);

signals:

    //TODO signals should have prefix "signal"
    void lowerValueChanged(int);
    void upperValueChanged(int);

public slots:
    
    //TODO slots should have prefix "slot"
    void setLowerValue(const int min);
    void setUpperValue(const int max);

private:

    void setLowerValuePrivate(const int min);
    void setUpperValuePrivate(const int max);

    //QPointer<QxtSpanSlider> m_spanslider;
    QPointer<QSpinBox> m_left_spinbox;
    QPointer<QSpinBox> m_right_spinbox;
    QPointer<QHBoxLayout> m_layout;

    int m_upper_value;
    int m_lower_value;

    Q_DISABLE_COPY(SpinBoxSlider)
};

#endif


