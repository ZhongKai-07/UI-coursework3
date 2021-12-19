#ifndef THE_SKIPBUTTON_H
#define THE_SKIPBUTTON_H


#include <QPushButton>
#include <QStyle>
#include <QWidget>

class ForwardButton : public QPushButton {
    Q_OBJECT
public:
    ForwardButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
        setIconSize(QSize(40, 40));
        setFixedSize(60,60);
   }

};
// as with the play button, QStyle is used for the button icon
class BackwardButton : public QPushButton {
    Q_OBJECT
public:
    BackwardButton(QWidget *parent) :  QPushButton( parent) {
        setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
        setIconSize(QSize(40, 40));
        setFixedSize(60,60);
   }

};

#endif
