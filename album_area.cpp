#include "album_button.h"
#include "album_area.h"

#include <QDir>
#include <QDirIterator>
#include <QInputDialog>
#include <QMessageBox>
#include<iostream>
#include <QDebug>

AlbumArea::AlbumArea()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);

    layout = new AlbumLayout();
    layout->setContentsMargins(64, 32, 64, 0);
    layout->setSpacing(32);

    widget = new QWidget();
    widget->setLayout(layout);

    allList = new QVector<VideoInfo*>();
    filterList = new QVector<VideoInfo*>();
    oneVideo = new QVector<VideoInfo*>();

    connect(layout, SIGNAL(widgetSizeHint(QSize)), this, SLOT(changeWidgetSize(QSize)));
}

AlbumArea::~AlbumArea()
{
    for(VideoInfo* v : *allList)
    {
        delete v;
    }
    delete allList;
    for(VideoInfo* v : *filterList)
    {
        delete v;
    }
    delete filterList;
    for(VideoInfo* v : *oneVideo)
    {
        delete v;
    }
    delete oneVideo;
}

void AlbumArea::resizeEvent(QResizeEvent *e)
{
    QScrollArea::resizeEvent(e);
    layout->setGeometry(rect());
}

QVector<VideoInfo*>* AlbumArea::getFilterList()
{
    return filterList;
}

QVector<VideoInfo*>* AlbumArea::getAllList()
{
    return allList;
}

QList<QUrl> AlbumArea::getUrlList()
{
    return urls;
}

void AlbumArea::showResults()
{
    QLayoutItem *child;
    while((child = layout->takeAt(0)) != nullptr)
    {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }
        delete child;
    }
    for(VideoInfo* i : *filterList)
    {
        AlbumButton *b = new AlbumButton(i);
        layout->addWidget(b);

        connect(b, SIGNAL(albumButtonClicked(VideoInfo*)), this, SLOT(videoButtonClicked(VideoInfo*)));
    }
    layout->setGeometry(rect());
    setWidget(widget);
}

void AlbumArea::addFiles(QStringList files)
{
    for(QString file : files)
    {
        if(file != nullptr && file != "")
        {
            bool in = false;
            for(VideoInfo* info : *allList)
            {
                if(QUrl(file) == info->getUrl())
                {
                    in = true;
                    break;
                }
            }
            if(in == true)
            {
                QMessageBox::information(this, "打开失败", "文件已存在！");
            }
            else
            {
                QUrl url;
                url = QUrl::fromLocalFile(file);
                urls.append(url);
                //qDebug() << "url_list" << urls[0] ;
                //qDebug() << "album_area" << url ;
                VideoInfo *video = new VideoInfo(file);
                //qDebug() << "video_info url" << video->getUrl();
                allList->push_back(video);
            }
        }
    }
}

//delete the video
void AlbumArea::deleteFiles(QVector<VideoInfo*> *video)
{
    QString filename;
    VideoInfo *devideo;
    int index = 0;
    for(auto i : *allList){
        for(auto j : *video){
            if(i->getName()!=j->getName()){
                index++;
            }else{
                devideo = i;
                filename = i->getName();
                qDebug() << "delete name:" << i->getName() ;
                allList->erase(allList->begin()+index);
            }
        }
    }
    int a =0;
    for(auto i : urls){
        if(i.toString().mid(i.toString().length()-7, i.toString().length())==
                devideo->getUrl().toString().mid(devideo->getUrl().toString().length()-7,
                                                   devideo->getUrl().toString().length()))
        {
            qDebug() << "matched";
            urls.removeAt(a);
        }else{
            a++;
            qDebug() << "Not mached";
        }
    }
}



void AlbumArea::getResults(QStringList infos)
{
    filterList->clear();
    for(VideoInfo *v : *allList)
    {
        if(v->matched(infos) == true)
        {
            filterList->push_back(v);
        }
    }
    showResults();
}

void AlbumArea::videoButtonClicked(VideoInfo *video)
{
    oneVideo->clear();
    oneVideo->push_back(video);
    emit videoClicked(oneVideo);
}

void AlbumArea::changeWidgetSize(QSize size)
{
    widget->resize(size);
}
