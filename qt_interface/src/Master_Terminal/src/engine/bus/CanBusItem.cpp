#include "CanBusItem.h"
#include "../command_manager/StringConvertor.h"

//========================================================================
//======================== CanBusItem Trace  =============================
//========================================================================


//====================== Time ==================================
const QString &CanBusItem::time() const{
    return m_time;
}

void CanBusItem::initTime(){
    QString milsec = QString::number(m_can_msg.info.msec);

    if(milsec.size() > 4) {
        milsec = "9999";
    }
    if(milsec.size() != 4) {
        while(milsec.size() != 4) {milsec.prepend("0"); }
    }

    QString timeString = QString::number(m_can_msg.info.seconds) + "." + milsec;
    m_time = timeString;
    emit timeChanged();
}

void CanBusItem::setTime(const QString& str_value){
    int dotIndex = str_value.indexOf(".");
    if (dotIndex == -1 || str_value.count(".") > 1) {
        // Invalid input format
        return;
    }

    QString secondsStr = str_value.left(dotIndex);
    QString milisecondsStr = str_value.mid(dotIndex + 1);

    bool ok = false;
    uint32_t newSeconds = secondsStr.toUInt(&ok);
    if (!ok) {
        // Invalid seconds value
        return;
    }

    uint16_t newMiliseconds = milisecondsStr.toUInt(&ok);
    if (!ok || (newMiliseconds >= 10000)) {
        // Invalid miliseconds value
        return;
    }

    m_can_msg.info.seconds = newSeconds;
    m_can_msg.info.msec = newMiliseconds;
    initTime();
}


//====================== CAN ==================================
const QString &CanBusItem::can() const{
    return m_can;
}

void CanBusItem::initCan(){
    m_can = (m_can_msg.info.can_number == 1) ? "CAN 1" : "CAN 2";
    emit canChanged();
}

void CanBusItem::setCan(const QString &newCan){
    if(newCan == "CAN 1")(m_can_msg.info.can_number = 1);
    else if(newCan == "CAN 2")(m_can_msg.info.can_number = 2);
    else return;
    initCan();
}
void CanBusItem::setIntCan(int dir){
    if(dir == 1){
        m_can_msg.info.can_number = 1;
    }
    else if(dir == 2){
        m_can_msg.info.can_number = 2;
    }
    else return;
    initCan();
}


//====================== ID ==================================
const QString &CanBusItem::id() const{
    return m_id;
}

void CanBusItem::initId(){
    m_id = StringConvertor::uint32_t_to_QString_as_HEX(CAN_ID(m_can_msg.info.msg)).toUpper();
    emit idChanged();
}

void CanBusItem::setId(const QString& value){
    bool conversion_result = false;
    uint32_t int_id = value.toInt(&conversion_result, 16);
    if(!conversion_result) return;
    if((m_can_msg.info.msg.ide == STD_ID) & (int_id > 0x7FF)) return;
    if((m_can_msg.info.msg.ide == EXT_ID) & (int_id > 0x1FFFFFFF)) return;

    if(m_can_msg.info.msg.ide == EXT_ID){
        m_can_msg.info.msg.id.ext_id = int_id;
        initId();
        return;
    }

    else if(m_can_msg.info.msg.ide == STD_ID){
        m_can_msg.info.msg.id.std_id.id_highbyte = (uint8_t)((int_id >> 8) & ~0xFF00);
        m_can_msg.info.msg.id.std_id.id_lowbyte = (uint8_t)((int_id >> 0) & ~0xFF00);
        initId();
        return;
    }
}


//====================== DLC ==================================
const QString &CanBusItem::dlc() const{
    return m_dlc;
}

void CanBusItem::initDlc(){
    m_dlc = StringConvertor::uint16_t_to_QString_as_HEX(m_can_msg.info.msg.dlc).toUpper();
    emit dlcChanged();
}

void CanBusItem::setDlc(const QString& value){
    if(value.size() <= 4){
        uint16_t _id_val = value.toUInt(nullptr, 16);
        if(_id_val > 8) return;
        m_can_msg.info.msg.dlc = _id_val;
        initDlc();
    }
}


//====================== Data ==================================
const QString &CanBusItem::data() const{
    return m_data;
}

void CanBusItem::initData(){
    QString response = "";
    for(size_t i = 0; i < m_can_msg.info.msg.dlc; i++){
        response.append(StringConvertor::uint8_t_to_QString_as_HEX(m_can_msg.info.msg.data[i]));
        if(i!= (m_can_msg.info.msg.dlc-1))response.append(" ");
    }
    m_data = response.toUpper();
    emit dataChanged();
}

void CanBusItem::setData(const QString& value){
    QString _strval = value;
    _strval.remove(" ");
    if(_strval.size() > 16) return;

    QByteArray str_data_bytes = QByteArray::fromHex(_strval.toUtf8());

    memcpy(m_can_msg.info.msg.data, str_data_bytes.constData(), str_data_bytes.size());
    initData();
}


//====================== Ide ==================================
const QString &CanBusItem::ide() const{
    return m_ide;
}

void CanBusItem::initIde(){
    if(m_can_msg.info.msg.ide == 1) m_ide = "EXT";
    else  m_ide = "STD";
    emit ideChanged();
}

void CanBusItem::setIde(const QString &new_ide){
    qDebug() << new_ide;
    if(new_ide == "EXT") m_can_msg.info.msg.ide = 1;
    else if(new_ide == "STD") m_can_msg.info.msg.ide = 0;
    else return;
    initIde();
}



//====================== Misc ==================================


bool CanBusItem::isSelected() const{
    return m_isSelected;
}

void CanBusItem::setIsSelected(bool newIsSelected){
    if (m_isSelected == newIsSelected)
        return;
    m_isSelected = newIsSelected;
    emit isSelectedChanged();
}


bool CanBusItem::bool_ext_ide() const{
    if(m_can_msg.info.msg.ide == 1) return true;
    else return false;
}

void CanBusItem::print() const{
    qDebug() << "************** " << m_isSelected << " **************";
    qDebug() << m_can_msg.raw_msg_data;
}






//========================================================================
//======================== CanBusItemMonitor =============================
//========================================================================
const int CanBusItemMonitor::int_id() const{
    return CAN_ID(m_last_can_msg.info.msg);
}

const QString &CanBusItemMonitor::can() const
{
    return m_can;
}

void CanBusItemMonitor::setCan(const QString &newCan)
{
    if (m_can == newCan)
        return;
    m_can = newCan;
    emit canChanged();
}

const QString &CanBusItemMonitor::id() const
{
    return m_id;
}

void CanBusItemMonitor::setId(const QString &newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

const QString &CanBusItemMonitor::dlc() const
{
    return m_dlc;
}

void CanBusItemMonitor::setDlc(const QString &newDlc)
{
    if (m_dlc == newDlc)
        return;
    m_dlc = newDlc;
    emit dlcChanged();
}

const QString &CanBusItemMonitor::count() const
{
    return m_count;
}

void CanBusItemMonitor::setCount(const QString &newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    emit countChanged();
}

const QString &CanBusItemMonitor::period() const{
    return m_period;
}

void CanBusItemMonitor::setPeriod(const QString &newPeriod)
{
    if (m_period == newPeriod)
        return;
    m_period = newPeriod;
    emit periodChanged();
}

const QString &CanBusItemMonitor::data() const
{
    return m_data;
}

void CanBusItemMonitor::setData(const QString &newData)
{
    if (m_data == newData)
        return;
    m_data = newData;
    emit dataChanged();
}


void CanBusItemMonitor::set_can_msg_data(const can_message_info_raw &_can_msg_data){
    m_last_can_msg = _can_msg_data;
    if(_can_msg_data.info.msg.dlc > 8 ) return;
  //  if(m_last_can_msg.info.can_number == 2) qDebug() << "*******";
    int new_time = int_time();
    m_iperiod = new_time - m_ilast_time;

  //  if(m_last_can_msg.info.can_number == 2) qDebug() << QString::number((CAN_ID(m_last_can_msg.info.msg)), 16) << "  " << m_ilast_time << "  " << new_time << "  " << m_iperiod;
    m_ilast_time = new_time;
    m_icount++;
    initQStringValues();
    emit canChanged();
    emit idChanged();
    emit dlcChanged();
    emit countChanged();
    emit periodChanged();
    emit dataChanged();
}

void CanBusItemMonitor::initQStringValues(){
    m_can = (m_last_can_msg.info.can_number == 1) ? "CAN 1" : "CAN 2";
    m_id = StringConvertor::uint32_t_to_QString_as_HEX(CAN_ID(m_last_can_msg.info.msg)).toUpper();
    m_dlc = StringConvertor::uint16_t_to_QString_as_HEX(m_last_can_msg.info.msg.dlc).toUpper();
    m_count = QString::number(m_icount, 10);

    m_period = QString::number(m_iperiod, 10);
    int len = m_period.length(); // Get length of string
    m_period.insert(len-1, "."); // Insert '.' before last character


    QString response = "";
    for(size_t i = 0; i < m_last_can_msg.info.msg.dlc; i++){
        response.append(StringConvertor::uint8_t_to_QString_as_HEX(m_last_can_msg.info.msg.data[i]));
        if(i!= (m_last_can_msg.info.msg.dlc-1))response.append(" ");
    }
    m_data =  response.toUpper();
}









