#ifndef FD_CAN_SETTINGS_H
#define FD_CAN_SETTINGS_H

#include <QObject>
#include "../bus/FDCAN_Macros.h"

//============================== ST CAN ==============================
class FD_CAN_settings{

public:
    explicit FD_CAN_settings(){};
    ~FD_CAN_settings() {};

    constexpr static inline const int fdcan_settings_size = sizeof(fdcan_settings);


    bool ASM(uint8_t _can_num)const;
    bool DAR(uint8_t _can_num)const;
    bool FDOE(uint8_t _can_num)const;
    bool BRSE(uint8_t _can_num)const;

    bool PXHD(uint8_t _can_num)const;
    bool EFBI(uint8_t _can_num)const;
    bool TXP(uint8_t _can_num)const;
    bool NISO(uint8_t _can_num)const;

    void setASM(uint8_t _can_num, bool val);
    void setDAR(uint8_t _can_num, bool val);
    void setFDOE(uint8_t _can_num, bool val);
    void setBRSE(uint8_t _can_num, bool val);

    void setPXHD(uint8_t _can_num, bool val);
    void setEFBI(uint8_t _can_num, bool val);
    void setTXP(uint8_t _can_num, bool val);
    void setNISO(uint8_t _can_num, bool val);

    uint8_t bitrate_psc(uint8_t _can_num, bool isNominalBtr = true) const;
    uint8_t bitrate_tseg1(uint8_t _can_num, bool isNominalBtr = true) const;
    uint8_t bitrate_tseg2(uint8_t _can_num, bool isNominalBtr = true) const;
    uint8_t bitrate_sjw(uint8_t _can_num, bool isNominalBtr = true) const;

    void set_bitrate_psc(uint8_t _can_num, uint8_t val, bool isNominalBtr = true);
    void set_bitrate_tseg1(uint8_t _can_num, uint8_t val, bool isNominalBtr = true);
    void set_bitrate_tseg2(uint8_t _can_num, uint8_t val, bool isNominalBtr = true);
    void set_bitrate_sjw(uint8_t _can_num, uint8_t val, bool isNominalBtr = true);

    void init(const QByteArray& _data);
    const QByteArray raw_data()const;

signals:

private:
    u_fdcan_settings m_u_fd_settings;
};
#endif // FD_CAN_SETTINGS_H
