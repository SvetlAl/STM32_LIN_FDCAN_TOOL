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

//============= Is id filter enabled? ======================
bool BusManager::range_id_used(){return m_parse_filter.use_range;}

//============= Enable/disable Id filter ======================
void BusManager::set_range_id_used(bool val){m_parse_filter.use_range = val; emit use_range_changed();}

/******************************************************************************************/
/*                                    Trace interface                                     */
/******************************************************************************************/

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

void BusManager::deleteSelectedTrace(){
    m_CanBusTraceModel.deleteSelected();
}
void BusManager::deleteRangeTrace(int begin, int end){
    m_CanBusTraceModel.deleteRange(begin, end);
}
void BusManager::setTraceIdDirection(int id, int can_n){
    m_CanBusTraceModel.setAllMsgsDirection(id, can_n);
}



//===================== save trace ===============================

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

//===================== load trace ===============================

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

//===================== Sort =================================

void BusManager::sortTraceColumn(const int col, bool fromTopToBottom){
    m_CanBusTraceModel.sortColumn(col, fromTopToBottom);
}

void BusManager::switchSortTraceColumn(const int col){
    m_CanBusTraceModel.switchSortColumn(col);
}

void BusManager::clearSortTrace(){
    m_CanBusTraceModel.clear();
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
    emit max_TraceItems_Changed();
}

/******************************************************************************************/
/*                                    Edit Trace interface                                */
/******************************************************************************************/

void BusManager::cropTime(){
    m_CanBusTraceModel.sortColumn(1, false);

    size_t sec_dec = m_CanBusTraceModel.dataPtr(0)->int_time();
  //  qDebug() << "sec_dec " << sec_dec << " time " << m_CanBusTraceModel.dataPtr(0)->time();

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



/****************************************************/
/****** Asynchronous Serial Port Read  **************/
/****************************************************/
