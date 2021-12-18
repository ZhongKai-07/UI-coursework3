#include "the_menu.h"

TheMenu::TheMenu(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    setLayout(layout);

    filter = new FilterWidget();
    album = new AlbumArea();
    menuBar = new MenuBar();
    infoBar = new InfoBar();

    layout->addWidget(filter);
    layout->addWidget(album);
    layout->addWidget(menuBar);
    layout->addWidget(infoBar);

    showMenuBar();

    addConnect();
}

TheMenu::~TheMenu()
{

}

void TheMenu::addConnect()
{
    connect(filter, SIGNAL(search(QStringList)), album, SLOT(getResults(QStringList)));

    connect(menuBar, SIGNAL(upload(QStringList)), album, SLOT(addFiles(QStringList)));
    connect(menuBar, SIGNAL(upload(QStringList)), filter, SLOT(defaultSearch()));
    connect(menuBar, SIGNAL(toPlay()), this, SLOT(toPlaySlot()));
    //player
    connect(menuBar, SIGNAL(toPlay()), this, SLOT(toPlaySlot1()));


    connect(album, SIGNAL(videoClicked(QVector<VideoInfo*>*)), this, SLOT(videoClicked(QVector<VideoInfo*>*)));
    connect(album, SIGNAL(videoClicked(QVector<VideoInfo*>*)), infoBar, SLOT(setInputPlaceHolder(QVector<VideoInfo*>*)));
    connect(album, SIGNAL(videoClicked(QVector<VideoInfo*>*)), infoBar, SLOT(clearLabels()));

    connect(infoBar, SIGNAL(back()), this, SLOT(showMenuBar()));
    connect(infoBar, SIGNAL(playVideo(QVector<VideoInfo*>*)), this, SLOT(toPlayOneSlot(QVector<VideoInfo*>*)));

    connect(infoBar, SIGNAL(deleteVideo(QVector<VideoInfo*>*)), album, SLOT(deleteFiles(QVector<VideoInfo*>*)));
    connect(infoBar, SIGNAL(deleteVideo(QVector<VideoInfo*>*)), filter, SLOT(defaultSearch()));

}

void TheMenu::showMenuBar()
{
    menuBar->setVisible(true);
    infoBar->setHidden(true);
}
void TheMenu::showInfoBar()
{
    menuBar->setHidden(true);
    infoBar->setVisible(true);
}

void TheMenu::toPlaySlot()
{
    QVector<VideoInfo*> *list = album->getAllList();
    //QList<QUrl> list = album->getAllList();
    if(list->size() > 0)
    {
        emit playListChanged(list);
    }
}

void TheMenu::toPlaySlot1()
{
    QList<QUrl> list = album->getUrlList();
    if(list.length() > 0){
        emit playListChanged1(list);
    }
}

void TheMenu::videoClicked(QVector<VideoInfo*> *video)
{
    showInfoBar();
    infoBar->setVideo(video);
}

void TheMenu::toPlayOneSlot(QVector<VideoInfo*> *video)
{
    emit playListChanged(video);
    showMenuBar();
}

//AlbumArea *TheMenu::getAlbum()
//{
//    return album;
//}
