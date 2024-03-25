#ifndef QSERIALPORTCONFIGITEM_H
#define QSERIALPORTCONFIGITEM_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <stdio.h>

/*****************************************************************************************/
/*** QSerialPortConfigItem is a general class that can incapsulate Serial Port settings: */
/***********                                                                   ***********/
/*********** Com Port Name (COM1, COM3, COM7)                                  ***********/
/*********** Flow control                                                      ***********/
/*********** Parity                                                            ***********/
/*********** Stop Bits                                                         ***********/
/*********** Data Bits                                                         ***********/
/*********** Baud Rate                                                         ***********/
/***********                                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class QSerialPortConfigItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY changed )
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY changed )

public:

    explicit QSerialPortConfigItem(QObject *parent = nullptr, QString a = "", int n = 0) : QObject(parent), m_name(a), m_value(n) {};
    QSerialPortConfigItem(QString a, int n) : QObject(), m_name(a), m_value(n) {};

    ~QSerialPortConfigItem( ){}


/*** setters and getters ***/
    const QString &name() const;
    void setName(const QString &newName);
    int value() const;
    void setValue(int newValue);

signals:
    void changed();

private:
    QString m_name;
    int m_value;
};


#endif // QSERIALPORTCONFIGITEM_H
