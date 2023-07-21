#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <iostream>
#include <map>
#include <QDebug>
#include "PhoneNumber.h"
#include "../../app_settings.h"

using namespace std;

class UserProfile
{
public:
    enum ProfileMembers {
        Name = 0,
        Language = 1,
        Email = 2,
        Phone = 3
    };

    explicit UserProfile();
    ~UserProfile();

#ifdef QT_IN_USE
    QString getValue(int _val) const;
    void setValue(int _val, QString _str);
    friend QDataStream& operator>>( QDataStream& d, UserProfile& up);

    UserProfile& operator= (const UserProfile &cs){
        if (this == &cs)
            return *this;
        m_name = cs.m_name;
        m_language = cs.m_language;
        m_email = cs.m_email;
        m_phone_number = cs.m_phone_number;
        return *this;
    }

#endif
    void print();
    friend class Core;
    /*** setters and getters ***/

    const QString &name() const;
    const QString &language() const;
    const QString &email() const;
    const PhoneNumber &phone_number() const;

private:
#ifdef QT_IN_USE
    QString m_name;
    QString m_language;
    QString m_email;
#endif

    PhoneNumber m_phone_number;
};

#ifdef QT_IN_USE
QDataStream& operator << (QDataStream& d, const UserProfile& up);
QDataStream& operator >> (QDataStream& d, UserProfile& up);
QDebug operator << (QDebug d, const UserProfile& up);
#endif

#endif // USERPROFILE_H
