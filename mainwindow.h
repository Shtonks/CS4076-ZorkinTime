#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include "World.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Up_clicked();
    void on_Down_clicked();
    void on_Right_clicked();
    void on_swordBlueprint_clicked();
    void addItem(Item *thing, QTreeWidget *theTree);
    void on_place_clicked();

    void on_Left_clicked();

    void on_talk_clicked();

    void on_blueprintTree_itemClicked(QTreeWidgetItem *item);

    void on_trapTree_itemClicked(QTreeWidgetItem *item);

private:
    Ui::MainWindow *ui;
    World *world;
    void movePlayerHighlight();
    void addPlayerItem(Item *thing);
    QTreeWidgetItem* selectedItem;

    friend class ShopInterface;
};
#endif // MAINWINDOW_H
