#ifndef QSERIALPORTCONFIGPC_H
#define QSERIALPORTCONFIGPC_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif

#include "QSerialPortConfigProperty.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "SerialConfig_Preset.h"
#include "QSerialPortConfig.h"


class QSerialPortConfigPC: public QSerialPortConfig{
    Q_OBJECT

public:
    QSerialPortConfigPC(QObject *parent = nullptr): QSerialPortConfig(parent){};
    ~QSerialPortConfigPC(){ }

    void refresh_ports() override{
        m_portnames.reinit();
    };

    SerialConfig_Preset make_preset() override;
    void set_preset(const SerialConfig_Preset& _preset) override;

};


#endif // QSERIALPORTCONFIGPC_H
