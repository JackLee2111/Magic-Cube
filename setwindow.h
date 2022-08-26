#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>

namespace Ui {
class SetWindow;
}

class SetWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetWindow(QWidget *parent = nullptr);
    ~SetWindow();

private slots:
    void on_pushButton_setdata_clicked();

    void on_pushButton_file_clicked();

private:
    Ui::SetWindow *ui;
};

#endif // SETWINDOW_H
