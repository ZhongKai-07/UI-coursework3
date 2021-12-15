#include "the_videoscreen.h"
#include <QMouseEvent>
#include <QKeyEvent>

void VideoScreen::keyPressEvent(QKeyEvent *event){
    setFullScreen(!isFullScreen());
    event->accept();
}

void VideoScreen::doubleclickEvent(QMouseEvent *event){
    setFullScreen(!isFullScreen());
    event->accept();
}

void VideoScreen::setFull(bool value) {
    setFullScreen(!value);
}
