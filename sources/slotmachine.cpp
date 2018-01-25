#include "headers/slotmachine.h"
#include "headers/canvas.h"


SlotMachine::SlotMachine()
{
    // Начальное состоние - ожидание
    state = SlotMachineState::sl_waiting;

    // Создаём все элементы игрового автомата и помещаем в соответствующие контейнеры указатели на них
    std::shared_ptr<ButtonStart> Start = std::make_shared<ButtonStart>(ButtonState::_disabled,
                                const_sm::start_button_lb_x_refp, const_sm::start_button_lb_y_refp,
                                const_sm::start_button_rt_x_refp, const_sm::start_button_rt_y_refp);
    buttonsMap.insert(ObjectPair(ObjectRole::_start, Start));

    std::shared_ptr<ButtonStop> Stop = std::make_shared<ButtonStop>(ButtonState::_disabled,
                                const_sm::stop_button_lb_x_refp, const_sm::stop_button_lb_y_refp,
                                const_sm::stop_button_rt_x_refp, const_sm::stop_button_rt_y_refp);
    buttonsMap.insert(ObjectPair(ObjectRole::_stop, Stop));

    std::shared_ptr<Wheel> LeftWheel = std::make_shared<Wheel>(WheelState::_stopped,
                                const_sm::left_wheel_lb_x_refp, const_sm::left_wheel_lb_y_refp,
                                const_sm::left_wheel_rt_x_refp, const_sm::left_wheel_rt_y_refp);
    wheelsMap.insert(ObjectPair(ObjectRole::_leftWheel, LeftWheel));

    std::shared_ptr<Wheel> CenterWheel = std::make_shared<Wheel>(WheelState::_stopped,
                                const_sm::center_wheel_lb_x_refp, const_sm::center_wheel_lb_y_refp,
                                const_sm::center_wheel_rt_x_refp, const_sm::center_wheel_rt_y_refp);
    wheelsMap.insert(ObjectPair(ObjectRole::_centerWheel, CenterWheel));

    std::shared_ptr<Wheel> RightWheel = std::make_shared<Wheel>(WheelState::_stopped,
                                const_sm::right_wheel_lb_x_refp, const_sm::right_wheel_lb_y_refp,
                                const_sm::right_wheel_rt_x_refp, const_sm::right_wheel_rt_y_refp);
    wheelsMap.insert(ObjectPair(ObjectRole::_rightWheel, RightWheel));
}


SlotMachine::~SlotMachine()
{

}

SlotMachine* SlotMachine::GetInstance(void) {
    static SlotMachine slotMachine;
    return &slotMachine;
}

int SlotMachine::getState() {
    return state;
}
void SlotMachine::Stop(){
    // Изменяем текущее состояние автомата
    state = SlotMachineState::sl_inProcess;
    TypeObjectsMap::iterator bit;
    // Останавливаем вращение барабанов
    TypeObjectsMap::iterator wit;

    for (wit = wheelsMap.begin(); wit != wheelsMap.end(); ++wit) {
        if (Wheel* w = dynamic_cast<Wheel*>(wit->second.get())) {
            w->Stop();
        }
    }
}

void SlotMachine::Start() {

    // Изменяем текущее состояние автомата
    state = SlotMachineState::sl_inProcess;
    TypeObjectsMap::iterator bit;
    // Проверяем состояние кнопки stop. Выключаем её, если она включена
    bit = buttonsMap.find(ObjectRole::_stop);
    if (bit != buttonsMap.end()) {
        std::shared_ptr<Object> stop = bit->second;
        if (stop->getState() == ButtonState::_enabled) {
            stop->Update();
        }
    }
    // Запускаем вращение барабанов
    TypeObjectsMap::iterator wit;

    for (wit = wheelsMap.begin(); wit != wheelsMap.end(); ++wit) {
        if (Wheel* w = dynamic_cast<Wheel*>(wit->second.get())) {
            w->Start();
        }
    }
}

void SlotMachine::Update() {
    if (state == SlotMachineState::sl_inProcess) {
        // Все ли барабаны остановлены
        bool allStoped = true;

        // Обновляем и проверяем состояние барабанов
        TypeObjectsMap::iterator wit; // Итератор для карты с барабанами

        // Проверяем состояние барабанов
        for (wit = wheelsMap.begin(); wit != wheelsMap.end(); ++wit) {
            if (wit->second->getState() == WheelState::_running) {
                wit->second->Update();
                allStoped = false;
            }
        }

        TypeObjectsMap::iterator bit; // Итератор для карты с кнопками

        // Все барабаны прекратили вращение
        if (allStoped) {
            bit = buttonsMap.find(ObjectRole::_start);
            if (bit != buttonsMap.end()) {
                std::shared_ptr<Object> start = bit->second;
                if (start->getState() == ButtonState::_enabled) {
                   state = SlotMachineState::sl_waiting;
                   start->Update();
                }
            }

        }
    }
}

TypeObjectsMap *SlotMachine::getButtonsMap() {
    return &buttonsMap;
}

TypeObjectsMap *SlotMachine::getWheelsMap() {
    return &wheelsMap;
}
