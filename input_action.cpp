#include "input_action.h"
#include "ui_input_action.h"
#include "window.h"
#include "cglobal.h"
#include <QRandomGenerator>
input_action::input_action(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::input_action)
{
    ui->setupUi(this);
}

input_action::~input_action()
{
    delete ui;
}

// action0-8 为各种旋转情况下每个面颜色的变化
void action0(bool r)
{
    int t1,t2,t3;
    if(r){
        t1=color_back[0];color_back[0]=color_down[0];color_down[0]=color_front[0];color_front[0]=color_up[0];color_up[0]=t1;
        t2=color_back[3];color_back[3]=color_down[3];color_down[3]=color_front[3];color_front[3]=color_up[3];color_up[3]=t2;
        t3=color_back[6];color_back[6]=color_down[6];color_down[6]=color_front[6];color_front[6]=color_up[6];color_up[6]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_left[i];
        for(int i=0;i<9;i++)color_left[i]=temp_a[q[i]];

    }else{
        t1=color_back[0];color_back[0]=color_up[0];color_up[0]=color_front[0];color_front[0]=color_down[0];color_down[0]=t1;
        t2=color_back[3];color_back[3]=color_up[3];color_up[3]=color_front[3];color_front[3]=color_down[3];color_down[3]=t2;
        t3=color_back[6];color_back[6]=color_up[6];color_up[6]=color_front[6];color_front[6]=color_down[6];color_down[6]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_left[i];
        for(int i=0;i<9;i++)color_left[i]=temp_a[q[i]];

    }
}


void action1(bool r)
{
    int t1,t2,t3;
    if(r){
        t1=color_back[1];color_back[1]=color_down[1];color_down[1]=color_front[1];color_front[1]=color_up[1];color_up[1]=t1;
        t2=color_back[4];color_back[4]=color_down[4];color_down[4]=color_front[4];color_front[4]=color_up[4];color_up[4]=t2;
        t3=color_back[7];color_back[7]=color_down[7];color_down[7]=color_front[7];color_front[7]=color_up[7];color_up[7]=t3;

    }else{
        t1=color_back[1];color_back[1]=color_up[1];color_up[1]=color_front[1];color_front[1]=color_down[1];color_down[1]=t1;
        t2=color_back[4];color_back[4]=color_up[4];color_up[4]=color_front[4];color_front[4]=color_down[4];color_down[4]=t2;
        t3=color_back[7];color_back[7]=color_up[7];color_up[7]=color_front[7];color_front[7]=color_down[7];color_down[7]=t3;

    }
}

void action2(bool r)
{
    int t1,t2,t3;
    if(r){
        t1=color_back[2];color_back[2]=color_down[2];color_down[2]=color_front[2];color_front[2]=color_up[2];color_up[2]=t1;
        t2=color_back[5];color_back[5]=color_down[5];color_down[5]=color_front[5];color_front[5]=color_up[5];color_up[5]=t2;
        t3=color_back[8];color_back[8]=color_down[8];color_down[8]=color_front[8];color_front[8]=color_up[8];color_up[8]=t3;


        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_right[i];
        for(int i=0;i<9;i++)color_right[i]=temp_a[q[i]];

    }else{
        t1=color_back[2];color_back[2]=color_up[2];color_up[2]=color_front[2];color_front[2]=color_down[2];color_down[2]=t1;
        t2=color_back[5];color_back[5]=color_up[5];color_up[5]=color_front[5];color_front[5]=color_down[5];color_down[5]=t2;
        t3=color_back[8];color_back[8]=color_up[8];color_up[8]=color_front[8];color_front[8]=color_down[8];color_down[8]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_right[i];
        for(int i=0;i<9;i++)color_right[i]=temp_a[q[i]];

    }
}

void action3(bool r)
{
    int t1,t2,t3;
    if(r){

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_down[i];
        for(int i=0;i<9;i++)color_down[i]=temp_a[q[i]];

        t1=color_back[0];color_back[0]=color_left[6];color_left[6]=color_front[8];color_front[8]=color_right[2];color_right[2]=t1;
        t2=color_back[1];color_back[1]=color_left[3];color_left[3]=color_front[7];color_front[7]=color_right[5];color_right[5]=t2;
        t3=color_back[2];color_back[2]=color_left[0];color_left[0]=color_front[6];color_front[6]=color_right[8];color_right[8]=t3;
    }else{
        t1=color_back[0];color_back[0]=color_right[2];color_right[2]=color_front[8];color_front[8]=color_left[6];color_left[6]=t1;
        t2=color_back[1];color_back[1]=color_right[5];color_right[5]=color_front[7];color_front[7]=color_left[3];color_left[3]=t2;
        t3=color_back[2];color_back[2]=color_right[8];color_right[8]=color_front[6];color_front[6]=color_left[0];color_left[0]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_down[i];
        for(int i=0;i<9;i++)color_down[i]=temp_a[q[i]];

    }
}

void action4(bool r)
{
    int t1,t2,t3;
    if(r){
        t1=color_back[3];color_back[3]=color_left[7];color_left[7]=color_front[5];color_front[5]=color_right[1];color_right[1]=t1;
        t2=color_back[4];color_back[4]=color_left[4];color_left[4]=color_front[4];color_front[4]=color_right[4];color_right[4]=t2;
        t3=color_back[5];color_back[5]=color_left[1];color_left[1]=color_front[3];color_front[3]=color_right[7];color_right[7]=t3;
    }else{
        t1=color_back[3];color_back[3]=color_right[1];color_right[1]=color_front[5];color_front[5]=color_left[7];color_left[7]=t1;
        t2=color_back[4];color_back[4]=color_right[4];color_right[4]=color_front[4];color_front[4]=color_left[4];color_left[4]=t2;
        t3=color_back[5];color_back[5]=color_right[7];color_right[7]=color_front[3];color_front[3]=color_left[1];color_left[1]=t3;
    }
}

void action5(bool r)
{
    int t1,t2,t3;
    if(r){
        t1=color_back[6];color_back[6]=color_left[8];color_left[8]=color_front[2];color_front[2]=color_right[0];color_right[0]=t1;
        t2=color_back[7];color_back[7]=color_left[5];color_left[5]=color_front[1];color_front[1]=color_right[3];color_right[3]=t2;
        t3=color_back[8];color_back[8]=color_left[2];color_left[2]=color_front[0];color_front[0]=color_right[6];color_right[6]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_up[i];
        for(int i=0;i<9;i++)color_up[i]=temp_a[q[i]];

    }else{
        t1=color_back[6];color_back[6]=color_right[0];color_right[0]=color_front[2];color_front[2]=color_left[8];color_left[8]=t1;
        t2=color_back[7];color_back[7]=color_right[3];color_right[3]=color_front[1];color_front[1]=color_left[5];color_left[5]=t2;
        t3=color_back[8];color_back[8]=color_right[6];color_right[6]=color_front[0];color_front[0]=color_left[2];color_left[2]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_up[i];
        for(int i=0;i<9;i++)color_up[i]=temp_a[q[i]];

    }
}

void action6(bool r)
{
    int t1,t2,t3;
    if(r){
        t1=color_up[6];color_up[6]=color_left[6];color_left[6]=color_down[2];color_down[2]=color_right[6];color_right[6]=t1;
        t2=color_up[7];color_up[7]=color_left[7];color_left[7]=color_down[1];color_down[1]=color_right[7];color_right[7]=t2;
        t3=color_up[8];color_up[8]=color_left[8];color_left[8]=color_down[0];color_down[0]=color_right[8];color_right[8]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_front[i];
        for(int i=0;i<9;i++)color_front[i]=temp_a[q[i]];

    }else{
        t1=color_up[6];color_up[6]=color_right[6];color_right[6]=color_down[2];color_down[2]=color_left[6];color_left[6]=t1;
        t2=color_up[7];color_up[7]=color_right[7];color_right[7]=color_down[1];color_down[1]=color_left[7];color_left[7]=t2;
        t3=color_up[8];color_up[8]=color_right[8];color_right[8]=color_down[0];color_down[0]=color_left[8];color_left[8]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_front[i];
        for(int i=0;i<9;i++)color_front[i]=temp_a[q[i]];

    }
}

void action7(bool r)
{
    int t1,t2,t3;
    if(r){
        t1=color_up[3];color_up[3]=color_left[3];color_left[3]=color_down[5];color_down[5]=color_right[3];color_right[3]=t1;
        t2=color_up[4];color_up[4]=color_left[4];color_left[4]=color_down[4];color_down[4]=color_right[4];color_right[4]=t2;
        t3=color_up[5];color_up[5]=color_left[5];color_left[5]=color_down[3];color_down[3]=color_right[5];color_right[5]=t3;
    }else{
        t1=color_up[3];color_up[3]=color_right[3];color_right[3]=color_down[5];color_down[5]=color_left[3];color_left[3]=t1;
        t2=color_up[4];color_up[4]=color_right[4];color_right[4]=color_down[4];color_down[4]=color_left[4];color_left[4]=t2;
        t3=color_up[5];color_up[5]=color_right[5];color_right[5]=color_down[3];color_down[3]=color_left[5];color_left[5]=t3;
    }
}

void action8(bool r)
{
    int t1,t2,t3;
    if(r){
        t1=color_up[0];color_up[0]=color_left[0];color_left[0]=color_down[8];color_down[8]=color_right[0];color_right[0]=t1;
        t2=color_up[1];color_up[1]=color_left[1];color_left[1]=color_down[7];color_down[7]=color_right[1];color_right[1]=t2;
        t3=color_up[2];color_up[2]=color_left[2];color_left[2]=color_down[6];color_down[6]=color_right[2];color_right[2]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_back[i];
        for(int i=0;i<9;i++)color_back[i]=temp_a[q[i]];

    }else{
        t1=color_up[0];color_up[0]=color_right[0];color_right[0]=color_down[8];color_down[8]=color_left[0];color_left[0]=t1;
        t2=color_up[1];color_up[1]=color_right[1];color_right[1]=color_down[7];color_down[7]=color_left[1];color_left[1]=t2;
        t3=color_up[2];color_up[2]=color_right[2];color_right[2]=color_down[6];color_down[6]=color_left[2];color_left[2]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=color_back[i];
        for(int i=0;i<9;i++)color_back[i]=temp_a[q[i]];

    }
}



void input_action::on_button_action_clicked()
{
    // 读入动作指令
    std::string action = ui->lineEdit_action->text().toStdString();
    do_action(action);
    this->close();
}

void input_action::create_R_action()
{
    std::string action;
    for(int i=0;i<60;i++)
    {

        int a=QRandomGenerator::global()->bounded(5);
        int r=QRandomGenerator::global()->bounded(10);
        action+=std::to_string(a);
        if(r)action+='+';else action+='-';
    }
    do_action(action);
}

void input_action::do_action(std::string &action)
{
    for(int i=0;i<action.size();i++){
        int k=0;
        switch (action[i]) {
        case '0':
            k=4;
            if(action[i+1]=='+'){k+=6;action0(true);}
            else action0(false);
            a.push_back(k);
            break;
        case '1':
            if(action[i+1]=='+'){
                a.push_back(12);
                action1(true);
            }
            else {
                a.push_back(13);
                action1(false);
            }
            break;
        case '2':
            k=5;
            if(action[i+1]=='-'){
                k+=6;
                action2(false);
            }else action2(true);
            a.push_back(k);
            break;
        case '3':
            k=3;
            if(action[i+1]=='-'){
                k+=6;
                action3(false);
            }else action3(true);
            a.push_back(k);
            break;
        case '4':
            if(action[i+1]=='+'){
                a.push_back(15);
                action4(true);
            }
            else{
                a.push_back(14);
                action4(false);
            }
            break;
        case '5':
            k=2;
            if(action[i+1]=='+'){
                k+=6;
                action5(true);
            }else action5(false);
            a.push_back(k);
            break;
        case '6':
            k=0;
            if(action[i+1]=='+'){
                k+=6;
                action6(true);
            }else action6(false);
            a.push_back(k);
            break;
        case '7':
            if(action[i+1]=='+'){
                a.push_back(16);
                action7(true);
            }else{
                a.push_back(17);
                action7(false);
            }
            break;
        case '8':
            k=1;
            if(action[i+1]=='-'){
                k+=6;
                action8(false);
            }else action8(true);
            a.push_back(k);
            break;
        default:
            break;
        }
    }
}

