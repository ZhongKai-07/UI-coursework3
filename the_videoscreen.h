#ifndef THE_VIDEOSCREEN_H
#define THE_VIDEOSCREEN_H


#include <QVideoWidget>

class VideoScreen : public QVideoWidget
{
Q_OBJECT
public:
    VideoScreen() : QVideoWidget(){

    }
protected:
    void keyPressEvent(QKeyEvent *event);
    //double click will make the screen full
    void doubleclickEvent(QMouseEvent *event);

private slots:
    void setFull(bool value);

};

#endif // THE_VIDEOSCREEN_H
