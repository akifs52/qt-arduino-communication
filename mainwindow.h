#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Rgb_clicked();

    void on_led_clicked();

    void on_lcd_clicked();

    void on_red_valueChanged(int value);

    void on_green_valueChanged(int value);

    void on_blue_valueChanged(int value);

    void on_pushButton_clicked();

    void on_RedB_toggled(bool checked);

    void on_BlueB_toggled(bool checked);

    void on_YellowB_toggled(bool checked);

    void on_brightness_valueChanged(int value);

    void on_info_clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_dragging = true;
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (m_dragging && (event->buttons() & Qt::LeftButton)) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_dragging = false;
            event->accept();
        }
    }

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    QString arduinoPortName;
    quint16 arduino_Product_id; //16 bitlik veriyi her platforma uygun hale getirir typdef od unsigned short
    quint16 arduino_Vendor_id;
    bool arduinoAvailable;
    bool m_dragging = false;
    QPoint m_dragPosition;
};
#endif // MAINWINDOW_H
