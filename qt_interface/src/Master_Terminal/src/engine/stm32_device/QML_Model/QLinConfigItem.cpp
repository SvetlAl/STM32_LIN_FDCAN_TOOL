#include "QLinConfigItem.h"

const QString &QLinConfigItem::name() const
{
    return m_name;
}

void QLinConfigItem::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit changed();
}

int QLinConfigItem::value() const
{
    return m_value;
}

void QLinConfigItem::setValue(int newValue)
{
    if (m_value == newValue)
        return;
    m_value = newValue;
    emit changed();
}
