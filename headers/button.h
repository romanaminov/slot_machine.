#ifndef BUTTON_H
#define BUTTON_H

#include "headers/object.h"
#include <list>
#include "headers/textureobjectmanager.h"

/*
Cass Button. Наслеуется от Object
*/

enum ButtonState {
    _enabled,
    _disabled
};

class Button: public Object
{
public:
    Button(ButtonState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr);
    ~Button();
    virtual void Update() override;
};


#endif // BUTTON_H
