#include "QOverrideFilter_ModelItem.h"

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

bool QOverrideFilter_ModelItem::editable() const{
    return m_editable;
}
void QOverrideFilter_ModelItem::setEditable(bool newval){
    m_editable = newval;
    emit changed();
}

int QOverrideFilter_ModelItem::dir_value() const{
    return m_can_dir;
}

void QOverrideFilter_ModelItem::setDir_value(int newDir_value){
    if (m_can_dir == newDir_value)
        return;
    m_can_dir = newDir_value;
    emit changed();
}

//================================ Byte 0 ====================================
const QString QOverrideFilter_ModelItem::str_byte0() const{
    return QString::number(byte0(), 16).toUpper();
}
void QOverrideFilter_ModelItem::setStr_byte0(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) {
        setByte0(new_id_value);
    }
}

bool QOverrideFilter_ModelItem::byte0_on() const{
    return (msk() & (0x01 << 0));
}
void QOverrideFilter_ModelItem::setByte0_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 0);
    else clearMsk(0x01 << 0);
}


//================================ Byte 1 ====================================
const QString QOverrideFilter_ModelItem::str_byte1() const{
    return QString::number(byte1(), 16).toUpper();
}
void QOverrideFilter_ModelItem::setStr_byte1(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte1(new_id_value);
}

bool QOverrideFilter_ModelItem::byte1_on() const{
    return (msk() & (0x01 << 1));
}
void QOverrideFilter_ModelItem::setByte1_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 1);
    else clearMsk(0x01 << 1);
}


//================================ Byte 2 ====================================
const QString QOverrideFilter_ModelItem::str_byte2() const{
    return QString::number(byte2(), 16).toUpper();
}
void QOverrideFilter_ModelItem::setStr_byte2(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte2(new_id_value);
}

bool QOverrideFilter_ModelItem::byte2_on() const{
    return (msk() & (0x01 << 2));
}
void QOverrideFilter_ModelItem::setByte2_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 2);
    else clearMsk(0x01 << 2);
}


//================================ Byte 3 ====================================
const QString QOverrideFilter_ModelItem::str_byte3() const{
    return QString::number(byte3(), 16).toUpper();
}
void QOverrideFilter_ModelItem::setStr_byte3(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte3(new_id_value);
}

bool QOverrideFilter_ModelItem::byte3_on() const{
    return (msk() & (0x01 << 3));
}
void QOverrideFilter_ModelItem::setByte3_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 3);
    else clearMsk(0x01 << 3);
}


//================================ Byte 4 ====================================
const QString QOverrideFilter_ModelItem::str_byte4() const{
    return QString::number(byte4(), 16).toUpper();
}
void QOverrideFilter_ModelItem::setStr_byte4(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte4(new_id_value);
}

bool QOverrideFilter_ModelItem::byte4_on() const{
    return (msk() & (0x01 << 4));
}
void QOverrideFilter_ModelItem::setByte4_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 4);
    else clearMsk(0x01 << 4);
}


//================================ Byte 5 ====================================
const QString QOverrideFilter_ModelItem::str_byte5() const{
    return QString::number(byte5(), 16).toUpper();
}
void QOverrideFilter_ModelItem::setStr_byte5(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte5(new_id_value);
}

bool QOverrideFilter_ModelItem::byte5_on() const{
    return (msk() & (0x01 << 5));
}
void QOverrideFilter_ModelItem::setByte5_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 5);
    else clearMsk(0x01 << 5);
}


//================================ Byte 6 ====================================
const QString QOverrideFilter_ModelItem::str_byte6() const{
    return QString::number(byte6(), 16).toUpper();
}
void QOverrideFilter_ModelItem::setStr_byte6(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte6(new_id_value);
}

bool QOverrideFilter_ModelItem::byte6_on() const{
    return (msk() & (0x01 << 6));
}
void QOverrideFilter_ModelItem::setByte6_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 6);
    else clearMsk(0x01 << 6);
}


//================================ Byte 7 ====================================
const QString QOverrideFilter_ModelItem::str_byte7() const{
    return QString::number(byte7(), 16).toUpper();
}
void QOverrideFilter_ModelItem::setStr_byte7(const QString &_val){
    bool res = false;
    int new_id_value = _val.toInt(&res, 16);
    if(res & (new_id_value <= 0xFF)) setByte7(new_id_value);
}

bool QOverrideFilter_ModelItem::byte7_on() const{
    return (msk() & (0x01 << 7));
}
void QOverrideFilter_ModelItem::setByte7_on(bool isOn){
    if(isOn)
        addMsk(0x01 << 7);
    else clearMsk(0x01 << 7);
}

//================================ Id ====================================

const QString QOverrideFilter_ModelItem::str_id_value()const{
    return QString::number(Id_value(), 16).toUpper();
}

void QOverrideFilter_ModelItem::str_set_id_value(const QString &_id){
    bool res = false;
    int new_id_value = _id.toInt(&res, 16);
    if((res) & (new_id_value <= 0x1fffffff)) setId_value(new_id_value);
}

//============================================================================
//=============================== Actual data ================================
//============================================================================

int QOverrideFilter_ModelItem::Id_value() const{
    return m_Id_value;
}

void QOverrideFilter_ModelItem::setId_value(int newId_value){
    m_Id_value = newId_value;
    emit changed();
}



bool QOverrideFilter_ModelItem::enabled() const{
    return m_enabled;
}

void QOverrideFilter_ModelItem::setEnabled(bool newEnabled){
    if (m_enabled == newEnabled)
        return;
    m_enabled = newEnabled;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::byte0() const{
    return m_byte0;
}

void QOverrideFilter_ModelItem::setByte0(uint8_t newByte0){
    m_byte0 = newByte0;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::byte1() const{
    return m_byte1;
}

void QOverrideFilter_ModelItem::setByte1(uint8_t newByte1){
    m_byte1 = newByte1;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::byte2() const{
    return m_byte2;
}

void QOverrideFilter_ModelItem::setByte2(uint8_t newByte2){
    m_byte2 = newByte2;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::byte3() const{
    return m_byte3;
}

void QOverrideFilter_ModelItem::setByte3(uint8_t newByte3){
    m_byte3 = newByte3;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::byte4() const{
    return m_byte4;
}

void QOverrideFilter_ModelItem::setByte4(uint8_t newByte4){
    m_byte4 = newByte4;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::byte5() const{
    return m_byte5;
}

void QOverrideFilter_ModelItem::setByte5(uint8_t newByte5){
    m_byte5 = newByte5;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::byte6() const{
    return m_byte6;
}

void QOverrideFilter_ModelItem::setByte6(uint8_t newByte6){
    m_byte6 = newByte6;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::byte7() const{
    return m_byte7;
}

void QOverrideFilter_ModelItem::setByte7(uint8_t newByte7){
    m_byte7 = newByte7;
    emit changed();
}

uint8_t QOverrideFilter_ModelItem::msk() const{
    return m_msk;
}

void QOverrideFilter_ModelItem::setMsk(uint8_t newMsk){
    m_msk = newMsk;
    emit changed();
}

void QOverrideFilter_ModelItem::addMsk(uint8_t newMsk){
    m_msk |= newMsk;
    emit changed();
}
void QOverrideFilter_ModelItem::clearMsk(uint8_t newMsk){
    m_msk &= ~newMsk;
    emit changed();
}

