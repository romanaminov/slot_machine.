#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H

#include "headers/object.h"
#include "headers/buttonstop.h"
#include "headers/buttonstart.h"
#include "headers/wheel.h"
#include "headers/common.h"
#include <list>
#include <map>

/*
Класс игрального автомата. Имеет единственное представление.
Создаёт группу объектов (кнопки, барабаны). Возвращает указатель на список данных
объектов.
*/

class Canvas;

enum SlotMachineState {
    sl_waiting,
    sl_inProcess,
};

typedef std::map<ObjectRole, std::shared_ptr<Object> > TypeObjectsMap;
typedef std::pair<ObjectRole, std::shared_ptr<Object> > ObjectPair;

class SlotMachine
{
public:
    // Возвращает указатель на единствонне рпедставление себя
    static SlotMachine* GetInstance(void);
    ~SlotMachine();
    // Возвращает указатель на список объектов
    int getState();
    TypeObjectsMap *getButtonsMap();
    TypeObjectsMap *getWheelsMap();
    // Запускаем вращение барабанов
    void Start();
    // Перкращаем вращение барабанов
    void Stop();
    // Обновляем состояние
    void Update();

private:
    SlotMachine();
    // список объектов (кнопки, барабаны)
    TypeObjectsMap buttonsMap;
    TypeObjectsMap wheelsMap;
    // Состояние автомата см. SlotMachineState
    SlotMachineState state;

};


#endif // SLOTMACHINE_H
