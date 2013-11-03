#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectDialog = new ConnectionDialog(this);

    connect(ui->actionConnect, SIGNAL(triggered()), connectDialog, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
