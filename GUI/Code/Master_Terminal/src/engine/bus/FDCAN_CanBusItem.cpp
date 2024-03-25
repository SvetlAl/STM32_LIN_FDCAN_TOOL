#include "FDCAN_CanBusItem.h"
#include "../command_manager/StringConvertor.h"
#include "QRegExp"

//========================================================================
//======================== CanBusItem Trace  =============================
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

const int FDCAN_CanBusItem::int_time() const {
    return (m_fdcan_hdr.info.seconds*10000 + m_fdcan_hdr.info.msec);
}
const int FDCAN_CanBusItem::int_dlc() const {
    return (m_fdcan_hdr.info.msg.msg_hdr.dlc);
}

void FDCAN_CanBusItem::setIntTime(int _time){
    m_fdcan_hdr.info.seconds = _time >= 10000 ? _time/10000 : 0;
    m_fdcan_hdr.info.msec = _time - (m_fdcan_hdr.info.seconds*10000);
    initTime();
}
const int FDCAN_CanBusItem::intCan() const{
    return m_fdcan_hdr.info.can_number;
}

void FDCAN_CanBusItem::setIntCan(int dir){
    if(dir == 1){
        m_fdcan_hdr.info.can_number = 1;
    }
    else if(dir == 2){
        m_fdcan_hdr.info.can_number = 2;
    }
    else return;
    initCan();
}
const int FDCAN_CanBusItem::int_id() const{
    return m_fdcan_hdr.info.msg.msg_hdr.id;
}

bool FDCAN_CanBusItem::isSelected() const{
    return m_isSelected;
}

void FDCAN_CanBusItem::setIsSelected(bool newIsSelected){
    if (m_isSelected == newIsSelected)
        return;
    m_isSelected = newIsSelected;
    emit isSelectedChanged();
}

const QByteArray FDCAN_CanBusItem::getByteArray() const{
    QByteArray raw_data = QByteArray::fromRawData(reinterpret_cast<const char*>(m_fdcan_hdr.raw_msg_data), sizeof(fdcan_message_info_raw));
    raw_data.append(m_data_array);
    return raw_data;
}


const QByteArray &FDCAN_CanBusItem::msg_data() const{
    return m_data_array;
}

void FDCAN_CanBusItem::set_msg_data(const QByteArray &newData_array){
    m_data_array = newData_array;
}

/********************************************************************
 *
 *
 *                     Debug and print
 *
 *
********************************************************************/

void FDCAN_CanBusItem::print() const{
    qDebug() << "************** " << m_isSelected << " **************";
    qDebug() << m_fdcan_hdr.raw_msg_data;
}

/********************************************************************
 *
 *
 *                     Class Setters/Getters
 *
 *
********************************************************************/
//====================== Time ==================================
const QString &FDCAN_CanBusItem::time() const{
    return m_time;
}

void FDCAN_CanBusItem::initTime(){
    QString milsec = QString::number(m_fdcan_hdr.info.msec);

    if(milsec.size() > 4) {
        milsec = "9999";
    }
    if(milsec.size() != 4) {
        while(milsec.size() != 4) {milsec.prepend("0"); }
    }

    QString timeString = QString::number(m_fdcan_hdr.info.seconds) + "." + milsec;
    m_time = timeString;
    emit timeChanged();
}

void FDCAN_CanBusItem::setTime(const QString& str_value){
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

    m_fdcan_hdr.info.seconds = newSeconds;
    m_fdcan_hdr.info.msec = newMiliseconds;
    initTime();
}

const QString &FDCAN_CanBusItem::can() const{
    return m_can;
}

void FDCAN_CanBusItem::initCan(){
    m_can = (m_fdcan_hdr.info.can_number == FDCAN1_E) ? "CAN 1" : "CAN 2";
    emit canChanged();
    emit colorChanged();
}

void FDCAN_CanBusItem::setCan(const QString &newCan){
    if(newCan == "CAN 1")(m_fdcan_hdr.info.can_number = FDCAN1_E);
    else if(newCan == "CAN 2")(m_fdcan_hdr.info.can_number = FDCAN2_E);
    else return;
    initCan();
}

// is a msg id extended?
/*
bool FDCAN_CanBusItem::bool_ext_ide() const{
    if(m_can_msg.info.msg.ide == 1) return true;
    else return false;
}
*/

//====================== ID ==================================
const QString &FDCAN_CanBusItem::id() const{
    return m_id;
}

void FDCAN_CanBusItem::initId(){
    /*
    m_id = StringConvertor::uint32_t_to_QString_as_HEX(CAN_ID(m_can_msg.info.msg)).toUpper();
    */
    m_id = StringConvertor::uint32_t_to_QString_as_HEX(m_fdcan_hdr.info.msg.msg_hdr.id).toUpper();
    const static QRegularExpression dlc_zero_crop = QRegularExpression("^0+");
    m_id = m_id.remove(dlc_zero_crop);
    emit idChanged();
}

void FDCAN_CanBusItem::setId(const QString& value){
    bool conversion_result = false;
    uint32_t int_id = value.toInt(&conversion_result, 16);
    if(!conversion_result) return;
   // if((m_can_msg.info.msg.ide == STD_ID) & (int_id > 0x7FF)) return;
   // if((m_can_msg.info.msg.ide == EXT_ID) & (int_id > 0x1FFFFFFF)) return;

    m_fdcan_hdr.info.msg.msg_hdr.id = int_id;
    initId();
    return;
    /*
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
    */
}

//====================== DLC ==================================
const QString &FDCAN_CanBusItem::dlc() const{
    return m_dlc;
}

int FDCAN_CanBusItem::ByteCount() const{
    const fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    uint32_t message_size = FDCAN_MSG_LENGTH(msg_hdr);
    if(message_size < 1) message_size = 1;
    return message_size;
}




void FDCAN_CanBusItem::initDlc(){
    m_dlc = StringConvertor::uint16_t_to_QString_as_HEX(m_fdcan_hdr.info.msg.msg_hdr.dlc).toUpper();
    const static QRegularExpression dlc_zero_crop = QRegularExpression("^0+");
    m_dlc = m_dlc.remove(dlc_zero_crop);
    if(m_dlc == "") m_dlc = "0";
    emit dlcChanged();
    emit byteCountChanged();
}

void FDCAN_CanBusItem::setDlc(const QString& value){
    bool res = false;
    uint8_t new_val_value = value.toInt(&res, 16);
    if(res & (new_val_value < 0x10)){
        m_fdcan_hdr.info.msg.msg_hdr.dlc = new_val_value;
        initDlc();
        initData();
    };
}

//====================== Data ==================================
const QString &FDCAN_CanBusItem::data() const{
    return m_data;
}

void FDCAN_CanBusItem::initData(){
    const fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    uint32_t message_size = FDCAN_MSG_LENGTH(msg_hdr);

    if (m_data_array.size() < message_size) {
        m_data_array.append(QByteArray(message_size - m_data_array.size(), '\x00'));
    }

    // Cropping the byte array if needed
    if (m_data_array.size() > message_size) {
        m_data_array.resize(message_size);
    }

    QString response = StringConvertor::FDCAN_convertByteArrayToFormattedString(m_data_array, message_size);
    m_data = response;
    emit dataChanged();
}

void FDCAN_CanBusItem::setData(const QString& value){
    QString _strval = value.trimmed();
    static QRegularExpression regex("[^0-9a-fA-F]");
    _strval.remove(regex);
    QByteArray str_data_bytes = QByteArray::fromHex(_strval.toUtf8());
    m_data_array = str_data_bytes;
    initData();
}

//====================== FD only ==================================

//======================   ESI   ==================================
QString FDCAN_CanBusItem::ESIflag() const{
    return m_esi_flag;
}

void FDCAN_CanBusItem::setESIflag (const QString& new_val){
    fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    uint8_t flag = new_val != "   " ? FDCAN_FLAG_SET : FDCAN_FLAG_RST;
    FDCAN_SET_MSG_ESI(msg_hdr, flag);
    initEsi();
}

void FDCAN_CanBusItem::initEsi(){
    fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    if(FDCAN_IS_MSG_ESI(msg_hdr)) m_esi_flag =  "ESI";
    else  m_esi_flag = "   ";
    emit ESIflagChanged();
}

//======================   XTD   ==================================
QString FDCAN_CanBusItem::XTDflag() const{
    return m_xtd_flag;
}

void FDCAN_CanBusItem::setXTDflag (const QString& new_val){
    fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    uint8_t flag = new_val != "   " ? FDCAN_FLAG_SET : FDCAN_FLAG_RST;
    FDCAN_SET_MSG_XTD(msg_hdr, flag);
    initXtd();
}

void FDCAN_CanBusItem::initXtd(){
    fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    if(FDCAN_IS_MSG_XTD(msg_hdr)) m_xtd_flag =  "XTD";
    else  m_xtd_flag = "   ";
    emit XTDflagChanged();
}

//======================   FDF   ==================================

QString FDCAN_CanBusItem::FDFflag() const{
    return m_fdf_flag;
}

void FDCAN_CanBusItem::setFDFflag (const QString& new_val){
    fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    uint8_t flag = new_val != "   " ? FDCAN_FLAG_SET : FDCAN_FLAG_RST;
    FDCAN_SET_MSG_FDF(msg_hdr, flag);
    initFdf();
    initData();
}

void FDCAN_CanBusItem::initFdf(){
    fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    if(FDCAN_IS_MSG_FDF(msg_hdr)) m_fdf_flag =  "FDF";
    else  m_fdf_flag = "   ";
    emit FDFflagChanged();
}

//======================   BRS   ==================================

QString FDCAN_CanBusItem::BRSflag() const{
    return m_brs_flag;
}

void FDCAN_CanBusItem::setBRSflag (const QString& new_val){
    fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    uint8_t flag = new_val != "   " ? FDCAN_FLAG_SET : FDCAN_FLAG_RST;
    FDCAN_SET_MSG_BRS(msg_hdr, flag);
    initBrs();
}

void FDCAN_CanBusItem::initBrs(){
    fdcan_message_hdr *msg_hdr = &m_fdcan_hdr.info.msg.msg_hdr;
    if(FDCAN_IS_MSG_BRS(msg_hdr)) m_brs_flag =  "BRS";
    else  m_brs_flag = "   ";
    emit BRSflagChanged();
}

//======================   Color   ==================================
QString FDCAN_CanBusItem::color() const{
    if(intCan() == 1) return data_color_wh;
    else if(intCan() == 2) return data_color_yl;
    else return data_color_df;
}


//========================================================================
//======================== CanBusItemMonitor =============================
//========================================================================

/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/
void FDCAN_CanBusItemMonitor::set_fdcan_msg_hdr_and_data(const fdcan_message_info_raw &_can_msg_hdr, const QByteArray _data){
    const QString old_can = m_can;
    const QString old_dlc = m_dlc;
    const QString old_flags = m_flags;
    const QString old_data = m_data;

    m_last_fdcan_hdr = _can_msg_hdr;
    set_msg_data(_data);
    int new_time = int_time();
    m_iperiod = new_time - m_ilast_time;

    m_ilast_time = new_time;
    m_icount++;
    initQStringValues();

    if(old_can != m_can) emit canChanged();
    if(old_flags != m_flags) emit flagsChanged();
    if(old_data != m_data) emit dataChanged();
    if(old_dlc != m_dlc){
        emit dlcChanged();
        emit byteCountChanged();
    }
    emit periodChanged();
    emit countChanged();
}

void FDCAN_CanBusItemMonitor::initQStringValues(){
    m_can = (m_last_fdcan_hdr.info.can_number == FDCAN1_E) ? "CAN 1" : "CAN 2";

    const static QRegularExpression dlc_zero_crop = QRegularExpression("^0+");

    m_id = StringConvertor::uint32_t_to_QString_as_HEX(m_last_fdcan_hdr.info.msg.msg_hdr.id).toUpper();
    m_id = m_id.remove(dlc_zero_crop);
    if(m_id == "") m_id = "0";

    m_dlc = StringConvertor::uint16_t_to_QString_as_HEX(m_last_fdcan_hdr.info.msg.msg_hdr.dlc).toUpper();
    m_dlc = m_dlc.remove(dlc_zero_crop);
    if(m_dlc == "") m_dlc = "0";

    m_count = QString::number(m_icount, 10);

    if(m_icount < 2) m_period = "";
    else{
        m_period = QString::number(m_iperiod, 10);
        int len = m_period.length(); // Get length of string
        m_period.insert(len-1, "."); // Insert '.' before last character
    }

    m_flags = "";
    m_flags.resize(0);

    fdcan_message_hdr *msg_hdr = &m_last_fdcan_hdr.info.msg.msg_hdr;

    if(FDCAN_IS_MSG_ESI(msg_hdr)) m_flags.append("<font color=\"#FF6C11\"> ESI </font>");
    if(FDCAN_IS_MSG_XTD(msg_hdr)) {
        m_flags.append("<font color=\"#CC1111\"> XTD </font>");
    }
    if(FDCAN_IS_MSG_FDF(msg_hdr)){
        m_flags.append("<font color=\"#0CCC0C\"> FDF </font>");
    }
    if(FDCAN_IS_MSG_BRS(msg_hdr)){
        m_flags.append("<font color=\"#0CCCBC\"> BRS </font>");
    }

    uint32_t message_size = FDCAN_MSG_LENGTH(msg_hdr);
    QString response = StringConvertor::FDCAN_convertByteArrayToFormattedString(m_last_data_array, message_size);

    m_data =  response;
}

/********************************************************************
 *
 *
 *                     Bool and Int Setters/Getters
 *
 *
********************************************************************/

const int FDCAN_CanBusItemMonitor::int_id() const{
    return m_last_fdcan_hdr.info.msg.msg_hdr.id;
}

const int FDCAN_CanBusItemMonitor::int_time() const {
    return (m_last_fdcan_hdr.info.seconds*10000 + m_last_fdcan_hdr.info.msec);
}

/********************************************************************
 *
 *
 *                     Class Setters/Getters
 *
 *
********************************************************************/

const QString &FDCAN_CanBusItemMonitor::can() const
{
    return m_can;
}

void FDCAN_CanBusItemMonitor::setCan(const QString &newCan)
{
    if (m_can == newCan)
        return;
    m_can = newCan;
    emit canChanged();
}

const QString &FDCAN_CanBusItemMonitor::id() const
{
    return m_id;
}

void FDCAN_CanBusItemMonitor::setId(const QString &newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

const QString &FDCAN_CanBusItemMonitor::dlc() const
{
    return m_dlc;
}

void FDCAN_CanBusItemMonitor::setDlc(const QString &newDlc)
{
    if (m_dlc == newDlc)
        return;
    m_dlc = newDlc;
    emit dlcChanged();
}

const QString &FDCAN_CanBusItemMonitor::flags() const
{
    return m_flags;
}


void FDCAN_CanBusItemMonitor::setFlags(const QString &newFlags)
{
    if (m_flags == newFlags)
        return;
    m_flags = newFlags;
    emit flagsChanged();
}


const QString &FDCAN_CanBusItemMonitor::count() const
{
    return m_count;
}

void FDCAN_CanBusItemMonitor::setCount(const QString &newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    emit countChanged();
}

const QString &FDCAN_CanBusItemMonitor::period() const{
    return m_period;
}

void FDCAN_CanBusItemMonitor::setPeriod(const QString &newPeriod)
{
    if (m_period == newPeriod)
        return;
    m_period = newPeriod;
    emit periodChanged();
}

const QString &FDCAN_CanBusItemMonitor::data() const
{
    return m_data;
}

void FDCAN_CanBusItemMonitor::setData(const QString &newData)
{
    if (m_data == newData)
        return;
    m_data = newData;
    emit dataChanged();
}


const QByteArray &FDCAN_CanBusItemMonitor::msg_data() const{
    return m_last_data_array;
}

void FDCAN_CanBusItemMonitor::set_msg_data(const QByteArray &newData_array){
    m_last_data_array = newData_array;
}



int FDCAN_CanBusItemMonitor::ByteCount() const{
    const fdcan_message_hdr *msg_hdr = &m_last_fdcan_hdr.info.msg.msg_hdr;
    uint32_t message_size = FDCAN_MSG_LENGTH(msg_hdr);
    if(message_size < 1) message_size = 1;
    return message_size;
}





