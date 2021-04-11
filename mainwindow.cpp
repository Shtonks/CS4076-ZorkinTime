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
    //NPC Shop spawn
    QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getShopRoomLabel()), Qt::FindDirectChildrenOnly);
    ui->shop->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
    QPixmap pix(":/Images/Direction/ZorkPics/NPC-token.png");
    ui->shop->setPixmap(pix);

    //Display turn counter
    ui->counter->setText(QString::fromStdString(to_string(world->numMoves)));
    ui->counter->setAlignment(Qt::AlignCenter);

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
        on_nextTurn_clicked();
    }
}


void MainWindow::on_Down_clicked()
{
    if(world->go("South")){
        ui->textDisplay->appendPlainText(QString::fromStdString(world->getCurrentRoom()->getDescription()));
        movePlayerHighlight();
        on_nextTurn_clicked();
    }
}


void MainWindow::on_Right_clicked()
{
    if(world->go("East")){
        ui->textDisplay->appendPlainText(QString::fromStdString(world->getCurrentRoom()->getDescription()));
        movePlayerHighlight();
        on_nextTurn_clicked();
    }

}

void MainWindow::on_Left_clicked()
{
    if(world->go("West")){
        ui->textDisplay->appendPlainText(QString::fromStdString(world->getCurrentRoom()->getDescription()));
        movePlayerHighlight();
        on_nextTurn_clicked();
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
    ui->textDisplay->appendPlainText(QString::fromStdString(to_string(playerTrapTotal)));
}

void MainWindow::addPlayerItem(Item *thing){
    try {
        if(Trap* trap = dynamic_cast<Trap*>(thing)) world->player.addTrap(trap);

    }  catch (out_of_range &oop) {
        ui->textDisplay->appendPlainText(QString::fromStdString(oop.what()));
    }
    if(playerTrapTotal < 10){
        addItem(thing, ui->trapTree);
        playerTrapTotal++;
        ui->textDisplay->appendPlainText("testy eset");
    }
    else{
        ui->textDisplay->appendPlainText("You hit your trap limit, sorry my guy");
    }
}

void MainWindow::addItem(Item *thing, QTreeWidget* theTree){
    //<LUKE>Dynamic cast either creates a downcast version of Item or else returns null
    //Can do just if cuz if null, null is converted to false automatically
    if(Trap* trap = dynamic_cast<Trap*>(thing)){
        QTreeWidgetItem *item ;
        item = new QTreeWidgetItem(theTree);
        item->setText(0, QString::fromStdString(trap->getName()));                     //Trap Name
        item->setText(1, QString::fromStdString(trap->getDmgType()));                  //Dmg Type
        item->setText(2, QString::fromStdString(to_string(trap->getBaseDmg())));       //Base Dmg
        item->setText(3, QString::fromStdString(to_string(trap->getMaxDmg())));        //Max Dmg
        item->setText(4, QString::fromStdString(to_string(trap->getTimeMod())));       //Build Time
    }
    else if(Blueprint* blueprint = dynamic_cast<Blueprint*>(thing)){

    }
}


class TrapExists : public exception{
    public:
        const char * what() const throw()
        {
            return "Trap and/or magic circle already exists in this room. Cannot replace it, sorry chief";
        }
};

void MainWindow::on_place_clicked()
{
    try {
        if(world->getCurrentRoom()->getTrapInRoom() == nullptr){
            if(ui->trapTree->selectionModel()->isSelected(ui->trapTree->currentIndex())){
                QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getCurrentRoomLabel()), Qt::FindDirectChildrenOnly);
                QLabel *trapName;
                for(int i = 0; i < 10; i++){
                    string trapSearchName = "trap" + std::to_string(i+1);
                    //TEMP
                    ui->textDisplay->appendPlainText(QString::fromStdString(trapSearchName));
                    trapName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(trapSearchName), Qt::FindDirectChildrenOnly);
                    if(trapName->width() != roomName->width()){
                        //<LUKE> At this point, we def successful
                        trapName->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
                        string trapStringName = ":/Images/Direction/ZorkPics/" + selectedItem->text(0).toStdString() + ".png";
                        //TEMP
                        ui->textDisplay->appendPlainText(QString::fromStdString(trapStringName));
                        QPixmap pix(QString::fromStdString(trapStringName));
                        trapName->setPixmap(pix);
                        ui->textDisplay->appendPlainText(QString::fromStdString(world->player.printTraps()));

                        world->numMoves -= stoi(selectedItem->text(4).toStdString());
                        ui->counter->setText(QString::fromStdString(to_string(world->numMoves)));

                        ui->textDisplay->appendPlainText(selectedItem->text(0));
                        string name = selectedItem->text(0).toStdString();
                        addItem(world->player.getTrap(name), ui->placedTrapsTree);
                        world->getCurrentRoom()->setTrapInRoom(world->player.getTrap(name));
                        world->player.removeTrap(name);
                        ui->textDisplay->appendPlainText(QString::fromStdString(world->player.printTraps()));

                        delete selectedItem;
                        return;
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
                            return;
                        }
                    }
             }
        }else{
            TrapExists x;
            throw x;
        }
    }
    catch (const TrapExists& e) {
        ui->textDisplay->appendPlainText(e.what());
    }
}



void MainWindow::on_blueprintTree_itemClicked(QTreeWidgetItem *item)
{
    selectedItem = item;
}

void MainWindow::on_trapTree_itemClicked(QTreeWidgetItem *item)
{
    selectedItem = item;
    ui->itemDesc->clear();
    ui->itemDesc->appendPlainText(QString::fromStdString(world->player.getTrap(item->text(0).toStdString())->getDescription()));
}

void MainWindow::on_quit_clicked()
{
    this->close();
}

void MainWindow::on_destroy_clicked()
{
    if(ui->trapTree->selectionModel()->isSelected(ui->trapTree->currentIndex())){
        string name = selectedItem->text(0).toStdString();
        ui->textDisplay->appendPlainText(QString::fromStdString(world->player.printTraps()));
        world->player.removeTrap(name);
        ui->textDisplay->appendPlainText(QString::fromStdString(world->player.printTraps()));
        delete selectedItem;
        ui->textDisplay->appendPlainText("Item destroyed");
        playerTrapTotal--;
    }
}

inline void MainWindow::on_nextTurn_clicked()
{
    world->numMoves -= 1;
    ui->counter->setText(QString::fromStdString(to_string(world->numMoves)));
}


void MainWindow::on_trapTree_currentItemChanged(QTreeWidgetItem *current)
{
    selectedItem = current;
    ui->itemDesc->clear();
    if(current != nullptr) ui->itemDesc->appendPlainText(QString::fromStdString(world->player.getTrap(current->text(0).toStdString())->getDescription()));
}
