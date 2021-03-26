#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "World.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), world(new World())
{
    ui->setupUi(this);
    QPixmap pix(":/Images/Direction/ZorkPics/pigg.jpg");
    ui->map->setPixmap(pix);
    ui->textDisplay->appendPlainText("TestyTest");

    world->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Up_clicked()
{
    ui->textDisplay->appendPlainText( QString::fromStdString(world->go("North")));
}


void MainWindow::on_Down_clicked()
{
    ui->textDisplay->appendPlainText( QString::fromStdString(world->go("South")));
}

