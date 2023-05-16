#ifndef PHONENUMBER_H
#define PHONENUMBER_H

#include <stdlib.h>
#include <iostream>
#include <QDataStream>
#include "../../app_settings.h"
#ifndef QT_IN_USE
#include "../../engine/file_manager/SimpleSerializer.h"
#endif

using namespace std;

class PhoneNumber{
#ifdef QT_IN_USE
//    Q_OBJECT
#endif
public:
    explicit PhoneNumber() = default;
    ~PhoneNumber() = default;

#ifdef QT_IN_USE
    PhoneNumber& operator= (const PhoneNumber &cs){
        if (this == &cs)
            return *this;

        m_phone_number = cs.m_phone_number;
        return *this;
    }

    const QString &phone_number() const;
    void setPhone_number(const QString &newPhone_number);
    friend QDataStream& operator>>( QDataStream& d, PhoneNumber& pn);
#endif

private:
#ifdef QT_IN_USE
    QString m_phone_number;
#endif

};

#ifdef QT_IN_USE
QDataStream& operator << (QDataStream& d, const PhoneNumber& pn);
QDataStream& operator >> (QDataStream& d, PhoneNumber& pn);
QDebug operator << (QDebug d, const PhoneNumber& pn);
#endif

#endif // PHONENUMBER_H
