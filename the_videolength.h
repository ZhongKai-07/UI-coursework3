#ifndef THE_VIDEOLENGTH_H
#define THE_VIDEOLENGTH_H

#include <QLabel>
#include <QUrl>
#include <QStyle>
#include <QAudio>
#include <QWidget>
#include <QSlider>
#include <QMediaPlayer>

class videoLength : public QLabel{
    Q_OBJECT
public:
        videoLength(QWidget *parent) : QLabel(parent){
    }
private slots:
    void  setLength(qint64);
private:
    bool playValue;

};

#endif // THE_VIDEOLENGTH_H
