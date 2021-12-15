//
// Created by twak on 11/11/2019.
//

#include "the_button.h"
#include "QFileInfo"


void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
}


void TheButton::clicked() {
    emit jumpTo(info);
}

/*the search button*/
void TheButton::search(QString index){
    QString path = info->url->toString(); //get the file path
    QFileInfo file(path);
    QString name = file.baseName();

    if(index == ""){
        setVisible(true);
    }else if(index != name){
        setHidden(true);
    }else{
        setVisible(true);
    }
}
