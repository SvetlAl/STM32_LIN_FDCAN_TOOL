#ifndef CORESTATUS_H
#define CORESTATUS_H

#include <stdlib.h>
#include <QDebug>
#include <iostream>
//#include "../engine/file_manager/SimpleSerializer.h"
#include "../app_settings.h"

using namespace std;

class CoreStatus{
public:
    explicit CoreStatus(){//DEBUG_OUT("CoreStatus");
    };

    ~CoreStatus(){//DEBUG_OUT("~CoreStatus");
    };

    CoreStatus& operator= (const CoreStatus &cs){
        if (this == &cs)
            return *this;

        m_last_used_profile = cs.m_last_used_profile;
        return *this;
    }

    friend QDataStream& operator >>( QDataStream& d, CoreStatus& cs);
    friend QDataStream& operator << (QDataStream& d, const CoreStatus& cs);

    const QString &last_used_profile() const;
    void setLast_used_profile(const QString &newLast_used_profile);

private:
    QString m_last_used_profile = App_settings::DEFAULT_USERNAME;
};



QDataStream& operator << (QDataStream& d, const CoreStatus& cs);
QDataStream& operator >> (QDataStream& d, CoreStatus& cs);

#endif // CORESTATUS_H
