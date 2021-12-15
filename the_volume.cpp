#include "the_volume.h"

void Volume::setMute(bool mute){
    muteValue = !mute;
}


void Volume::click(){
    if(!muteValue){
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        emit moveSlider(0);
    }else{
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        emit moveSlider(10);
    }
    setMute(muteValue);
    emit mute(muteValue);
}

void Volume::changeIcon(int volume){
    if(volume == 0){
        setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));

    }else if(volume !=0 && muteValue == false){
        setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }

}

void VolumeSlider::moveSlider(int volume){
    setSliderPosition(volume);
}
