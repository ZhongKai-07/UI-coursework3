#include "the_videoslider.h"

void videoSlider::SetValue(qint64 position){
    setValue(position);
}

void videoSlider::SetRange(qint64 position){
    setRange(0, position);
}
