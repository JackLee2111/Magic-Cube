#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include <QMainWindow>


namespace Ui {
class input_action;
}

class input_action : public QMainWindow
{
    Q_OBJECT

public:
    explicit input_action(QWidget *parent = nullptr);
    static void do_action(std::string &action);
    static void create_R_action();
    ~input_action();

private slots:
    void on_button_action_clicked();

private:
    Ui::input_action *ui;
};

#endif // INPUT_ACTION_H
