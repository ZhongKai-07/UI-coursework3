#ifndef THE_MENU_H
#define THE_MENU_H

#include "album_area.h"
#include "filter_widget.h"
#include "info_bar.h"
#include "menu_bar.h"
#include "video_info.h"
#include "player/player.h"

#include <QVBoxLayout>
#include <QWidget>

class TheMenu : public QWidget
{
Q_OBJECT

public:
    TheMenu(QWidget *parent=nullptr);
    ~TheMenu();

    //AlbumArea *getAlbum();
private:

    QVBoxLayout *layout;

    FilterWidget *filter;
    AlbumArea *album;
    MenuBar *menuBar;
    InfoBar *infoBar;

    void addConnect();

private slots:
    void showMenuBar();
    void showInfoBar();

    void toPlaySlot();

    //the real play
    void toPlaySlot1();
    void videoClicked(QVector<VideoInfo*> *video);
    void toPlayOneSlot(QVector<VideoInfo*> *video);

signals:
    void playListChanged(QVector<VideoInfo*> *video);
    void playListChanged1(QList<QUrl> list);
};

#endif // THE_MENU_H
