#ifndef THE_VIDEOSLIDER_H
#define THE_VIDEOSLIDER_H

#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QSlider>

class videoSlider : public QSlider{
    Q_OBJECT
public:
    videoSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent){
        setTracking(true);
        setRange(0, 0);
    }

private slots:
    void SetValue(qint64 volume);
    void SetRange(qint64 volume);
};

#endif // THE_VIDEOSLIDER_H
