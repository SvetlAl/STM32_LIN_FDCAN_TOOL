#ifndef CDC_PC_DRIVER_H
#define CDC_PC_DRIVER_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include "CDC_Driver.h"
#include <QSerialPort>


class CDC_PC_Driver : public CDC_Driver{
Q_OBJECT
public:
    CDC_PC_Driver(QObject *parent = nullptr): CDC_Driver(parent){
        m_pSerialPort = new QSerialPort(this);
    };
    ~CDC_PC_Driver(){
    };

    bool init() override;
    bool connect() override;
    bool disconnect() override;

    QByteArray exchange_data(const QByteArray &cmd, int custom_timeout = 0) override;
    bool writeData(const QByteArray &data) override;
    QByteArray readData(int timeout = 0) override;

    void startAsynchReading(int mode) override;
    void stopAsynchReading(int mode) override;



    QASerialPort *getQASerialPortPtr() override {return nullptr;}
    QSerialPort *getQSerialPortPtr() override {return m_pSerialPort;}

private:
    QSerialPort *m_pSerialPort;

};

#endif // CDC_PC_DRIVER_H
