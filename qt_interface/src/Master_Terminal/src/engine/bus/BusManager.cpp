#include "BusManager.h"

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
        m_CanBusTraceModel.addItem(QByteArray::fromHex(default_init_data));
    }
    else m_CanBusTraceModel.addItem(QByteArray::fromHex(newItem.toUtf8()));
}

void BusManager::deleteSelectedTrace(){m_CanBusTraceModel.deleteSelected();}
void BusManager::deleteRangeTrace(int begin, int end){m_CanBusTraceModel.deleteRange(begin, end);}



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

void BusManager::cropTime(){
    m_CanBusTraceModel.sortColumn(1, false);

    size_t sec_dec = m_CanBusTraceModel.dataPtr(0)->int_time();
  //  qDebug() << "sec_dec " << sec_dec << " time " << m_CanBusTraceModel.dataPtr(0)->time();

    if(sec_dec > 0xFFFFFFFF) return;
    m_CanBusTraceModel.deductTimeStamp(sec_dec);
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
/*
void BusManager::startScanThread(){

}
void BusManager::stopScanThread(){

}
*/
/******************************************************************************************/
/*                          On asynch scanner data recieved                               */
/******************************************************************************************/

bool BusManager::processIncomingData(const QByteArray _data){
//    static size_t total_size = 0;
//    total_size += _data.size();
//    qDebug() << total_size;

    m_parse_buffer.append(_data);
   QList<QByteArray> data_list = m_parse_buffer.extractAllParseableLines();

    foreach (const auto item, data_list) {
      //      qDebug() << item.size();
      //      qDebug() << item.toHex(' ');

        if(traceScanOn) m_CanBusTraceModel.addItem(item, m_parse_filter);
        if(monitorScanOn) m_CanBusMonitorModel.addItem(item, m_parse_filter);
    }

    /*
     *     CanBusTraceProperty m_CanBusTraceModel;
    CanBusMonitorProperty m_CanBusMonitorModel;
    m_parse_buffer.append(_data);
    connect(&m_BusParser, SIGNAL(finished()), this, SLOT(onParseFinished()));
    m_BusParser.start();*/
    return true;
}





/****************************************************/
/****** Asynchronous Serial Port Read  **************/
/****************************************************/
