#ifndef CUBESSTATE_H
#define CUBESSTATE_H
#include <QQueue>


class cubesstate
{
public:
    cubesstate();
    void frontCubes();
    void backCubes();
    void upCubes();
    void downCubes();
    void leftCubes();
    void rightCubes();
    void X_Cubes();
    void Y_Cubes();
    void Z_Cubes();

    void rotateFront(bool r);
    void rotateBack(bool r);
    void rotateUp(bool r);
    void rotateDown(bool r); 
    void rotateLeft(bool r);
    void rotateRight(bool r);
    void rotateM_X(bool r);
    void rotateM_Y(bool r);
    void rotateM_Z(bool r);

    int  rotateN(int x, bool r);

    void updateGState();

    int cubePosition(int n);
    int cubeDirection(int n);

    int rVState(int i);

    int r_cubes[9];

    int Gm_state[3][3][3];
    int Gv_state[27];

    QQueue <int> s_answer;
    int m_state[3][3][3]; //放到protected
private:
    void rotateX(bool r, int s);
    void rotateY(bool r, int s);
    void rotateZ(bool r, int s);
    void rotateV(bool r, int f);



    int v_state[27]={2,2,2, 4,0,0, 4,0,0,  2,2,2, 4,0,5, 4,3,5,  2,2,2, 1,1,5, 1,1,5};
    int v_table[12][6]={ {0,1,4,5,3,2},
                        {0,1,5,4,2,3},
                        {5,4,2,3,0,1},
                        {4,5,2,3,1,0},
                        {2,3,1,0,4,5},
                        {3,2,0,1,4,5},

                        {0,1,5,4,2,3},
                        {0,1,4,5,3,2},
                        {4,5,2,3,1,0},
                        {5,4,2,3,0,1},
                        {3,2,0,1,4,5},
                        {2,3,1,0,4,5}
                        };

};

#endif // CUBES_STATE_H
