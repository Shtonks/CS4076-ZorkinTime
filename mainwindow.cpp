#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "World.h"
#include "Character.h"
#include "shopInterface.h"
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), world(new World())
{
    ui->setupUi(this);

    //<LUKE> sets the initial column sizes
    for(int i = 0; i < 5; i++){
        ui->trapTree->resizeColumnToContents(i);        
    }

    //<LUKE> this assigns all the bonusDmg room colours
    for(int i = 0; i < 16; i++){
        string icon = ":/Images/Direction/ZorkPics/" + world->getGenRooms()[i]->getIcon();
        string roomSearchName;
        if(i+1 < 10) roomSearchName = "room0" + std::to_string(i+1);
        else roomSearchName = "room" + std::to_string(i+1);
        QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(roomSearchName), Qt::FindDirectChildrenOnly);
        QPixmap pix(QString::fromStdString(icon));
        roomName->setPixmap(pix);
    }
    QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getShopRoomLabel()), Qt::FindDirectChildrenOnly);
    ui->shop->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
    QPixmap pix(":/Images/Direction/ZorkPics/pigg.jpg");
    ui->shop->setPixmap(pix);




    movePlayerHighlight();
    //<LUKE> Not working, easy fix. I just have more pressing things to do rn
    world->printWelcome();
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
    }
}


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

//<LUKE> Opens the shop window
void MainWindow::on_talk_clicked()
{
    if(world->getShopRoomLabel() == world->getCurrentRoomLabel()){
        ShopInterface shopUI(this);
        shopUI.move(730, 0);
        shopUI.setModal(true);
        shopUI.exec();
    }
}

void MainWindow::on_swordBlueprint_clicked()
{
    ui->textDisplay->appendPlainText(QString::fromStdString(world->player.printTraps()));

    addPlayerItem(world->shop.getTrap("Crossbow Volley"));

    ui->textDisplay->appendPlainText(QString::fromStdString(world->player.printTraps()));
}

void MainWindow::addPlayerItem(Item *thing){
    try {
        if(Trap* trap = dynamic_cast<Trap*>(thing)) world->player.addTrap(trap);
    }  catch (out_of_range &oop) {
        ui->textDisplay->appendPlainText(QString::fromStdString(oop.what()));
    }
    addItem(thing, ui->trapTree);
    //else if(Blueprint* blueprint = dynamic_cast<Blueprint*>(thing)) world->player.addBlueprint(trap);
}

void MainWindow::addItem(Item *thing, QTreeWidget* theTree){
    //<LUKE>Dynamic cast either creates a downcast version of Item or else returns null
    //Can do just if cuz if null, null is converted to false automatically
    if(Trap* trap = dynamic_cast<Trap*>(thing)){
        QTreeWidgetItem *item ;
        item = new QTreeWidgetItem(theTree);
        item->setText(0, QString::fromStdString(trap->getName()));                     //Trap Name
        item->setText(1, QString::fromStdString(trap->getDmgType()));                  //Dmg Type
        item->setText(2, QString::fromStdString(to_string(trap->getMaxDmg())));                     //Max Dmg
        item->setText(3, QString::fromStdString(to_string(trap->getTimeMod())));       //Build Time
    }
    else if(Blueprint* blueprint = dynamic_cast<Blueprint*>(thing)){

    }
}




void MainWindow::on_place_clicked()
{
    if(world->getCurrentRoom()->getTrapInRoom() == nullptr){
        if(ui->trapTree->selectionModel()->isSelected(ui->trapTree->currentIndex())){
            QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getCurrentRoomLabel()), Qt::FindDirectChildrenOnly);
            QLabel *trapName;
            for(int i = 0; i < 10; i++){
                string trapSearchName = "trap" + std::to_string(i+1);
                trapName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(trapSearchName), Qt::FindDirectChildrenOnly);
                if(trapName->width() != roomName->width()){
                    trapName->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
                    string trapStringName = ":/Images/Direction/ZorkPics/" + selectedItem->text(0).toStdString() + ".png";
                    QPixmap pix(QString::fromStdString(":/Images/Direction/ZorkPics/spearRoom.png"));
                    trapName->setPixmap(pix);
                    ui->textDisplay->appendPlainText("Trap placed");
                }
            }
        } else if(ui->blueprintTree->selectionModel()->isSelected(ui->blueprintTree->currentIndex())){
                QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getCurrentRoomLabel()), Qt::FindDirectChildrenOnly);
                QLabel *blueprintName;
                for(int i = 0; i < 6; i++){
                    string blueprintSearchName = "blueprint" + std::to_string(i+1);
                    blueprintName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(blueprintSearchName), Qt::FindDirectChildrenOnly);
                    if(blueprintName->width() != roomName->width()){
                        blueprintName->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
                        QPixmap pix(QString::fromStdString(":/Images/Direction/ZorkPics/SwordRoom.png"));
                        blueprintName->setPixmap(pix);
                        ui->textDisplay->appendPlainText("Trap placed");
                    }
                }
         }
    }
}

void MainWindow::on_blueprintTree_itemClicked(QTreeWidgetItem *item)
{
    selectedItem = item;
}

void MainWindow::on_trapTree_itemClicked(QTreeWidgetItem *item)
{
    selectedItem = item;
}
