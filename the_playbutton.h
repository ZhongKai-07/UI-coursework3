#ifndef THE_PLAYBUTTON_H
#define THE_PLAYBUTTON_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QMediaPlayer>


class PlayButton : public QPushButton {
    Q_OBJECT
public:
    PlayButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        setIconSize(QSize(40, 40));
        setFixedSize(60,60);
        //we use the QStyle in built icons for our play button
   }
private slots:
    //void clicked();
    void setState(QMediaPlayer::State state);
};

class StopButton : public QPushButton {
    Q_OBJECT
public:
    StopButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaStop));
        setIconSize(QSize(40, 40));
        setFixedSize(60,60);
   }
private slots:
    //void clicked();
};


#endif
