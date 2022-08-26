#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include "transform3d.h"
#include "vertex.h"
#include "cubesstate.h"
#include <QBasicTimer>
#include <QQueue>
#include <QVector2D>
#include <QKeyEvent>

class QOpenGLShaderProgram;

class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Window();
    ~Window();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void teardownGL();
    void init_cubes();
    void solve();
    bool pause;
    Vertex cubes_vertex[972];

protected slots:
    void update();

protected:
    void timerEvent(QTimerEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QBasicTimer timer;
    //OpenGL State Information
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;

    //Shader Information
    QMatrix4x4 m_projection;
    Transform3D m_transform[27];

    int u_modelToWorld;
    int u_worldToView;

    //Private Helpers
    void printContextInformation();  

    //Cubes State
    cubesstate m_cubesstate;
    QQueue <int> quene_transform;

    bool sign_solve;
    float step_time;  
    float d_angle;
    void transformAction(int X, float angle, bool t_end); //X是前后上下左右 angle带符号角度 t_end是否执行弹出

    //Mouse Information
    QVector2D mouseLastPosition;
    bool mouseOnPress;
};

#endif // WINDOW_H
