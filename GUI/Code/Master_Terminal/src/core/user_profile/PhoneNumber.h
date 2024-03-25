#ifndef PHONENUMBER_H
#define PHONENUMBER_H

#include <stdlib.h>
#include <iostream>
#include <QDataStream>
#include "../../app_settings.h"

using namespace std;

class PhoneNumber{
public:
    explicit PhoneNumber() = default;
    ~PhoneNumber() = default;


    //===================================== Operators ================================
    PhoneNumber& operator= (const PhoneNumber &cs){
        if (this == &cs)
            return *this;

        m_phone_number = cs.m_phone_number;
        return *this;
    }
    friend QDataStream& operator>>( QDataStream& d, PhoneNumber& pn);


    //======================== Class setters/getters =================================
    const QString &phone_number() const;
    void setPhone_number(const QString &newPhone_number);


private:
    QString m_phone_number;
};

QDataStream& operator << (QDataStream& d, const PhoneNumber& pn);
QDataStream& operator >> (QDataStream& d, PhoneNumber& pn);
QDebug operator << (QDebug d, const PhoneNumber& pn);

#endif // PHONENUMBER_H
