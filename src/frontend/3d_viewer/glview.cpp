#include "glview.h"
#include "ui_glview.h"

#include<QDebug>
#include <QErrorMessage>

GLVIew::GLVIew(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::GLVIew)
{
    setWindowTitle("3d Viewer");
    setFixedSize(800, 800);
    this->object = {};
    file_name = NULL;
    scale_val = 0.5;
}

GLVIew::~GLVIew()
{
    destroy_object_contents(&object);
    delete ui;
}

void GLVIew::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void GLVIew::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLVIew::scaleObject() {
    scale_object(&(this->object), this->scale_val);
}

void GLVIew::paintGL() {
    // Draw the scene:

    glClearColor(double(bgColorR) / 255, double(bgColorG) / 255, double(bgColorB) / 255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-1, 1, -1, 1, -1, 1);
    if (this->projection_type == 0) {
        glOrtho(-1, 1 , -1, 1, -1, 1000);
        // glTranslatef(0, -0.5, 0);
    } else {
        glFrustum(-1, 1, -1, 1, 1, 1000);
        glTranslatef(0, 0, -2);
    }

    paintEdges();

    if (this->vertexType != 0) {
        paintVertices();
    }

}

void GLVIew::paintVertices() {
    if (this->vertexType == 1) {
        glEnable(GL_BLEND);
    } else if (this->vertexType == 2) {
        glEnable(GL_POINT_SMOOTH);
    }
    glPointSize(this->verticesSize);
    glColor3f(double(vertexColorR)/255, double(vertexColorG)/255, double(vertexColorB)/255);

    glBegin(GL_POINTS);
    for (int i = 0; i < this->object.vertices.count; i ++) {
        point_t point = this->object.vertices.coords[i];
        glVertex3d(point.x, point.y, point.z);
    }
    glEnd();

    if (this->vertexType == 1) {
        glDisable(GL_BLEND);
    } else if (this->vertexType == 2) {
        glDisable(GL_POINT_SMOOTH);
    }
}

void GLVIew::paintEdges() {
    glLineWidth(this->edgeSize);
    glColor3d(double(edgesColorR)/255, double(edgesColorG)/255, double(edgesColorB)/255);

    if (this->edgeType == 1) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
    }

    for (int i = 0; i < this->object.poligons.count; i ++) {
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < this->object.poligons.connections[i].count; j ++) {
            point_t point = this->object.vertices.coords[object.poligons.connections[i].vertex_indices[j]];
            glVertex3d(point.x, point.y, point.z);
            // qDebug() << point.x << " " << point.y << " " << point.z << "\n";
        }
        glEnd();
    }

    if (this->edgeType == 1) {
        glDisable(GL_LINE_STIPPLE);
    }
}

void GLVIew::mousePressEvent(QMouseEvent *event) {
    cur_pos = event->globalPosition().toPoint();
}

void GLVIew::mouseMoveEvent(QMouseEvent *event) {
    new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);

    if (event->buttons() & Qt::LeftButton) {
        move_object_by_vector(&this->object, {0.001 * new_pos.x(), 0, 0});
        move_object_by_vector(&this->object, {0, -0.001 * new_pos.y(), 0});
        update();
    } else if (event->buttons() & Qt::RightButton) {
        rotationY += 0.003 * new_pos.x();
        rotationX += 0.003 * new_pos.y();
        rotate_object_around_y(&this->object, 0.003 * new_pos.x());
        rotate_object_around_x(&this->object, 0.003 * new_pos.y());
        update();
    }
    cur_pos = event->globalPosition().toPoint();
}

void GLVIew::openObject() {
    destroy_object_contents(&(this->object));

    controller_error_t status = open_object(this->file_name.toStdString().c_str(), &(this->object));
    if (status == no_error) {
        move_object_to_center(&(this->object));
        scale_object(&(this->object), 0.5);
        this->scale_val = 0.5;
        update();
    } else {
        QMessageBox warning = QMessageBox();
        warning.setWindowTitle("Error");
        warning.setText("Please choose .obj file");
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
    }
}

void GLVIew::moveObjectToCenter() {
    move_object_to_center(&(this->object));
    update();
}

void GLVIew::wheelEvent(QWheelEvent *event) {
    QPoint numDegrees = event->angleDelta() / 120;
    this->scale_val += numDegrees.y() * 0.03;
    if (scale_val > 0) {
        scale_object(&this->object, scale_val);
        update();
    }
}

void GLVIew::moveObjectByVector(vector_t vector) {
    move_object_by_vector(&(this->object), vector);
    update();
}

void GLVIew::rotateObject() {
    rotate_object_around_x(&(this->object), rotationX);
    rotate_object_around_y(&(this->object), rotationY);
    rotate_object_around_z(&(this->object), rotationZ);
}

void GLVIew::setRotationToZero() {
    rotate_object_around_x(&(this->object), -rotationX);
    rotate_object_around_y(&(this->object), -rotationY);
    rotate_object_around_z(&(this->object), -rotationZ);
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
}
