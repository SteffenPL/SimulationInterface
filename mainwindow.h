#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QProcess>

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
    void open_parameter_dir();
    void update_parameter_list();

    void update_variables_list();

    void run_simulation();
    void stop_simulation();

    void open_output_dir();

    void load_current_script();
    void save_current_script();


private:
    Ui::MainWindow *ui;
    QSettings m_settings;

    QMap<QString,QString> m_variables;

    QList<QProcess> m_processes;

};

#endif // MAINWINDOW_H
