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
/*
    QPixmap pix(":/Images/Direction/ZorkPics/map.png");
    int w = ui->map->width();
    int h = ui->map->height();
    ui->map->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    */

    ui->textDisplay->appendPlainText("TestyTest");
    for(int i = 0; i < 5; i++){
        ui->trapTree->resizeColumnToContents(i);        
    }

    //<LUKE> this assigns all the bonusDmg room colours appropriately
    for(int i = 0; i < 16; i++){
        string icon = ":/Images/Direction/ZorkPics/" + world->getGenRooms()[i]->getIcon();
        string roomSearchName;
        if(i+1 < 10) roomSearchName = "room0" + std::to_string(i+1);
        else roomSearchName = "room" + std::to_string(i+1);
        QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(roomSearchName), Qt::FindDirectChildrenOnly);
        QPixmap pix(QString::fromStdString(icon));
        roomName->setPixmap(pix);
    }

    movePlayerHighlight();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//<LUKE> Function to have a highlight display wherever the player currently is on the map
void MainWindow::movePlayerHighlight(){
    QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getCurrentRoomLabel()), Qt::FindDirectChildrenOnly);
    ui->playerRoom->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
    QPixmap pix(QString::fromStdString(":/Images/Direction/ZorkPics/highlight.png"));
    ui->playerRoom->setPixmap(pix);
    ui->textDisplay->appendPlainText(QString::fromStdString(world->getCurrentRoomLabel()));

}


void MainWindow::on_Up_clicked()
{
    if(world->go("North")){
        ui->textDisplay->appendPlainText(QString::fromStdString(world->getCurrentRoom()->getDescription()));
        movePlayerHighlight();
    }
}


void MainWindow::on_Down_clicked()
{
    if(world->go("South")){
        ui->textDisplay->appendPlainText(QString::fromStdString(world->getCurrentRoom()->getDescription()));
        movePlayerHighlight();
    }}


void MainWindow::on_Right_clicked()
{
    if(world->go("East")){
        ui->textDisplay->appendPlainText(QString::fromStdString(world->getCurrentRoom()->getDescription()));
        movePlayerHighlight();
    }
}

void MainWindow::on_Left_clicked()
{
    if(world->go("West")){
        ui->textDisplay->appendPlainText(QString::fromStdString(world->getCurrentRoom()->getDescription()));
        movePlayerHighlight();
    }
}

void MainWindow::on_swordBlueprint_clicked()
{
    //addItem();
}

//<LUKE> Can make this a template function

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


void MainWindow::on_placeTrap_clicked()
{/*
    //if something is selecetd
    if(ui->trapTree->selectionModel()->isSelected(ui->trapTree->currentIndex())){
        world->currentRoom->placeTrap(world->player.getInventorySlot(1));
        //world->getCurrentRoom()->placeTrap(world->player.getInventorySlot(ui->trapTree->currentIndex().row));
        cout<<"trap placed";
    }
    */
}


