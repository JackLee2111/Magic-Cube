#include "cglobal.h"
#include <iostream>
#include "input_action.h"
#include <queue>
#include <QDebug>
#include <QString>
#include <algorithm>

using namespace std;

#define MaxTrace 1000 //轨迹数组的最大长度
#define MAX_DEPTH 20 //最大步数

//20220823 1.0
//20220824 2.0

typedef struct
{
    char nowcolor_back[9];
    char nowcolor_up[9];
    char nowcolor_front[9];
    char nowcolor_right[9];
    char nowcolor_left[9];
    char nowcolor_down[9];//储存当前状态各个面的颜色
    //int from;//该状态的上一个状态记录
    std::vector <char> trace; // 记录这个状态的来源操作步骤
    int depth;//搜索深度
} State;

std::queue <State> que; // 定义队列

State trace[MaxTrace]; //记录操作轨迹

std::vector <State> repeat; // 记录该图案是否出现过


//出现过的图案设置重复
void setRepeat(State state)
{
    repeat.push_back(state);
}

//检查是否有颜色重复
bool checkColor(State state,int num)
{
    for(int j=0;j<9;j++)
    {
        if(repeat[num].nowcolor_back[j] != state.nowcolor_back[j]) return false;
    }
    for(int j=0;j<9;j++)
    {
        if(repeat[num].nowcolor_down[j] != state.nowcolor_down[j]) return false;
    }
    for(int j=0;j<9;j++)
    {
        if(repeat[num].nowcolor_front[j] != state.nowcolor_front[j]) return false;
    }
    for(int j=0;j<9;j++)
    {
        if(repeat[num].nowcolor_left[j] != state.nowcolor_left[j]) return false;
    }
    for(int j=0;j<9;j++)
    {
        if(repeat[num].nowcolor_right[j] != state.nowcolor_right[j]) return false;
    }
    for(int j=0;j<9;j++)
    {
        if(repeat[num].nowcolor_up[j] != state.nowcolor_up[j]) return false;
    }
    return true;
}

//检查是否有状态重复
bool checkRepeat(State state)
{
    for(int i=0;i<repeat.size();i++)
    {
        if(checkColor(state,i)==true)//找到重复的状态
            return true;
    }
    return false;//全部都没有重复
}

//复制状态
void copy(State *child, State *curState)
{
    //qDebug() <<"enter copy";
    for(int i=0;i<9;i++)
    {
        child->nowcolor_back[i] = curState->nowcolor_back[i];
        child->nowcolor_down[i] = curState->nowcolor_down[i];
        child->nowcolor_front[i] = curState->nowcolor_front[i];
        child->nowcolor_left[i] = curState->nowcolor_left[i];
        child->nowcolor_right[i] = curState->nowcolor_right[i];
        child->nowcolor_up[i] = curState->nowcolor_up[i];
    }
    child->depth = curState->depth;
    //复制轨迹数组
    for(int i=0;i<curState->trace.size();i++)
    {
        child->trace.push_back(curState->trace[i]);
        //cout<< curState->trace[i] <<" ";
    }
    //cout<<endl;
}
//生成新的子节点
void expansion(State *child, State *curState, int act)
{
    copy(child, curState);
    child->depth++;
    if(act == 1)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[0];child->nowcolor_back[0]=child->nowcolor_down[0];child->nowcolor_down[0]=child->nowcolor_front[0];child->nowcolor_front[0]=child->nowcolor_up[0];child->nowcolor_up[0]=t1;
        t2=child->nowcolor_back[3];child->nowcolor_back[3]=child->nowcolor_down[3];child->nowcolor_down[3]=child->nowcolor_front[3];child->nowcolor_front[3]=child->nowcolor_up[3];child->nowcolor_up[3]=t2;
        t3=child->nowcolor_back[6];child->nowcolor_back[6]=child->nowcolor_down[6];child->nowcolor_down[6]=child->nowcolor_front[6];child->nowcolor_front[6]=child->nowcolor_up[6];child->nowcolor_up[6]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_left[i];
        for(int i=0;i<9;i++)child->nowcolor_left[i]=temp_a[q[i]];
    }
    else if(act == 2)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[0];child->nowcolor_back[0]=child->nowcolor_up[0];child->nowcolor_up[0]=child->nowcolor_front[0];child->nowcolor_front[0]=child->nowcolor_down[0];child->nowcolor_down[0]=t1;
        t2=child->nowcolor_back[3];child->nowcolor_back[3]=child->nowcolor_up[3];child->nowcolor_up[3]=child->nowcolor_front[3];child->nowcolor_front[3]=child->nowcolor_down[3];child->nowcolor_down[3]=t2;
        t3=child->nowcolor_back[6];child->nowcolor_back[6]=child->nowcolor_up[6];child->nowcolor_up[6]=child->nowcolor_front[6];child->nowcolor_front[6]=child->nowcolor_down[6];child->nowcolor_down[6]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_left[i];
        for(int i=0;i<9;i++)child->nowcolor_left[i]=temp_a[q[i]];
    }
    else if(act == 3)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[1];child->nowcolor_back[1]=child->nowcolor_down[1];child->nowcolor_down[1]=child->nowcolor_front[1];child->nowcolor_front[1]=child->nowcolor_up[1];child->nowcolor_up[1]=t1;
        t2=child->nowcolor_back[4];child->nowcolor_back[4]=child->nowcolor_down[4];child->nowcolor_down[4]=child->nowcolor_front[4];child->nowcolor_front[4]=child->nowcolor_up[4];child->nowcolor_up[4]=t2;
        t3=child->nowcolor_back[7];child->nowcolor_back[7]=child->nowcolor_down[7];child->nowcolor_down[7]=child->nowcolor_front[7];child->nowcolor_front[7]=child->nowcolor_up[7];child->nowcolor_up[7]=t3;
    }
    else if(act == 4)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[1];child->nowcolor_back[1]=child->nowcolor_up[1];child->nowcolor_up[1]=child->nowcolor_front[1];child->nowcolor_front[1]=child->nowcolor_down[1];child->nowcolor_down[1]=t1;
        t2=child->nowcolor_back[4];child->nowcolor_back[4]=child->nowcolor_up[4];child->nowcolor_up[4]=child->nowcolor_front[4];child->nowcolor_front[4]=child->nowcolor_down[4];child->nowcolor_down[4]=t2;
        t3=child->nowcolor_back[7];child->nowcolor_back[7]=child->nowcolor_up[7];child->nowcolor_up[7]=child->nowcolor_front[7];child->nowcolor_front[7]=child->nowcolor_down[7];child->nowcolor_down[7]=t3;
    }
    else if(act == 5)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[2];child->nowcolor_back[2]=child->nowcolor_down[2];child->nowcolor_down[2]=child->nowcolor_front[2];child->nowcolor_front[2]=child->nowcolor_up[2];child->nowcolor_up[2]=t1;
        t2=child->nowcolor_back[5];child->nowcolor_back[5]=child->nowcolor_down[5];child->nowcolor_down[5]=child->nowcolor_front[5];child->nowcolor_front[5]=child->nowcolor_up[5];child->nowcolor_up[5]=t2;
        t3=child->nowcolor_back[8];child->nowcolor_back[8]=child->nowcolor_down[8];child->nowcolor_down[8]=child->nowcolor_front[8];child->nowcolor_front[8]=child->nowcolor_up[8];child->nowcolor_up[8]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_right[i];
        for(int i=0;i<9;i++)child->nowcolor_right[i]=temp_a[q[i]];
    }
    else if(act == 6)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[2];child->nowcolor_back[2]=child->nowcolor_up[2];child->nowcolor_up[2]=child->nowcolor_front[2];child->nowcolor_front[2]=child->nowcolor_down[2];child->nowcolor_down[2]=t1;
        t2=child->nowcolor_back[5];child->nowcolor_back[5]=child->nowcolor_up[5];child->nowcolor_up[5]=child->nowcolor_front[5];child->nowcolor_front[5]=child->nowcolor_down[5];child->nowcolor_down[5]=t2;
        t3=child->nowcolor_back[8];child->nowcolor_back[8]=child->nowcolor_up[8];child->nowcolor_up[8]=child->nowcolor_front[8];child->nowcolor_front[8]=child->nowcolor_down[8];child->nowcolor_down[8]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_right[i];
        for(int i=0;i<9;i++)child->nowcolor_right[i]=temp_a[q[i]];
    }

    else if(act == 7)
    {
        int t1,t2,t3;
        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_down[i];
        for(int i=0;i<9;i++)child->nowcolor_down[i]=temp_a[q[i]];

        t1=child->nowcolor_back[0];child->nowcolor_back[0]=child->nowcolor_left[6];child->nowcolor_left[6]=child->nowcolor_front[8];child->nowcolor_front[8]=child->nowcolor_right[2];child->nowcolor_right[2]=t1;
        t2=child->nowcolor_back[1];child->nowcolor_back[1]=child->nowcolor_left[3];child->nowcolor_left[3]=child->nowcolor_front[7];child->nowcolor_front[7]=child->nowcolor_right[5];child->nowcolor_right[5]=t2;
        t3=child->nowcolor_back[2];child->nowcolor_back[2]=child->nowcolor_left[0];child->nowcolor_left[0]=child->nowcolor_front[6];child->nowcolor_front[6]=child->nowcolor_right[8];child->nowcolor_right[8]=t3;
    }
    else if(act == 8)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[0];child->nowcolor_back[0]=child->nowcolor_right[2];child->nowcolor_right[2]=child->nowcolor_front[8];child->nowcolor_front[8]=child->nowcolor_left[6];child->nowcolor_left[6]=t1;
        t2=child->nowcolor_back[1];child->nowcolor_back[1]=child->nowcolor_right[5];child->nowcolor_right[5]=child->nowcolor_front[7];child->nowcolor_front[7]=child->nowcolor_left[3];child->nowcolor_left[3]=t2;
        t3=child->nowcolor_back[2];child->nowcolor_back[2]=child->nowcolor_right[8];child->nowcolor_right[8]=child->nowcolor_front[6];child->nowcolor_front[6]=child->nowcolor_left[0];child->nowcolor_left[0]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_down[i];
        for(int i=0;i<9;i++)child->nowcolor_down[i]=temp_a[q[i]];
    }
    else if(act == 9)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[3];child->nowcolor_back[3]=child->nowcolor_left[7];child->nowcolor_left[7]=child->nowcolor_front[5];child->nowcolor_front[5]=child->nowcolor_right[1];child->nowcolor_right[1]=t1;
        t2=child->nowcolor_back[4];child->nowcolor_back[4]=child->nowcolor_left[4];child->nowcolor_left[4]=child->nowcolor_front[4];child->nowcolor_front[4]=child->nowcolor_right[4];child->nowcolor_right[4]=t2;
        t3=child->nowcolor_back[5];child->nowcolor_back[5]=child->nowcolor_left[1];child->nowcolor_left[1]=child->nowcolor_front[3];child->nowcolor_front[3]=child->nowcolor_right[7];child->nowcolor_right[7]=t3;
    }
    else if(act == 10)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[3];child->nowcolor_back[3]=child->nowcolor_right[1];child->nowcolor_right[1]=child->nowcolor_front[5];child->nowcolor_front[5]=child->nowcolor_left[7];child->nowcolor_left[7]=t1;
        t2=child->nowcolor_back[4];child->nowcolor_back[4]=child->nowcolor_right[4];child->nowcolor_right[4]=child->nowcolor_front[4];child->nowcolor_front[4]=child->nowcolor_left[4];child->nowcolor_left[4]=t2;
        t3=child->nowcolor_back[5];child->nowcolor_back[5]=child->nowcolor_right[7];child->nowcolor_right[7]=child->nowcolor_front[3];child->nowcolor_front[3]=child->nowcolor_left[1];child->nowcolor_left[1]=t3;
    }
    else if(act == 11)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[6];child->nowcolor_back[6]=child->nowcolor_left[8];child->nowcolor_left[8]=child->nowcolor_front[2];child->nowcolor_front[2]=child->nowcolor_right[0];child->nowcolor_right[0]=t1;
        t2=child->nowcolor_back[7];child->nowcolor_back[7]=child->nowcolor_left[5];child->nowcolor_left[5]=child->nowcolor_front[1];child->nowcolor_front[1]=child->nowcolor_right[3];child->nowcolor_right[3]=t2;
        t3=child->nowcolor_back[8];child->nowcolor_back[8]=child->nowcolor_left[2];child->nowcolor_left[2]=child->nowcolor_front[0];child->nowcolor_front[0]=child->nowcolor_right[6];child->nowcolor_right[6]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_up[i];
        for(int i=0;i<9;i++)child->nowcolor_up[i]=temp_a[q[i]];

    }
    else if(act == 12)
    {
        int t1,t2,t3;
        t1=child->nowcolor_back[6];child->nowcolor_back[6]=child->nowcolor_right[0];child->nowcolor_right[0]=child->nowcolor_front[2];child->nowcolor_front[2]=child->nowcolor_left[8];child->nowcolor_left[8]=t1;
        t2=child->nowcolor_back[7];child->nowcolor_back[7]=child->nowcolor_right[3];child->nowcolor_right[3]=child->nowcolor_front[1];child->nowcolor_front[1]=child->nowcolor_left[5];child->nowcolor_left[5]=t2;
        t3=child->nowcolor_back[8];child->nowcolor_back[8]=child->nowcolor_right[6];child->nowcolor_right[6]=child->nowcolor_front[0];child->nowcolor_front[0]=child->nowcolor_left[2];child->nowcolor_left[2]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_up[i];
        for(int i=0;i<9;i++)child->nowcolor_up[i]=temp_a[q[i]];
    }
    else if(act == 13)
    {
        int t1,t2,t3;
        t1=child->nowcolor_up[6];child->nowcolor_up[6]=child->nowcolor_left[6];child->nowcolor_left[6]=child->nowcolor_down[2];child->nowcolor_down[2]=child->nowcolor_right[6];child->nowcolor_right[6]=t1;
        t2=child->nowcolor_up[7];child->nowcolor_up[7]=child->nowcolor_left[7];child->nowcolor_left[7]=child->nowcolor_down[1];child->nowcolor_down[1]=child->nowcolor_right[7];child->nowcolor_right[7]=t2;
        t3=child->nowcolor_up[8];child->nowcolor_up[8]=child->nowcolor_left[8];child->nowcolor_left[8]=child->nowcolor_down[0];child->nowcolor_down[0]=child->nowcolor_right[8];child->nowcolor_right[8]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_front[i];
        for(int i=0;i<9;i++)child->nowcolor_front[i]=temp_a[q[i]];
    }
    else if(act == 14)
    {
        int t1,t2,t3;
        t1=child->nowcolor_up[6];child->nowcolor_up[6]=child->nowcolor_right[6];child->nowcolor_right[6]=child->nowcolor_down[2];child->nowcolor_down[2]=child->nowcolor_left[6];child->nowcolor_left[6]=t1;
        t2=child->nowcolor_up[7];child->nowcolor_up[7]=child->nowcolor_right[7];child->nowcolor_right[7]=child->nowcolor_down[1];child->nowcolor_down[1]=child->nowcolor_left[7];child->nowcolor_left[7]=t2;
        t3=child->nowcolor_up[8];child->nowcolor_up[8]=child->nowcolor_right[8];child->nowcolor_right[8]=child->nowcolor_down[0];child->nowcolor_down[0]=child->nowcolor_left[8];child->nowcolor_left[8]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_front[i];
        for(int i=0;i<9;i++)child->nowcolor_front[i]=temp_a[q[i]];
    }
    else if(act == 15)
    {
        int t1,t2,t3;
        t1=child->nowcolor_up[3];child->nowcolor_up[3]=child->nowcolor_left[3];child->nowcolor_left[3]=child->nowcolor_down[5];child->nowcolor_down[5]=child->nowcolor_right[3];child->nowcolor_right[3]=t1;
        t2=child->nowcolor_up[4];child->nowcolor_up[4]=child->nowcolor_left[4];child->nowcolor_left[4]=child->nowcolor_down[4];child->nowcolor_down[4]=child->nowcolor_right[4];child->nowcolor_right[4]=t2;
        t3=child->nowcolor_up[5];child->nowcolor_up[5]=child->nowcolor_left[5];child->nowcolor_left[5]=child->nowcolor_down[3];child->nowcolor_down[3]=child->nowcolor_right[5];child->nowcolor_right[5]=t3;
    }
    else if(act == 16)
    {
        int t1,t2,t3;
        t1=child->nowcolor_up[3];child->nowcolor_up[3]=child->nowcolor_right[3];child->nowcolor_right[3]=child->nowcolor_down[5];child->nowcolor_down[5]=child->nowcolor_left[3];child->nowcolor_left[3]=t1;
        t2=child->nowcolor_up[4];child->nowcolor_up[4]=child->nowcolor_right[4];child->nowcolor_right[4]=child->nowcolor_down[4];child->nowcolor_down[4]=child->nowcolor_left[4];child->nowcolor_left[4]=t2;
        t3=child->nowcolor_up[5];child->nowcolor_up[5]=child->nowcolor_right[5];child->nowcolor_right[5]=child->nowcolor_down[3];child->nowcolor_down[3]=child->nowcolor_left[5];child->nowcolor_left[5]=t3;

    }
    else if(act == 17)
    {
        int t1,t2,t3;
        t1=child->nowcolor_up[0];child->nowcolor_up[0]=child->nowcolor_left[0];child->nowcolor_left[0]=child->nowcolor_down[8];child->nowcolor_down[8]=child->nowcolor_right[0];child->nowcolor_right[0]=t1;
        t2=child->nowcolor_up[1];child->nowcolor_up[1]=child->nowcolor_left[1];child->nowcolor_left[1]=child->nowcolor_down[7];child->nowcolor_down[7]=child->nowcolor_right[1];child->nowcolor_right[1]=t2;
        t3=child->nowcolor_up[2];child->nowcolor_up[2]=child->nowcolor_left[2];child->nowcolor_left[2]=child->nowcolor_down[6];child->nowcolor_down[6]=child->nowcolor_right[2];child->nowcolor_right[2]=t3;

        int q[9]={2,5,8,1,4,7,0,3,6};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_back[i];
        for(int i=0;i<9;i++)child->nowcolor_back[i]=temp_a[q[i]];
    }
    else if(act == 18)
    {
        int t1,t2,t3;
        t1=child->nowcolor_up[0];child->nowcolor_up[0]=child->nowcolor_right[0];child->nowcolor_right[0]=child->nowcolor_down[8];child->nowcolor_down[8]=child->nowcolor_left[0];child->nowcolor_left[0]=t1;
        t2=child->nowcolor_up[1];child->nowcolor_up[1]=child->nowcolor_right[1];child->nowcolor_right[1]=child->nowcolor_down[7];child->nowcolor_down[7]=child->nowcolor_left[1];child->nowcolor_left[1]=t2;
        t3=child->nowcolor_up[2];child->nowcolor_up[2]=child->nowcolor_right[2];child->nowcolor_right[2]=child->nowcolor_down[6];child->nowcolor_down[6]=child->nowcolor_left[2];child->nowcolor_left[2]=t3;

        int q[9]={6,3,0,7,4,1,8,5,2};
        int temp_a[9];
        for(int i=0;i<9;i++)temp_a[i]=child->nowcolor_back[i];
        for(int i=0;i<9;i++)child->nowcolor_back[i]=temp_a[q[i]];
    }

}
//判断是否已完成魔方
bool isTarget(State *state)
{
    char a1 = state->nowcolor_back[0];
    for(int j=0;j<9;j++)
    {
        if(state->nowcolor_back[j]!=a1) return false;
    }

    char a2 = state->nowcolor_down[0];
    for(int j=0;j<9;j++)
    {
        if(state->nowcolor_down[j]!=a2) return false;
    }

    char a3 = state->nowcolor_front[0];
    for(int j=0;j<9;j++)
    {
        if(state->nowcolor_front[j]!=a3) return false;
    }

    char a4 = state->nowcolor_left[0];
    for(int j=0;j<9;j++)
    {
        if(state->nowcolor_left[j]!=a4) return false;
    }

    char a5 = state->nowcolor_right[0];
    for(int j=0;j<9;j++)
    {
        if(state->nowcolor_right[j]!=a5) return false;
    }

    return true;
}

//广搜
void bfs()
{
    // State *tmp = new State;
    State curState;
    while (que.empty() == 0)
    {
        //qDebug() << "enter the next round";
        curState = que.front();
        que.pop();

        //超过最大步数不再搜索
        if(curState.depth >= MAX_DEPTH) continue;

        int act;
        //对每一个动作进行扩展，然后进入队列
        for(act=1;act<=18;act++)
        {
            State *child = new State;
            expansion(child,&curState,act);//生成新状态

            //if(checkRepeat(*child)==false)
            //{
                //setRepeat(*child);

                //状态记录
                int num = (act - 1) / 2;
                char op = num + 48;

                //将到达这一步的操作存入trace
                child->trace.push_back(op);
                int code = act % 2;
                if(code==1) child->trace.push_back('+');
                else child->trace.push_back('-');

                //入队
                que.push(*child);

                //qDebug("creating child %c %d", op,code);
                //qDebug() <<  "record";
                //qDebug("the depth is %d", child->depth);
            //}

            //检查是否为目标状态
            if(isTarget(child)==true)
            {
                qDebug() <<  "succeed in solving cube！！";
                string ans;
                for (int i=0;i<child->trace.size();i++)
                {
                     ans += child->trace[i];
                     cout<<child->trace[i]<<" ";
                }
                cout<<endl;

                //存入输出的string，输出变换步骤
                input_action::do_action(ans);
                cout<<"final answer is "<<ans<<endl;
                return;
            }
            //qDebug() <<  "searching...";
        }
    }
}

void solveFunction()
{
    // 代码在此界面实现，main函数粘贴到此函数，运行后按space键直接调用，其他辅助函数粘贴到上部

    //初始化最开始的魔方状态
    State init;
    for(int i=0;i<9;i++)
    {
        init.nowcolor_back[i] = color_back[i];
        init.nowcolor_down[i] = color_down[i];
        init.nowcolor_front[i] = color_front[i];
        init.nowcolor_left[i] = color_left[i];
        init.nowcolor_right[i] = color_right[i];
        init.nowcolor_up[i] = color_up[i];
    }

    //初始化后入队
    que.push(init);
    //设置状态出现过
    setRepeat(init);

    qDebug() << "begin";

    bfs();

    //清空记录重复容器
    std::vector <State>().swap(repeat);
    //清空状态队列
    while (!que.empty()) que.pop();
    return;

    //attention:
    // 六个面颜色数据在输入界面输入
    // 六个面颜色数据分别存储在:color_up[9],color_down[9],color_front[9],color_back[9],color_left[9],color_right[9]数组中
    // 六个数组数据可直接调用，但不要更改

    // 输出动作结果调用input_action::do_action(string&)函数
    // 动作必须严格按照ppt 输出为 数字（0-8）加‘+’或‘-’其中‘+’代表正方向，‘-’代表负方向
    // 示例：
    // 1. 可以每个动作依次输出
    // s = "1+"; input_action::do_action(s);
    // 2. 也可以若干动作连续输出
    // s = "1+0-3+ 4+ 1-"; input_action::do_action(s);
    // 动作与动作之间可以存在空格，但数字后面必须紧跟‘+’或‘-’
}
