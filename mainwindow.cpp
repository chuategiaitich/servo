#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduino = new QSerialPort();
    arduino_is_available=false;
    arduino->setPortName("COM3");
    arduino->setBaudRate(QSerialPort::BaudRate::Baud9600);
    arduino->setParity(QSerialPort::Parity::NoParity);
    arduino->setDataBits(QSerialPort::DataBits::Data8);
    arduino->setStopBits(QSerialPort::StopBits::OneStop);
    arduino->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    arduino->open(QIODevice::ReadWrite);
    if(arduino->isOpen())
    {
        qDebug()<<"Serial Port is connected";
    }
    else
    {
        qDebug()<<"Serial Port is not connected";
    }

    // // Tìm ID kết nối COM Port
    // qDebug()<<"available port:"<<QSerialPortInfo::availablePorts().length();
    // foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    // {
    //     // Tìm vendor ID
    //     qDebug()<<"vendor id:"<<serialPortInfo.hasVendorIdentifier();
    //     if(serialPortInfo.hasVendorIdentifier())
    //     {
    //         qDebug()<<"vendor id:"<<serialPortInfo.vendorIdentifier();
    //     } //vendorID=6790

    //     // Tìm product ID
    //     qDebug()<<"product id:"<<serialPortInfo.hasProductIdentifier();
    //     if(serialPortInfo.hasProductIdentifier())
    //     {
    //         qDebug()<<"product id:"<<serialPortInfo.productIdentifier();
    //     }//productID=29987
    // }


    // foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    // {
    //     if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
    //     {
    //         if(serialPortInfo.vendorIdentifier() == arduino_uno_vendorID)
    //         {
    //             if(serialPortInfo.vendorIdentifier() == arduino_uno_productID)
    //             {
    //                 arduino_port_name=serialPortInfo.portName();
    //                 arduino_is_available=true;
    //             }
    //         }
    //     }
    // }
    // if(arduino_is_available)
    // {
    //     qDebug()<<"Serial Port is connected";
    //     arduino->setPortName(arduino_port_name);
    //     arduino->setBaudRate(QSerialPort::BaudRate::Baud9600);
    //     arduino->setParity(QSerialPort::Parity::NoParity);
    //     arduino->setDataBits(QSerialPort::DataBits::Data8);
    //     arduino->setStopBits(QSerialPort::StopBits::OneStop);
    //     arduino->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    //     arduino->open(QIODevice::ReadWrite);
    // }
    // else
    // {
    //     qDebug()<<"Serial Port is not connected";
    // }
    // connect(arduino, SIGNAL(readyRead()), this, SLOT(Read_data()));
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // if(arduino->isOpen())
    // {
    //     arduino->write(ui->lineEdit->text().toLatin1()+char(10));
    //     arduino->flush();
    // }
    Data_from_serialPort = ui->lineEdit->text();
    updateServo(Data_from_serialPort);
}
// void MainWindow::Read_data()
// {
//     if(arduino->isOpen())
//     {
//         while (arduino->bytesAvailable())
//         {
//             Data_from_serialPort += arduino->readAll();
//         }
//         if(Data_from_serialPort.at(Data_from_serialPort.length()-1)==char(10))
//         {
//             IS_Data_Reveived=true;
//         }
//         if(IS_Data_Reveived==true)
//         {
//             qDebug()<<"Data from serial port:"<<Data_from_serialPort;
//             IS_Data_Reveived=false;
//         }
//     }
// }
void MainWindow::updateServo(QString cmd)
{
    if(arduino->isWritable())
    {
        qDebug()<<cmd.toStdString().c_str();
        arduino->write(cmd.toStdString().c_str());
    }
    else
    {
        qDebug()<<"coundn't write to serial";
    }
}


