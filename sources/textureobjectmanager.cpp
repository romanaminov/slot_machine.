#include "headers/textureobjectmanager.h"
#include "headers/object.h"

Texture::Texture(TextureGroup _group, Position _pos, bool _ena) {
    group = _group;
    pos = _pos;
    ena = _ena;
    rotatingAngle = 0;
    data = std::make_shared<QImage>();
}

Texture::~Texture() {
}

TextureObjectManager::TextureObjectManager(TextureGroup _texGroup, bool _ena, Object *_object) :
object(_object)
{
    texture = std::make_shared<Texture>(_texGroup, object->getPos(), _ena);
    setEna(_ena);

}

TextureObjectManager::~TextureObjectManager() {
}

void TextureObjectManager::setEna(bool state) {
    texture->ena = state;
}

void TextureObjectManager::setPos(Position _pos) {
    texture->pos = _pos;
}

std::shared_ptr<Texture> TextureObjectManager::getTexture() {
    return texture;
}
