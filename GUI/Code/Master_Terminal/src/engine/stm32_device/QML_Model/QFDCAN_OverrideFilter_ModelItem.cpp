#include "QFDCAN_OverrideFilter_ModelItem.h"

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

bool QFDCAN_OverrideFilter_ModelItem::active() const{
    return m_active;
}
void QFDCAN_OverrideFilter_ModelItem::set_active(bool newval){
    if(m_active != newval){
        m_active = newval;
        emit changed();
    }
}


QString QFDCAN_OverrideFilter_ModelItem::number ()const{
    return QString::number(m_count_num, 10);
}


QString QFDCAN_OverrideFilter_ModelItem::begin_val() const{
    return QString::number(m_filter_byte.from_value, 16).toUpper();
}

void QFDCAN_OverrideFilter_ModelItem::set_begin_val(const QString &newval){
    bool res = false;
    uint8_t new_int_value = newval.toInt(&res, 16);
    if(res & (new_int_value <= 0xFF)) {
        m_filter_byte.from_value = new_int_value;
    }
    emit changed();
}

QString QFDCAN_OverrideFilter_ModelItem::end_val() const{
    return QString::number(m_filter_byte.to_value, 16).toUpper();
}

void QFDCAN_OverrideFilter_ModelItem::set_end_val(const QString &newval){
    bool res = false;
    uint8_t new_int_value = newval.toInt(&res, 16);
    if(res & (new_int_value <= 0xFF)) {
        m_filter_byte.to_value = new_int_value;
    }
    emit changed();
}

QString QFDCAN_OverrideFilter_ModelItem::step() const{
    return QString::number(m_filter_byte.step, 16).toUpper();
}
void QFDCAN_OverrideFilter_ModelItem::set_step(const QString &newval){
    bool res = false;
    uint8_t new_int_value = newval.toInt(&res, 16);
    if(res & (new_int_value <= 0xFF)) {
        m_filter_byte.step = new_int_value;
    }
    emit changed();
}


//============================================================================
//=============================== Actual data ================================
//============================================================================

int QFDCAN_OverrideFilter_ModelItem::method() const{
    return static_cast<int>(m_filter_byte.method);
}
void QFDCAN_OverrideFilter_ModelItem::set_method(int newval){
    if(newval < 0x00 | newval > 0x03) return;
    eFdcanByteFilterMethod tmp = static_cast<eFdcanByteFilterMethod>(newval);
    m_filter_byte.method = tmp;
    emit changed();
}


