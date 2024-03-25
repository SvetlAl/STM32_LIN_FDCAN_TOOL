#include "LinBusItem.h"
#include "../command_manager/StringConvertor.h"

//========================================================================
//======================== LinBusItem Trace  =============================
//========================================================================


/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/

/********************************************************************
 *
 *
 *                     Bool and Int Setters/Getters
 *
 *
********************************************************************/

const int LinBusItem::int_time() const {
    return (m_lin_msg.info.seconds*10000 + m_lin_msg.info.msec);
}

const int LinBusItem::int_length() const {
    return (m_lin_msg.info.lin_msg.item.length);
}

void LinBusItem::setIntTime(int _time){
    m_lin_msg.info.seconds = _time >= 10000 ? _time/10000 : 0;
    m_lin_msg.info.msec = _time - (m_lin_msg.info.seconds*10000);
    initTime();
}
const int LinBusItem::intLin() const{
    return m_lin_msg.info.lin_msg.item.role;
}

void LinBusItem::setIntLin(int dir){
    m_lin_msg.info.lin_msg.item.role = dir;
    initLin();
}
const int LinBusItem::int_id() const{
    return m_lin_msg.info.lin_msg.item.id;
}

bool LinBusItem::isSelected() const{
    return m_isSelected;
}

void LinBusItem::setIsSelected(bool newIsSelected){
    if (m_isSelected == newIsSelected)
        return;
    m_isSelected = newIsSelected;
    emit isSelectedChanged();
}

const QByteArray LinBusItem::getByteArray() const{
    return QByteArray::fromRawData(reinterpret_cast<const char*>(m_lin_msg.raw_msg_data), sizeof(lin_message_info_raw));
}

/********************************************************************
 *
 *
 *                     Debug and print
 *
 *
********************************************************************/

void LinBusItem::print() const{
    qDebug() << "************** " << m_isSelected << " **************";
    qDebug() << m_lin_msg.raw_msg_data;
}

/********************************************************************
 *
 *
 *                     Class Setters/Getters
 *
 *
********************************************************************/
//====================== Time ==================================
const QString &LinBusItem::time() const{
    return m_time;
}

void LinBusItem::initTime(){
    QString milsec = QString::number(m_lin_msg.info.msec);

    if(milsec.size() > 4) {
        milsec = "9999";
    }
    if(milsec.size() != 4) {
        while(milsec.size() != 4) {milsec.prepend("0"); }
    }

    QString timeString = QString::number(m_lin_msg.info.seconds) + "." + milsec;
    m_time = timeString;
    emit timeChanged();
}

void LinBusItem::setTime(const QString& str_value){
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

    m_lin_msg.info.seconds = newSeconds;
    m_lin_msg.info.msec = newMiliseconds;
    initTime();
}

const QString &LinBusItem::lin() const{
    return m_lin;
}

void LinBusItem::initLin(){
    switch(m_lin_msg.info.lin_msg.item.role){
    case LIN_ITEM_DEFAULT:
        m_lin = "DEFAULT";
        break;
    case LIN_ITEM_ROLE_MS_DATA:
        m_lin = "MASTER D";
        break;
    case LIN_ITEM_ROLE_MS_RQST:
        m_lin = "MS RQST";
        break;
    case LIN_ITEM_ROLE_SL_DATA:
        m_lin = "SLAVE D";
        break;
    case LIN_ITEM_ROLE_MS_IN:
        m_lin = "MASTER";
        break;
    case LIN_ITEM_ROLE_SL_IN:
        m_lin = "SLAVE";
        break;
    default:
        m_lin = "DEFAULT";
        break;
    }
    emit linChanged();
}

void LinBusItem::setLin(const QString &newLin){
    if(newLin == "DEFAULT"){
        m_lin_msg.info.lin_msg.item.role = LIN_ITEM_DEFAULT;
    }
    else if(newLin == "MASTER D"){
        m_lin_msg.info.lin_msg.item.role = LIN_ITEM_ROLE_MS_DATA;
    }
    else if(newLin == "MS RQST"){
        m_lin_msg.info.lin_msg.item.role = LIN_ITEM_ROLE_MS_RQST;
    }
    else if(newLin == "SLAVE D"){
        m_lin_msg.info.lin_msg.item.role = LIN_ITEM_ROLE_SL_DATA;
    }
    else if(newLin == "MASTER"){
        m_lin_msg.info.lin_msg.item.role = LIN_ITEM_ROLE_MS_IN;
    }
    else if(newLin == "SLAVE"){
        m_lin_msg.info.lin_msg.item.role = LIN_ITEM_ROLE_SL_IN;
    }
    else return;
    initLin();
}

//====================== ID ==================================
const QString &LinBusItem::id() const{
    return m_id;
}

void LinBusItem::initId(){
    m_id = StringConvertor::uint32_t_to_QString_as_HEX(m_lin_msg.info.lin_msg.item.id).toUpper();
    emit idChanged();
}

void LinBusItem::setId(const QString& value){
    bool conversion_result = false;
    uint8_t int_id = value.toInt(&conversion_result, 16);
    if(!conversion_result) return;

    m_lin_msg.info.lin_msg.item.id = int_id;
    initId();
}

//====================== Length ==================================
const QString &LinBusItem::length() const{
    return m_length;
}

void LinBusItem::initLength(){
    m_length = StringConvertor::uint16_t_to_QString_as_HEX(m_lin_msg.info.lin_msg.item.length).toUpper();
    emit lengthChanged();
}

void LinBusItem::setLength(const QString& value){
    uint16_t _id_val = value.toUInt(nullptr, 16);
    m_lin_msg.info.lin_msg.item.length = _id_val;
    initLength();
}

//====================== Data ==================================
const QString &LinBusItem::data() const{
    return m_data;
}

void LinBusItem::initData(){
    QString response = "";
    for(size_t i = 0; i < m_lin_msg.info.lin_msg.item.length; i++){
        response.append(StringConvertor::uint8_t_to_QString_as_HEX(m_lin_msg.info.lin_msg.item.data[i]));
        if(i!= (m_lin_msg.info.lin_msg.item.length - 1))response.append(" ");
    }
    if(m_lin_msg.info.lin_msg.item.length != 0){
        response.append(" ");
        response.append("<font color=\"#FF0000\">");
        response.append(StringConvertor::uint8_t_to_QString_as_HEX(m_lin_msg.info.lin_msg.item.data[m_lin_msg.info.lin_msg.item.length]));
        response.append("</font>");
    }
    m_data = response.toUpper();
    emit dataChanged();
}

void LinBusItem::setData(const QString& value){
    QString _strval = value;
    _strval.remove(" ");
    if(_strval.size() > 16) return;

    QByteArray str_data_bytes = QByteArray::fromHex(_strval.toUtf8());

    memcpy(m_lin_msg.info.lin_msg.item.data, str_data_bytes.constData(), str_data_bytes.size());
    initData();
}

//========================================================================
//======================== LinBusItemMonitor =============================
//========================================================================

/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/

void LinBusItemMonitor::set_lin_msg_data(const lin_message_info_raw &_lin_msg_data){
    // skip period update for slave responses
    if(_lin_msg_data.info.lin_msg.item.length > 9) return;
    if(_lin_msg_data.info.lin_msg.item.role == LIN_ITEM_ROLE_MS_RQST){

    }

    int new_time = int_time();
    m_iperiod = new_time - m_ilast_time;
    m_icount++;
    m_ilast_time = new_time;
    m_last_lin_msg = _lin_msg_data;

    initQStringValues();
    emit linChanged();
    emit idChanged();
    emit lengthChanged();
    emit countChanged();
    emit periodChanged();
    emit dataChanged();
}

void LinBusItemMonitor::initQStringValues(){
    switch(m_last_lin_msg.info.lin_msg.item.role){
    case LIN_ITEM_DEFAULT:
        m_lin = "DEFAULT";
        break;
    case LIN_ITEM_ROLE_MS_DATA:
        m_lin = "MASTER D";
        break;
    case LIN_ITEM_ROLE_MS_RQST:
        m_lin = "MS RQST";
        break;
    case LIN_ITEM_ROLE_SL_DATA:
        m_lin = "SLAVE D";
        break;
    case LIN_ITEM_ROLE_MS_IN:
        m_lin = "MASTER";
        break;
    case LIN_ITEM_ROLE_SL_IN:
        m_lin = "SLAVE";
        break;
    default:
        m_lin = "DEFAULT";
        break;
    }
    m_id = StringConvertor::uint32_t_to_QString_as_HEX(m_last_lin_msg.info.lin_msg.item.id).toUpper();
    //m_id = StringConvertor::uint32_t_to_QString_as_HEX(CAN_ID(m_last_lin_msg.info.msg)).toUpper();

    m_length = StringConvertor::uint16_t_to_QString_as_HEX(m_last_lin_msg.info.lin_msg.item.length).toUpper();
    m_count = QString::number(m_icount, 10);

    m_period = QString::number(m_iperiod, 10);
    int len = m_period.length(); // Get length of string
    m_period.insert(len-1, "."); // Insert '.' before last character


    QString response = "";
    for(size_t i = 0; i < m_last_lin_msg.info.lin_msg.item.length; i++){
        response.append(StringConvertor::uint8_t_to_QString_as_HEX(m_last_lin_msg.info.lin_msg.item.data[i]));
        if(i!= (m_last_lin_msg.info.lin_msg.item.length-1))response.append(" ");
    }

    if(m_last_lin_msg.info.lin_msg.item.length != 0){
        response.append(" ");
        response.append("<font color=\"#FF0000\">");
        response.append(StringConvertor::uint8_t_to_QString_as_HEX(m_last_lin_msg.info.lin_msg.item.data[m_last_lin_msg.info.lin_msg.item.length]));
        response.append("</font>");
    }

    m_data =  response.toUpper();
}

/********************************************************************
 *
 *
 *                     Bool and Int Setters/Getters
 *
 *
********************************************************************/

const int LinBusItemMonitor::int_id() const{
    return m_last_lin_msg.info.lin_msg.item.id;
}

const int LinBusItemMonitor::int_time() const {
    return (m_last_lin_msg.info.seconds*10000 + m_last_lin_msg.info.msec);
}

/********************************************************************
 *
 *
 *                     Class Setters/Getters
 *
 *
********************************************************************/

const QString &LinBusItemMonitor::lin() const
{
    return m_lin;
}

void LinBusItemMonitor::setLin(const QString &newLin)
{
    if (m_lin == newLin)
        return;
    m_lin = newLin;
    emit linChanged();
}

const QString &LinBusItemMonitor::id() const
{
    return m_id;
}

void LinBusItemMonitor::setId(const QString &newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

const QString &LinBusItemMonitor::length() const
{
    return m_length;
}

void LinBusItemMonitor::setLength(const QString &newLength)
{
    if (m_length == newLength)
        return;
    m_length = newLength;
    emit lengthChanged();
}

const QString &LinBusItemMonitor::count() const
{
    return m_count;
}

void LinBusItemMonitor::setCount(const QString &newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    emit countChanged();
}

const QString &LinBusItemMonitor::period() const{
    return m_period;
}

void LinBusItemMonitor::setPeriod(const QString &newPeriod)
{
    if (m_period == newPeriod)
        return;
    m_period = newPeriod;
    emit periodChanged();
}

const QString &LinBusItemMonitor::data() const
{
    return m_data;
}

void LinBusItemMonitor::setData(const QString &newData)
{
    if (m_data == newData)
        return;
    m_data = newData;
    emit dataChanged();
}












