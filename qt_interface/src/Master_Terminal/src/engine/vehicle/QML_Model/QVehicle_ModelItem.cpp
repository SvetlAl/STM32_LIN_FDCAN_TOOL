#include "QVehicle_ModelItem.h"

const QString &QVehicle_ModelItem::name() const
{
    return m_name;
}

void QVehicle_ModelItem::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit changed();
}

int QVehicle_ModelItem::value() const
{
    return m_hex_value;
}

void QVehicle_ModelItem::setValue(int newValue)
{
    if (m_hex_value == newValue)
        return;
    m_hex_value = newValue;
    emit changed();
}

int QVehicle_ModelItem::getBrand_code() const
{
    return brand_code;
}

void QVehicle_ModelItem::setBrand_code(int newBrand_code)
{
    brand_code = newBrand_code;
}
