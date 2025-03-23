#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QDebug>

#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include "socketcan_cpp.h"
#include <fcntl.h>    // O_RDWR
#include <signal.h>
#include <unistd.h>   // exit

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openCANPort();
    void sendCANMessage();
    void receiveCANMessage();
    void receiveAnemometervalue();
    void receiveTemperaturevalue();
    void receiveHumidityvalue();
    void receiveRangevalue();
    void receivePressurevalue();
    void receiveLuminosityvalue();

public slots:

    void onButSendClicked();
    void Motor_On();
    void Motor_Off();
    void Motor_Auto();
    void Switch_Luminosity();
    void Switch_Distance();
    void onTimer_Tick();

private:

    scpp::SocketCan socket_can;

     Ui::MainWindow  *ui;
     QGridLayout     *m_layout;
     QPushButton     *but_send;
     QPushButton     *motor_on;
     QPushButton     *motor_off;
     QPushButton     *motor_auto;
     QPushButton     *switch_lum;
     QPushButton     *switch_dis;
     QLineEdit       *receive_box_0,*receive_box_1,*receive_box_2,*receive_box_3 ;
     QLineEdit       *receive_box_4,*receive_box_5,*receive_box_6,*receive_box_7 ;
     QLineEdit       *send_box_0, *send_box_1,*send_box_2,*send_box_3;
     QLineEdit       *send_box_4, *send_box_5,*send_box_6,*send_box_7;
     QLineEdit       *anemometre_value_box;
     QLineEdit       *temperature_value_box;
     QLineEdit       *humidity_value_box;
     QLineEdit       *range_value_box;
     QLineEdit       *pressure_value_box;
     QLineEdit       *luminosity_value_box;

    QTimer *timer_tick;
};

#endif // MAINWINDOW_H
