//
// Created by konstantin on 20.05.23.
//

#ifndef KAZ_BREKKER_SETTINGWINDOW_H
#define KAZ_BREKKER_SETTINGWINDOW_H
#include <QDialog>
#include "settings.h"
QT_BEGIN_NAMESPACE
namespace Ui { class SettingWindow; }
QT_END_NAMESPACE
class SettingWindow : public QDialog {
Q_OBJECT
public:
    explicit SettingWindow(Settings& sttings,QWidget *parent = nullptr);
    ~SettingWindow() override;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_ColorEdit_clicked();
private:
    Settings& settings;
    Ui::SettingWindow *ui;
};


#endif //KAZ_BREKKER_SETTINGWINDOW_H
