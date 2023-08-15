#include "CoreStatus.h"

/********************************************************************
 *
 *
 *                    Class setters/getters
 *
 *
********************************************************************/

const QString &CoreStatus::last_used_profile() const{
    return m_last_used_profile;
}

void CoreStatus::setLast_used_profile(const QString &newLast_used_profile){
    m_last_used_profile = newLast_used_profile;
}

/********************************************************************
 *
 *
 *                    Operators
 *
 *
********************************************************************/

QDataStream& operator << (QDataStream& d, const CoreStatus& cs){
    d << cs.last_used_profile();
    return d;
}

QDataStream& operator >> (QDataStream& d, CoreStatus& cs){
    d >> cs.m_last_used_profile;
    return d;
}
