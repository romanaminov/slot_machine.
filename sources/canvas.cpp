#include "headers/canvas.h"


Canvas::Canvas(int width, int heigth) :
currentWidth(width),
currentHeight(heigth),
state(_waiting)
{
    // Основная задача, собрать указатели на все использующиеся текстуры
    // Фон создаём прямо здесь. Остальные создаются с помощью SlotMachine

    Position customPos;
    std::shared_ptr<Texture> background = std::make_shared<Texture>(TextureGroup::_backgrounds, customPos, true);
    textureMap.insert(TexturePair(TextureRole::_backgound, background));

    // Заполняем карту указателей на текстуры из объектов, содержащихся в SlotMachine,
    // которая была создана во время инициализации программы.
    // Типы объектов кнопки и барабаны.
    slotMachine = SlotMachine::GetInstance();

    // Добавляем в карту текстуры кнопок
    createTextureMap(slotMachine->getButtonsMap());
    // Текстуры барабанов
    createTextureMap(slotMachine->getWheelsMap());

    }

Canvas::~Canvas()
{
}


void Canvas::createTextureMap(TypeObjectsMap* objectsMap) {

    TypeObjectsMap::iterator oit;

    TextureMap *objectTextureMap;
    TextureMap::iterator tit;

    for (oit = objectsMap->begin(); oit != objectsMap->end(); oit++) {
        objectTextureMap = oit->second->getTextureMap();
        for (tit = objectTextureMap->begin(); tit != objectTextureMap->end(); tit++) {
            textureMap.insert(*tit);
        }
    }
}

void Canvas::setSize(int width, int height) {
    currentWidth = width;
    currentHeight = height;
}


void Canvas::getSize(int &width, int &height) const {
    width = currentWidth;
    height = currentHeight;
}

TextureMap *Canvas::getTextureMap() {
    return &textureMap;
}

bool Canvas::inProcess() {
    if (slotMachine->getState()) {
        return true;
    }
    else {
        return false;
    }
}

void Canvas::mouseClicked(int x, int y) {
    // Переводим координаты мыши в относительные координаты полотна
    double x_ref, y_ref;
    x_ref = (double)x/currentWidth;
    y_ref = 1 - (double)y/currentHeight; //Отчёт пикселей идёт свеху

    TypeObjectsMap *buttonsMap = slotMachine->getButtonsMap();
    TypeObjectsMap::iterator bit;

    // Проверяем, соответствуют ли координаты положения мыши
    // координатам какого либо из объектов (кнопки)
    for (bit = buttonsMap->begin(); bit != buttonsMap->end(); bit++) {
        if (bit->second->checkPos(x_ref, y_ref)) {
            if(bit->first == ObjectRole::_start) {
            // Была нажата кнопка Start
               if (slotMachine->getState() != SlotMachineState::sl_waiting) {
                   return;
               }
                bit->second->Update();
               slotMachine->Start();
            }else if(bit->first == ObjectRole::_stop) {
               if (slotMachine->getState() == SlotMachineState::sl_waiting)
                  return;
            // Была нажата кнопка Stop
               bit->second->Update();
               slotMachine->Stop();
            }

        }
    }
}



void Canvas::Update() {
    slotMachine->Update();
}
