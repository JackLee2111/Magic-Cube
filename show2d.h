#ifndef SHOW2D_H
#define SHOW2D_H

#include <QWidget>

namespace Ui {
class show2D;
}

class show2D : public QWidget
{
    Q_OBJECT

public:
    explicit show2D(QWidget *parent = nullptr);
    ~show2D();

private:
    Ui::show2D *ui;
};

#endif // SHOW2D_H
