#include "headers/buttonstart.h"

ButtonStart::ButtonStart(ButtonState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr) :
Button(_state, _lb_xrf, _lb_yrf, _rt_xrf, _rt_yr)
{
    // Инициализируем тестуры (не загружаем их) посреством TextureObjectManager
    // куда переаётся информация о назначении кнопки
    textureEna = std::make_shared<TextureObjectManager>(TextureGroup::_buttons, false, this);
    textureDis = std::make_shared<TextureObjectManager>(TextureGroup::_buttons, true, this);

    TextureMap *textureMap = this->getTextureMap();
    textureMap->insert(TexturePair(TextureRole::_startEna, textureEna->getTexture()));
    textureMap->insert(TexturePair(TextureRole::_startDis, textureDis->getTexture()));

}

ButtonStart::~ButtonStart()
{
}
