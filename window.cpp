#include "window.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include "vertex.h"
#include "cubes.h"
#include <QTime>
#include <QMouseEvent>
#include "solvefunction.h"
#include <QtMath>
#include "input_action.h"
#include "cglobal.h"
#include "show2d.h"
#include <iostream>
#include <QRandomGenerator>
Window::Window()
{
    setTitle("magicCube");

    for(int i=0;i<27;i++)
        m_transform[i].translate(0.0f, 0.0f, -10.0f);
    Window::init_cubes();
    step_time=0.1;
    d_angle=0;
    mouseOnPress=false;
    sign_solve=true;
    pause=false;/*
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));*/
    for(int i=0;i<0;i++)
        quene_transform.push_back(QRandomGenerator::global()->bounded(11));
    //quene_transform.push_back(2);
    //qDebug() << m_cubesstate.v_state[1][1][0];
}

Window::~Window()
{
    makeCurrent();
    teardownGL();
}

void Window::initializeGL()
{
    initializeOpenGLFunctions();

    connect(this,SIGNAL(frameSwapped()),this,SLOT(update()));
    printContextInformation();

    //Set global information
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    glEnable(GL_CULL_FACE);

    //Application-specific initialization
    {
        //Create Shader,and do not release it until VAO is created
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/simple.frag");
        m_program->link();
        m_program->bind(); //Bind the shader so that it is the current active shader

        //Cache Uniform Locations
        u_modelToWorld=m_program->uniformLocation("modelToWorld");
        u_worldToView =m_program->uniformLocation("worldToView");
        //Create Buffer,and do not release it until VAO is created
        m_vertex.create();
        m_vertex.bind();

        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(cubes_vertex,sizeof(cubes_vertex));

        //Create Vertex Array Object
        m_object.create();
        m_object.bind();
        m_program->enableAttributeArray(0);
        m_program->enableAttributeArray(1);
        //use this to orientation every data   //position相对Vertex偏移量   //position有几个元素       //每个Vertex的size
        m_program->setAttributeBuffer(0,GL_FLOAT,Vertex::positionOffset(),Vertex::PositionTupleSize,Vertex::stride());
        m_program->setAttributeBuffer(1,GL_FLOAT,Vertex::colorOffset(),Vertex::ColorTupleSize,Vertex::stride());

        //Release (unbind) all
        m_object.release();
        m_vertex.release();
        m_program->release();
    }
    timer.start(25, this);
}

void Window::resizeGL(int width, int height)
{
    m_projection.setToIdentity();
    m_projection.perspective(60.0f, width/float(height), 5.0f, 15.0f);

    m_projection.translate(QVector3D(0.0f, 0.0f, -10.0f));
    m_projection.rotate(40.0, QVector3D(1.0f, 0.0f, 0.0f));
    m_projection.rotate(-40.0, QVector3D(0.0f, 1.0f, 0.0f));
    //m_projection.rotate(-40.0, QVector3D(1.0f, 0.0f, 0.0f));
    m_projection.translate(QVector3D(0.0f, 0.0f, 10.0f));
    //m_projection.lookAt(QVector3D(0,0,-20),QVector3D(0,0,-10),QVector3D(0,1,10));

}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Render using our shader
    m_program->bind();
    m_program->setUniformValue(u_worldToView, m_projection);
    {
        m_object.bind();
        for(int i=0;i<27;i++)
        {
        m_program->setUniformValue(u_modelToWorld, m_transform[i].toMatrix());
        glDrawArrays(GL_TRIANGLES,i*36,36);
        }
        m_object.release();
    }
    m_program->release();

}

void Window::teardownGL()
{
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
}



void Window::update()
{

}

void Window::timerEvent(QTimerEvent *e)
{
    if(a.size()>0){
        for(int i=0;i<a.size();i++)quene_transform.push_back(a[i]);
        a.clear();
    }
    if(!quene_transform.empty() && !pause)
    {
        float delt=90.0/(25.3*step_time);
        float j;
        bool t_end=false;

        //delt=delt*sqrt(sqrtf(sin(d_angle*0.0349)+0.01));
        //qDebug() << sin();
        j=d_angle+delt;
        if (j>=90) {j=90-d_angle;d_angle=90;t_end=true;d_angle=0;}
        else {d_angle=j;j=delt;}
        //Rot是0-5依次为前后上下左右的正转，6-11为前后上下左右的反转
        int Rot=quene_transform.front();
        if(Rot<=11){
            int sign=(Rot>5)?1:-1;//符号位1正转-1反转
            Rot=Rot%6;
            transformAction(Rot,sign*j,t_end);
        }else{
            // 转中间时情况
            if(Rot == 12)transformAction(8,j,t_end);
            if(Rot == 13)transformAction(8,-j,t_end);
            if(Rot == 14)transformAction(7,j,t_end);
            if(Rot == 15)transformAction(7,-j,t_end);
            if(Rot == 16)transformAction(6,-j,t_end);
            if(Rot == 17)transformAction(6,j,t_end);
        }
    }
    else if(sign_solve && !pause)
        sign_solve=false;
    QOpenGLWindow::update();
}

void Window::mousePressEvent(QMouseEvent *event)
{
    mouseLastPosition=QVector2D(event->pos());
    mouseOnPress=true;
    //qDebug() << mouseLastPosition;
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
    mouseOnPress=false;
    //qDebug() << mouseLastPosition;
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseOnPress)
    {
        QVector2D diff = QVector2D(event->pos()) - mouseLastPosition;
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        float acc = diff.length();

        m_projection.translate(QVector3D(0.0f, 0.0f, -10.0f));
        m_projection.rotate(acc*0.4,n);
        m_projection.translate(QVector3D(0.0f, 0.0f, 10.0f));
        mouseLastPosition=QVector2D(event->pos());
    }
}

void Window::keyPressEvent(QKeyEvent *event)
{
    int i=0;
    bool t=false,t2=false,t3=false;
    if(event->modifiers()==Qt::ControlModifier) i=6;
    switch (event->key())
    {
        case Qt::Key_R: step_time=0.15;input_action::create_R_action();break;//for(int i=0;i<30;i++)   quene_transform.push_back(qrand()%6);     break;
        case Qt::Key_Shift:  t2=true;break;
        case Qt::Key_S:  t3=true;break;
        case Qt::Key_Down: { pause=(pause==false)?true:false; break;}
        case Qt::Key_Space: if(!sign_solve){ sign_solve=true; solve();break;}
    }
    if(t2){
        input_action* w = new input_action;
        w->show();
    }

    if(t3){
        show2D* w1 = new show2D;
        w1->show();
    }

}

void Window::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast <const char *>(glGetString(GL_VERSION));

#define CASE(c) case QSurfaceFormat::c: glProfile = #c;break;
    switch(format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
#undef CASE

    qDebug() << qPrintable(glType) <<qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
    qDebug() << "s键展示二维平面展开情况";
    qDebug() << "shift键打开动作指令框";
    qDebug() << "R键随机打乱魔方";
    qDebug() << "Space键还原";
    qDebug() << "keyDown暂停";
    qDebug() << "鼠标点击魔方可拖动";
}

void Window::transformAction(int X, float angle, bool t_end)
{

    bool r=(angle<0)?true:false;
    switch (X)
    {
    case 0:
        m_cubesstate.frontCubes();
        for(int i=0;i<9;i++)
             m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(0.0f,0.0f,-1.0f));
        if(t_end) m_cubesstate.rotateFront(r);
        break;
    case 1:
        m_cubesstate.backCubes();
        for(int i=0;i<9;i++)
            m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(0.0f,0.0f,1.0f));
        if(t_end) m_cubesstate.rotateBack(r);
        break;
    case 2:
        m_cubesstate.upCubes();

        for(int i=0;i<9;i++)
            m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(0.0f,-1.0f,0.0f));
        if(t_end) m_cubesstate.rotateUp(r);
        break;
    case 3:
        m_cubesstate.downCubes();
        for(int i=0;i<9;i++)
            m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(0.0f,1.0f,0.0f));
        if(t_end) m_cubesstate.rotateDown(r);
        break;
    case 4:
        m_cubesstate.leftCubes();
        for(int i=0;i<9;i++)
            m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(1.0f,0.0f,0.0f));
        if(t_end) m_cubesstate.rotateLeft(r);
        break;
    case 5:
        m_cubesstate.rightCubes();
        for(int i=0;i<9;i++)
            m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(-1.0f,0.0f,0.0f));
        if(t_end) m_cubesstate.rotateRight(r);
        break;
    case 6:
        m_cubesstate.X_Cubes();
        for(int i=0;i<9;i++)
            m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(0.0f,0.0f,1.0f));
        if(t_end) m_cubesstate.rotateM_X(r);
        break;
    case 7:
        m_cubesstate.Y_Cubes();
        for(int i=0;i<9;i++)
            m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(0.0f,1.0f,0.0f));
        if(t_end) m_cubesstate.rotateM_Y(!r);
        break;
    case 8:
        m_cubesstate.Z_Cubes();
        for(int i=0;i<9;i++)
            m_transform[m_cubesstate.r_cubes[i]].rotate(angle,QVector3D(1.0f,0.0f,0.0f));
        if(t_end) m_cubesstate.rotateM_Z(r);
        break;
    default:
        break;
    }
    if(t_end)
    {
        quene_transform.pop_front();
        m_cubesstate.frontCubes();
    }
}

void Window::init_cubes()
{
    float dx=0,dy=0,dz=0,k=1.05;
    QVector3D color[6];
    for(int i=0;i<27;i++)
    {
        memcpy(color,my_color[i],sizeof(color));
        dx=(i%3-1)*k;
        dy=(1-(i/3%3))*k;
        dz=(1-i/9)*k;
        Vertex t[36]=
        {
            // Front
            Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  0.5f+dz), color[0] ), Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  0.5f+dz), color[0] ),
            Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  0.5f+dz), color[0] ), Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  0.5f+dz), color[0] ),
            Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  0.5f+dz), color[0] ), Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  0.5f+dz), color[0] ),
            // Face 2 (Back)
            Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  -0.5f+dz), color[1] ), Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  -0.5f+dz),  color[1] ),
            Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  -0.5f+dz), color[1] ), Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  -0.5f+dz),  color[1] ),
            Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  -0.5f+dz), color[1] ), Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  -0.5f+dz),   color[1] ),
            // Face 3 (Top)
            Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  0.5f+dz), color[2] ), Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  -0.5f+dz), color[2] ),
            Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  -0.5f+dz),  color[2] ), Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  -0.5f+dz),  color[2] ),
            Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  0.5f+dz), color[2] ), Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  0.5f+dz), color[2] ),
            // Face 4 (Bottom)
            Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  0.5f+dz), color[3] ), Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  0.5f+dz), color[3] ),
            Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  -0.5f+dz),   color[3] ), Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  -0.5f+dz),   color[3] ),
            Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  -0.5f+dz), color[3] ), Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  0.5f+dz), color[3] ),
            // Face 5 (Left)
            Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  0.5f+dz), color[4] ), Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  0.5f+dz), color[4] ),
            Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  -0.5f+dz),  color[4] ), Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  0.5f+dz), color[4] ),
            Vertex( QVector3D( -0.5f+dx,  0.5f+dy,  -0.5f+dz),  color[4] ), Vertex( QVector3D( -0.5f+dx,  -0.5f+dy,  -0.5f+dz),   color[4] ),
            // Face 6 (Right)
            Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  0.5f+dz), color[5] ), Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  0.5f+dz), color[5] ),
            Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  -0.5f+dz), color[5] ), Vertex( QVector3D( 0.5f+dx,  -0.5f+dy,  -0.5f+dz), color[5] ),
            Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  -0.5f+dz), color[5] ), Vertex( QVector3D( 0.5f+dx,  0.5f+dy,  0.5f+dz), color[5] )
       };
       memcpy(cubes_vertex+i*36,t,sizeof(t));
    }
}

void Window::solve()
{
    step_time=0.25;
    sign_solve=true;
    std::string push_action;
    solveFunction();
    // 翻译动作指令
    for(int i=0;i<solve_action.size();i++){
        switch (solve_action[i]) {
        case 'U':
            if(i+1 < solve_action.size() and solve_action[i+1]=='\'' ){
                push_action+="5";
                push_action+="-";
                break;
            }
            if(i+1 < solve_action.size() and solve_action[i+1]=='2' ){
                push_action+="5";
                push_action+="+";
                push_action+="5";
                push_action+="+";
                break;
            }
            push_action+="5+";
            break;

        case 'D':
            if(i+1 < solve_action.size() and solve_action[i+1]=='\'' ){
                push_action+="3";
                push_action+="+";
                break;
            }
            if(i+1 < solve_action.size() and solve_action[i+1]=='2' ){
                push_action+="3";
                push_action+="+";
                push_action+="3";
                push_action+="+";
                break;
            }
            push_action+="3-";
            break;
        case 'F':
            if(i+1 < solve_action.size() and solve_action[i+1]=='\'' ){
                push_action+="6";
                push_action+="-";
                break;
            }
            if(i+1 < solve_action.size() and solve_action[i+1]=='2' ){
                push_action+="6";
                push_action+="+";
                push_action+="6";
                push_action+="+";
                break;
            }
            push_action+="6+";
            break;
        case 'B':
            if(i+1 < solve_action.size() and solve_action[i+1]=='\'' ){
                push_action+="8";
                push_action+="+";
                break;
            }
            if(i+1 < solve_action.size() and solve_action[i+1]=='2' ){
                push_action+="8";
                push_action+="+";
                push_action+="8";
                push_action+="+";
                break;
            }
            push_action+="8-";
            break;
        case 'L':
            if(i+1 < solve_action.size() and solve_action[i+1]=='\'' ){
                push_action+="0";
                push_action+="-";
                break;
            }
            if(i+1 < solve_action.size() and solve_action[i+1]=='2' ){
                push_action+="0";
                push_action+="+";
                push_action+="0";
                push_action+="+";
                break;
            }
            push_action+="0+";
            break;
        case 'R':
            if(i+1 < solve_action.size() and solve_action[i+1]=='\'' ){
                push_action+="2";
                push_action+="+";
                break;
            }
            if(i+1 < solve_action.size() and solve_action[i+1]=='2' ){
                push_action+="2";
                push_action+="+";
                push_action+="2";
                push_action+="+";
                break;
            }
            push_action+="2-";
            break;
        default:
            break;
        }
    }
    input_action::do_action(push_action);
}
