#ifndef SHOPINTERFACE_H
#define SHOPINTERFACE_H

#include <QDialog>
#include "mainwindow.h"
#include <QTreeWidgetItem>


namespace Ui {
class ShopInterface;
}

class ShopInterface : public QDialog
{
    Q_OBJECT

public:
    ShopInterface(MainWindow *parent);
    ~ShopInterface();

private slots:
    void on_exit_clicked();

    void on_buy_clicked();

    void on_trapTree_itemClicked(QTreeWidgetItem *item);

    void on_blueprintTree_itemClicked(QTreeWidgetItem *item);
private:
    Ui::ShopInterface *ui;
    MainWindow* mainInterface;
    QTreeWidgetItem* selectedItem = nullptr;
};

#endif // SHOPINTERFACE_H
