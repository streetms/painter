//
// Created by konstantin on 13.05.23.
//

#ifndef KAZ_BREKKER_MAINWINDOW_H
#define KAZ_BREKKER_MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QTimer>
#include <QResizeEvent>
#include "canvas.h"
#include "settings.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::MainWindow *ui;
    QToolBar* toolBar;
    void clearChecked(QAction* action);
    Canvas* canvas;
    QTimer* timer;
    Settings settings;
private slots:
    void slotTimer();
    void on_Exit_triggered();
    void on_Settings_triggered();
    void on_Save_as_triggered();
    void on_Open_triggered();
    void CircleAction();
    void LineAction();
    void PenAction();
    void RectangleAction();
};

#endif //KAZ_BREKKER_MAINWINDOW_H
