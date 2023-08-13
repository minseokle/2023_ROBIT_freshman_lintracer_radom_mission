#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsView>
#include "map.h"
#define MISSION_NUM 5
#define OBSTACLE_NUM 3

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
    void on_rand_but_clicked();
    void time_count();
    void on_copy_but_clicked();

    void on_start_but_clicked();

private:
    Ui::MainWindow *ui;
    QLabel * pos_label[MISSION_NUM];
    QLabel * mis_label[MISSION_NUM];
    map* now_map;
    map* next_map;
};
#endif // MAINWINDOW_H
