#include "QOverrideFilter_ModelProperty.h"


//====================== Enable/Disable =============================
void QOverrideFilter_ModelProperty::enable_filter(const int i, bool _value){
    auto val_ptr = dataPtr(i);
    val_ptr->setEnabled(_value);
    if(i < (App_settings::MAX_OVERRIDE_FILTER_COUNT - 1)){
        auto val_ptr = dataPtr(i+1);
        val_ptr->setEditable(_value);
    }
    if(_value == false){
        for(size_t k = i+1; k < App_settings::MAX_OVERRIDE_FILTER_COUNT; k++){
            auto val_ptr = dataPtr(k);
            val_ptr->setEditable(false);
            val_ptr->setEnabled(false);
        }
    }
    emit changed();
}


//====================== Id Value =============================
const void QOverrideFilter_ModelProperty::set_str_id_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->str_set_id_value(_new_val);
}

//====================== Byte Value =============================
const void QOverrideFilter_ModelProperty::set_byte0_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setStr_byte0(_new_val);
}
const void QOverrideFilter_ModelProperty::set_byte1_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setStr_byte1(_new_val);
}
const void QOverrideFilter_ModelProperty::set_byte2_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setStr_byte2(_new_val);
}
const void QOverrideFilter_ModelProperty::set_byte3_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setStr_byte3(_new_val);
}
const void QOverrideFilter_ModelProperty::set_byte4_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setStr_byte4(_new_val);;
}
const void QOverrideFilter_ModelProperty::set_byte5_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setStr_byte5(_new_val);
}
const void QOverrideFilter_ModelProperty::set_byte6_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setStr_byte6(_new_val);
}
const void QOverrideFilter_ModelProperty::set_byte7_value(const int i, const QString &_new_val){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setStr_byte7(_new_val);
}
const void QOverrideFilter_ModelProperty::enable_byte0(const int i, bool _on){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setByte0_on(_on);
}
const void QOverrideFilter_ModelProperty::enable_byte1(const int i, bool _on){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setByte1_on(_on);
}
const void QOverrideFilter_ModelProperty::enable_byte2(const int i, bool _on){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setByte2_on(_on);
}
const void QOverrideFilter_ModelProperty::enable_byte3(const int i, bool _on){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setByte3_on(_on);
}
const void QOverrideFilter_ModelProperty::enable_byte4(const int i, bool _on){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setByte4_on(_on);
}
const void QOverrideFilter_ModelProperty::enable_byte5(const int i, bool _on){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setByte5_on(_on);
}
const void QOverrideFilter_ModelProperty::enable_byte6(const int i, bool _on){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setByte6_on(_on);
}
const void QOverrideFilter_ModelProperty::enable_byte7(const int i, bool _on){
    QSharedPointer<QOverrideFilter_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setByte7_on(_on);
}




void QOverrideFilter_ModelProperty::fill_OverrideStatus(OverrideStatus* ovr_sts) const{
    uint16_t _overrided_id_num = 0;
    uint16_t _overrided_id_dirs_msk = 0;

    for(size_t i = 0; i < App_settings::MAX_DISCARD_ID_COUNT; i++){
        const auto val_ptr = dataPtr(i);
        if(val_ptr->enabled()) _overrided_id_num++; // add count
        if(val_ptr->dir_value() == 2) _overrided_id_dirs_msk |= (0x1 << i); // set direction
        ovr_sts->set_override_msks(i, val_ptr->msk()); // add mask
        //create filter
        can_override_filter _filter;

        // id
        if(val_ptr->Id_value() <= 0x7FF){
            _filter.id.std_id.id_highbyte = ((val_ptr->Id_value() >> 8) &~0xFFFFFF00);
            _filter.id.std_id.id_lowbyte = ((val_ptr->Id_value() >> 0) &~0xFFFFFF00);
            _filter.id.std_id.unused = 0xFFFF;
        }
        else if(val_ptr->Id_value() > 0x7FF & val_ptr->Id_value() < 0x1fffffff) _filter.id.ext_id = val_ptr->Id_value();
        else _filter.id.ext_id = 0;
        // fill data
        _filter.override_data[0] = val_ptr->byte0();
        _filter.override_data[1] = val_ptr->byte1();
        _filter.override_data[2] = val_ptr->byte2();
        _filter.override_data[3] = val_ptr->byte3();
        _filter.override_data[4] = val_ptr->byte4();
        _filter.override_data[5] = val_ptr->byte5();
        _filter.override_data[6] = val_ptr->byte6();
        _filter.override_data[7] = val_ptr->byte7();


        ovr_sts->set_filter(i, _filter);
    }
    ovr_sts->set_overrided_id_num(_overrided_id_num);
    ovr_sts->set_overrided_id_dirs_msk(_overrided_id_dirs_msk);
}

void QOverrideFilter_ModelProperty::update_model_from_OverrideStatus(OverrideStatus* ovr_sts){
    clear();
    uint16_t _overrided_id_num = ovr_sts->get_overrided_id_num();
    uint16_t _overrided_id_dirs_msk = ovr_sts->get_overrided_id_dirs_msk();

    for(size_t i = 0; i < App_settings::MAX_OVERRIDE_FILTER_COUNT; i++){

        auto _item = QSharedPointer<QOverrideFilter_ModelItem> (new QOverrideFilter_ModelItem(this));       

        bool isCan2 = _overrided_id_dirs_msk & (0x1 << i);
        if(isCan2)_item->setDir_value(2);                   // Dir
        else _item->setDir_value(1);

        if(i+1 <= _overrided_id_num) _item->setEnabled(true); // Enabled/disabled

        can_override_filter _filter = ovr_sts->get_filter(i);

        if(_filter.id.std_id.unused == 0xFFFF){
            uint32_t std_val = _filter.id.std_id.id_highbyte << 8 | _filter.id.std_id.id_lowbyte;
            if(std_val <= 0x7FF)_item->setId_value(std_val);
        }
        if(_filter.id.ext_id <= 0x1fffffff) _item->setId_value(_filter.id.ext_id);
        _item->setByte0(_filter.override_data[0]);
        _item->setByte1(_filter.override_data[1]);
        _item->setByte2(_filter.override_data[2]);
        _item->setByte3(_filter.override_data[3]);
        _item->setByte4(_filter.override_data[4]);
        _item->setByte5(_filter.override_data[5]);
        _item->setByte6(_filter.override_data[6]);
        _item->setByte7(_filter.override_data[7]);
        _item->setMsk(ovr_sts->get_override_msks(i));

        this->append(_item);
    }
    /**********************************
     *  Set editable items
     * *********************************/

    /* set the first item editable */
    auto val_ptr = dataPtr(0);
    val_ptr->setEditable(true);

    for(size_t i = 0; i < App_settings::MAX_OVERRIDE_FILTER_COUNT - 1; i++){
        val_ptr = dataPtr(i);
        auto val_ptr_next = dataPtr(i +1);
        if(val_ptr->enabled()) val_ptr_next->setEditable(true);
        else val_ptr_next->setEditable(false);
    }
//    val_ptr->setEditable(false);
//    val_ptr->setEnabled(false);
}

