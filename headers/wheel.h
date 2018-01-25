#ifndef WHEEL_H
#define WHEEL_H

#include "headers/object.h"
#include <ctime>
#include "headers/textureobjectmanager.h"

/*
Cass Wheel наслеуется от Object
*/

// Состояние барабана
enum WheelState {
    _stopped,
    _running
};

class Wheel: public Object
{
public:
    Wheel(WheelState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr);
    ~Wheel();
    // Запускает вращение барабана
    void Start();
    // Останавливает вращение барабана
    void Stop();
    virtual void Update();
private:
    // Связанные текстуры.
    std::shared_ptr<TextureObjectManager> wheel;
    // Время момента начала вращения барабана
    std::time_t lastTime;
    // Текущее время
    std::time_t currentTime;
    // Время, которое барабан бует вращаться
    double rotatingTime;
    // Текущая "скорость вращения"
    double rotatingSpeed;
    // Доп угол ля оворота при остановке барабана
    double currentAnngle;
    // Тормоз вращения
    double brake;
    //Состояние ВЫКЛ барабанов
    bool stopStatus;
    // Позиция, на которой в данный момент находится барабан
    // необходима для подсчёта результатов
    // Угол доворота
    double adjustmenAngle;
    // Счётчик итераций доворота
    int currentAdjustmentCount;
    // Максимальное значение счётчика
    const static int AdjustmentCount = 250;
};


#endif // WHEEL_H
