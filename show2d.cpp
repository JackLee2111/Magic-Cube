#include "show2d.h"
#include "ui_show2d.h"
#include <QPainter>
#include "cglobal.h"
#include <cstring>
#include <QDebug>


show2D::show2D(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::show2D)
{
    ui->setupUi(this);

    std::string s;
    // 打印各个面
    //back
    for(int i=0;i<9;i++){
        s+=color_back[i];
        if(i==2 or i==5 or i==8)s+='\n';
        else s+=' ';
    }
    ui->textBrowser_back->setText(QString::fromStdString(s));

    //up
    s="";
    for(int i=0;i<9;i++){
        s+=color_up[i];
        if(i==2 or i==5 or i==8)s+='\n';
        else s+=' ';
    }
    ui->textBrowser_up->setText(QString::fromStdString(s));

    //front
    s="";
    for(int i=0;i<9;i++){
        s+=color_front[i];
        if(i==2 or i==5 or i==8)s+='\n';
        else s+=' ';
    }
    ui->textBrowser_front->setText(QString::fromStdString(s));

    //down
    s="";
    for(int i=0;i<9;i++){
        s+=color_down[i];
        if(i==2 or i==5 or i==8)s+='\n';
        else s+=' ';
    }
    ui->textBrowser_down->setText(QString::fromStdString(s));

    //right
    s="";
    for(int i=0;i<9;i++){
        s+=color_right[i];
        if(i==2 or i==5 or i==8)s+='\n';
        else s+=' ';
    }
    ui->textBrowser_right->setText(QString::fromStdString(s));

    //left
    s="";
    for(int i=0;i<9;i++){
        s+=color_left[i];
        if(i==2 or i==5 or i==8)s+='\n';
        else s+=' ';
    }
    ui->textBrowser_left->setText(QString::fromStdString(s));

}

show2D::~show2D()
{
    delete ui;
}
