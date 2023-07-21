#ifndef QASERIALPORTINFO_H
#define QASERIALPORTINFO_H


#include "qlist.h"
#include "../../app_settings.h"
#ifdef ANDROID_V
#include <QJniObject>
#include <QJniEnvironment>
#endif

class QASerialPortInfo
{
private:
    QString _portName;
    QString _device;
    QString _description;
    QString _manufacturer;
    QString _serialNumber;

    quint16 _vendorIdentifier;
    quint16 _productIdentifier;

    bool    _hasVendorIdentifier;
    bool    _hasProductIdentifier;

public:
    QASerialPortInfo();
    QASerialPortInfo(const QASerialPortInfo &other);
    QASerialPortInfo& operator=(const QASerialPortInfo &other);

    static QList<QASerialPortInfo> availablePorts();
    QString portName() const;
};

#endif // QASerialPortInfo_H
