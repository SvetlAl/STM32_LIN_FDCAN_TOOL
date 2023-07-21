#ifndef CDC_JNI_DRIVER_H
#define CDC_JNI_DRIVER_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif

#include "CDC_Driver.h"
#include "../androidserial/QASerialPort.h"
#include "../androidserial/QASerialPortinfo.h"

#ifdef ANDROID_V

class CDC_JNI_Driver : public CDC_Driver{
Q_OBJECT
public:
    CDC_JNI_Driver(QObject *parent = nullptr): CDC_Driver(parent){
        m_pSerialPort = new QASerialPort();
    };
    ~CDC_JNI_Driver(){
        delete m_pSerialPort;
    };

    bool init() override;
    bool connect() override;
    bool disconnect() override;
    QByteArray exchange_data(const QByteArray &cmd, int custom_timeout = 0) override;
    QByteArray readData(int timeout = 0) override;
    bool writeData(const QByteArray &data) override;
    void startAsynchReading(int mode) override;
    void stopAsynchReading(int mode) override;
    QASerialPort *getQASerialPortPtr() override {return m_pSerialPort;}
    QSerialPort *getQSerialPortPtr() override {return nullptr;}

private:
     QASerialPort *m_pSerialPort;

};
#endif

#endif // CDC_JNI_DRIVER_H
