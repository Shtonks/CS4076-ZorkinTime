#include "shopInterface.h"
#include "ui_shopInterface.h"
#include "mainwindow.h"

ShopInterface::ShopInterface(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::ShopInterface)
{
    ui->setupUi(this);
    mainInterface = parent;

    int limit = mainInterface->world->shop.getTrapArrLength();
    for(int i = 0; i < limit; i++){
        mainInterface->addItem(mainInterface->world->shop.getTrap(i), ui->trapTree);
    }
}

ShopInterface::~ShopInterface()
{
    delete ui;
    ///<LUKE > dunno if these are needed????
    //delete mainInterface;
    delete selectedItem;
}

void ShopInterface::on_exit_clicked()
{
    this->close();
}

void ShopInterface::on_buy_clicked()
{
    if(ui->trapTree->selectionModel()->isSelected(ui->trapTree->currentIndex())){
        mainInterface->addPlayerItem(mainInterface->world->shop.getTrap(selectedItem->text(0).toStdString()));
    }
}


void ShopInterface::on_trapTree_itemClicked(QTreeWidgetItem *item)
{
    selectedItem = item;
    ui->itemDesc->clear();
    ui->itemDesc->appendPlainText(QString::fromStdString(mainInterface->world->shop.getTrap(item->text(0).toStdString())->getDescription()));

}
