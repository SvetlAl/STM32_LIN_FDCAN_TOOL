#ifndef COMMANDCONSTRUCTOR_H
#define COMMANDCONSTRUCTOR_H

#include "../../app_settings.h"
#include <QDebug>
#include "Command.h"
#include "../stm32_device/Lin_filter.h"
#include "../vehicle/Vehicle.h"


class CommandConstructor{

public:
    CommandConstructor(){
        isBigEndian = App_settings::isBigEndian();
    };
    ~CommandConstructor(){
    };

    enum MemChipAddress {
        BOOTLOADER_EMERGENCY_PROGRAMM_ADDR = 0,
        BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR = 1,
        BOOTLOADER_UPDATE_PROGRAMM_ADDR = 2,
        BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR = 3
    };

    uint32_t getMemchipAddress(uint32_t address_code, uint32_t device_code);

    bool constructCmd(uint32_t _cmd);
    bool constructCmd(uint32_t _cmd, bool mosi, lin_filter_raw *filter_ptr);
    bool constructCmd(uint32_t _cmd, uint32_t value32_to_string);

    bool constructCmd(uint32_t _cmd, uint32_t var1, uint32_t var2);

    bool constructCmd(uint32_t _cmd, uint32_t address, uint32_t value32_to_string, uint32_t option);
    bool constructCmd(uint32_t _cmd, uint8_t override_method, uint8_t add_method, uint8_t can, uint32_t can_id, uint8_t ovr_fltr_msk, const QByteArray &msgdata);

    // bool constructCmd(uint32_t _cmd, QByteArray& input_buf, QByteArray& input_buf); , const QByteArray& input_buf


    void translateVehicleStatus(const QString& status_string, Vehicle& _trgt_vhcl) const;
    void translateVehicleStatus(const QByteArray& status_string, Vehicle& _trgt_vhcl) const; /* HEX */

    static bool isResponseBusy(const QString& _response){
        return _response.contains(Command::ELP_BUSY_RESPONSE);
    }
    static bool isResponseOk(const QString& _response){
        return _response.contains(Command::ELP_OK_RESPONSE);
    }

    const QByteArray &cmd_string() const;

private:
    QByteArray m_cmd_output;
    bool isBigEndian = false;

};

#endif // COMMANDCONSTRUCTOR_H
