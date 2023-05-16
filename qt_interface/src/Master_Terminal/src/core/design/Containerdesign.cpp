#include "Containerdesign.h"

QDataStream& operator << (QDataStream& d, const ContainerDesignInt& cd){
    d << cd.m_name << cd.p_items;
    return d;
}

QDataStream& operator >> (QDataStream& d, ContainerDesignInt& cd){
    d >> cd.m_name >> cd.p_items;
    return d;
}

QDataStream& operator << (QDataStream& d, const ContainerDesignFloat& cd){
    d << cd.m_name << cd.p_items;
    return d;
}

QDataStream& operator >> (QDataStream& d, ContainerDesignFloat& cd){
    d >> cd.m_name >> cd.p_items;
    return d;
}

QDataStream& operator << (QDataStream& d, const ContainerDesignQstring& cd){
    d << cd.m_name << cd.p_items;
    return d;
}

QDataStream& operator >> (QDataStream& d, ContainerDesignQstring& cd){
    d >> cd.m_name >> cd.p_items;
    return d;
}


