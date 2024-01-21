#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void on_pushButton_clicked();
    void updateServo(QString cmd);

private:
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendorID = 6790;
    static const quint16 arduino_uno_productID = 29987;
    QString arduino_port_name;
    bool arduino_is_available;
    Ui::MainWindow *ui;
    QString defaulteagle;
    QString Data_from_serialPort;
    bool IS_Data_Reveived=false;
};
#endif // MAINWINDOW_H
