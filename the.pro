QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        the_button.cpp \
        the_playbutton.cpp \
        the_player.cpp \
        the_videolength.cpp \
        the_videoscreen.cpp \
        the_videoslider.cpp \
        the_volume.cpp \
        tomeo.cpp

HEADERS += \
    the_button.h \
    the_playbutton.h \
    the_player.h \
    the_skipbutton.h \
    the_videolength.h \
    the_videoscreen.h \
    the_videoslider.h \
    the_volume.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

