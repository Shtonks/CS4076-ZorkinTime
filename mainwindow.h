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

private:
    Ui::MainWindow *ui;
    World *world;
};
#endif // MAINWINDOW_H
