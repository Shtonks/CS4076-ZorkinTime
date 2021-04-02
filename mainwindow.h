#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void addItem(Item *thing);
    void on_placeTrap_clicked();

    void on_Left_clicked();

private:
    Ui::MainWindow *ui;
    World *world;
    void movePlayerHighlight();
};
#endif // MAINWINDOW_H
