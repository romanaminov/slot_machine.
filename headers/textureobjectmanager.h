#ifndef TEXTUREOBJECTMANAGER_H
#define TEXTUREOBJECTMANAGER_H

#include "headers/object.h"
#include <qimage.h>


/*
Менеджер текстур для объектов.
*/

enum TextureRole{
    _backgound,
    _startEna,
    _startDis,
    _selectEna,
    _selectDis,
    _wheel,
};

enum TextureGroup {
    _backgrounds,
    _buttons,
    _wheels,
};

/*
Текстура. соержит данны загруженно тестуры, а также вспомогательные поля
необхоимые для управления
*/
struct Texture{
    Texture(TextureGroup _group, Position _pos, bool _ena);
    ~Texture();
    // Приналежность к опреелённой группе (кнопка, барабан, фон)
    TextureGroup group;
    // Функциональная роль самого объекта
    ObjectRole objRole;
    // Позиция в относительных кооринатах
    Position pos;
    // Иентификатор текстуры. Устанавливается срествами OpenGl
    unsigned int id;
    // Данные Устанавливаются срествами OpenGl
    std::shared_ptr<QImage> data;
    // Угол поворота, если тектура вращается
    double rotatingAngle;
    bool ena;//показывать или нет текстуру
};

// Обёртка для Текстуры
class TextureObjectManager {
public:
    TextureObjectManager(TextureGroup _texGroup, bool _ena, Object *_obj);
    ~TextureObjectManager();
    TextureRole textureRole;
    Position &getPos() const;
    void setPos(Position pos);
    std::shared_ptr<Texture> getTexture();
    void setEna(bool state);
private:
    Object* object;
    std::shared_ptr<Texture> texture;

};


#endif // TEXTUREOBJECTMANAGER_H
