#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <GL/glu.h>
#include <GL/gl.h>
#include <QTimer>
#include "headers/canvas.h"
#include <QMouseEvent>
#include <QTimer>
#include <QTime>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
protected:
    // Полотно
    std::shared_ptr<Canvas> canvas;
    // Таймеры
    std::time_t current_time, base_time;
    std::shared_ptr<QTimer> timer;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void updateGL() override;

    // Функция перерисовки сцены
    void Redisplay(void);
    // Обработчик изменения размеров окна
    void Resize(int width, int height);
    // Обработчик нажатия ЛКМ
    void mousePressEvent(QMouseEvent *pe);
    // Загрузка текстур в список, полученный от полотна
    void loadTextures();

};


#endif // GLWIDGET_H
