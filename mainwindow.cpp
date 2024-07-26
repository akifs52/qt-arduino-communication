#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->normal->hide();
    ui->frame->hide();
    ui->sidemin->hide();
    ui->label_7->hide();
    ui->label_9->hide();
    ui->label_8->hide();

    arduino = new QSerialPort();
    arduinoPortName = "";
    arduinoAvailable = false;

    foreach(const QSerialPortInfo &serialPortInfo,QSerialPortInfo::availablePorts())
    {
        qDebug()<< "Has Vendor ID: "<< serialPortInfo.hasVendorIdentifier();
        if (serialPortInfo.hasVendorIdentifier())
        {
            qDebug()<<"Vendor ID: "<<serialPortInfo.vendorIdentifier();            //bu kısımda arduinonun vendor idsi ile product idsini bulduk
            arduino_Vendor_id = serialPortInfo.vendorIdentifier();
        }
        qDebug()<<"Has Product ID: "<< serialPortInfo.hasProductIdentifier();
        if (serialPortInfo.hasProductIdentifier())
        {
            qDebug()<<"Has Product ID: "<<serialPortInfo.productIdentifier();
            arduino_Product_id = serialPortInfo.productIdentifier();
        }
    }


    foreach (const QSerialPortInfo &serialPort, QSerialPortInfo::availablePorts()) {
        if(serialPort.hasProductIdentifier() && serialPort.hasVendorIdentifier())
        {
            if(serialPort.productIdentifier() == arduino_Product_id)
            {
                if(serialPort.vendorIdentifier()== arduino_Vendor_id)
                {
                    arduinoPortName= serialPort.portName();
                    arduinoAvailable = true;
                }
            }
        }
    }

    if(arduinoAvailable)
    {
        arduino->setPortName(arduinoPortName);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setStopBits(QSerialPort::OneStop);

    }
    else
    {
        QMessageBox::warning(this,"Warning","arduino has not been started yet");
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    if(arduino->isOpen())
    {
        arduino->close();
    }
}

void MainWindow::on_Rgb_clicked()
{
    if(ui->stackedWidget->currentIndex()!=0)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_led_clicked()
{
    if(ui->stackedWidget->currentIndex()!=1)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}




void MainWindow::on_lcd_clicked()
{
    if(ui->stackedWidget->currentIndex()!=2)
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
}


void MainWindow::on_red_valueChanged(int value)
{
    QString command = QString("r%1").arg(value);
    QString label = QString("%1").arg(value);
    ui->label->setText(label);
    if(arduino->isWritable())
    {
        arduino->write(command.toStdString().c_str());
    }
    qDebug()<<command;
}


void MainWindow::on_green_valueChanged(int value)
{
    QString command = QString("g%1").arg(value);
    QString label = QString("%1").arg(value);
    ui->label_2->setText(label);
    if(arduino->isWritable())
    {
        arduino->write(command.toStdString().c_str());
    }
    qDebug()<<command;
}


void MainWindow::on_blue_valueChanged(int value)
{
    QString command = QString("b%1").arg(value);
    QString label = QString("%1").arg(value);
    ui->label_3->setText(label);
    if(arduino->isWritable())
    {
        arduino->write(command.toStdString().c_str());
    }
    qDebug()<<command;
}


void MainWindow::on_pushButton_clicked()
{
    QString text = "LCD" + ui->lineEdit->text();
    if(!text.isEmpty())
    {
        QByteArray textData = text.toUtf8(); //metni byte array'e dönüştür
        arduino->write(textData); //metni arduinoya gönder
    }
    qDebug() << text;
}


void MainWindow::on_RedB_toggled(bool checked)
{
    QString command;
    if(checked == true)
    {
        command = "LED1ON";
    }
    else
    {
        command = "LED1OFF";
    }
    qDebug() << command;
    arduino->write(command.toStdString().c_str());
}


void MainWindow::on_BlueB_toggled(bool checked)
{
    QString command;
    if(checked == true)
    {
        command = "LED2ON";
    }
    else
    {
        command = "LED2OFF";
    }
    qDebug() << command;
    arduino->write(command.toStdString().c_str());
}




void MainWindow::on_YellowB_toggled(bool checked)
{
    QString command;
    if(checked == true)
    {
        command = "LED3ON";
    }
    else
    {
        command = "LED3OFF";
    }
    qDebug() << command;
    arduino->write(command.toStdString().c_str());
}


void MainWindow::on_brightness_valueChanged(int value)
{
    QString command = QString("l%1").arg(value);
    if(arduino->isWritable())
    {
        arduino->write(command.toStdString().c_str());
    }

}


void MainWindow::on_info_clicked()
{
    if(arduinoAvailable)
    {
        QMessageBox::information(this,"Connected","Arduino is available",QMessageBox::StandardButtons());
    }
    else
        QMessageBox::warning(this,"Not Connected","Arduino is Not Available",QMessageBox::StandardButtons());
}

