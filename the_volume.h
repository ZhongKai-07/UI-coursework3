#ifndef THE_VOLUME_H
#define THE_VOLUME_H

#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QSlider>
#include <QStyleFactory>

class Volume : public QPushButton{
    Q_OBJECT
public:
    Volume(QWidget *parent) : QPushButton(parent){
        setIconSize(QSize(40, 40));
        setFixedSize(60, 60);
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        connect(this, SIGNAL(released()), this, SLOT(clicked()));
    }
    void setMute(bool mute);

private slots:
    void click();
    void changeIcon(int vol_value);

signals:
    void mute(bool muted);
    void moveSlider(int volume);

private:
    //starts muted;
    bool muteValue = false;
};

class VolumeSlider : public QSlider{
    Q_OBJECT
public:
    VolumeSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent){
        setStyle(QStyleFactory::create("Fusion"));
        setTracking(true);
        setRange(0,100);
        setFixedSize(500,40);
    }

private slots:
    void moveSlider(int volume);
};

#endif // THE_VOLUME_H
