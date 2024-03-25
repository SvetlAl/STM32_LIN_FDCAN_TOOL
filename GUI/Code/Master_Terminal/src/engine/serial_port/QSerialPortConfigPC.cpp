#include "QSerialPortConfigPC.h"

SerialConfig_Preset QSerialPortConfigPC::make_preset(){
    return SerialConfig_Preset(
                m_portnames.dataPtr(m_portnames.getCurrentIndex())->name(),
                m_baudrate.dataPtr(m_baudrate.getCurrentIndex())->value(),
                m_parity.dataPtr(m_parity.getCurrentIndex())->value(),
                m_databits.dataPtr(m_databits.getCurrentIndex())->value(),
                m_stopbits.dataPtr(m_stopbits.getCurrentIndex())->value(),
                m_flowcontrol.dataPtr(m_flowcontrol.getCurrentIndex())->value(),
                m_baudrate.custom_value(),
                m_Cdc_write_timeout,
                m_Cdc_read_timeout,
                m_Cdc_cmd_process_timeout,
                m_Cdc_Jni_drv_timeout,
                m_Cdc_busy_cmd_trials,
                m_max_transmit_data_per_request,
                m_max_recieve_data_per_request,

                m_filename_recieved,
                m_filename_to_send,
                m_filename_scan_recieved,
                m_filename_script_to_send);
}

void QSerialPortConfigPC::set_preset(const SerialConfig_Preset& _preset){
    auto i = 0;
    /************************* Port name ******************************************/
    for(i = 0; i < m_portnames.count(); i++){
        auto name = m_portnames.dataPtr(i)->name();
        if(_preset.getPortname() == name){
            m_portnames.setCurrentIndex(i);
            break;
        }
    }
    /************************* Baud rate ******************************************/
    for(i = 0; i < (m_baudrate.count() -1); i++){

        auto value = m_baudrate.dataPtr(i)->value();
        if(_preset.getBaudrate() == value){
            m_baudrate.setCurrentIndex(i);
            break;
        }
    }
    if((i == (m_baudrate.count() - 1)) & (i == m_baudrate.get_custom_index())){
        m_baudrate.dataPtr(i)->setValue(_preset.getCustom_baudrate());
        if(i != m_baudrate.getCurrentIndex()) m_baudrate.setCurrentIndex(i);
    }
    /************************* Parity ******************************************/
    for(i = 0; i < m_parity.count(); i++){
        auto value = m_parity.dataPtr(i)->value();
        if(_preset.getParity() == value){
            m_parity.setCurrentIndex(i);
            break;
        }
    }
    /************************* Data Bits ******************************************/
    for(i = 0; i < m_databits.count(); i++){
        auto value = m_databits.dataPtr(i)->value();
        if(_preset.getDatabits() == value){
            m_databits.setCurrentIndex(i);
            break;
        }
    }
    /************************* Stop Bits ******************************************/
    for(i = 0; i < m_stopbits.count(); i++){
        auto value = m_stopbits.dataPtr(i)->value();
        if(_preset.getStopbits() == value){
            m_stopbits.setCurrentIndex(i);
            break;
        }
    }
    /************************* Flowcontrol ******************************************/
    for(i = 0; i < m_flowcontrol.count(); i++){
        auto value = m_flowcontrol.dataPtr(i)->value();
        if(_preset.getFlowcontrol() == value){
            m_flowcontrol.setCurrentIndex(i);
            break;
        }
    }
    setCdc_write_timeout(_preset.getWrite_timeout());
    setCdc_read_timeout(_preset.getRead_timeout());
    setCdc_cmd_process_timeout(_preset.getCmd_process_timeout());
    setCdc_Jni_drv_timeout(_preset.getJni_drv_timeout());
    setCdc_busy_cmd_trials(_preset.getBusy_cmd_trials());
    setMax_transmit_data_per_request(_preset.getMax_tx_bytes_per_request());
    setMax_recieve_data_per_request(_preset.getMax_rx_bytes_per_request());


    setFilename_recieved(_preset.getFilename_recieved());
    setFilename_to_send(_preset.getFilename_to_send());
    setFilename_scan_recieved(_preset.getFilename_scan_recieved());
    setFilename_script_to_send(_preset.getFilename_script_to_send());
}


