#include "window.h"
#include "login.h"

#include <QApplication>

#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    Login login;
    login.setWindowTitle("Login in");
    w.setWindowTitle("Tomeo");
    try {
        if(login.exec() == QDialog::Accepted)
        {
            w.show();
            return a.exec();
        }
    } catch (exception e) {
        qDebug() << e.what() << endl;
    }

    return a.exec();
}
