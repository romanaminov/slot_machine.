#ifndef BUTTONSTOP_H
#define BUTTONSTOP_H

#include "headers/button.h"

class ButtonStop: public Button
{
public:
    ButtonStop(ButtonState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr);
    ~ButtonStop();
private:
    // Связанные текстуры. Отображают состояние кнопки,
    // кога она выключена или включена
    std::shared_ptr<TextureObjectManager> textureEna;
    std::shared_ptr<TextureObjectManager> textureDis;
};


#endif // BUTTONSTOP_H
