QT       += core gui widgets multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    album_area.cpp \
    album_button.cpp \
    album_layout.cpp \
    filter_widget.cpp \
    info_bar.cpp \
    login.cpp \
    main.cpp \
    menu_bar.cpp \
    player/player.cpp \
    player/playercontrols.cpp \
    player/playlistdelegate.cpp \
    player/playlistmodel.cpp \
    player/videowidget.cpp \
    the_menu.cpp \
    uploadform.cpp \
    video_info.cpp \
    window.cpp

HEADERS += \
    album_area.h \
    album_button.h \
    album_layout.h \
    filter_widget.h \
    info_bar.h \
    login.h \
    menu_bar.h \
    player/absolutesetstyle.h \
    player/player.h \
    player/playercontrols.h \
    player/playlistdelegate.h \
    player/playlistitem.h \
    player/playlistmodel.h \
    player/videowidget.h \
    the_menu.h \
    uploadform.h \
    video_info.h \
    window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    player/img/img.qrc

DISTFILES += \
    player/img/add.png \
    player/img/backward.png \
    player/img/delete.png \
    player/img/forward.png \
    player/img/fullscreen.png \
    player/img/mute.png \
    player/img/tag.png \
    player/img/volume.png

FORMS += \
    login.ui
