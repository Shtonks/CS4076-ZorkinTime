#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QPixmap>

#include "World.h"
#include "Character.h"

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
    void addItem(Item *thing, QTreeWidget *theTree);
    void on_place_clicked();

    void on_Left_clicked();

    void on_talk_clicked();

    void on_blueprintTree_itemClicked(QTreeWidgetItem *item);

    void on_trapTree_itemClicked(QTreeWidgetItem *item);

    void on_quit_clicked();

    void on_destroy_clicked();

    void on_nextTurn_clicked();

    void on_trapTree_currentItemChanged(QTreeWidgetItem *current);

    void on_blueprintTree_currentItemChanged(QTreeWidgetItem *current);

    void on_bossHealth_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    World *world;
    void movePlayerHighlight();
    void addPlayerItem(Item *thing);
    void endSequence();
    QTreeWidgetItem* selectedItem;
    int playerTrapTotal = 0;
    int playerBlueTotal = 0;

    friend class ShopInterface;
};
#endif // MAINWINDOW_H
