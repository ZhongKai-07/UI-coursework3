#include "the_videolength.h"
#include <QTime>

void videoLength::setLength(qint64 position){
    setNum(static_cast<int>(position));

    QString str;
    QTime currTime((position / 60000) / 60, (position / 10000) / 60, (position / 1000), (position % 1000));
    QString format;
    if(position <= 60000){
        format = "mm:ss";  //if the length of the video is less than 60min
    }else{
        format = "hh:mm:ss"; //if the length is more than 60 min
    }
    str = currTime.toString(format) + "   /      ";
    setText(str);

}
