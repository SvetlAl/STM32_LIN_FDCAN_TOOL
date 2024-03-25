#include "OverrideStatus.h"
/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/

void OverrideStatus::init_OverrideStatuswithRawData(const QByteArray &data){
    if(data.size()!=DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH) return;
    for(size_t i = 0; i < DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH; i++){
        m_ovr_status.raw_data[i] = data.at(i);
    }
}

/********************************************************************
 *
 *
 *                     Class Setters/getters
 *
 *
********************************************************************/

void OverrideStatus::setActiveFilters(const QByteArray &data){
    if(data.size()!= 4) return;
    for(size_t i = 0; i < 4; i++){
        m_ovr_status.raw_data[i] = data.at(i);
    }
}

const QByteArray OverrideStatus::getRawData() const{
    const QByteArray data(reinterpret_cast<const char*>(m_ovr_status.raw_data), sizeof(u_can_override_status));
    return data;
}

const uint16_t OverrideStatus::get_ignored_id_num() const{
    return m_ovr_status.status.ignored_id_num;
}
const uint16_t OverrideStatus::get_overrided_id_num() const{
    return m_ovr_status.status.overrided_id_num;
}
const uint16_t OverrideStatus::get_ignored_id_dirs_msk() const{
    return m_ovr_status.status.ignored_id_dirs_msk;
} // 0 - CAN1, 1 - CAN2
const uint16_t OverrideStatus::get_overrided_id_dirs_msk() const{
    return m_ovr_status.status.overrided_id_dirs_msk;
} // 0 - CAN1, 1 - CAN2

const can_override_filter OverrideStatus::get_filter(int index) const{
    if(index >= MAX_OVERRIDE_FILTERS) return m_ovr_status.status.filters[MAX_OVERRIDE_FILTERS-1];
    else return m_ovr_status.status.filters[index];
}

const can_id OverrideStatus::get_ignored_ids(int index) const{
    if(index >= MAX_IGNORED_IDS) return m_ovr_status.status.ignored_ids[MAX_IGNORED_IDS-1];
    else return m_ovr_status.status.ignored_ids[index];
}

const uint32_t OverrideStatus::get_int_ignored_ids(int index) const{
    can_id ret_value;
    if(index >= MAX_IGNORED_IDS) ret_value = m_ovr_status.status.ignored_ids[MAX_IGNORED_IDS-1];
    else ret_value = m_ovr_status.status.ignored_ids[index];
    if(ret_value.std_id.unused == 0xFFFF){
        uint32_t std_val = ret_value.std_id.id_highbyte << 8 | ret_value.std_id.id_lowbyte;
        if(std_val <= 0x7FF) return std_val;
    }
    if(ret_value.ext_id <= 0x1fffffff) return ret_value.ext_id;
    return 0x00;
}


const uint8_t OverrideStatus::get_override_msks(int index) const{
    if(index >= MAX_OVERRIDE_FILTERS) return m_ovr_status.status.override_msks[MAX_OVERRIDE_FILTERS-1];
    else return m_ovr_status.status.override_msks[index];
}

void OverrideStatus::set_ignored_id_num(uint16_t value){
    m_ovr_status.status.ignored_id_num = value;
}
void OverrideStatus::set_overrided_id_num(uint16_t value){
    m_ovr_status.status.overrided_id_num = value;
}
void OverrideStatus::set_ignored_id_dirs_msk(uint16_t value){
    m_ovr_status.status.ignored_id_dirs_msk = value;
} // 0 - CAN1, 1 - CAN2
void OverrideStatus::set_overrided_id_dirs_msk(uint16_t value){
    m_ovr_status.status.overrided_id_dirs_msk = value;
} // 0 - CAN1, 1 - CAN2

void OverrideStatus::set_filter(int index, can_override_filter value){
    if(index >= MAX_OVERRIDE_FILTERS) m_ovr_status.status.filters[MAX_OVERRIDE_FILTERS-1] = value;
    else m_ovr_status.status.filters[index] = value;
}
void OverrideStatus::set_ignored_ids(int index, can_id value){
    if(index >= MAX_IGNORED_IDS) m_ovr_status.status.ignored_ids[MAX_IGNORED_IDS-1] = value;
    else m_ovr_status.status.ignored_ids[index] = value;
}
void OverrideStatus::set_ignored_ids(int index, uint32_t value){
    can_id _can_id_value;
    if(value <= 0x7FF){
        _can_id_value.std_id.id_highbyte = ((value >> 8) &~0xFFFFFF00);
        _can_id_value.std_id.id_lowbyte = ((value >> 0) &~0xFFFFFF00);
        _can_id_value.std_id.unused = 0xFFFF;
    }
    else if(value > 0x7FF & value < 0x1fffffff) _can_id_value.ext_id = value;
    else _can_id_value.ext_id = 0;
    set_ignored_ids(index, _can_id_value);
}

void OverrideStatus::set_override_msks(int index, uint8_t value){
    if(index >= MAX_OVERRIDE_FILTERS) m_ovr_status.status.override_msks[MAX_OVERRIDE_FILTERS-1] = value;
    else m_ovr_status.status.override_msks[index] = value;
}





/********************************************************************
 *
 *
 *                     FD CAN
 *
 *
********************************************************************/

void FDCAN_OverrideStatus::init_OverrideStatuswithRawData(const QByteArray &data){
    if(data.size()!=DEVICE_FDCAN_OVERRIDE_FILTER_SETTINGS_LENGTH) return;
    for(size_t i = 0; i < DEVICE_FDCAN_OVERRIDE_FILTER_SETTINGS_LENGTH; i++){
        m_ovr_status.data[i] = data.at(i);
    }

}

const QByteArray FDCAN_OverrideStatus::getRawData() const{
    const QByteArray data(reinterpret_cast<const char*>(m_ovr_status.data), sizeof(u_fdcan_filter));
    return data;
}
