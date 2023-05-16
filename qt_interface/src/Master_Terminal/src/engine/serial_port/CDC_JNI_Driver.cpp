#include "CDC_JNI_Driver.h"

#ifdef ANDROID_V

bool CDC_JNI_Driver::init(){
    if(m_pSerialPort == nullptr) return RESULT_FAIL;
    m_pSerialPort->setPortName(pSerialPortConfig()->get_portname());
    m_pSerialPort->setBaudRate(QASerialPort::BaudRate::Baud115200);
//    m_pSerialPort->setDataBits(pSerialPortConfig()->get_databits());
//    m_pSerialPort->setParity(pSerialPortConfig()->get_parity());
//    m_pSerialPort->setStopBits(pSerialPortConfig()->get_stopbits());
//    m_pSerialPort->setFlowControl(pSerialPortConfig()->get_flowcontrol());
    print_data(this->m_pSerialPort->portName());
    return RESULT_OK;
}

bool CDC_JNI_Driver::connect(){
    if(this->m_pSerialPort->portName() == "No_Port"){
        print_data("No configuration found. Check USB connection, restart and finish configuration in the Settings.");
        return RESULT_FAIL;
    }
    bool result = this->m_pSerialPort->open(QIODevice::ReadWrite);
    if (!result) {
        print_data("Failed to open port: " +
                   this->m_pSerialPort->portName() +
                   ", error: JNI" );
        m_connection_status = App_settings::ConnectionStatus::Failed;
        m_pConsole->set_connection_status_description(static_cast<int>(m_connection_status));
        return RESULT_FAIL;
    } else {
        print_data("Connected to " + this->m_pSerialPort->portName());
        m_connection_status = App_settings::ConnectionStatus::Connected;
        m_pConsole->set_connection_status_description(static_cast<int>(m_connection_status));
        return RESULT_OK;
    }
}

bool CDC_JNI_Driver::disconnect(){
    m_connection_status = App_settings::ConnectionStatus::Disconnected;
    m_pConsole->set_connection_status_description(static_cast<int>(m_connection_status));

    if(m_pSerialPort->isOpen()){
        m_pSerialPort->close();
        print_data("Disconnected.");
        return RESULT_OK;
    }
    else return RESULT_FAIL;
}

QByteArray CDC_JNI_Driver::exchange_data(const QByteArray &cmd, int custom_timeout){
  //  m_pSerialPort->readAll();
    int _timeout = (custom_timeout == 0) ? m_pSerialPortConfig->Cdc_read_timeout() : custom_timeout;
    if(isConnected() & (m_asynch_read == false)){
        int result = 0;
        int trials = 5;
        while((trials-- > 0) & (result == 0)){
            this->thread()->msleep(m_pSerialPortConfig->Cdc_Jni_drv_timeout());
            try
            {
               result = m_pSerialPort->write(cmd, cmd.size());
            }
            catch ( exception &e )
            {
                 m_pConsole->append_manual_override(e.what());
            };


            if(result != 0) break;
        }
        if(result == 0) return QByteArray("");

        this->thread()->msleep(_timeout /*m_pSerialPortConfig->Cdc_cmd_process_timeout()*/);

        QByteArray response = "";
        try
        {
           response = m_pSerialPort->readAll();
        }
        catch ( exception &e )
        {
             m_pConsole->append_manual_override(e.what());
        };


        return response;
    }
    else return QByteArray("");
}


bool CDC_JNI_Driver::writeData(const QByteArray &data){
    if(isConnected() & (data.size() != 0)){
        int result = 0;
        int trials = 5;
        while((trials-- > 0) & (result == 0)){
            this->thread()->msleep(m_pSerialPortConfig->Cdc_Jni_drv_timeout());
            result = m_pSerialPort->write(data, data.size());
            if(result != 0) break;
        }
        if(result == 0) return false;
        this->thread()->msleep(m_pSerialPortConfig->Cdc_cmd_process_timeout());
    }
    else return false;

    return true;
}

QByteArray CDC_JNI_Driver::readData(int timeout){
    int _timeout = (timeout == 0) ? m_pSerialPortConfig->Cdc_read_timeout() : timeout;
    if(isConnected()){
        this->thread()->msleep(_timeout);
        this->thread()->msleep(m_pSerialPortConfig->Cdc_Jni_drv_timeout());
        this->thread()->msleep(m_pSerialPortConfig->Cdc_cmd_process_timeout());
        return m_pSerialPort->readAll();
    }
    else return QByteArray();
}


void CDC_JNI_Driver::startAsynchReading(int mode){
    if(m_asynch_read) return;
    setAsynch_read(true);
    switch (mode){
    case AsynchReadToConsole:{
        m_pConsole->setPCdc_driver(this);
        QObject::connect(m_pSerialPort, &QASerialPort::readyRead, m_pConsole, &Console::read_serialport_and_append_data);
        return;
        }
    case AsynchReadToScanner:{
       // static size_t counter =0;


        conn = QObject::connect(m_pSerialPort,&QASerialPort::readyRead,this,[this](){
            if (m_pSerialPort->bytesAvailable()) {
                const QByteArray recv_data = m_pSerialPort->readAll();
               // static size_t total_size = 0;
               // total_size += recv_data.size();

               // qDebug() << total_size;
                emit async_data_passover(recv_data);
           //     m_pBusManager->onScannerDataRecieved(recv_data);
            }
        });

        return ;
        }
    }

}
void CDC_JNI_Driver::stopAsynchReading(int mode){
    if(!m_asynch_read) return;
    setAsynch_read(false);
    switch (mode)
    {
    case AsynchReadToConsole:
#ifdef ANDROID_V
        QObject::disconnect(m_pSerialPort, &QASerialPort::readyRead, m_pConsole, &Console::read_serialport_and_append_data);
#else
        QObject::disconnect(m_pSerialPort, &QSerialPort::readyRead, m_pConsole, &Console::read_serialport_and_append_data);
#endif
        return;
    case AsynchReadToScanner:
        QObject::disconnect(conn);

      //  QObject::disconnect(m_pSerialPort, &QSerialPort::readyRead, m_pBusManager, &BusManager::read_serialport_and_append_data);
        return ;
    }

}












#endif

