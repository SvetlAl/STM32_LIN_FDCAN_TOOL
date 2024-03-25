#include "QFDCAN_OverrideFilter_ModelProperty.h"

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

void QFDCAN_OverrideFilter_ModelProperty::fill_OverrideStatus(FDCAN_OverrideStatus* ovr_sts) const{
    u_fdcan_filter* ptr = ovr_sts->get_main_ptr();
    ptr->filter.hdr = m_fdcan_filter_hdr;

    for(size_t i = 0; i < App_settings::MAX_FDCAN_BYTES_COUNT; i++){
        const auto val_ptr = dataPtr(i);
        ptr->filter.filter_byte[i] = *(dataPtr(i)->get_filter_byte());

        if((ptr->filter.filter_byte[i].from_value == ptr->filter.filter_byte[i].to_value) && (ptr->filter.filter_byte[i].method != FDCAN_filter_method_default)){
            ptr->filter.filter_byte[i].method = FDCAN_filter_method_const;
        }

        if(ptr->filter.filter_byte[i].method == FDCAN_filter_method_inc){
            if(ptr->filter.filter_byte[i].from_value > ptr->filter.filter_byte[i].to_value){
                uint8_t tmp = ptr->filter.filter_byte[i].from_value;
                ptr->filter.filter_byte[i].from_value = ptr->filter.filter_byte[i].to_value;
                ptr->filter.filter_byte[i].to_value = tmp;
            }
        }

        else if(ptr->filter.filter_byte[i].method == FDCAN_filter_method_dec){
            if(ptr->filter.filter_byte[i].from_value < ptr->filter.filter_byte[i].to_value){
                uint8_t tmp = ptr->filter.filter_byte[i].from_value;
                ptr->filter.filter_byte[i].from_value = ptr->filter.filter_byte[i].to_value;
                ptr->filter.filter_byte[i].to_value = tmp;
            }
        }
        ptr->filter.filter_byte[i].tmp = ptr->filter.filter_byte[i].from_value;
    }

    if((ptr->filter.hdr.id_begin > ptr->filter.hdr.id_end) & (range_used()== true)){
        uint32_t tmp = ptr->filter.hdr.id_begin;
        ptr->filter.hdr.id_begin = ptr->filter.hdr.id_end;
        ptr->filter.hdr.id_end = tmp;
    }
    else if(range_used()!= true){
        ptr->filter.hdr.id_end = ptr->filter.hdr.id_begin;
    }
}

//********************************************************************************************************************
// An OverrideStatus is a structure used to hold filter status with acceptabe format for microcontroller firmware
// update_model_from_OverrideStatus function updates the interface override model with OverrideStatus data to display to user.
//********************************************************************************************************************

void QFDCAN_OverrideFilter_ModelProperty::update_model_from_OverrideStatus(FDCAN_OverrideStatus* ovr_sts){
    clear();
    u_fdcan_filter* ptr = ovr_sts->get_main_ptr();
    m_fdcan_filter_hdr = ptr->filter.hdr;
    set_range_used(true);

    for(size_t i = 0; i< App_settings::MAX_FDCAN_BYTES_COUNT; i++){
        auto _item = QSharedPointer<QFDCAN_OverrideFilter_ModelItem>
                (new QFDCAN_OverrideFilter_ModelItem(this, i, ptr->filter.filter_byte[i].from_value,
                                                     ptr->filter.filter_byte[i].to_value,
                                                     ptr->filter.filter_byte[i].step,
                                                     ptr->filter.filter_byte[i].method));

        this->append(_item);
    }
    emit changed();
}



/********************************************************************
 *
 *
 *                    Setters/getters
 *
 *
********************************************************************/




