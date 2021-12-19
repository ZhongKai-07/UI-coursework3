//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//  2811 cw3 : twak 11/11/2021
//

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include "the_videoscreen.h"
#include "the_videolength.h"
#include "the_videoslider.h"
#include "the_volume.h"
#include "the_playbutton.h"
#include "the_skipbutton.h"


// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn( std::string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }

    // the widget that will show the video
    VideoScreen *videoWidget = new VideoScreen();

    QWidget *BigWindow = new QWidget();
    QWidget *VideoWindow = new QWidget();
    QWidget *ControlWindow = new QWidget();
    QWidget *VideoSliderWindow = new QWidget();

    QVBoxLayout *BigLayout = new QVBoxLayout();
    QHBoxLayout *VideoLayout = new QHBoxLayout();
    QHBoxLayout *ControlLayout = new QHBoxLayout();
    QHBoxLayout *VideoSliderLayout = new QHBoxLayout();

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();        //videos button
    buttonWidget->setLayout(layout);

    // create the four videos buttons
    for ( int i = 0; i < 4; i++ ) {
        TheButton *button_v = new TheButton(buttonWidget);
        button_v->connect(button_v, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        buttons.push_back(button_v);
        layout->addWidget(button_v);
        button_v->init(&videos.at(i));
    }

    //video lenth label
    videoLength *length = new videoLength(buttonWidget);
    length->setWhatsThis("length");
    player->connect(player, SIGNAL(positionChanged(qint64)), length, SLOT(setLength(qint64)));
    //video duration label
    videoLength *duration = new videoLength(buttonWidget);
    duration->setWhatsThis("duration");
    player->connect(player, SIGNAL(durationChanged(qint64)), duration, SLOT (setLength(qint64)));

    //video length slider
    videoSlider *videoslider = new videoSlider(buttonWidget);
    player->connect(player, SIGNAL(durationChanged(qint64)), videoslider, SLOT (SetRange(qint64)));
    player->connect(player, SIGNAL(positionChanged(qint64)), videoslider, SLOT (SetValue(qint64)));
    videoslider->connect(videoslider, SIGNAL(valueChanged(int)), player, SLOT (SetPosition(int)));

    //video play/skip button
    ForwardButton *forwardSkipBtn = new ForwardButton(buttonWidget);
    BackwardButton *backwardSkipBtn = new BackwardButton(buttonWidget);
    PlayButton *playBtn = new PlayButton(buttonWidget);

    playBtn->connect(playBtn, SIGNAL(clicked(bool)), player, SLOT (click(bool)));
    player->connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), playBtn, SLOT (setState(QMediaPlayer::State)));
    forwardSkipBtn->connect(forwardSkipBtn, SIGNAL(clicked(bool)), player, SLOT(skipBack(bool)));
    backwardSkipBtn->connect(backwardSkipBtn, SIGNAL(clicked(bool)), player, SLOT(skipForward(bool)));

    StopButton *stopBtn = new StopButton(buttonWidget);
    stopBtn->connect(stopBtn, SIGNAL(clicked(bool)), player, SLOT (stop()));

    //video volume control
    Volume *button = new Volume(buttonWidget);
    VolumeSlider *volumeSlider = new VolumeSlider(buttonWidget);

    button->connect(button, SIGNAL(mute(bool)), player, SLOT(setMute(bool)));
    button->connect(button, SIGNAL(moveSlider(int)), volumeSlider, SLOT(moveSlider(int)));

    volumeSlider->connect(volumeSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    volumeSlider->connect(volumeSlider, SIGNAL(valueChanged(int)), button, SLOT (changeIcon(int)));

    player->connect(player, SIGNAL(positionChanged(qint64)), length, SLOT (setLength(qint64)));
    player->connect(player, SIGNAL(durationChanged(qint64)), duration, SLOT (setLength(qint64)));
    //as video changes, length and duration labels will change

    //set start as full screen
    videoWidget->setFullScreen(false);

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    // create the main window and layout
    QWidget window;
    QVBoxLayout *top = new QVBoxLayout();
    window.setLayout(top);
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);

    // add the video and the buttons to the top level widget


    VideoLayout->addWidget(videoWidget);
    VideoWindow->setLayout(VideoLayout);
    BigLayout->addWidget(VideoWindow);
    BigLayout->addWidget(VideoSliderWindow);
    BigLayout->addWidget(ControlWindow);

    VideoSliderLayout->addWidget(videoslider);
    VideoSliderLayout->addWidget(length);
    VideoSliderLayout->addWidget(duration);
    VideoSliderWindow->setLayout(VideoSliderLayout);

    ControlWindow->setLayout(ControlLayout);
    ControlLayout->addWidget(stopBtn);
    ControlLayout->addWidget(forwardSkipBtn);
    ControlLayout->addWidget(playBtn);
    ControlLayout->addWidget(backwardSkipBtn);
    ControlLayout->addWidget(button);     //volunme button
    ControlLayout->addWidget(volumeSlider);   //volume slider
    ControlLayout->addStretch();  // 添加伸缩

    BigWindow->setLayout(BigLayout);

    top->addWidget(BigWindow);
    top->addWidget(buttonWidget);
    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
