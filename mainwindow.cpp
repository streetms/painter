//
// Created by konstantin on 13.05.23.
//
#include "canvas.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingwindow.h"
#include <QRect>
#include <QToolBar>

#include <QPainter>
#include <iostream>
#include <QFileDialog>
#include <QPainterPath>
#define CIRCLE 1
#define LINE 2
#define RECT 3
#define POINT 4
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const char* filename = "settings.dat";
    FILE* file = fopen(filename, "r");
    if (file != nullptr) {
        fread(&settings, sizeof(settings), 1, file);
        fclose(file);
    } else{
        settings.width= 5;
        settings.color = Qt::red;
        settings.CircleRadius = 50;
        settings.RectangleHeight = 150;
        settings.RectangleWidth = 150;
    }
    toolBar = new QToolBar(this);
    toolBar->addAction(QPixmap(":/icons/circle.png"),"окружность",this,SLOT(CircleAction()));
    toolBar->addAction(QPixmap(":/icons/rectangle.png"),"прямоугольник",this,SLOT(RectangleAction()));
    toolBar->addAction(QPixmap(":/icons/line.png"),"линия",this,SLOT(LineAction()));
    toolBar->addAction(QPixmap(":/icons/pen.png"),"рисование от руки",this,SLOT(PenAction()));
    for (auto action : toolBar->actions()){
        action->setCheckable(true);
    }
    addToolBar(Qt::LeftToolBarArea,toolBar);
    canvas = new Canvas(settings);
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(slotTimer()));
    ui->graphicsView->setScene(canvas);
    timer->start(100);
    canvas->addRect(100,100,100,100,QPen(Qt::red));
}

MainWindow::~MainWindow() {
    delete ui;
    delete timer;
}

void MainWindow::clearChecked(QAction *action) {
    for (auto _action : toolBar->actions()){
        if (_action != action){
            _action->setChecked(false);
        }
    }
}
void MainWindow::CircleAction() {
    clearChecked((QAction*)sender());
    ui->statusbar->showMessage("Окружность");
    canvas->setDrawMode(Canvas::DrawMode::Circle);
}

void MainWindow::LineAction() {
    clearChecked((QAction*)sender());
    ui->statusbar->showMessage("Линия");
    canvas->setDrawMode(Canvas::DrawMode::Line);
}

void MainWindow::PenAction() {
    clearChecked((QAction*)sender());
    ui->statusbar->showMessage("перо");
    canvas->setDrawMode(Canvas::DrawMode::Pen);
}

void MainWindow::RectangleAction() {
    clearChecked((QAction*)sender());
    ui->statusbar->showMessage("Прямоугольник");
    canvas->setDrawMode(Canvas::DrawMode::Rect);
}

void MainWindow::on_Exit_triggered() {
    this->close();
}

void MainWindow::on_Settings_triggered() {
    SettingWindow settingWindow(settings);
    settingWindow.exec();
}

void MainWindow::slotTimer() {
    timer->stop();
    canvas->setSceneRect(0,0,ui->graphicsView->width()-20,ui->graphicsView->height()-20);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    const char* filename = "settings.dat";
    FILE* file = fopen(filename, "w");
    fwrite(&settings, sizeof(settings), 1, file);
    fclose(file);
    this->close();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    canvas->setSceneRect(0,0,ui->graphicsView->width()-20,ui->graphicsView->height()-20);

    double X = double(event->size().width())/event->oldSize().width();
    double Y = double (event->size().height())/event->oldSize().height();

    for (auto figure : canvas->figures){
        figure->setTransform(figure->transform()*QTransform::fromScale(X,Y));
        //figure->shape();
    }
    std::cout << canvas->figures.size() << "\n";
}

void MainWindow::on_Save_as_triggered() {
    QString path = QFileDialog::getSaveFileName(nullptr, "сохранение файла", "", "");
    if (not path.isEmpty()){
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::WriteOnly);
        QDataStream stream(&file);
        stream << canvas->paths.size();
        std::cout << canvas->paths.size() << "\n";
        for (auto& figure : canvas->paths){
            stream << *(figure.first) << figure.second;
        }
        file.close();
    }
}

void MainWindow::on_Open_triggered() {
    QString path = QFileDialog::getOpenFileName(nullptr,"выбор файла", "", "");
    if (not path.isEmpty()){
        for (auto figure : canvas->figures){
            delete figure;
        }
        canvas->figures.clear();
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::ReadOnly);
        QDataStream stream(&file);
        int N;
        stream >> N;
        std::cout << N << "\n";
        for (int i = 0; i < N;i++){
            QPainterPath* t = new QPainterPath;
            QPen pen;
            stream >> *t >> pen;
            this->canvas->addPath(*t,pen);
            this->canvas->paths.push_back(std::pair(t,pen));
            this->canvas->figures += this->canvas->items(*t);
        }
        file.close();
    }
}

