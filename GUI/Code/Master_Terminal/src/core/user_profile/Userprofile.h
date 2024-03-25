#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <iostream>
#include <map>
#include <QDebug>
#include "PhoneNumber.h"

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

    //======================== Setters/getters =================================
    QString getValue(int _val) const;
    void setValue(int _val, QString _str);

    //============================= Operators ==================================
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

    friend class Core;

    //======================== Debug and print ==================================
    void print();

    //==================== Class setters/getters ================================
    const QString &name() const;
    const QString &language() const;
    const QString &email() const;
    const PhoneNumber &phone_number() const;

private:

    QString m_name;
    QString m_language;
    QString m_email;

    PhoneNumber m_phone_number;
};


QDataStream& operator << (QDataStream& d, const UserProfile& up);
QDataStream& operator >> (QDataStream& d, UserProfile& up);
QDebug operator << (QDebug d, const UserProfile& up);


#endif // USERPROFILE_H
