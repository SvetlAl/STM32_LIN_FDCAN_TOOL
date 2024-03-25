#include "BusManager.h"
#include "../command_manager/StringConvertor.h"
/******************************************************************************************/
/******************************************************************************************/
/*                                                                                        */
/*                          Trace and monitor handling                                    */
/*                                                                                        */
/******************************************************************************************/
/******************************************************************************************/



/******************************************************************************************/
/*                                    Scanner filters                                     */
/******************************************************************************************/

bool BusManager::getMonitorScanOn() const{
    return monitorScanOn;
}

void BusManager::setMonitorScanOn(bool newMonitorScanOn){
    if (monitorScanOn == newMonitorScanOn)
        return;
    monitorScanOn = newMonitorScanOn;
    traceScanOn = !newMonitorScanOn;
    emit monitorScanOnChanged();
}

//====================================== FD CAN ============================================

bool BusManager::fd_getMonitorScanOn() const{
    return fd_monitorScanOn;
}

void BusManager::fd_setMonitorScanOn(bool newMonitorScanOn){
    if (fd_monitorScanOn == newMonitorScanOn)
        return;
    fd_monitorScanOn = newMonitorScanOn;
    fd_traceScanOn = !newMonitorScanOn;
    emit fd_monitorScanOnChanged();
}

//========================================= LIN ============================================
bool BusManager::getMonitorLinScanOn() const{
    return monitorLinScanOn;
}
void BusManager::setMonitorLinScanOn(bool newMonitorScanOn){
    if (monitorLinScanOn == newMonitorScanOn)
        return;
    monitorLinScanOn = newMonitorScanOn;
    traceLinScanOn = !newMonitorScanOn;
    emit monitorLinScanOnChanged();
}


//====================================== ST CAN ============================================
void BusManager::setFilterCan(const int can_num, bool isEnabled){
    if(can_num == 1){
        m_parse_filter.m_can1 = isEnabled;
    }
    else if(can_num == 2){
        m_parse_filter.m_can2 = isEnabled;
    }
}

void BusManager::setFilterRange(const int start, const int end, bool isEnabled){
    if(isEnabled){
        m_parse_filter.start_id = start;
        m_parse_filter.end_id = end;
    }
    set_range_id_used(isEnabled);
}

//====================================== FD CAN ============================================
void BusManager::fd_setFilterCan(const int can_num, bool isEnabled){
    if(can_num == 1){
        m_fd_parse_filter.m_can1 = isEnabled;
    }
    else if(can_num == 2){
        m_fd_parse_filter.m_can2 = isEnabled;
    }
}

void BusManager::fd_setFilterRange(const int start, const int end, bool isEnabled){
    if(isEnabled){
        m_fd_parse_filter.start_id = start;
        m_fd_parse_filter.end_id = end;
    }
    fd_set_range_id_used(isEnabled);
}

//====================================== ST CAN ============================================
//============= Is id filter enabled? ======================
bool BusManager::range_id_used(){return m_parse_filter.use_range;}

//============= Enable/disable Id filter ======================
void BusManager::set_range_id_used(bool val){m_parse_filter.use_range = val; emit use_range_changed();}

//====================================== FD CAN ============================================
//============= Is id filter enabled? ======================
bool BusManager::fd_range_id_used(){return m_fd_parse_filter.use_range;}

//============= Enable/disable Id filter ======================
void BusManager::fd_set_range_id_used(bool val){m_fd_parse_filter.use_range = val; emit fd_use_range_changed();}


/******************************************************************************************/
/*                                    Trace interface                                     */
/******************************************************************************************/

//====================================== ST CAN ============================================
void BusManager::createNewTraceItem(const QString &newItem, bool _default){
    if(_default){
        can_message_info_raw default_item;
        default_item.info.start_char = '@';
        default_item.info.can_number = 2;
        default_item.info.msec = 0;
        default_item.info.seconds = 0;
        default_item.info.msg.id.std_id.id_lowbyte = 0x01;
        default_item.info.msg.id.std_id.id_highbyte = 0x00;
        default_item.info.msg.ide = 0;
        default_item.info.msg.dlc = 8;

        default_item.info.msg.data[0] = 0;
        default_item.info.msg.data[1] = 0;
        default_item.info.msg.data[2] = 0;
        default_item.info.msg.data[3] = 0;
        default_item.info.msg.data[4] = 0;
        default_item.info.msg.data[5] = 0;
        default_item.info.msg.data[6] = 0;
        default_item.info.msg.data[7] = 0;

        m_CanBusTraceModel.addItem(QByteArray::fromRawData(reinterpret_cast<const char*>(default_item.raw_msg_data), sizeof(can_message_info_raw)));

    }
    else m_CanBusTraceModel.addItem(QByteArray::fromHex(newItem.toUtf8()));
}
//====================================== FD CAN ============================================
void BusManager::fd_createNewTraceItem(const QString &newItem, bool _default){
    if(_default){
        fdcan_message_info_raw default_item;
        default_item.info.start_char = '#';
        default_item.info.can_number = 1;
        default_item.info.msec = 1;
        default_item.info.seconds = 1;
        default_item.info.msg.msg_hdr.id = 0x00000001;
        default_item.info.msg.msg_hdr.dlc = 0;
        default_item.info.msg.msg_hdr.fdflags.byte = 0x00;
        default_item.info.msg.msg_hdr.fdflags.flags.ESI = FDCAN_FLAG_RST;
        default_item.info.msg.msg_hdr.fdflags.flags.XTD = FDCAN_FLAG_RST;
        default_item.info.msg.msg_hdr.fdflags.flags.FDF = FDCAN_FLAG_RST;
        default_item.info.msg.msg_hdr.fdflags.flags.BRS = FDCAN_FLAG_RST;
        default_item.info.msg.msg_hdr.rxts = 0x0000;
        const QByteArray _data = "";

        m_FdCanBusTraceModel.addItem(QByteArray::fromRawData(reinterpret_cast<const char*>(default_item.raw_msg_data), sizeof(fdcan_message_info_raw)) , _data);
     }
    else{
        //TODO
    }
}

//====================================== ST CAN ============================================
void BusManager::deleteSelectedTrace(){
    m_CanBusTraceModel.deleteSelected();
}
void BusManager::deleteRangeTrace(int begin, int end){
    m_CanBusTraceModel.deleteRange(begin, end);
}
void BusManager::setTraceIdDirection(int id, int can_n){
    m_CanBusTraceModel.setAllMsgsDirection(id, can_n);
}
//====================================== FD CAN ============================================
void BusManager::fd_deleteSelectedTrace(){
    m_FdCanBusTraceModel.deleteSelected();
}
void BusManager::fd_deleteRangeTrace(int begin, int end){
    m_FdCanBusTraceModel.deleteRange(begin, end);
}
void BusManager::fd_setTraceIdDirection(int id, int can_n){
    m_FdCanBusTraceModel.setAllMsgsDirection(id, can_n);
}


//===================== save trace ===============================
//====================================== ST CAN ============================================
void BusManager::saveTrace(const QString &filename){
    if(m_CanBusTraceModel.length()==0){
        qDebug() << ("FAILED: no data in the model.");
        return;
    }
    QFile traceFile(filename);
    bool open = traceFile.open(QFile::WriteOnly);
    if(!open){
        qDebug() << ("FAILED: The file unavailable.");
        return;
    }

    QDataStream stream(&traceFile);
    for(size_t i = 0; i < m_CanBusTraceModel.count() ; i++){
        QByteArray line = m_CanBusTraceModel.raw_data(i);
        stream.writeRawData(line, line.size());
    }
    traceFile.close();
}

//====================================== FD CAN ============================================
void BusManager::fd_saveTrace(const QString &filename){
    if(m_FdCanBusTraceModel.length()==0){
        qDebug() << ("FAILED: no data in the model.");
        return;
    }
    QFile traceFile(filename);
    bool open = traceFile.open(QFile::WriteOnly);
    if(!open){
        qDebug() << ("FAILED: The file unavailable.");
        return;
    }

    QDataStream stream(&traceFile);
    for(size_t i = 0; i < m_FdCanBusTraceModel.count() ; i++){
        QByteArray line = m_FdCanBusTraceModel.raw_data(i);
        stream.writeRawData(line, line.size());
    }
    traceFile.close();
}

//===================== load trace ===============================
//====================================== ST CAN ============================================
void BusManager::loadTrace(const QString &filename){

    QFile traceFile(filename);
    bool open = traceFile.open(QFile::ReadOnly);
    if(!open){
        qDebug() << ("FAILED: File read.");
        return;
    }

    if(traceFile.size() % sizeof(can_message_info_raw) != 0){
        qDebug() << ("FAILED: File read length mismatch.");
        return;
    }

    const size_t chunksize = sizeof(can_message_info_raw);
    QDataStream stream(&traceFile);
    QByteArray data;
    qint64 dataLength = traceFile.size();
    data.resize(dataLength);
    stream.readRawData(data.data(), dataLength);

    m_CanBusMonitorModel.reset();
    m_CanBusTraceModel.clear();

    for(size_t i = 0 ; i < dataLength; i+= chunksize){
        m_CanBusTraceModel.addItem(data.mid(i, chunksize));
        m_CanBusMonitorModel.addItem(data.mid(i, chunksize));
    }

    emit cdc_trace_emptyChanged();
    traceFile.close();
}
//====================================== FD CAN ============================================

void BusManager::fd_loadTrace(const QString &filename){

    QFile traceFile(filename);
    bool open = traceFile.open(QFile::ReadOnly);
    if(!open){
        qDebug() << ("FAILED: File read.");
        return;
    }

    const size_t hdr_chunksize = sizeof(fdcan_message_info_raw);

    QDataStream stream(&traceFile);
    QByteArray data;
    qint64 dataLength = traceFile.size();
    data.resize(dataLength);
    stream.readRawData(data.data(), dataLength);

    m_FdCanBusMonitorModel.reset();
    m_FdCanBusTraceModel.clear();

    size_t i = 0;
    size_t pos = 0;
    while(i < dataLength){
        QByteArray header = (data.mid(pos, hdr_chunksize));

        uint8_t data_length = FDCAN_ParseBuffer::calculate_fdmsg_data_length(header);
        pos += hdr_chunksize;

        i += (hdr_chunksize + data_length);
        QByteArray _data = (data.mid(pos, data_length));
        pos += data_length;

        m_FdCanBusTraceModel.addItem(header, _data);
        m_FdCanBusMonitorModel.addItem(header, _data);
    }

    emit cdc_trace_emptyChanged();
    traceFile.close();
}


//===================== Sort =================================
//====================================== ST CAN ============================================
void BusManager::sortTraceColumn(const int col, bool fromTopToBottom){
    m_CanBusTraceModel.sortColumn(col, fromTopToBottom);
}

void BusManager::switchSortTraceColumn(const int col){
    m_CanBusTraceModel.switchSortColumn(col);
}

void BusManager::clearSortTrace(){
    m_CanBusTraceModel.clear();
}
//====================================== FD CAN ============================================
void BusManager::fd_sortTraceColumn(const int col, bool fromTopToBottom){
    m_FdCanBusTraceModel.sortColumn(col, fromTopToBottom);
}

void BusManager::fd_switchSortTraceColumn(const int col){
    m_FdCanBusTraceModel.switchSortColumn(col);
}

void BusManager::fd_clearSortTrace(){
    m_FdCanBusTraceModel.clear();
}

//==================== LIN ====================================

void BusManager::sortLinTraceColumn(const int col, bool fromTopToBottom){
    m_LinBusTraceModel.sortColumn(col, fromTopToBottom);
}
void BusManager::switchLinSortTraceColumn(const int col){
    m_LinBusTraceModel.switchSortColumn(col);
}
void BusManager::clearLinSortTrace(){
    m_LinBusTraceModel.clear();
}

const QString BusManager::max_TraceItems() const{
   return QString::number(m_CanBusTraceModel.max_items());
}

void BusManager::setMaxTraceItems(const QString &newMax_items){
    bool result = false;
    int new_val = newMax_items.toInt(&result, 10);
    if(!result) return;
    if(new_val > 0xFFFFFFFF) return;
    m_CanBusTraceModel.setMax_items(new_val);
    m_FdCanBusTraceModel.setMax_items(new_val);
    emit max_TraceItems_Changed();
    emit fd_max_TraceItems_Changed();
}

const QString BusManager::fd_max_TraceItems() const{
   return QString::number(m_FdCanBusTraceModel.max_items());
}

void BusManager::fd_setMaxTraceItems(const QString &newMax_items){
    setMaxTraceItems(newMax_items);
}
/******************************************************************************************/
/*                                    Edit Trace interface                                */
/******************************************************************************************/

//====================================== ST CAN ============================================
void BusManager::cropTime(){
    m_CanBusTraceModel.sortColumn(1, false);

    size_t sec_dec = m_CanBusTraceModel.dataPtr(0)->int_time();

    if(sec_dec > 0xFFFFFFFF) return;
    m_CanBusTraceModel.deductTimeStamp(sec_dec);
}

void BusManager::deleteTimeRangeTrace(const QString &begin, const QString &end){
//    m_CanBusTraceModel.sortColumn(1, false);
    const int begin_time = StringConvertor::can_timestamp_to_intTime(begin);
    if(begin_time < 0) return;
    const int end_time = StringConvertor::can_timestamp_to_intTime(end);
    if(end_time < 0) return;
    m_CanBusTraceModel.deleteTimeStampRange(begin_time, end_time);
}

//====================================== FD CAN ============================================
void BusManager::fd_cropTime(){
    m_FdCanBusTraceModel.sortColumn(1, false);

    uint32_t sec_dec = m_FdCanBusTraceModel.dataPtr(0)->int_time();
    //if(sec_dec > 0xFFFFFFFF) return;
    m_FdCanBusTraceModel.deductTimeStamp(sec_dec);
}

void BusManager::fd_deleteTimeRangeTrace(const QString &begin, const QString &end){
    const int begin_time = StringConvertor::can_timestamp_to_intTime(begin);
    if(begin_time < 0) return;
    const int end_time = StringConvertor::can_timestamp_to_intTime(end);
    if(end_time < 0) return;
    m_FdCanBusTraceModel.deleteTimeStampRange(begin_time, end_time);
}

/******************************************************************************************/
/******************************************************************************************/
/*                                                                                        */
/*                          Override and discard filters                                  */
/*                                                                                        */
/******************************************************************************************/
/******************************************************************************************/

/******************************************************************************************/
/*                                    Scanner filters                                     */
/******************************************************************************************/




/******************************************************************************************/
/******************************************************************************************/
/*                                                                                        */
/*                          Serial data reading and parsing                               */
/*                                                                                        */
/******************************************************************************************/
/******************************************************************************************/

/******************************************************************************************/
/*                                       Start/stop                                       */
/******************************************************************************************/


/******************************************************************************************/
/*                          On asynch scanner data recieved                               */
/******************************************************************************************/

bool BusManager::processIncomingData(const QByteArray _data){
   m_parse_buffer.append(_data);
   QList<QByteArray> data_list = m_parse_buffer.extractAllParseableLines();

    foreach (const auto item, data_list) {
        if(traceScanOn) m_CanBusTraceModel.addItem(item, m_parse_filter);
        if(monitorScanOn) m_CanBusMonitorModel.addItem(item, m_parse_filter);
    }

    return true;
}

bool BusManager::fd_processIncomingData(const QByteArray _data){
   m_fd_parse_buffer.append(_data);
   QList<QByteArray> data_list = m_fd_parse_buffer.extractAllParseableLines();


    foreach (const auto item, data_list) {
        QByteArray hdr = item.mid(0, FDCAN_ParseBuffer::chunkSize);
        QByteArray msg = item.mid(FDCAN_ParseBuffer::chunkSize);

        if(msg.size() == FDCAN_ParseBuffer::calculate_fdmsg_data_length(hdr)){
            if(fd_traceScanOn) m_FdCanBusTraceModel.addItem(hdr, msg, m_parse_filter);
            if(fd_monitorScanOn) m_FdCanBusMonitorModel.addItem(hdr, msg, m_parse_filter);
        }
        else qDebug() << item.toHex();
    }
    return true;
}


bool BusManager::processLinIncomingData(const QByteArray _data){
    m_lin_parse_buffer.append(_data);
    QList<QByteArray> data_list = m_lin_parse_buffer.extractAllParseableLines();

     foreach (const auto item, data_list) {
         if(traceLinScanOn) m_LinBusTraceModel.addItem(item);
         if(monitorLinScanOn) m_LinBusMonitorModel.addItem(item);
     }
     return true;
}

/******************************************************************************************/
/******************************************************************************************/
/*                                                                                        */
/*                                 Aux trace/monitor                                      */
/*                                                                                        */
/******************************************************************************************/
/******************************************************************************************/
void BusManager::loadAuxTrace(const QString &filename){

    QFile traceFile(filename);
    bool open = traceFile.open(QFile::ReadOnly);
    if(!open){
        qDebug() << ("FAILED: File read.");
        return;
    }
    if(traceFile.size() % sizeof(can_message_info_raw) != 0){
        qDebug() << ("FAILED: File read length mismatch.");
        return;
    }
    const size_t chunksize = sizeof(can_message_info_raw);
    QDataStream stream(&traceFile);
    QByteArray data;
    qint64 dataLength = traceFile.size();
    data.resize(dataLength);
    stream.readRawData(data.data(), dataLength);

    m_CanBusTraceModelAux.clear();

    for(size_t i = 0 ; i < dataLength; i+= chunksize){
        m_CanBusTraceModelAux.addItem(data.mid(i, chunksize));
        m_CanBusMonitorModelAux.addItem(data.mid(i, chunksize));
    }

    traceFile.close();
    emit aux_trace_sizeChanged();
}

int BusManager::aux_trace_size() const{
    return m_CanBusTraceModelAux.size();
}


void BusManager::fd_loadAuxTrace(const QString &filename){

    QFile traceFile(filename);
    bool open = traceFile.open(QFile::ReadOnly);
    if(!open){
        qDebug() << ("FAILED: File read.");
        return;
    }

    const size_t hdr_chunksize = sizeof(fdcan_message_info_raw);

    QDataStream stream(&traceFile);
    QByteArray data;
    qint64 dataLength = traceFile.size();
    data.resize(dataLength);
    stream.readRawData(data.data(), dataLength);

    m_FdCanBusMonitorModelAux.reset();
    m_FdCanBusTraceModelAux.clear();

    size_t i = 0;
    size_t pos = 0;
    while(i < dataLength){
        QByteArray header = (data.mid(pos, hdr_chunksize));
        uint8_t data_length = FDCAN_ParseBuffer::calculate_fdmsg_data_length(header);
        pos += hdr_chunksize;

        i += (hdr_chunksize + data_length);
        QByteArray _data = (data.mid(pos, data_length));
        pos += data_length;

        m_FdCanBusTraceModelAux.addItem(header, _data);
        m_FdCanBusMonitorModelAux.addItem(header, _data);
    }

    emit fd_aux_trace_sizeChanged();
    traceFile.close();
}

int BusManager::fd_aux_trace_size() const{
    return m_FdCanBusTraceModelAux.size();
}
/****************************************************/
/****** Asynchronous Serial Port Read  **************/
/****************************************************/
