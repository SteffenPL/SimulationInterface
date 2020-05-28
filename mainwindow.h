#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void update_parameter_list();

    void run_simulation();
    void stop_simulation();




private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
