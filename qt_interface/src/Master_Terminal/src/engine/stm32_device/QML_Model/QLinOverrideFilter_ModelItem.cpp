#include "QLinOverrideFilter_ModelItem.h"

/********************************************************************
 *
 *
 *                     Class Setters/getters
 *
 *
********************************************************************/


//============================================================================
//========================== QML representation ==============================
//============================================================================
/*
bool QLinOverrideFilter_ModelItem::editable() const{
    return m_editable;
}
void QLinOverrideFilter_ModelItem::setEditable(bool newval){
    m_editable = newval;
    emit changed();
}
*/
bool QLinOverrideFilter_ModelItem::dir_value() const{
    return m_lin_dir;
}

void QLinOverrideFilter_ModelItem::setDir_value(bool dir){
    if (m_lin_dir == dir)
        return;
    m_lin_dir = dir;
    emit changed();
}

//================================ Byte 0 ====================================
const QString QLinOverrideFilter_ModelItem::str_byte0() const{
    return QString::number(byte0(), 16).toUpper();
}
void QLinOverrideFilter_ModelItem::setStr_byte0(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) {
        setByte0(new_id_value);
    }
}

bool QLinOverrideFilter_ModelItem::byte0_on() const{
    return (msk() & (0x01 << 0));
}
void QLinOverrideFilter_ModelItem::setByte0_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 0);
    else clearMsk(0x01 << 0);
}


//================================ Byte 1 ====================================
const QString QLinOverrideFilter_ModelItem::str_byte1() const{
    return QString::number(byte1(), 16).toUpper();
}
void QLinOverrideFilter_ModelItem::setStr_byte1(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte1(new_id_value);
}

bool QLinOverrideFilter_ModelItem::byte1_on() const{
    return (msk() & (0x01 << 1));
}
void QLinOverrideFilter_ModelItem::setByte1_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 1);
    else clearMsk(0x01 << 1);
}


//================================ Byte 2 ====================================
const QString QLinOverrideFilter_ModelItem::str_byte2() const{
    return QString::number(byte2(), 16).toUpper();
}
void QLinOverrideFilter_ModelItem::setStr_byte2(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte2(new_id_value);
}

bool QLinOverrideFilter_ModelItem::byte2_on() const{
    return (msk() & (0x01 << 2));
}
void QLinOverrideFilter_ModelItem::setByte2_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 2);
    else clearMsk(0x01 << 2);
}


//================================ Byte 3 ====================================
const QString QLinOverrideFilter_ModelItem::str_byte3() const{
    return QString::number(byte3(), 16).toUpper();
}
void QLinOverrideFilter_ModelItem::setStr_byte3(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte3(new_id_value);
}

bool QLinOverrideFilter_ModelItem::byte3_on() const{
    return (msk() & (0x01 << 3));
}
void QLinOverrideFilter_ModelItem::setByte3_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 3);
    else clearMsk(0x01 << 3);
}


//================================ Byte 4 ====================================
const QString QLinOverrideFilter_ModelItem::str_byte4() const{
    return QString::number(byte4(), 16).toUpper();
}
void QLinOverrideFilter_ModelItem::setStr_byte4(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte4(new_id_value);
}

bool QLinOverrideFilter_ModelItem::byte4_on() const{
    return (msk() & (0x01 << 4));
}
void QLinOverrideFilter_ModelItem::setByte4_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 4);
    else clearMsk(0x01 << 4);
}


//================================ Byte 5 ====================================
const QString QLinOverrideFilter_ModelItem::str_byte5() const{
    return QString::number(byte5(), 16).toUpper();
}
void QLinOverrideFilter_ModelItem::setStr_byte5(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte5(new_id_value);
}

bool QLinOverrideFilter_ModelItem::byte5_on() const{
    return (msk() & (0x01 << 5));
}
void QLinOverrideFilter_ModelItem::setByte5_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 5);
    else clearMsk(0x01 << 5);
}


//================================ Byte 6 ====================================
const QString QLinOverrideFilter_ModelItem::str_byte6() const{
    return QString::number(byte6(), 16).toUpper();
}
void QLinOverrideFilter_ModelItem::setStr_byte6(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte6(new_id_value);
}

bool QLinOverrideFilter_ModelItem::byte6_on() const{
    return (msk() & (0x01 << 6));
}
void QLinOverrideFilter_ModelItem::setByte6_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 6);
    else clearMsk(0x01 << 6);
}


//================================ Byte 7 ====================================
const QString QLinOverrideFilter_ModelItem::str_byte7() const{
    return QString::number(byte7(), 16).toUpper();
}
void QLinOverrideFilter_ModelItem::setStr_byte7(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte7(new_id_value);
}

bool QLinOverrideFilter_ModelItem::byte7_on() const{
    return (msk() & (0x01 << 7));
}
void QLinOverrideFilter_ModelItem::setByte7_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 7);
    else clearMsk(0x01 << 7);
}

//================================ Id ====================================

const QString QLinOverrideFilter_ModelItem::str_id_value()const{
    return QString::number(Id_value(), 16).toUpper();
}

void QLinOverrideFilter_ModelItem::str_set_id_value(const QString &_id){
    bool res = false;
    int new_id_value = _id.toInt(&res, 16);
    if((res) & (new_id_value <= 0x1fffffff)) setId_value(new_id_value);
}

//============================================================================
//=============================== Actual data ================================
//============================================================================

int QLinOverrideFilter_ModelItem::Id_value() const{
    return m_Id_value;
}

void QLinOverrideFilter_ModelItem::setId_value(int newId_value){
    m_Id_value = newId_value;
    emit changed();
}


/*
bool QLinOverrideFilter_ModelItem::enabled() const{
    return m_enabled;
}

void QLinOverrideFilter_ModelItem::setEnabled(bool newEnabled){
    if (m_enabled == newEnabled)
        return;
    m_enabled = newEnabled;
    emit changed();
}
*/

uint8_t QLinOverrideFilter_ModelItem::byte0() const{
    return m_byte0;
}

void QLinOverrideFilter_ModelItem::setByte0(uint8_t newByte0){
    m_byte0 = newByte0;
    emit changed();
}

uint8_t QLinOverrideFilter_ModelItem::byte1() const{
    return m_byte1;
}

void QLinOverrideFilter_ModelItem::setByte1(uint8_t newByte1){
    m_byte1 = newByte1;
    emit changed();
}

uint8_t QLinOverrideFilter_ModelItem::byte2() const{
    return m_byte2;
}

void QLinOverrideFilter_ModelItem::setByte2(uint8_t newByte2){
    m_byte2 = newByte2;
    emit changed();
}

uint8_t QLinOverrideFilter_ModelItem::byte3() const{
    return m_byte3;
}

void QLinOverrideFilter_ModelItem::setByte3(uint8_t newByte3){
    m_byte3 = newByte3;
    emit changed();
}

uint8_t QLinOverrideFilter_ModelItem::byte4() const{
    return m_byte4;
}

void QLinOverrideFilter_ModelItem::setByte4(uint8_t newByte4){
    m_byte4 = newByte4;
    emit changed();
}

uint8_t QLinOverrideFilter_ModelItem::byte5() const{
    return m_byte5;
}

void QLinOverrideFilter_ModelItem::setByte5(uint8_t newByte5){
    m_byte5 = newByte5;
    emit changed();
}

uint8_t QLinOverrideFilter_ModelItem::byte6() const{
    return m_byte6;
}

void QLinOverrideFilter_ModelItem::setByte6(uint8_t newByte6){
    m_byte6 = newByte6;
    emit changed();
}

uint8_t QLinOverrideFilter_ModelItem::byte7() const{
    return m_byte7;
}

void QLinOverrideFilter_ModelItem::setByte7(uint8_t newByte7){
    m_byte7 = newByte7;
    emit changed();
}

uint8_t QLinOverrideFilter_ModelItem::msk() const{
    return m_msk;
}

void QLinOverrideFilter_ModelItem::setMsk(uint8_t newMsk){
    m_msk = newMsk;
    emit changed();
}

void QLinOverrideFilter_ModelItem::addMsk(uint8_t newMsk){
    m_msk |= newMsk;
    emit changed();
}
void QLinOverrideFilter_ModelItem::clearMsk(uint8_t newMsk){
    m_msk &= ~newMsk;
    emit changed();
}

