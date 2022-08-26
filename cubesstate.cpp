#include "cubesstate.h"
#include <QDebug>
#include "cubes.h"
#include <QVector3D>


cubesstate::cubesstate()
{
    for(int i=0;i<27;i++)
        m_state[i/9][i%9/3][i%3]=i;
}





void cubesstate::frontCubes()
{
    for(int j=0;j<3;j++)
            for(int i=0;i<3;i++)
                r_cubes[j*3+i]=m_state[0][j][i];
}

void cubesstate::backCubes()
{
    for(int j=0;j<3;j++)
            for(int i=0;i<3;i++)
                r_cubes[j*3+i]=m_state[2][j][i];
}

void cubesstate::upCubes()
{
    for(int j=0;j<3;j++)
            for(int i=0;i<3;i++)
                r_cubes[j*3+i]=m_state[j][0][i];
}

void cubesstate::downCubes()
{
    for(int j=0;j<3;j++)
            for(int i=0;i<3;i++)
                r_cubes[j*3+i]=m_state[j][2][i];
}

void cubesstate::leftCubes()
{
    for(int j=0;j<3;j++)
            for(int i=0;i<3;i++)
                r_cubes[j*3+i]=m_state[j][i][0];
}

void cubesstate::rightCubes()
{
    for(int j=0;j<3;j++)
            for(int i=0;i<3;i++)
                r_cubes[j*3+i]=m_state[j][i][2];
}

void cubesstate::X_Cubes()
{
    for(int j=0;j<3;j++)
        for(int i=0;i<3;i++)
            r_cubes[j*3+i]=m_state[1][j][i];
}

void cubesstate::Y_Cubes()
{
    for(int j=0;j<3;j++)
        for(int i=0;i<3;i++)
            r_cubes[j*3+i]=m_state[j][1][i];
}

void cubesstate::Z_Cubes()
{
    for(int j=0;j<3;j++)
        for(int i=0;i<3;i++)
            r_cubes[j*3+i]=m_state[j][i][1];
}

void cubesstate::rotateFront(bool r)
{
    rotateZ(r,0);
    rotateV(r,0);
}

void cubesstate::rotateBack(bool r)
{
    rotateZ(!r,2);
    rotateV(r,1);
}

void cubesstate::rotateUp(bool r)
{   //true 为顺时针
    rotateY(r,0);
    rotateV(r,2);
}

void cubesstate::rotateDown(bool r)
{
    rotateY(!r,2);
    rotateV(r,3);
}

void cubesstate::rotateLeft(bool r)
{
    rotateX(r,0);
    rotateV(r,4);
}

void cubesstate::rotateRight(bool r)
{
    rotateX(!r,2);
    rotateV(r,5);
}

void cubesstate::rotateM_X(bool r)
{
    rotateZ(!r,1);
}

void cubesstate::rotateM_Y(bool r)
{
    rotateY(r,1);
}

void cubesstate::rotateM_Z(bool r)
{
    rotateX(r,1);
}

int cubesstate::rotateN(int x, bool r)
{
    switch (x)
    {
    case 0: rotateFront(r); break;
    case 1: rotateBack(r) ; break;
    case 2: rotateUp(r);    break;
    case 3: rotateDown(r);  break;
    case 4: rotateLeft(r);  break;
    case 5: rotateRight(r); break;
    default:
        break;
    }
    int i=(int)r;
    return x+!i*6;
}


void cubesstate::updateGState()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                Gm_state[i][j][k]=m_state[i][j][k];
    for(int i=0;i<27;i++)
        Gv_state[i]=v_state[i];
}

int cubesstate::cubePosition(int n)
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                if (m_state[i][j][k]==n)
                    return 9*i+3*j+k;

}

int cubesstate::cubeDirection(int n)
{
    return v_state[n];
}

int cubesstate::rVState(int i)
{
    return v_state[i];
}

int c_cal(int x,int y,int z){
    return 9*x+3*y+z;
}
QVector3D t;

void cubesstate::rotateX(bool r, int s)
{
    int i;
    if(r)
    {
        i=m_state[0][0][s];m_state[0][0][s]=m_state[0][2][s];m_state[0][2][s]=m_state[2][2][s];m_state[2][2][s]=m_state[2][0][s];m_state[2][0][s]=i;
        i=m_state[0][1][s];m_state[0][1][s]=m_state[1][2][s];m_state[1][2][s]=m_state[2][1][s];m_state[2][1][s]=m_state[1][0][s];m_state[1][0][s]=i;
    }
    else
    {
        i=m_state[0][0][s];m_state[0][0][s]=m_state[2][0][s];m_state[2][0][s]=m_state[2][2][s];m_state[2][2][s]=m_state[0][2][s];m_state[0][2][s]=i;
        i=m_state[0][1][s];m_state[0][1][s]=m_state[1][0][s];m_state[1][0][s]=m_state[2][1][s];m_state[2][1][s]=m_state[1][2][s];m_state[1][2][s]=i;
    }
}

void cubesstate::rotateY(bool r, int s)
{
    int i;
    if(r)
    {
        i=m_state[0][s][0];m_state[0][s][0]=m_state[2][s][0];m_state[2][s][0]=m_state[2][s][2];m_state[2][s][2]=m_state[0][s][2];m_state[0][s][2]=i;
        i=m_state[0][s][1];m_state[0][s][1]=m_state[1][s][0];m_state[1][s][0]=m_state[2][s][1];m_state[2][s][1]=m_state[1][s][2];m_state[1][s][2]=i;
    }
    else
    {
        i=m_state[0][s][0];m_state[0][s][0]=m_state[0][s][2];m_state[0][s][2]=m_state[2][s][2];m_state[2][s][2]=m_state[2][s][0];m_state[2][s][0]=i;
        i=m_state[0][s][1];m_state[0][s][1]=m_state[1][s][2];m_state[1][s][2]=m_state[2][s][1];m_state[2][s][1]=m_state[1][s][0];m_state[1][s][0]=i;
    }
}

void cubesstate::rotateZ(bool r, int s)
{
    int i;
    if(r)
    {
        i=m_state[s][0][0];m_state[s][0][0]=m_state[s][0][2];m_state[s][0][2]=m_state[s][2][2];m_state[s][2][2]=m_state[s][2][0];m_state[s][2][0]=i;
        i=m_state[s][0][1];m_state[s][0][1]=m_state[s][1][2];m_state[s][1][2]=m_state[s][2][1];m_state[s][2][1]=m_state[s][1][0];m_state[s][1][0]=i;
//        for(int i=0;i<6;i++){
//        t=my_color[c_cal(0,s,0)][i];my_color[c_cal(0,s,0)][i]=my_color[c_cal(0,s,2)][i];my_color[c_cal(0,s,2)][i]=my_color[c_cal(2,s,2)][i];my_color[c_cal(2,s,2)][i]=my_color[c_cal(2,s,0)][i];my_color[c_cal(2,s,0)][i]=t;
//        t=my_color[c_cal(0,s,1)][i];my_color[c_cal(0,s,1)][i]=my_color[c_cal(1,s,2)][i];my_color[c_cal(1,s,2)][i]=my_color[c_cal(2,s,1)][i];my_color[c_cal(2,s,1)][i]=my_color[c_cal(1,s,0)][i];my_color[c_cal(1,s,0)][i]=t;
//        }
    }
    else  
    {
        i=m_state[s][0][0];m_state[s][0][0]=m_state[s][2][0];m_state[s][2][0]=m_state[s][2][2];m_state[s][2][2]=m_state[s][0][2];m_state[s][0][2]=i;
        i=m_state[s][0][1];m_state[s][0][1]=m_state[s][1][0];m_state[s][1][0]=m_state[s][2][1];m_state[s][2][1]=m_state[s][1][2];m_state[s][1][2]=i;
    }
}

void cubesstate::rotateV(bool r, int f)
{
    switch (f) //0-5 前后上下左右
    {
    case 0: frontCubes(); break;
    case 1: backCubes();  break;
    case 2: upCubes();    break;
    case 3: downCubes();  break;
    case 4: leftCubes();  break;
    case 5: rightCubes(); break;
    default: break;
    }
    //qDebug() << int(r)<<int(!r) << "该面的方位";
    for(int i=0;i<9;i++)
        v_state[r_cubes[i]]=v_table[f+int(!r)*6][v_state[r_cubes[i]]];
}



