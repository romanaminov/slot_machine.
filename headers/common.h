#ifndef COMMON_H
#define COMMON_H

#include <list>
#include <map>
#include <memory>
namespace const_sm {


    // Общие данные
    const int window_width  =           604;		// Ширина окна, пкс.
    const int window_height =           400;		// Высота окна, пкс
    const double acceleration_time =    3.5;		// Время разгона барабана
    const double brake_start_coef  =    1.1;		// Начальное значение коэффициента торможения
    const double brake_adding_coef =    0.1;		// Постепенное торможение
    const int brake_smooth_coef	   =    10;			// Коэффициент для плавного торможения
    const int start_cmooth_coef	   =    10;			// Коэффициент для плавного разгона
    const double wheel_min_time	   =    5;			// Минимальное время, которое крутиться барабан
    const int wheel_rotate_offset  =    5;			// Угол, на который доворачивается барабан при инициализации,
                                                    // чтобы картинка была по центру
    const int wheel_elements_count =    9;          // Количество элементов на барабане
    // Шаг барабана, гр. Угловое значение между двумя полями
    const double wheel_angle_step  =    360/wheel_elements_count;

    const double stop_button_lb_x_refp  =	0.2748013245033113;	// Опорные точки для кнопки start и select
    const double stop_button_lb_y_refp  =	0.050793991416309;	// Рассчитаны относительно дефолтного значения окна
    const double stop_button_rt_x_refp  =	0.4867880794701987;	// Относительные значения
    const double stop_button_rt_y_refp  =	0.1680901287553648;

    const double start_button_lb_x_refp =	0.5099006622516556;
    const double start_button_lb_y_refp	=   0.050793991416309;
    const double start_button_rt_x_refp	=   0.721887417218543;
    const double start_button_rt_y_refp	=   0.1680901287553648;

    const double left_wheel_lb_x_refp	=   0.2456556291390728; // То же самое для барабанов
    const double left_wheel_lb_y_refp	=   0.229343347639485;
    const double left_wheel_rt_x_refp	=   0.4070066225165563;
    const double left_wheel_rt_y_refp	=   0.7397596566523605;

    const double center_wheel_lb_x_refp =	0.413841059602649;
    const double center_wheel_lb_y_refp	=   0.229343347639485;
    const double center_wheel_rt_x_refp	=   0.5762251655629139;
    const double center_wheel_rt_y_refp	=   0.7397596566523605;

    const double right_wheel_lb_x_refp	=   0.5827483443708609;
    const double right_wheel_lb_y_refp	=   0.229343347639485;
    const double right_wheel_rt_x_refp	=   0.7467549668874172;
    const double right_wheel_rt_y_refp	=   0.7397596566523605;
}

struct Texture;
typedef  std::multimap<int ,std::shared_ptr<Texture>> TextureMap;
typedef std::pair<int, std::shared_ptr<Texture>> TexturePair;

typedef  std::multimap<int ,std::shared_ptr<Texture> > SmartTextureMap;
typedef std::pair<int,std::shared_ptr< Texture> > SmartTexturePair;

#endif // COMMON_H
