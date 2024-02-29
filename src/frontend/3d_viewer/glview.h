#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <QMessageBox>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>
#include <iostream>

extern "C" {
    #include "../../3d_viewer.h"
}


QT_BEGIN_NAMESPACE
namespace Ui {
class GLVIew;
}
QT_END_NAMESPACE

class GLVIew : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLVIew(QWidget *parent = nullptr);
    ~GLVIew();

    QString file_name;
    int projection_type = 0; // 0 - parallel, 1 - central

    void initializeGL() override;
    void resizeGL(int w, int h) override;

    void openObject();

    void paintGL() override;
    void paintEdges();
    void paintVertices();

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void setRotationToZero();
    void rotateObject();

    void moveObjectToCenter();
    void moveObjectByVector(vector_t vector);

    void scaleObject();

    object_t object;

    double scale_val;

    double rotationX = 0;
    double rotationY = 0;
    double rotationZ = 0;

    int edgeType = 0;
    int edgesColorR = 0;
    int edgesColorG = 0;
    int edgesColorB = 0;
    int edgeSize = 3;

    int vertexType;
    int vertexColorR = 0;
    int vertexColorG = 0;
    int vertexColorB = 0;
    int verticesSize;

    int bgColorR = 0;
    int bgColorG = 0;
    int bgColorB = 0;
private:
    Ui::GLVIew *ui;
    QPoint cur_pos;
    QPoint new_pos;

    void set_normalize_coef();
};
#endif // GLVIEW_H
