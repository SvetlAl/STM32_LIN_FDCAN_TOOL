#include "QDiscardId_ModelProperty.h"

/********************************************************************
 *
 *
 *                    Initialization
 *
 *
********************************************************************/

//********************************************************************************************************************
// An OverrideStatus is a structure used to hold filter status with acceptabe format for microcontroller firmware
// fill_OverrideStatus function prepares an OverrideStatus with interface data for further sending to a microcontroller.
//********************************************************************************************************************
void QDiscardId_ModelProperty::fill_OverrideStatus(OverrideStatus* ovr_sts) const{

    uint16_t _ignored_id_num = 0;
    uint16_t _ignored_id_dirs_msk = 0;
    for(size_t i = 0; i < App_settings::MAX_DISCARD_ID_COUNT; i++){
        const auto val_ptr = dataPtr(i);
        if(val_ptr->enabled()) _ignored_id_num++;
        if(val_ptr->dir_value() == 2) _ignored_id_dirs_msk |= (0x1 << i);
        ovr_sts->set_ignored_ids(i, val_ptr->Id_value());
    }
    ovr_sts->set_ignored_id_num(_ignored_id_num);
    ovr_sts->set_ignored_id_dirs_msk(_ignored_id_dirs_msk);
}

//********************************************************************************************************************
// An OverrideStatus is a structure used to hold filter status with acceptabe format for microcontroller firmware
// update_model_from_OverrideStatus function updates the interface override model with OverrideStatus data to display to user.
//********************************************************************************************************************
void QDiscardId_ModelProperty::update_model_from_OverrideStatus(OverrideStatus* ovr_sts){
    clear();
    uint16_t _ignored_id_num = ovr_sts->get_ignored_id_num();
    uint16_t _ignored_id_dirs_msk = ovr_sts->get_ignored_id_dirs_msk();

    for(size_t i = 0; i < App_settings::MAX_DISCARD_ID_COUNT; i++){

        auto _item = QSharedPointer<QDiscardId_ModelItem> (new QDiscardId_ModelItem(this));
        bool isCan2 = _ignored_id_dirs_msk & (0x1 << i);
        if(isCan2)_item->setDir_value(2); // Dir
        else _item->setDir_value(1);

        if(i+1 <= _ignored_id_num) _item->setEnabled(true); // Enabled/disabled
        _item->setId_value(ovr_sts->get_int_ignored_ids(i));// ID
        this->append(_item);
    }
    /**********************************
     *  Set editable items
     * *********************************/

    /* set the first item editable */
    auto val_ptr = dataPtr(0);
    val_ptr->setEditable(true);

    for(size_t i = 0; i < App_settings::MAX_DISCARD_ID_COUNT - 1; i++){
        val_ptr = dataPtr(i);
        auto val_ptr_next = dataPtr(i +1);
        if(val_ptr->enabled())val_ptr_next->setEditable(true);
        else val_ptr_next->setEditable(false);
    }
}


/********************************************************************
 *
 *
 *                    Setters/getters
 *
 *
********************************************************************/

void QDiscardId_ModelProperty::enable_filter(const int i, bool _value){
    QSharedPointer<QDiscardId_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setEnabled(_value);
    if(i < (App_settings::MAX_DISCARD_ID_COUNT - 1)){
        QSharedPointer<QDiscardId_ModelItem> val_ptr = dataPtr(i+1);
        val_ptr->setEditable(_value);
    }
    if(_value == false){
        for(size_t k = i+1; k < App_settings::MAX_DISCARD_ID_COUNT; k++){
            auto val_ptr = dataPtr(k);
            val_ptr->setEditable(false);
            val_ptr->setEnabled(false);
        }
    }
    emit changed();
}

void QDiscardId_ModelProperty::set_filter_id_value(const int i, const QString &_new_val){
    QSharedPointer<QDiscardId_ModelItem> val_ptr = dataPtr(i);
    val_ptr->str_set_id_value(_new_val);
    emit changed();
}

void QDiscardId_ModelProperty::set_filter_can_value(const int i, int can){
    QSharedPointer<QDiscardId_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setDir_value(can);
    emit changed();
}






