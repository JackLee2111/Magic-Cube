#include "cubes.h"

QVector3D to_my_color(Qt::GlobalColor color)
{
    QVector3D i;
    i.setX(QColor(color).redF());
    i.setY(QColor(color).greenF());
    i.setZ(QColor(color).blueF());
    return i;
}


//定义的颜色依次为 前、后、上、下、左、右
#define FR to_my_color(Qt::red)
#define BA QVector3D(230.0/255,87.0/255,5.0/255) //RGB
#define UP to_my_color(Qt::yellow)
#define DN to_my_color(Qt::white)
#define LE to_my_color(Qt::blue)
#define RI to_my_color(Qt::green)
#define DE to_my_color(Qt::white)

QVector3D my_color[27][6]=
{
    {FR,DE,UP,DE,LE,DE},{FR,DE,UP,DE,DE,DE},{FR,DE,UP,DE,DE,RI},
    {FR,DE,DE,DE,LE,DE},{FR,DE,DE,DE,DE,DE},{FR,DE,DE,DE,DE,RI},
    {FR,DE,DE,DN,LE,DE},{FR,DE,DE,DN,DE,DE},{FR,DE,DE,DN,DE,RI},

    {DE,DE,UP,DE,LE,DE},{DE,DE,UP,DE,DE,DE},{DE,DE,UP,DE,DE,RI},
    {DE,DE,DE,DE,LE,DE},{DE,DE,DE,DE,DE,DE},{DE,DE,DE,DE,DE,RI},
    {DE,DE,DE,DN,LE,DE},{DE,DE,DE,DN,DE,DE},{DE,DE,DE,DN,DE,RI},

    {DE,BA,UP,DE,LE,DE},{DE,BA,UP,DE,DE,DE},{DE,BA,UP,DE,DE,RI},
    {DE,BA,DE,DE,LE,DE},{DE,BA,DE,DE,DE,DE},{DE,BA,DE,DE,DE,RI},
    {DE,BA,DE,DN,LE,DE},{DE,BA,DE,DN,DE,DE},{DE,BA,DE,DN,DE,RI}
};
#undef FR
#undef BA
#undef UP
#undef DN
#undef LE
#undef RI
#undef DE
