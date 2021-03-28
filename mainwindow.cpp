#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "World.h"
#include "Character.h"
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), world(new World())
{
    ui->setupUi(this);
    QPixmap pix(":/Images/Direction/ZorkPics/pigg.jpg");
    ui->map->setPixmap(pix);
    ui->textDisplay->appendPlainText("TestyTest");
    for(int i = 0; i < 5; i++){
        ui->trapTree->resizeColumnToContents(i);
    }
    //<LUKE>temp desc
    Character player("player");
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


void MainWindow::on_Right_clicked()
{
    ui->textDisplay->appendPlainText( QString::fromStdString(world->go("East")));
}

void MainWindow::on_swordBlueprint_clicked()
{
    //addItem();
}

void MainWindow::addItem(Item *thing){
    //<LUKE> TO DO: can maybe implement a dynamic cast to identify the which Item it is (trap, blueprint, etc
    //https://stackoverflow.com/questions/351845/finding-the-type-of-an-object-in-c)
    QTreeWidgetItem *item ;
    item = new QTreeWidgetItem(ui->trapTree);
    item->setIcon(0,QIcon(":/Images/Direction/ZorkPics/pigg.jpg"));                 //icon
    item->setText(1, QString::fromStdString(thing->getName()));                     //name
    item->setText(2, QString::fromStdString(to_string(thing->getTimeMod())));       //build time
    item->setText(3, QString::fromStdString(thing->getName()));                     //dmg NOT DONE
    item->setText(4, QString::fromStdString(to_string(thing->getAmount())));        //quantity
}

