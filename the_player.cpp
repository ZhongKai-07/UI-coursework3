//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    play();
}

void ThePlayer::setPlay(bool flipPlay) {
    playValue = !flipPlay;
}

void ThePlayer::click(bool click) {
    if(playValue) {
        play();
    } else {
        pause();
    }
    setPlay(playValue);
}

void ThePlayer::SetPosition(int pos) {
    setPosition(pos);
}

void ThePlayer::skipBack(bool skip) {
    if(!skip) {
        setPosition(position()-5000);
    }
}
//skip by 5 seconds, hence the +-5000
void ThePlayer::skipForward(bool skip) {
    if(!skip) {
        setPosition(position()+5000);
    }
}

void ThePlayer::stop() {
    setPosition(0);
    pause();
}
