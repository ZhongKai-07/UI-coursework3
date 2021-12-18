#include "window.h"

#include <QDir>
#include <QDirIterator>

Window::Window()
{
    layout = new QHBoxLayout();
    layout->setMargin(0);
    setLayout(layout);

    //icons = readIcons("../icon");

    theMenu = new TheMenu();
    thePlayer = new Player();

    layout->addWidget(theMenu);
    layout->addWidget(thePlayer);


    addConnect();

    setMinimumSize(1080, 720);

    showMenu();
}

Window::~Window()
{
    //delete icons;
}

//QMap<QString, QIcon>* Window::readIcons(QString loc)
//{
//    QMap<QString, QIcon>* icons = new QMap<QString, QIcon>();
//    QDir dir(loc);
//    QDirIterator it(dir);
//    while (it.hasNext())
//    {
//        QFileInfo file(it.next());
//        icons->insert(file.baseName(), QIcon(file.filePath()));
//    }
//    return icons;
//}

void Window::addConnect()
{
    //connect(thePlayer, SIGNAL(backToMenu()), this, SLOT(showMenu()));
    connect(theMenu, SIGNAL(playListChanged(QVector<VideoInfo*>*)), this, SLOT(showPlayer()));
    connect(theMenu, SIGNAL(playListChanged(QVector<VideoInfo*>*)), thePlayer, SLOT(open(QVector<VideoInfo*>*)) );
    //player
    connect(theMenu, SIGNAL(playListChanged1(QList<QUrl>)), thePlayer, SLOT(launch(QList<QUrl>)));
    //connect(theMenu, SIGNAL(playListChanged(QVector<VideoInfo*>*)), thePlayer, SLOT(setMediaList(QVector<VideoInfo*>*)));
    connect(thePlayer, SIGNAL(backClicked()), this, SLOT(showMenu()));
}

void Window::showMenu()
{
    theMenu->setVisible(true);
    thePlayer->setHidden(true);
}
void Window::showPlayer()
{
    thePlayer->clearPlaylist();
    theMenu->setHidden(true);
    thePlayer->setVisible(true);
}
