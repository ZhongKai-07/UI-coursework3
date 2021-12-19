#ifndef WINDOW_H
#define WINDOW_H

#include "the_menu.h"


#include <QWidget>

class Window : public QWidget
{
Q_OBJECT

public:
    Window();
    ~Window();

private:
    QHBoxLayout *layout;

    //QMap<QString, QIcon>* icons;

    TheMenu *theMenu;

    //QMap<QString, QIcon>* readIcons(QString loc);
    void addConnect();

private slots:
    void showMenu();
    void showPlayer();
};

#endif // WINDOW_H
