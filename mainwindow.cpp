#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_run, &QPushButton::clicked, this, &MainWindow::run_simulation);
    connect(ui->pushButton_stop, &QPushButton::clicked, this, &MainWindow::stop_simulation);

    connect(ui->lineEdit_params, &QLineEdit::editingFinished, this, &MainWindow::update_parameter_list);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_parameter_list()
{
    // read all parameter files from the current directory
}


void MainWindow::run_simulation()
{
    QSettings settings(QString("configs/config.ini"), QSettings::IniFormat);

    this->ui->frame_params->setEnabled(false);

    // collect the list of parameters

    // run simulations
}

void MainWindow::stop_simulation()
{
    this->ui->frame_params->setEnabled(true);

    // stop simulations
}

