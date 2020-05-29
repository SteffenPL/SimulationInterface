#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_settings("./scripts.ini", QSettings::IniFormat)
{
    ui->setupUi(this);


    // load scripts
    auto scripts = m_settings.childKeys();
    ui->comboBox_script_name->addItems(scripts);
    ui->comboBox_script_selection->addItems(scripts);
    load_current_script();


    // load variables
    m_settings.beginGroup("Variables");
    auto variables_keys = m_settings.childKeys();
    foreach(QString key, variables_keys)
    {
        m_variables["$" + key] = m_settings.value(key).toString();
    }
    m_settings.endGroup();




    // load defaults
    this->ui->lineEdit_params->setText( m_settings.value("Config/param_dir",".").toString() );
    this->ui->lineEdit_outdir->setText( m_settings.value("Config/output_dir",".").toString() );

    update_parameter_list();
    update_variables_list();


    connect(ui->pushButton_run, &QPushButton::clicked, this, &MainWindow::run_simulation);
    connect(ui->pushButton_stop, &QPushButton::clicked, this, &MainWindow::stop_simulation);

    connect(ui->lineEdit_params, &QLineEdit::editingFinished, this, &MainWindow::update_parameter_list);
    connect(ui->pushButton_params, &QPushButton::clicked, this, &MainWindow::open_parameter_dir);
    connect(ui->pushButton_outdir, &QPushButton::clicked, this, &MainWindow::open_output_dir);

    connect(ui->comboBox_script_name, &QComboBox::currentTextChanged, this, &MainWindow::load_current_script);
    connect(ui->pushButton_save_script, &QPushButton::clicked, this, &MainWindow::save_current_script);

    connect(ui->listWidget_params, &QListWidget::itemSelectionChanged, this, &MainWindow::update_variables_list);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_parameter_dir()
{
    QDir directory = QFileDialog::getExistingDirectory(this, tr("select parameter directory"));
    this->ui->lineEdit_params->setText( directory.absolutePath() );
    update_parameter_list();
}

void MainWindow::update_parameter_list()
{
    // read all parameter files from the current directory

    QDir directory(this->ui->lineEdit_params->text());
    if( directory.exists() )
    {
        QStringList parameter_files = directory.entryList(QStringList() << "*.xlsx", QDir::Files);

        this->ui->listWidget_params->clear();
        foreach(QString parameter_file, parameter_files)
        {
            this->ui->listWidget_params->addItem(parameter_file);
        }
    }
    this->ui->listWidget_params->selectAll();

    update_variables_list();
}

namespace{
void add_row(QTableWidget* table, const QString& key, const QString& value)
{
    table->insertRow(table->rowCount());
    table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(key));
    table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(value));
}

}

void MainWindow::update_variables_list()
{
    this->ui->tableWidget_vars->setRowCount(0);

    auto end = m_variables.cend();
    for(auto it = m_variables.cbegin(); it != end; ++it) {
        add_row(this->ui->tableWidget_vars, it.key(), it.value() );
    }

    add_row(this->ui->tableWidget_vars, "$param_dir", this->ui->lineEdit_params->text() );
    add_row(this->ui->tableWidget_vars, "$output_dir", this->ui->lineEdit_outdir->text() );


    int idx = 0;
    foreach(auto parameter_file, this->ui->listWidget_params->selectedItems())
    {
        add_row(this->ui->tableWidget_vars, "$parameter_file[" + QString::number(idx++) + "]", parameter_file->text() );
    }
}


void MainWindow::open_output_dir()
{
    QDir directory = QFileDialog::getExistingDirectory(this, tr("select output directory"));
    this->ui->lineEdit_outdir->setText( directory.absolutePath() );
}

void MainWindow::load_current_script()
{
    this->ui->plainTextEdit_script->setPlainText(m_settings.value(this->ui->comboBox_script_name->currentText(), "").toString());
}

void MainWindow::save_current_script()
{
    m_settings.setValue(this->ui->comboBox_script_name->currentText(), this->ui->plainTextEdit_script->toPlainText());
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

