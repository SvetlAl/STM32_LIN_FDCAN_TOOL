#include "FD_CAN_settings.h"

bool FD_CAN_settings::ASM(uint8_t _can_num)const{
    return m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.ASM;
}
bool FD_CAN_settings::DAR(uint8_t _can_num)const{
    return m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.DAR;
}
bool FD_CAN_settings::FDOE(uint8_t _can_num)const{
    return m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.FDOE;
}
bool FD_CAN_settings::BRSE(uint8_t _can_num)const{
    return m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.BRSE;
}
bool FD_CAN_settings::PXHD(uint8_t _can_num)const{
    return m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.PXHD;
}
bool FD_CAN_settings::EFBI(uint8_t _can_num)const{
    return m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.EFBI;
}
bool FD_CAN_settings::TXP(uint8_t _can_num)const{
    return m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.TXP;
}
bool FD_CAN_settings::NISO(uint8_t _can_num)const{
    return m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.NISO;
}

void FD_CAN_settings::setASM(uint8_t _can_num, bool val){
    m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.ASM = val;
}
void FD_CAN_settings::setDAR(uint8_t _can_num, bool val){
    m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.DAR = val;
}
void FD_CAN_settings::setFDOE(uint8_t _can_num, bool val){
    m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.FDOE = val;
}
void FD_CAN_settings::setBRSE(uint8_t _can_num, bool val){
    m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.BRSE = val;
}
void FD_CAN_settings::setPXHD(uint8_t _can_num, bool val){
    m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.PXHD = val;
}
void FD_CAN_settings::setEFBI(uint8_t _can_num, bool val){
    m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.EFBI = val;
}
void FD_CAN_settings::setTXP(uint8_t _can_num, bool val){
    m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.TXP = val;
}
void FD_CAN_settings::setNISO(uint8_t _can_num, bool val){
    m_u_fd_settings.settings.cccr_cfg[_can_num].cfg.NISO = val;
}


uint8_t FD_CAN_settings::bitrate_psc(uint8_t _can_num, bool isNominalBtr) const{
    return (isNominalBtr == true) ? m_u_fd_settings.settings.nominal_bitrate[_can_num].PSC : m_u_fd_settings.settings.data_bitrate[_can_num].PSC;
}
uint8_t FD_CAN_settings::bitrate_tseg1(uint8_t _can_num, bool isNominalBtr) const{
    return (isNominalBtr == true) ? m_u_fd_settings.settings.nominal_bitrate[_can_num].TSEG1 : m_u_fd_settings.settings.data_bitrate[_can_num].TSEG1;
}
uint8_t FD_CAN_settings::bitrate_tseg2(uint8_t _can_num, bool isNominalBtr) const{
    return (isNominalBtr == true) ? m_u_fd_settings.settings.nominal_bitrate[_can_num].TSEG2 : m_u_fd_settings.settings.data_bitrate[_can_num].TSEG2;
}
uint8_t FD_CAN_settings::bitrate_sjw(uint8_t _can_num, bool isNominalBtr) const{
    return (isNominalBtr == true) ? m_u_fd_settings.settings.nominal_bitrate[_can_num].SJW : m_u_fd_settings.settings.data_bitrate[_can_num].SJW;
}

void FD_CAN_settings::set_bitrate_psc(uint8_t _can_num, uint8_t val, bool isNominalBtr){
    if (isNominalBtr == true){
        m_u_fd_settings.settings.nominal_bitrate[_can_num].PSC = val;
    }
    else m_u_fd_settings.settings.data_bitrate[_can_num].PSC = val;
}
void FD_CAN_settings::set_bitrate_tseg1(uint8_t _can_num, uint8_t val, bool isNominalBtr){
    if (isNominalBtr == true){
        m_u_fd_settings.settings.nominal_bitrate[_can_num].TSEG1 = val;
    }
    else m_u_fd_settings.settings.data_bitrate[_can_num].TSEG1 = val;
}
void FD_CAN_settings::set_bitrate_tseg2(uint8_t _can_num, uint8_t val, bool isNominalBtr){
    if (isNominalBtr == true){
        m_u_fd_settings.settings.nominal_bitrate[_can_num].TSEG2 = val;
    }
    else m_u_fd_settings.settings.data_bitrate[_can_num].TSEG2 = val;
}
void FD_CAN_settings::set_bitrate_sjw(uint8_t _can_num, uint8_t val, bool isNominalBtr){
    if (isNominalBtr == true){
        m_u_fd_settings.settings.nominal_bitrate[_can_num].SJW = val;
    }
    else m_u_fd_settings.settings.data_bitrate[_can_num].SJW = val;
}


void FD_CAN_settings::init(const QByteArray& _data){
    if(_data.size() != sizeof(fdcan_settings)) return;
    const char* rawData = _data.constData();
    memcpy(m_u_fd_settings.raw_data, rawData, sizeof(fdcan_settings));
}

const QByteArray FD_CAN_settings::raw_data()const{
    return QByteArray(reinterpret_cast<const char*>(m_u_fd_settings.raw_data), sizeof(fdcan_settings));
}



