#include "setwindow.h"
#include "ui_setwindow.h"
#include <cstring>
#include "cubes.h"
#include "window.h"
#include "cglobal.h"

#include <fstream>
#include <QGuiApplication>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>


SetWindow::SetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetWindow)
{
    ui->setupUi(this);
}

SetWindow::~SetWindow()
{
    delete ui;
}

void SetWindow::on_pushButton_setdata_clicked()
{
    #define r to_my_color(Qt::red)
    #define p QVector3D(230.0/255,87.0/255,5.0/255) //RGB
    #define y to_my_color(Qt::yellow)
    #define w to_my_color(Qt::white)
    #define b to_my_color(Qt::blue)
    #define g to_my_color(Qt::green)

//    for(int i=0;i<27;i++)
//        for(int j=0;j<6;j++)
//            my_color[i][j]=w;

    // 保存并设置各个面颜色
    int k;std::string text_info;
    //back:
    k=0;
    int q[9]={24,25,26,21,22,23,18,19,20};
    text_info = ui->text_back->toPlainText().toStdString();
    for(int i=0;i<text_info.size();i++){

        if(text_info[i]>='a' and text_info[i]<='z')
            color_back[k]=text_info[i];

        switch (text_info[i]) {
        case 'r':
            my_color[q[k]][1]=r;
            k++;
            break;
        case 'p':
            my_color[q[k]][1]=p;
            k++;
            break;
        case 'y':
            my_color[q[k]][1]=y;
            k++;
            break;
        case 'w':
            my_color[q[k]][1]=w;
            k++;
            break;
        case 'b':
            my_color[q[k]][1]=b;
            k++;
            break;
        case 'g':
            my_color[q[k]][1]=g;
            k++;
            break;
        default:
            break;
        }
    }

    //down:
    k=0;
    int q2[9]={6,7,8,15,16,17,24,25,26};
    text_info = ui->text_down->toPlainText().toStdString();
    for(int i=0;i<text_info.size();i++){

        if(text_info[i]>='a' and text_info[i]<='z')
            color_down[k]=text_info[i];

        switch (text_info[i]) {

        case 'r':
            my_color[q2[k]][3]=r;
            k++;
            break;
        case 'p':
            my_color[q2[k]][3]=p;
            k++;
            break;
        case 'y':
            my_color[q2[k]][3]=y;
            k++;
            break;
        case 'w':
            my_color[q2[k]][3]=w;
            k++;
            break;
        case 'b':
            my_color[q2[k]][3]=b;
            k++;
            break;
        case 'g':
            my_color[q2[k]][3]=g;
            k++;
            break;
        default:
            break;
        }

    }


    //front:
    k=0;
    int q3[9]={0,1,2,3,4,5,6,7,8};
    text_info = ui->text_front->toPlainText().toStdString();
    for(int i=0;i<text_info.size();i++){

        if(text_info[i]>='a' and text_info[i]<='z')
            color_front[k]=text_info[i];

        switch (text_info[i]) {
        case 'r':
            my_color[q3[k]][0]=r;
            k++;
            break;
        case 'p':
            my_color[q3[k]][0]=p;
            k++;
            break;
        case 'y':
            my_color[q3[k]][0]=y;
            k++;
            break;
        case 'w':
            my_color[q3[k]][0]=w;
            k++;
            break;
        case 'b':
            my_color[q3[k]][0]=b;
            k++;
            break;
        case 'g':
            my_color[q3[k]][0]=g;
            k++;
            break;
        default:
            break;
        }

    }

    //left:
    k=0;
    int q4[9]={24,21,18,15,12,9,6,3,0};
    text_info = ui->text_left->toPlainText().toStdString();
    for(int i=0;i<text_info.size();i++){

        if(text_info[i]>='a' and text_info[i]<='z')
            color_left[k]=text_info[i];

        switch (text_info[i]) {
        case 'r':
            my_color[q4[k]][4]=r;
            k++;
            break;
        case 'p':
            my_color[q4[k]][4]=p;
            k++;
            break;
        case 'y':
            my_color[q4[k]][4]=y;
            k++;
            break;
        case 'w':
            my_color[q4[k]][4]=w;
            k++;
            break;
        case 'b':
            my_color[q4[k]][4]=b;
            k++;
            break;
        case 'g':
            my_color[q4[k]][4]=g;
            k++;
            break;
        default:
            break;
        }

    }

    //right:
    k=0;
    int q5[9]={20,23,26,11,14,17,2,5,8};
    text_info = ui->text_right->toPlainText().toStdString();
    for(int i=0;i<text_info.size();i++){

        if(text_info[i]>='a' and text_info[i]<='z')
            color_right[k]=text_info[i];

        switch (text_info[i]) {
        case 'r':
            my_color[q5[k]][5]=r;
            k++;
            break;
        case 'p':
            my_color[q5[k]][5]=p;
            k++;
            break;
        case 'y':
            my_color[q5[k]][5]=y;
            k++;
            break;
        case 'w':
            my_color[q5[k]][5]=w;
            k++;
            break;
        case 'b':
            my_color[q5[k]][5]=b;
            k++;
            break;
        case 'g':
            my_color[q5[k]][5]=g;
            k++;
            break;
        default:
            break;
        }

    }

    //up:
    k=0;
    int q6[9]={18,19,20,9,10,11,0,1,2};
    text_info = ui->text_up->toPlainText().toStdString();
    for(int i=0;i<text_info.size();i++){

        if(text_info[i]>='a' and text_info[i]<='z')
            color_up[k]=text_info[i];

        switch (text_info[i]) {
        case 'r':
            my_color[q6[k]][2]=r;
            k++;
            break;
        case 'p':
            my_color[q6[k]][2]=p;
            k++;
            break;
        case 'y':
            my_color[q6[k]][2]=y;
            k++;
            break;
        case 'w':
            my_color[q6[k]][2]=w;
            k++;
            break;
        case 'b':
            my_color[q6[k]][2]=b;
            k++;
            break;
        case 'g':
            my_color[q6[k]][2]=g;
            k++;
            break;
        default:
            break;
        }

    }


    #undef r;
    #undef p;
    #undef y;
    #undef w;
    #undef b;
    #undef g;
    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);

    Window* new_win = new Window;
    new_win->setFormat(format);
    new_win->resize(QSize(800, 600));
    new_win->show();
    this->close();
}


void SetWindow::on_pushButton_file_clicked()
{
    std::string file_name = QFileDialog::getOpenFileName(NULL,"打开输入文件",".","*.txt").toStdString();
    std::ifstream fin;
    fin.open(file_name);
    std::string temp_s="1";
    while(!fin.eof()){
        getline(fin,temp_s);
        if(temp_s=="\n" or temp_s=="\0")continue;
        char temp_c;
        std::string tp_s="";
        for(int i=0;i<9;i++){
            fin>>temp_c;
            while(temp_c<'a' or temp_c>'z')fin>>temp_c;
            tp_s+=temp_c;
            if(i==2 or i==5 or i==8)tp_s+='\n';else tp_s+=' ';
        }
        if(temp_s=="back")
            ui->text_back->setText(QString::fromStdString(tp_s));
        if(temp_s=="up")
            ui->text_up->setText(QString::fromStdString(tp_s));
        if(temp_s=="front")
            ui->text_front->setText(QString::fromStdString(tp_s));
        if(temp_s=="down")
            ui->text_down->setText(QString::fromStdString(tp_s));
        if(temp_s=="right")
            ui->text_right->setText(QString::fromStdString(tp_s));
        if(temp_s=="left")
            ui->text_left->setText(QString::fromStdString(tp_s));
    }
   fin.close();
}

