#include "QDiscardId_ModelItem.h"

/********************************************************************
 *
 *
 *                     Class Setters/getters
 *
 *
********************************************************************/

int QDiscardId_ModelItem::Id_value() const{
    return m_Id_value;
}

void QDiscardId_ModelItem::setId_value(int newId_value){
    m_Id_value = newId_value;
    emit changed();
}

const QString QDiscardId_ModelItem::str_id_value()const{
    return QString::number(Id_value(), 16).toUpper();
}

void QDiscardId_ModelItem::str_set_id_value(const QString &_id){
    bool res = false;
    int new_id_value = _id.toInt(&res, 16);
    if(res & (new_id_value <= 0x1FFFFFFF)) setId_value(new_id_value);
}


bool QDiscardId_ModelItem::enabled() const{
    return m_enabled;
}

void QDiscardId_ModelItem::setEnabled(bool newEnabled){
    m_enabled = newEnabled;
    emit changed();
}

bool QDiscardId_ModelItem::editable() const{
    return m_editable;
}
void QDiscardId_ModelItem::setEditable(bool newval){
    m_editable = newval;
    emit changed();
}

int QDiscardId_ModelItem::dir_value() const{
    return m_can_dir;
}

void QDiscardId_ModelItem::setDir_value(int newDir_value){
    if (m_can_dir == newDir_value)
        return;
    m_can_dir = newDir_value;
    emit changed();
}
