#include "QSerialPortConfigItem.h"

const QString &QSerialPortConfigItem::name() const
{
    return m_name;
}

void QSerialPortConfigItem::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit changed();
}

int QSerialPortConfigItem::value() const
{
    return m_value;
}

void QSerialPortConfigItem::setValue(int newValue)
{
    if (m_value == newValue)
        return;
    m_value = newValue;
    emit changed();
}
