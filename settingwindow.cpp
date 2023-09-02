//
// Created by konstantin on 20.05.23.
//

#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QPixmap>
#include <QColorDialog>

SettingWindow::~SettingWindow() {
    delete ui;
}

SettingWindow::SettingWindow(Settings& settings,QWidget *parent) : QDialog(parent), settings(settings), ui(new Ui::SettingWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Настройки");
    QPixmap image(ui->CurrentColor->width(),ui->CurrentColor->height());
    image.fill(settings.color);
    ui->CurrentColor->setPixmap(image);
    ui->Radius->setMaximum(std::numeric_limits<int>::max());
    ui->Width->setMaximum(std::numeric_limits<int>::max());
    ui->Height->setMaximum(std::numeric_limits<int>::max());
    ui->Height->setMaximum(std::numeric_limits<int>::max());
    ui->Radius->setMinimum(1);
    ui->Height->setMinimum(1);
    ui->Width->setMinimum(1);
    ui->Pen->setMinimum(0);

    ui->Pen->setValue(settings.width);
    ui->Height->setValue(settings.RectangleHeight);
    ui->Width->setValue(settings.RectangleWidth);
    ui->Radius->setValue(settings.CircleRadius);
}


void SettingWindow::on_buttonBox_rejected() {
    this->close();
}

void SettingWindow::on_buttonBox_accepted() {
    settings.color = (ui->CurrentColor->pixmap(Qt::ReturnByValue).toImage().pixelColor(0,0));
    settings.width = (ui->Pen->value());
    settings.CircleRadius = ui->Radius->value();
    settings.RectangleHeight = ui->Height->value();
    settings.RectangleWidth = ui->Width->value();
    this->close();
}

void SettingWindow::on_ColorEdit_clicked() {
    QColor color = QColorDialog::getColor(ui->CurrentColor->pixmap(Qt::ReturnByValue).toImage().pixelColor(0,0));
    if (color.isValid()) {
        QPixmap image(ui->CurrentColor->width(),ui->CurrentColor->height());
        image.fill(color);
        ui->CurrentColor->setPixmap(image);
    }
}
