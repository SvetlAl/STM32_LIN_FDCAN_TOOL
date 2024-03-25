#include "FDCAN_injection_message.h"


uint8_t FDCAN_injection_message::makeFlags()const{
    uint8_t flags = 0;
    if(xtd_flag()) flags |= 0x02;
    if(fdf_flag()) flags |= 0x04;
    if(brs_flag()) flags |= 0x08;
    return flags;
}

QString FDCAN_injection_message::makeData()const{
    QString data;
    foreach(auto item, m_data){
        data.append(item);
    }
    return data;
}


