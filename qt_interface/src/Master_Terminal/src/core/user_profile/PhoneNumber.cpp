#include "PhoneNumber.h"

#ifdef QT_IN_USE
QDataStream& operator << (QDataStream& d, const PhoneNumber& pn){
    d << pn.phone_number();
    return d;
}

QDataStream& operator >> (QDataStream& d, PhoneNumber& pn){
    d >> pn.m_phone_number;
    return d;
}

QDebug operator << (QDebug d, const PhoneNumber& pn){
    d << pn.phone_number();
    return d;
}

const QString &PhoneNumber::phone_number() const
{
    return m_phone_number;
}

void PhoneNumber::setPhone_number(const QString &newPhone_number)
{
    m_phone_number = newPhone_number;
}
#endif
