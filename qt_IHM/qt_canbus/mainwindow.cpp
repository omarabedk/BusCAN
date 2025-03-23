#include "mainwindow.h"
#include "ui_mainwindow.h"

//===============================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QWidget *zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    but_send = new QPushButton("Send Message");
    motor_on = new QPushButton("Motor On");
    motor_off = new QPushButton("Motor Off");
    motor_auto = new QPushButton("Motor Auto");
    switch_lum = new QPushButton("Switch Luminosité");
    switch_dis = new QPushButton("Switch Distance");
    m_layout = new QGridLayout();

    QLabel *label_to_send = new QLabel;
    label_to_send->setText("Message to Send");
    QLabel *label_received = new QLabel;
    label_received->setText("Message Received");
    QLabel *label_anemometre = new QLabel;
    label_anemometre->setText("Valeur de l'anemometre");
    QLabel *label_temperature = new QLabel;
    label_temperature->setText("Valeur de la temperature");
    QLabel *label_humidity = new QLabel;
    label_humidity->setText("Valeur de l'humidité");
    QLabel *label_range = new QLabel;
    label_range->setText("Valeur de la distance");
    QLabel *label_pressure = new QLabel;
    label_pressure->setText("Valeur de la pression");
    QLabel *label_luminosity = new QLabel;
    label_luminosity->setText("Valeur de la luminosité");

    send_box_0 = new QLineEdit();
    send_box_1 = new QLineEdit();
    send_box_2 = new QLineEdit();
    send_box_3 = new QLineEdit();
    send_box_4 = new QLineEdit();
    send_box_5 = new QLineEdit();
    send_box_6 = new QLineEdit();
    send_box_7 = new QLineEdit();

    receive_box_0 = new QLineEdit();
    receive_box_1 = new QLineEdit();
    receive_box_2 = new QLineEdit();
    receive_box_3 = new QLineEdit();
    receive_box_4 = new QLineEdit();
    receive_box_5 = new QLineEdit();
    receive_box_6 = new QLineEdit();
    receive_box_7 = new QLineEdit();

    anemometre_value_box = new QLineEdit();
    temperature_value_box = new QLineEdit();
    humidity_value_box = new QLineEdit();
    range_value_box = new QLineEdit();
    pressure_value_box = new QLineEdit();
    luminosity_value_box = new QLineEdit();

    m_layout->addWidget(label_to_send,0,1);
    m_layout->addWidget(label_anemometre,5,1);
    m_layout->addWidget(label_temperature,5,2);
    m_layout->addWidget(label_humidity,5,3);
    m_layout->addWidget(label_range,5,4);
    m_layout->addWidget(label_pressure,5,5);
    m_layout->addWidget(label_luminosity,5,6);

    m_layout->addWidget(but_send,1,0);
    m_layout->addWidget(motor_on,4,1);
    m_layout->addWidget(motor_off,4,2);
    m_layout->addWidget(motor_auto,4,3);
    m_layout->addWidget(switch_lum,4,4);
    m_layout->addWidget(switch_dis,4,5);

    m_layout->addWidget(send_box_7,1,1);
    m_layout->addWidget(send_box_6,1,2);
    m_layout->addWidget(send_box_5,1,3);
    m_layout->addWidget(send_box_4,1,4);
    m_layout->addWidget(send_box_3,1,5);
    m_layout->addWidget(send_box_2,1,6);
    m_layout->addWidget(send_box_1,1,7);
    m_layout->addWidget(send_box_0,1,8);

    m_layout->addWidget(label_received,2,1);

    m_layout->addWidget(receive_box_7,3,1);
    m_layout->addWidget(receive_box_6,3,2);
    m_layout->addWidget(receive_box_5,3,3);
    m_layout->addWidget(receive_box_4,3,4);
    m_layout->addWidget(receive_box_3,3,5);
    m_layout->addWidget(receive_box_2,3,6);
    m_layout->addWidget(receive_box_1,3,7);
    m_layout->addWidget(receive_box_0,3,8);

    m_layout->addWidget(anemometre_value_box,6,1);
    m_layout->addWidget(temperature_value_box,6,2);
    m_layout->addWidget(humidity_value_box,6,3);
    m_layout->addWidget(range_value_box,6,4);
    m_layout->addWidget(pressure_value_box,6,5);
    m_layout->addWidget(luminosity_value_box,6,6);

    zoneCentrale->setLayout(m_layout);

    openCANPort();

    timer_tick = new QTimer();

    connect( timer_tick, SIGNAL(timeout()), this, SLOT(onTimer_Tick()));
    connect(motor_off,SIGNAL(clicked()),this,SLOT(Motor_Off()));
    connect(motor_auto,SIGNAL(clicked()),this,SLOT(Motor_Auto()));
    connect(motor_on,SIGNAL(clicked()),this,SLOT(Motor_On()));
    connect(switch_lum,SIGNAL(clicked()),this,SLOT(Switch_Luminosity()));
    connect(switch_dis,SIGNAL(clicked()),this,SLOT(Switch_Distance()));
    connect(but_send,SIGNAL(clicked()),this,SLOT(onButSendClicked()));

     timer_tick -> start(1); // in ms
}
//===============================================================

MainWindow::~MainWindow()
{
    delete ui;
}

//===============================================================
void MainWindow::openCANPort()
{

    if (socket_can.open("can0") == scpp::STATUS_OK)
    {
         printf("can socket opened");
    }
    else
    {
        printf("Cannot open can socket!");
    }

}
//===============================================================
void MainWindow::onButSendClicked()
{
    sendCANMessage();
}
//===============================================================
void MainWindow::sendCANMessage()
{
    scpp::CanFrame frame_to_write;

    frame_to_write.id     =   0x4;
    frame_to_write.len     =   8;

    frame_to_write.data[0] =   send_box_0->text().toInt();
    frame_to_write.data[1] =   send_box_1->text().toInt();
    frame_to_write.data[2] =   send_box_2->text().toInt();
    frame_to_write.data[3] =   send_box_3->text().toInt();
    frame_to_write.data[4] =   send_box_4->text().toInt();
    frame_to_write.data[5] =   send_box_5->text().toInt();
    frame_to_write.data[6] =   send_box_6->text().toInt();
    frame_to_write.data[7] =   send_box_7->text().toInt();

    socket_can.write(frame_to_write);
}
//===============================================================
void MainWindow::receiveCANMessage()
{

 scpp::CanFrame fr;

    if(socket_can.read(fr) == scpp::STATUS_OK)
	{
		receive_box_0->setText(QString::number((uint)fr.data[0]));
		receive_box_1->setText(QString::number((uint)fr.data[1]));
		receive_box_2->setText(QString::number((uint)fr.data[2]));
		receive_box_3->setText(QString::number((uint)fr.data[3]));
		receive_box_4->setText(QString::number((uint)fr.data[4]));
		receive_box_5->setText(QString::number((uint)fr.data[5]));
		receive_box_6->setText(QString::number((uint)fr.data[6]));
		receive_box_7->setText(QString::number((uint)fr.data[7]));
	}

}
//===============================================================

void MainWindow::onTimer_Tick()
{
receiveCANMessage();
receiveAnemometervalue();
receiveTemperaturevalue();
receiveHumidityvalue();
receiveRangevalue();
receivePressurevalue();
receiveLuminosityvalue();
}

void MainWindow::Motor_On()
{
    scpp::CanFrame frame_to_write;

    frame_to_write.id     =   0x4;
    frame_to_write.len     =   8;

    frame_to_write.data[0] =   1;
    frame_to_write.data[1] =   0;
    frame_to_write.data[2] =   0;
    frame_to_write.data[3] =   0;
    frame_to_write.data[4] =   0;
    frame_to_write.data[5] =   0;
    frame_to_write.data[6] =   0;
    frame_to_write.data[7] =   0;

    socket_can.write(frame_to_write);
}

void MainWindow::Motor_Off()
{
    scpp::CanFrame frame_to_write;

    frame_to_write.id     =   0x4;
    frame_to_write.len     =   8;

    frame_to_write.data[0] =   0;
    frame_to_write.data[1] =   0;
    frame_to_write.data[2] =   0;
    frame_to_write.data[3] =   0;
    frame_to_write.data[4] =   0;
    frame_to_write.data[5] =   0;
    frame_to_write.data[6] =   0;
    frame_to_write.data[7] =   0;

    socket_can.write(frame_to_write);
}

void MainWindow::Motor_Auto()
{
    scpp::CanFrame frame_to_write;

    frame_to_write.id     =   0x4;
    frame_to_write.len     =   8;

    frame_to_write.data[0] =   2;
    frame_to_write.data[1] =   0;
    frame_to_write.data[2] =   0;
    frame_to_write.data[3] =   0;
    frame_to_write.data[4] =   0;
    frame_to_write.data[5] =   0;
    frame_to_write.data[6] =   0;
    frame_to_write.data[7] =   0;

    socket_can.write(frame_to_write);
}

//==========================================================

void MainWindow::receiveAnemometervalue()
{
 scpp::CanFrame fr;

    if(socket_can.read(fr) == scpp::STATUS_OK  && fr.id == 0x55)
    {
        uint16_t received_speed = (fr.data[1] << 8) | fr.data[0];
        anemometre_value_box->setText(QString::number((uint)received_speed));
    }
}


void MainWindow::receiveTemperaturevalue()
{
    scpp::CanFrame fr;

       if(socket_can.read(fr) == scpp::STATUS_OK && fr.id == 0x56)
       {

           uint16_t received_temp = (fr.data[1] << 8) | fr.data[0];
           temperature_value_box->setText(QString::number((uint)received_temp));

       }
}


void MainWindow::receiveHumidityvalue()
{
    scpp::CanFrame fr;

       if(socket_can.read(fr) == scpp::STATUS_OK && fr.id == 0x57)
       {

           uint16_t received_hum = (fr.data[1] << 8) | fr.data[0];
           humidity_value_box->setText(QString::number((uint)received_hum));

       }
}

void MainWindow::receiveRangevalue()
{
    scpp::CanFrame fr;

       if(socket_can.read(fr) == scpp::STATUS_OK && fr.id == 0x58)
       {

           uint16_t received_range = (fr.data[1] << 8) | fr.data[0];
           range_value_box->setText(QString::number((uint)received_range));

       }
}

void MainWindow::receivePressurevalue()
{
    scpp::CanFrame fr;

       if(socket_can.read(fr) == scpp::STATUS_OK && fr.id == 0x59)
       {

           uint16_t received_pressure = (fr.data[1] << 8) | fr.data[0];
           pressure_value_box->setText(QString::number((uint)received_pressure));

       }
}

void MainWindow::receiveLuminosityvalue()
{
    scpp::CanFrame fr;

       if(socket_can.read(fr) == scpp::STATUS_OK && fr.id == 0x60)
       {

           uint16_t received_lum = (fr.data[1] << 8) | fr.data[0];
           luminosity_value_box->setText(QString::number((uint)received_lum));

       }
}


void MainWindow::Switch_Luminosity()
{
    scpp::CanFrame frame_to_write;

    frame_to_write.id     =   0x4;
    frame_to_write.len     =   8;

    frame_to_write.data[0] =   3;
    frame_to_write.data[1] =   0;
    frame_to_write.data[2] =   0;
    frame_to_write.data[3] =   0;
    frame_to_write.data[4] =   0;
    frame_to_write.data[5] =   0;
    frame_to_write.data[6] =   0;
    frame_to_write.data[7] =   0;

    socket_can.write(frame_to_write);
}



void MainWindow::Switch_Distance()
{
    scpp::CanFrame frame_to_write;

    frame_to_write.id     =   0x4;
    frame_to_write.len     =   8;

    frame_to_write.data[0] =   4;
    frame_to_write.data[1] =   0;
    frame_to_write.data[2] =   0;
    frame_to_write.data[3] =   0;
    frame_to_write.data[4] =   0;
    frame_to_write.data[5] =   0;
    frame_to_write.data[6] =   0;
    frame_to_write.data[7] =   0;

    socket_can.write(frame_to_write);
}
