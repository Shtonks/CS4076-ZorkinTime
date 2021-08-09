#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shopInterface.h"


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
    //<LUKE> Print welcome in textDisplay
    ui->textDisplay->appendPlainText(QString::fromStdString(world->printWelcome()));

    //<ISHA> setting the range and value for BB healthbar
    ui->bossHealth->setRange(0,world->bb.getMaxHealth());
    ui->bossHealth->setValue(world->bb.getMaxHealth());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete world;
}

//<LUKE> Function to have a highlight display wherever the player currently is on the map
void MainWindow::movePlayerHighlight(){
    QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getCurrentRoomLabel()), Qt::FindDirectChildrenOnly);
    ui->playerRoom->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
    QPixmap pix(QString::fromStdString(":/Images/Direction/ZorkPics/highlight.png"));
    ui->playerRoom->setPixmap(pix);
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
        ui->textDisplay->appendPlainText("Hello darling, care to obtain some magical goods?");
        ShopInterface shopUI(this);
        shopUI.move(730, 0);
        shopUI.setModal(true);
        shopUI.exec();
    }
}

void MainWindow::addPlayerItem(Item *thing){
    try {
        if(Trap* trap = dynamic_cast<Trap*>(thing)){
            world->player.addTrap(trap);

            if(playerTrapTotal < 10){
                ui->textDisplay->appendPlainText("You receivce a " + QString::fromStdString(trap->getName()));
                addItem(thing, ui->trapTree);
                playerTrapTotal++;
            }
            else{
                ui->textDisplay->appendPlainText("You've hit your trap limit of 10");
            }
        }
        else if(Blueprint* blue = dynamic_cast<Blueprint*>(thing)){
            world->player.addBlueprint(blue);
            if(playerBlueTotal < 4){
                ui->textDisplay->appendPlainText("You receivce a " + QString::fromStdString(blue->getName()));
                addItem(thing, ui->blueprintTree);
                playerBlueTotal++;
            }
            else{
                ui->textDisplay->appendPlainText("You've hit your blueprint limit of 4");
            }
        }
    }  catch (out_of_range &oop) {
        ui->textDisplay->appendPlainText(QString::fromStdString(oop.what()));
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
        QTreeWidgetItem *item ;
        item = new QTreeWidgetItem(theTree);
        item->setText(0, QString::fromStdString(blueprint->getName()));                     //Trap Name
        item->setText(1, QString::fromStdString(blueprint->getDmgType()));                  //Dmg Type
        item->setText(2, QString::fromStdString(to_string(blueprint->getIncrease())));       //Base Dmg
        item->setText(3, QString::fromStdString(to_string(blueprint->getTimeMod())));
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
        //check room empty
        if(world->getCurrentRoom()->getTrapInRoom() == nullptr){
            //check trap selected
            if(ui->trapTree->selectionModel()->isSelected(ui->trapTree->currentIndex())){
                QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getCurrentRoomLabel()), Qt::FindDirectChildrenOnly);
                QLabel *trapName;
                for(int i = 0; i < 10; i++){
                    string trapSearchName = "trap" + std::to_string(i+1);
                    trapName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(trapSearchName), Qt::FindDirectChildrenOnly);
                    if(trapName->width() != roomName->width()){
                        //<LUKE> At this point, we def successful
                        trapName->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
                        string trapStringName = ":/Images/Direction/ZorkPics/" + selectedItem->text(0).toStdString() + ".png";
                        QPixmap pix(QString::fromStdString(trapStringName));
                        trapName->setPixmap(pix);

                        world->numMoves -= stoi(selectedItem->text(4).toStdString());
                        ui->counter->setText(QString::fromStdString(to_string(world->numMoves)));
                        ui->counter->setAlignment(Qt::AlignCenter);

                        string name = selectedItem->text(0).toStdString();
                        addItem(world->player.getTrap(name), ui->placedTrapsTree);
                        world->getCurrentRoom()->setTrapInRoom(world->shop.getTrap(name));
                        ui->textDisplay->appendPlainText("Trap added to this room: " + QString::fromStdString(world->player.getTrap(name)->getName()));
                        world->player.removeTrap(name);

                        delete selectedItem;
                        return;
                    }
                }
            }
        }else{
            TrapExists y;
            throw y;
        }
        if(world->getCurrentRoom()->getBlueprintInRoom() == nullptr){
            if(ui->blueprintTree->selectionModel()->isSelected(ui->blueprintTree->currentIndex())){
                QLabel *roomName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(world->getCurrentRoomLabel()), Qt::FindDirectChildrenOnly);
                QLabel *blueprintName;
                for(int i = 0; i < 6; i++){
                    string blueprintSearchName = "blueprint" + std::to_string(i+1);
                    blueprintName = ui->centralwidget->findChild<QLabel *>(QString::fromStdString(blueprintSearchName), Qt::FindDirectChildrenOnly);
                    if(blueprintName->width() != roomName->width()){
                        blueprintName->setGeometry(QRect(roomName->x(), roomName->y(), roomName->width(), roomName->height()));
                        string blueprintStringName = ":/Images/Direction/ZorkPics/" + selectedItem->text(0).toStdString() + ".png";
                        QPixmap pix(QString::fromStdString(blueprintStringName));
                        blueprintName->setPixmap(pix);

                        world->numMoves -= stoi(selectedItem->text(3).toStdString());
                        ui->counter->setText(QString::fromStdString(to_string(world->numMoves)));
                        ui->counter->setAlignment(Qt::AlignCenter);

                        string name = selectedItem->text(0).toStdString();
                        addItem(world->player.getBlueprint(name), ui->placedTrapsTree);
                        world->getCurrentRoom()->setBlueprintInRoom(world->shop.getBlueprint(name));
                        ui->textDisplay->appendPlainText("Blueprint added to this room: " + QString::fromStdString(world->player.getBlueprint(name)->getName()));
                        world->player.removeBlueprint(name);

                        //world->getCurrentRoom()->getBlueprintInRoom();

                        delete selectedItem;
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
        world->player.removeTrap(name);
        delete selectedItem;
        ui->textDisplay->appendPlainText("Item destroyed");
        playerTrapTotal--;
    }else if(ui->blueprintTree->selectionModel()->isSelected(ui->blueprintTree->currentIndex())){
        string name = selectedItem->text(0).toStdString();
        world->player.removeBlueprint(name);
        delete selectedItem;
        ui->textDisplay->appendPlainText("Blueprint destroyed");
        playerBlueTotal--;
    }
}

void MainWindow::on_nextTurn_clicked()
{
    world->numMoves -= 1;
    ui->counter->setText(QString::fromStdString(to_string(world->numMoves)));
    ui->counter->setAlignment(Qt::AlignCenter);
    if(world->numMoves <= 0) endSequence();
}


void MainWindow::on_trapTree_currentItemChanged(QTreeWidgetItem *current)
{
    selectedItem = current;
    ui->itemDesc->clear();
    if(current != nullptr) ui->itemDesc->appendPlainText(QString::fromStdString(world->player.getTrap(current->text(0).toStdString())->getDescription()));
}

void MainWindow::on_blueprintTree_currentItemChanged(QTreeWidgetItem *current)
{
    selectedItem = current;
}

void MainWindow::on_bossHealth_valueChanged(int value)
{
    ui->bossHealth->setValue(value);
}

void MainWindow::endSequence(){
    world->numMoves = 0;
    ui->counter->setText(QString::fromStdString(to_string(world->numMoves)));
    ui->counter->setAlignment(Qt::AlignCenter);
    ui->Down->setEnabled(false);
    ui->Left->setEnabled(false);
    ui->Right->setEnabled(false);
    ui->Up->setEnabled(false);
    ui->place->setEnabled(false);
    ui->destroy->setEnabled(false);
    ui->talk->setEnabled(false);
    ui->nextTurn->setEnabled(false);
    ui->textDisplay->appendPlainText("He has awakened.");
    ui->textDisplay->appendPlainText("He's resistant to " + QString::fromStdString(world->bb.getResistanceString()) + ". He takes half as much damage of this type.");
    ui->textDisplay->appendPlainText("He's vulnerable to " + QString::fromStdString(world->bb.getVulnerabilityString() + ". He takes twice as much damage of this type."));
    for(int i = 0; i < world->numOfRooms; i++){
        Trap* ti =  world->genRooms[i]->getTrapInRoom();
        if(ti == nullptr) continue;
        srand(time(0));
        ti->setDealtDmg();
        ti->setResistant(world->bb.getResistance());
        ti->setVulnerable(world->bb.getVulnerability());
        world->bb.takeDmg(ti->getDealtDmg());
        ui->textDisplay->appendPlainText("In room " + QString::number(i+1) +", the " + QString::fromStdString(world->genRooms[i]->getDescription()) + " and " +
                                        "the trap, " + QString::fromStdString(ti->getName()) + ", "
                                         + "dealt " + QString::number(ti->getDealtDmg()) + " " + QString::fromStdString(ti->getDmgType()) + " damage.");
        on_bossHealth_valueChanged(world->bb.getCurrHealth());
        if(world->bb.getCurrHealth() <= 0) {
            on_bossHealth_valueChanged(0);
             ui->textDisplay->appendPlainText("You manage to bring him down to 0!");
             break;
        }
        ui->textDisplay->appendPlainText("He's at " + QString::number(world->bb.getCurrHealth()) + " hp!");
    }
    (world->bb.getCurrHealth() > 0) ? ui->textDisplay->appendPlainText("Your foe still lives. He will wreak havoc onto the world. You have failed.") :
                                      ui->textDisplay->appendPlainText("You've defeated the foe! He's vanquished from the earth and you've saved the people. Congratulations!");
}
