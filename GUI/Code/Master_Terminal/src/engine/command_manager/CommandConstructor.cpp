#include "CommandConstructor.h"
//#include "../../core/VersionManager.h"


bool CommandConstructor::constructCmd(uint32_t _cmd){
    m_cmd_output.clear();
    switch(_cmd){

    case ELPR_VEHICLE_GET_CURRENT_STATUS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_VEHICLE_GET_CURRENT_STATUS_STRING_ASCII:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_VEHICLE_GET_SW_VERSION:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_VEHICLE_GET_DEV_MODEL:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_VEHICLE_SAVE_STATUS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_DEVICE_GET_CURRENT_STATUS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_OVR_FLTR_GET_CURRENT_STATUS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_DEVICE_SAVE_STATUS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_OVR_FLTR_GET_FILTER_NUMS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_UPDATE_OVR_FILTERS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_LIN_GET_POLL_PERIOD:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_LIN_GET_MOSI_FILTER:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_LIN_GET_MISO_FILTER:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_FDCAN_GET_SETTINGS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_UPDATE_FDCAN_STNGS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_RESTART_FDCAN:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_SAVE_FDCAN_STNGS:{
        Command elp_cmd(_cmd, isBigEndian);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }

    default:
        return false;
        break;
    }
}

bool CommandConstructor::constructCmd(uint32_t _cmd, bool mosi, lin_filter_raw *filter_ptr){
    m_cmd_output.clear();
    switch(_cmd){
    case ELP_LIN_SET_FILTER:{
        //if(input_buf.length() != 4) return false;
        Command elp_cmd(_cmd, isBigEndian);
        uint8_t mosi_flag = mosi ? 0x00 : 0xFF;
        elp_cmd.add_param(mosi_flag);
        for(size_t i = 0; i < sizeof(lin_filter_raw); i++){
            elp_cmd.add_param(filter_ptr->data[i]);
        }
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    default:
        return false;
        break;
    }
}

bool CommandConstructor::constructCmd(uint32_t _cmd, uint32_t value32_to_string){
    m_cmd_output.clear();
    switch(_cmd){
    case ELP_VEHICLE_SET_MODEL:{
        //if(input_buf.length() != 4) return false;
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.append_uint_to_string(value32_to_string);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_VEHICLE_SET_MODE:
    case ELP_VEHICLE_SET_SPEEDOMETER_MLT:
    case ELP_VEHICLE_SET_CRUISE_MLT:
    case ELP_VEHICLE_SET_TYRES_THRESHOLD:
    case ELP_VEHICLE_SET_ODOMETER_MLT:{
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.append_uint_to_string(value32_to_string);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_LIN_POLL_PERIOD:{
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.append_uint_to_string(value32_to_string);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }

    default:
        return false;
        break;
    }
}


bool CommandConstructor::constructCmd(uint32_t _cmd, uint32_t var1, uint32_t var2){
    m_cmd_output.clear();
    switch(_cmd){
    case ELP_CMD_SPI_MEMCHIP_READ:{
        //if(input_buf.length() != 4) return false;
        Command elp_cmd(_cmd, isBigEndian);

        elp_cmd.add_param(((var1 >> 16)  & ~0xFF00));
        elp_cmd.add_param(((var1 >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((var1 >> 0)   & ~0xFFFFFF00));
        elp_cmd.add_param(((var2 >> 16)  & ~0xFF00));
        elp_cmd.add_param(((var2 >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((var2 >> 0)   & ~0xFFFFFF00));

        // elp_cmd.append_uint_to_string(value32_to_string);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_CMD_SPI_MEMCHIP_READ32:{
        //if(input_buf.length() != 4) return false;
        Command elp_cmd(_cmd, isBigEndian);

        elp_cmd.add_param(((var1 >> 24)         ));
        elp_cmd.add_param(((var1 >> 16)  & ~0xFF00));
        elp_cmd.add_param(((var1 >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((var1 >> 0)   & ~0xFFFFFF00));

        elp_cmd.add_param(((var2 >> 24)         ));
        elp_cmd.add_param(((var2 >> 16)  & ~0xFF00));
        elp_cmd.add_param(((var2 >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((var2 >> 0)   & ~0xFFFFFF00));

        // elp_cmd.append_uint_to_string(value32_to_string);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_DEVICE_SET_MODE:{
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.add_param(((var1 >> 16)  & ~0xFF00));
        elp_cmd.add_param(((var1 >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((var1 >> 0)   & ~0xFFFFFF00));
        var2 &=~0xFFFFFF00;
        elp_cmd.add_param((uint8_t)var2);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELP_ERASE_AREA:{
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.add_param(((var1 >> 16)  & ~0xFF00));
        elp_cmd.add_param(((var1 >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((var1 >> 0)   & ~0xFFFFFF00));
        elp_cmd.add_param(((var2 >> 16)  & ~0xFF00));
        elp_cmd.add_param(((var2 >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((var2 >> 0)   & ~0xFFFFFF00));
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_SEND_CUSTOM_FDCAN_MSG:{
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.add_param(((var1 >> 8)   & ~0xFF00));
        elp_cmd.add_param(((var1 >> 0)   & ~0xFF00));
        elp_cmd.add_param((uint8_t)(var2));

        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    default:
        return false;
        break;
    }
}
bool CommandConstructor::constructCmd(uint32_t _cmd, uint32_t address, uint32_t value32_to_string, uint32_t option){
    m_cmd_output.clear();
    switch(_cmd){
    case ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP:{
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.add_param(((address >> 16)  & ~0xFF00));
        elp_cmd.add_param(((address >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((address >> 0)   & ~0xFFFFFF00));
        elp_cmd.add_param(((value32_to_string >> 16)  & ~0xFF00));
        elp_cmd.add_param(((value32_to_string >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((value32_to_string >> 0)   & ~0xFFFFFF00));
        elp_cmd.add_param((uint8_t) option);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    case ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP32:{
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.add_param(((address >> 24)  & 0xFF));
        elp_cmd.add_param(((address >> 16)  & ~0xFF00));
        elp_cmd.add_param(((address >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((address >> 0)   & ~0xFFFFFF00));
        elp_cmd.add_param(((value32_to_string >> 24)  & 0xFF));
        elp_cmd.add_param(((value32_to_string >> 16)  & ~0xFF00));
        elp_cmd.add_param(((value32_to_string >> 8)   & ~0xFFFF00));
        elp_cmd.add_param(((value32_to_string >> 0)   & ~0xFFFFFF00));
        elp_cmd.add_param((uint8_t) option);
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }


    default:
        return false;
        break;
    }
}

bool CommandConstructor::constructCmd(uint32_t _cmd, uint8_t override_method, uint8_t add_method, uint8_t can, uint32_t can_id, uint8_t ovr_fltr_msk, const QByteArray &msgdata){
    m_cmd_output.clear();
    switch(_cmd){
    case ELP_OVR_FLTR_SET_VALUE:{
        if(msgdata.size() > 8) return false;
        Command elp_cmd(_cmd, isBigEndian);
        elp_cmd.add_param((uint8_t) override_method); // 00
        elp_cmd.add_param((uint8_t) override_method); // 01
        elp_cmd.add_param((uint8_t) can); // 02

        elp_cmd.add_param(((can_id >> 24)  & ~0x00)); // 03
        elp_cmd.add_param(((can_id >> 16)  & ~0xFF00)); // 04
        elp_cmd.add_param(((can_id >> 8)   & ~0xFFFF00)); // 05
        elp_cmd.add_param(((can_id >> 0)   & ~0xFFFFFF00)); // 06

        elp_cmd.add_param((uint8_t) ovr_fltr_msk); // 07


        for(size_t i = 0; i < msgdata.size(); i++){
            elp_cmd.add_param( msgdata.at(i));
        }
        m_cmd_output.resize(elp_cmd.calculateStringSize());
        elp_cmd.makeString(m_cmd_output);
        return true;
        break;
    }
    default:
        return false;
        break;
    }
}


const QByteArray &CommandConstructor::cmd_string() const{
    return m_cmd_output;
}

void CommandConstructor::translateVehicleStatus(const QString& status_string, Vehicle& _trgt_vhcl) const{
    QByteArray qb_string = status_string.toLocal8Bit();
    uint8_t *data = reinterpret_cast<uint8_t*>(qb_string.data());

    size_t i = 0;
    uint16_t _model = 0xFFFF;
    _model = StringConvertor::str_to_uint16_be(data);

    i+=4;
    uint8_t _modes;
    StringConvertor::str_to_ascii((data + i), &_modes, 2);

    i+=2;
    uint8_t mlt[4];
    StringConvertor::str_to_ascii( (data + i), &mlt[0], 8);

    bool needToInitNewModel = (_trgt_vhcl.model() == _model) ? false : true;

    if(needToInitNewModel){
        _trgt_vhcl.set_model(_model);
        _trgt_vhcl.initNewModel();
    }
    _trgt_vhcl.set_modes(_modes);
    _trgt_vhcl.set_speedometer_mlt(mlt[0]);
    _trgt_vhcl.set_odometer_mlt(mlt[1]);
    _trgt_vhcl.set_cruise_mlt(mlt[2]);
    _trgt_vhcl.set_tyres_threshold(mlt[3]);
}

void CommandConstructor::translateVehicleStatus(const QByteArray& status_string, Vehicle& _trgt_vhcl) const{
    _trgt_vhcl.init_with_response_bytes(status_string);
}


uint32_t CommandConstructor::getMemchipAddress(uint32_t address_code, uint32_t device_code){
    switch(device_code){
    //===================================
    case TEC_MODULE_MCODE:{
        switch(address_code){
            case BOOTLOADER_EMERGENCY_PROGRAMM_ADDR: return 0x020000; break;
            case BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR: return (0x030000 - 0x04); break;
            case BOOTLOADER_UPDATE_PROGRAMM_ADDR: return 0x030000; break;
            case BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR: return (0x040000 - 0x04); break;

            default: return INVALID_MEMCHIP_ADDRESS;
        }

    }
    //===================================
    default:
       switch(address_code){
            case BOOTLOADER_EMERGENCY_PROGRAMM_ADDR: return 0x020000; break;
            case BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR: return (0x030000 - 0x04); break;
            case BOOTLOADER_UPDATE_PROGRAMM_ADDR: return 0x030000; break;
            case BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR: return (0x040000 - 0x04); break;

            default: return INVALID_MEMCHIP_ADDRESS;
       }
    }
}
