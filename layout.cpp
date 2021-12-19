#include "layout.h"
#include <QScrollArea>
#include <iostream>
#include "the_button.h"
#include <QVideoWidget>
#include <QSlider>
#include <QComboBox>
#include <QStyle>
#include "the_button.h"
#include "the_videolength.h"
#include "the_player.h"
#include "the_videoscreen.h"
#include "the_videoslider.h"
#include "the_volume.h"


using namespace std;

void ResponsiveLayout::setGeometry(const QRect &r) {

    QLayout::setGeometry(r);

    for (int i = 0; i < list_.size(); i++) { //iterates through all of our added widgets

        QLayoutItem *o = list_.at(i);

        try { //then specific geometries will be set for each one, depending on the widget

            QWidget *videoWidget = dynamic_cast<QWidget *>(o->widget());
            QSlider *videoSlider = dynamic_cast<QSlider *>(o->widget());
            VolumeSlider *volumeSlider = dynamic_cast<VolumeSlider *>(o->widget());

            if(videoSlider){
                videoSlider->setGeometry(r.x() + 5,0.8*r.height() - 65, 0.8*r.width() - 10 - 60 - 60 - 120, 30);
            }
        }

        catch (bad_cast) {
            // bad_case: cast failed on reference...
            cout << "warning, unknown widget class in layout" << endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(300,300);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
