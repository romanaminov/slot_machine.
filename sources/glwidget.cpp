#include "headers/glwidget.h"
#include <QString>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    canvas = std::make_shared<Canvas>(const_sm::window_width, const_sm::window_height);
    current_time = base_time = std::time(nullptr);
    setFormat(QGLFormat(QGL::DoubleBuffer)); // Двойная буферизация
    glDepthFunc(GL_LEQUAL); // Буфер глубины
}

GLWidget::~GLWidget()
{

}
void GLWidget::mousePressEvent(QMouseEvent *pe){
    QPoint mousePosition = pe->pos();
    canvas->mouseClicked(mousePosition.x(),mousePosition.y());
}
void GLWidget::initializeGL()
{
    loadTextures();
    resizeGL(const_sm::window_width, const_sm::window_height);
    timer = std::make_shared<QTimer>();
    timer->setInterval(1);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start();

}
void GLWidget::paintGL()
{
    Redisplay();
}
void GLWidget::updateGL()
{
    Redisplay();
}



void GLWidget::resizeGL(int w, int h)
{
    Resize(w,h);
    Redisplay();
}

void GLWidget::Redisplay()
{
        // Обновляем состояние полотна
        canvas->Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glColor3d(1, 1, 1);

        // Получаем все необхоимы тектуры
        TextureMap *TexManList = canvas->getTextureMap();
        TextureMap::iterator it;
        double offset_x = 0, offset_y = 0;
        int windowsWight, windowsHeigth;
        double textureWight = 0, textureHeigth = 0;
        canvas->getSize(windowsWight, windowsHeigth);
        for (it = TexManList->begin(); it != TexManList->end(); it++) {
            std::shared_ptr<Texture> texture = it->second;
            if (texture->ena) { // Отображать ли тектуру
                Position pos = texture->pos;
                switch (texture->group) {	// Различный механизм обработки и отображение текстуры
                    // в зависимости от типа объекта к которому она привязана
                case TextureGroup::_backgrounds:	// Фон
                    textureWight = windowsWight;
                    textureHeigth = windowsHeigth;
                    break;
                case TextureGroup::_buttons:	// Кнопки
                case TextureGroup::_wheels:		// Барабаны
                    // Сдвиг по x и y
                    offset_x = pos.lb_xrf * windowsWight;
                    offset_y = pos.lb_yrf * windowsHeigth;
                    // Ширина и высота текстуры при данном размере полотна
                    textureWight = pos.rt_xrf * windowsWight - offset_x;
                    textureHeigth = pos.rt_yrf * windowsHeigth - offset_y;
                    break;
                }

                if ((((texture->group) == TextureGroup::_backgrounds)) || ((texture->group) == TextureGroup::_buttons)) {
                    // Связываем и наклаываем текстуру
                    glBindTexture(GL_TEXTURE_2D, texture->id);
                    glBegin(GL_QUADS);
                    glTexCoord2d(0, 0); glVertex3d(offset_x, offset_y, -0.1);
                    glTexCoord2d(0, 1); glVertex3d(offset_x, offset_y + ((double)textureHeigth), -0.1);
                    glTexCoord2d(1, 1); glVertex3d(offset_x + ((double)textureWight), offset_y + ((double)textureHeigth), -0.1);
                    glTexCoord2d(1, 0); glVertex3d(offset_x + ((double)textureWight), offset_y, -0.1);
                    glEnd();


                }else if ((texture->group) == TextureGroup::_wheels) {// Для барабанов
                    // Связываем текстуру с цилиндром
                    glBindTexture(GL_TEXTURE_2D, texture->id);

                    GLUquadricObj *quadObj;
                    quadObj = gluNewQuadric();
                    gluQuadricTexture(quadObj, GL_TRUE);
                    gluQuadricDrawStyle(quadObj, GLU_FILL);
                    glColor3d(1, 1, 1);

                    glPushMatrix();
                    // Свиг для разных цилиндров
                    glTranslated(offset_x + textureWight, offset_y + textureHeigth / 2, 0);
                    // Поворот лицом к зрителю
                    glRotated(-90, 0.0, 1.0, 0.0);
                    // Доворот ленты
                    glRotated(const_sm::wheel_rotate_offset, 0.0, 0.0, 1.0);
                    // Вращение
                    GLfloat RotateAngle = (GLfloat)texture->rotatingAngle;
                    glRotated(-RotateAngle, 0, 0, 1);
                    // Цилиндр
                    gluCylinder(quadObj, textureHeigth / 2, textureHeigth / 2, textureWight, 100, 100);
                    glPopMatrix();

                    gluDeleteQuadric(quadObj);
                }
            }

            textureWight = 0, textureHeigth = 0;
            offset_x = 0, offset_y = 0;

        }
        glDisable(GL_TEXTURE_2D);
        swapBuffers();


}

void GLWidget::Resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, ((double)width), 0, ((double)height), 0.0, 300.0);
    gluLookAt(0, 0, 290, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);

    // Записываем новые размеры в полотно
    canvas->setSize(width, height);
}

void GLWidget::loadTextures()
{

    TextureMap *TexManList = canvas->getTextureMap();
    TextureMap::iterator it;

    for (it = TexManList->begin(); it != TexManList->end(); it++) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        std::shared_ptr<Texture> texture = it->second;
        switch (it->first) {
        case TextureRole::_backgound:
            texture->data->load(":/textures/background.bmp");
            *(texture->data) = QGLWidget::convertToGLFormat(*(texture->data));
            break;
        case TextureRole::_startEna:
            texture->data->load(":/textures/startEna.bmp");
            *(texture->data) = QGLWidget::convertToGLFormat(*(texture->data));
            break;
        case TextureRole::_startDis:
            texture->data->load(":/textures/startDis.bmp");
            *(texture->data) = QGLWidget::convertToGLFormat(*(texture->data));
            break;
        case TextureRole::_selectEna:
            texture->data->load(":/textures/selectEna.bmp");
            *(texture->data) = QGLWidget::convertToGLFormat(*(texture->data));
            break;
        case TextureRole::_selectDis:
            texture->data->load(":/textures/selectDis.bmp");
            *(texture->data) = QGLWidget::convertToGLFormat(*(texture->data));
            break;
        case TextureRole::_wheel:
            texture->data->load(":/textures/Wheel_9.bmp");
            *(texture->data) = QGLWidget::convertToGLFormat(*(texture->data));
            break;
        default:
            continue;
            break;
        }

        // Генерация и связывание текстуры
        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        // Установка фильтров при несовпаении размеров тектуры и объекта
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, 3,
            (GLsizei)texture->data->width(),
           (GLsizei)texture->data->height(),
            0, GL_RGBA, GL_UNSIGNED_BYTE,
            texture->data->bits());
    }
}
