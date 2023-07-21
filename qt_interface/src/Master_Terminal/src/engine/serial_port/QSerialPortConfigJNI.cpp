#include "QSerialPortConfigJNI.h"

SerialConfig_Preset QSerialPortConfigJNI::make_preset(){
    return SerialConfig_Preset(
                m_portnames.dataPtr(m_portnames.getCurrentIndex())->name(),
                0,
                0,
                0,
                0,
                0,
                0,
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

void QSerialPortConfigJNI::set_preset(const SerialConfig_Preset& _preset){
    setCdc_write_timeout(_preset.getWrite_timeout());
    setCdc_read_timeout(_preset.getRead_timeout());
    setCdc_cmd_process_timeout(_preset.getCmd_process_timeout());
    setCdc_Jni_drv_timeout(_preset.getJni_drv_timeout());
    setCdc_busy_cmd_trials(_preset.getBusy_cmd_trials());
    setMax_recieve_data_per_request(_preset.getMax_rx_bytes_per_request());
    setMax_transmit_data_per_request(_preset.getMax_tx_bytes_per_request());

    setFilename_recieved(_preset.getFilename_recieved());
    setFilename_to_send(_preset.getFilename_to_send());
    setFilename_scan_recieved(_preset.getFilename_scan_recieved());
    setFilename_script_to_send(_preset.getFilename_script_to_send());

}
