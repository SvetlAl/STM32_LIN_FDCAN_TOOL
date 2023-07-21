#include "Userprofile.h"
#include <QDebug>


UserProfile::UserProfile(){
    #ifdef QT_IN_USE
    m_name = App_settings::DEFAULT_USERNAME;
    m_language = "English";
    m_email = App_settings::DEFAULT_USERNAME + "@" + App_settings::DEFAULT_USERNAME + "." + App_settings::DEFAULT_USERNAME;
    m_phone_number.setPhone_number("+70123456789");
    #endif
    #ifndef QT_IN_USE
    m_name = App_settings::DEFAULT_USERNAME);
    m_language = "English";
    m_email = QString::fromStdString(App_settings::DEFAULT_USERNAME) + "@" + QString::fromStdString(App_settings::DEFAULT_USERNAME) + "." + QString::fromStdString(App_settings::DEFAULT_USERNAME);
    m_phone_number.setPhone_number("+70123456789");
    #endif
}

UserProfile::~UserProfile(){
}

void UserProfile::print(){
#ifdef QT_IN_USE
    QDEBUG_OUT("********* " + m_name + " *********");
    QDEBUG_OUT("m_language " + m_language);
    QDEBUG_OUT("m_email " + m_email);
    QDEBUG_OUT("m_phone_number " + m_phone_number.phone_number());
#endif
#ifndef QT_IN_USE
    DEBUG_OUT("********* " + m_name + " *********");
    DEBUG_OUT("m_language " + m_language);
    DEBUG_OUT("m_email " + m_email);
    DEBUG_OUT("m_phone_number " + m_phone_number.phone_number());
#endif
}


#ifdef QT_IN_USE
const QString &UserProfile::name() const
{
    return m_name;
}

const QString &UserProfile::language() const
{
    return m_language;
}

const QString &UserProfile::email() const
{
    return m_email;
}

const PhoneNumber &UserProfile::phone_number() const
{
    return m_phone_number;
}


QString UserProfile::getValue(int _val) const{
    switch(_val){
    case Name:
        return m_name;
    case Language:
        return m_language;
    case Email:
        return m_email;
    case Phone:
        return m_phone_number.phone_number();
    default:
        return "default";
    }
}

void UserProfile::setValue(int _val, QString _str){
    switch(_val){
    case Name:
        m_name = _str;
        break;
    case Language:
        m_language = _str;
        break;
    case Email:
        m_email = _str;
        break;
    case Phone:
        m_phone_number.setPhone_number(_str);
        break;
    default:
        return;
    }
}

QDataStream& operator << (QDataStream& d, const UserProfile& up){
    d << up.name() << up.email() << up.language() << up.phone_number();
    return d;
}

QDataStream& operator >> (QDataStream& d, UserProfile& up){
    d >> up.m_name >> up.m_email >> up.m_language >> up.m_phone_number;
    return d;
}

QDebug operator << (QDebug d, const UserProfile& up){
    d << up.name() << up.email() << up.language() << up.phone_number();
    return d;
}

#endif

#ifndef QT_IN_USE
string UserProfile::getValue(int _val) const{
    switch(_val){
    case Name:
        return m_name;
    case Language:
        return m_language;
    case Email:
        return m_email;
    case Phone:
        return m_phone_number.phone_number();
    default:
        return "default";
    }
}

void UserProfile::setValue(int _val, string _str){
    switch(_val){
    case Name:
        m_name = _str;
        break;
    case Language:
        m_language = _str;
        break;
    case Email:
        m_email = _str;
        break;
    case Phone:
        m_phone_number.setPhone_number(_str);
        break;
    default:
        return;
    }
}
#endif
