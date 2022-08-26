#ifndef CUBES_H
#define CUBES_H

#include <QVector3D>
#include <QColor>
#include "vertex.h"
#include "window.h"

QVector3D to_my_color(Qt::GlobalColor color);

extern QVector3D my_color[27][6];
#endif // CUBES_H
