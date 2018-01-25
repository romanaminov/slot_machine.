#include "headers/wheel.h"
#include "headers/textureobjectmanager.h"

Wheel::Wheel(WheelState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr) :
Object(_state, _lb_xrf, _lb_yrf, _rt_xrf, _rt_yr)
{
    // Инициализируем тестуры (не загружаем их) посреством TextureObjectManager
    // куда передаётся информация о назначении барабана
    wheel = std::make_shared<TextureObjectManager>(TextureGroup::_wheels, true, this);

    TextureMap *textureMap = this->getTextureMap();
    textureMap->insert(TexturePair(TextureRole::_wheel, wheel->getTexture()));

    stopStatus = false;
}

Wheel::~Wheel()
{
}

void Wheel::Start() {

    //состояние ВКЛ
    stopStatus = false;
    // Обнуляем часы
    currentTime = lastTime = std::time(nullptr);
    this->setState(WheelState::_running);

    // Время вращения устанавливается от 5 до 6 с
    std::srand(std::time(0)); //use current time as seed for random generator
    int random_variable = rand() % 30;
    rotatingTime = const_sm::wheel_min_time + (double)random_variable/10;

    // Отсчёт угла начинаем заново
    currentAnngle = 0;

    // Устанавливаем нулевую скорость
    rotatingSpeed = 0;

    // Тормоз
    brake = const_sm::brake_start_coef;

    adjustmenAngle = 0;
    currentAdjustmentCount = 0;

}
void Wheel::Stop(){
    stopStatus = true;
    currentTime = std::time(nullptr);
    lastTime = currentTime;
    rotatingTime =  2;
}

void Wheel::Update() {
    switch (this->getState()) {
            case WheelState::_stopped:
                // Ничего не делаем
            break;
        case WheelState::_running:
            currentTime = std::time(nullptr);
            // Время с момента начала вращения
            std::time_t elapse = currentTime - lastTime;

            if ((stopStatus == false)&&(elapse >= 0) && ((elapse < const_sm::acceleration_time))) { // Разгон колеса
                int randomValue = rand() % 25 + const_sm::start_cmooth_coef;
                rotatingSpeed += randomValue; // Увеличиваем скорость
                currentAnngle += randomValue;
            }
            else if (elapse <= rotatingTime) { //Торможение колеса
                int randomValue = rand() % 10 + const_sm::brake_smooth_coef;
                rotatingSpeed += randomValue / brake; // Используем тормоз
                currentAnngle += randomValue / brake;
                brake += const_sm::brake_adding_coef;
            }
            else if (elapse > rotatingTime) { // Останавливаем колесо
                // Используем плавный доворот
                if (currentAdjustmentCount == 0) {
                    adjustmenAngle = const_sm::wheel_angle_step - std::fmod(currentAnngle, const_sm::wheel_angle_step);
                }
                else if (currentAdjustmentCount == AdjustmentCount + 1) {
                    this->setState(WheelState::_stopped);
                }
                else {
                    rotatingSpeed += adjustmenAngle / AdjustmentCount;
                }
                currentAdjustmentCount++;

            }

            wheel->getTexture()->rotatingAngle = rotatingSpeed;

            break;
    }
}

