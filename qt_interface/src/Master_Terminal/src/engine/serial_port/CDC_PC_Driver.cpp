#include "CDC_PC_Driver.h"

/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/

bool CDC_PC_Driver::init(){
    if(m_pSerialPort == nullptr) return RESULT_FAIL;
    m_pSerialPort->setPortName(pSerialPortConfig()->get_portname());
    m_pSerialPort->setBaudRate(pSerialPortConfig()->get_baudrate());
    m_pSerialPort->setDataBits(pSerialPortConfig()->get_databits());
    m_pSerialPort->setParity(pSerialPortConfig()->get_parity());
    m_pSerialPort->setStopBits(pSerialPortConfig()->get_stopbits());
    m_pSerialPort->setFlowControl(pSerialPortConfig()->get_flowcontrol());

    print_data(this->m_pSerialPort->portName());
    return RESULT_OK;
}

/********************************************************************
 *
 *
 *                     COM-port connect/disconnect
 *
 *
********************************************************************/

bool CDC_PC_Driver::connect(){
    if(this->m_pSerialPort->portName() == ""){
        print_data("No configuration found");
        return RESULT_FAIL;
    }
    bool result = this->m_pSerialPort->open(QIODevice::ReadWrite);
    if (!result) {
        print_data("Failed to open port: " +
                   this->m_pSerialPort->portName() +
                   ", error: " + this->m_pSerialPort->errorString());
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

bool CDC_PC_Driver::disconnect(){
    m_connection_status = App_settings::ConnectionStatus::Disconnected;
    m_pConsole->set_connection_status_description(static_cast<int>(m_connection_status));

    if(m_pSerialPort->isOpen()){
        m_pSerialPort->clear();
        m_pSerialPort->close();
        print_data("Disconnected.");
        return RESULT_OK;
    }
    else return RESULT_FAIL;
}

/********************************************************************
 *
 *
 *                     Exchange data IO
 *
 *
********************************************************************/

QByteArray CDC_PC_Driver::exchange_data(const QByteArray &cmd, int custom_timeout){
    int _timeout = (custom_timeout == 0) ? m_pSerialPortConfig->Cdc_read_timeout() : custom_timeout;
    if(isConnected() & (m_asynch_read == false)){
        m_pSerialPort->write(cmd);
        m_pSerialPort->waitForBytesWritten(m_pSerialPortConfig->Cdc_write_timeout());

        this->thread()->msleep(_timeout /*m_pSerialPortConfig->Cdc_cmd_process_timeout()*/);
        m_pSerialPort->waitForReadyRead(_timeout);

        QByteArray response = m_pSerialPort->readAll();
        return response;
    }
    else return QByteArray();
}


bool CDC_PC_Driver::writeData(const QByteArray &data){
    if(isConnected()){
        m_pSerialPort->write(data);
        m_pSerialPort->waitForBytesWritten(m_pSerialPortConfig->Cdc_write_timeout());
        this->thread()->msleep(m_pSerialPortConfig->Cdc_cmd_process_timeout());
    }
    else return false;

    return true;
}

QByteArray CDC_PC_Driver::readData(int timeout){
    int _timeout = (timeout == 0) ? m_pSerialPortConfig->Cdc_read_timeout() : timeout;
    if(isConnected()){
        m_pSerialPort->waitForBytesWritten(m_pSerialPortConfig->Cdc_write_timeout());
        this->thread()->msleep(m_pSerialPortConfig->Cdc_cmd_process_timeout());
        m_pSerialPort->waitForReadyRead(_timeout);
        return m_pSerialPort->readAll();
    }
    else return QByteArray();
}

/********************************************************************
 *
 *
 *                    Asynchronous mode
 *
 *
********************************************************************/

void CDC_PC_Driver::startAsynchReading(int mode){
    if(m_asynch_read) return;
    setAsynch_read(true);
    switch (mode){
    case AsynchReadToConsole:{
        m_pConsole->setPCdc_driver(this);
        conn = QObject::connect(m_pSerialPort, &QSerialPort::readyRead, m_pConsole, &Console::read_serialport_and_append_data);
        return;
    }
    case AsynchReadToScanner:{
        conn = QObject::connect(m_pSerialPort,&QSerialPort::readyRead,this,[this](){
            if (m_pSerialPort->bytesAvailable()) {
                const QByteArray recv_data = m_pSerialPort->readAll();
                emit async_data_passover(recv_data);} });
        return;
    }
    case AsynchReadInjectionMode:{
        conn = QObject::connect(m_pSerialPort,&QSerialPort::readyRead,this,[this](){
            if (m_pSerialPort->bytesAvailable()) {
                const QByteArray recv_data = m_pSerialPort->readAll();
                //qDebug() << "const QByteArray recv_data" << recv_data.toHex();
                emit async_data_passover(recv_data); } });
        return ;
    }
    }

}
void CDC_PC_Driver::stopAsynchReading(int mode){
    if(!m_asynch_read) return;
    setAsynch_read(false);
    switch (mode)
    {
    case AsynchReadToConsole:
        QObject::disconnect(conn);
        return;
    case AsynchReadToScanner:
        QObject::disconnect(conn);
        return;
    case AsynchReadInjectionMode:
        QObject::disconnect(conn);
        return ;
    }

}

