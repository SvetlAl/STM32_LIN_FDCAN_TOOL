#ifndef OVERRIDE_STATUS_H
#define OVERRIDE_STATUS_H

#include <QObject>
#include <QDebug>
#include "../bus/CanBusItem.h"
//#include "../../core/Console.h"


/**************************************************************
 *
 *  Import from can.h
 *
 *************************************************************/




/**************************************************************
 *
 *  Import from can_override.h
 *
 *************************************************************/



#define MAX_OVERRIDE_FILTERS 16
#define MAX_IGNORED_IDS 16

/* CAN override filter */
typedef struct can_override_filter{
    can_id id;
    uint8_t override_data[8];
} can_override_filter; //creating new type

/* STATUS CAN override */
typedef struct can_override_status{
    uint16_t ignored_id_num;
    uint16_t overrided_id_num;
    uint16_t ignored_id_dirs_msk; // 0 - CAN1, 1 - CAN2
    uint16_t overrided_id_dirs_msk; // 0 - CAN1, 1 - CAN2
    can_override_filter filters[MAX_OVERRIDE_FILTERS];
    can_id ignored_ids[MAX_IGNORED_IDS];
    uint8_t override_msks[MAX_OVERRIDE_FILTERS];
} can_override_status; //creating new type

typedef union u_can_override_status{
    can_override_status status;
    uint8_t raw_data[sizeof(can_override_status)];
} u_can_override_status; //creating new type

#define DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH	sizeof(can_override_status)



class OverrideStatus : public QObject{

public:
    explicit OverrideStatus(QObject *parent = 0) : QObject(parent){
      //  reset();
    }
    ~OverrideStatus() {};

    void init_OverrideStatuswithRawData(const QByteArray &data);
    void setActiveFilters(const QByteArray &data);



    const uint16_t get_ignored_id_num() const;
    const uint16_t get_overrided_id_num() const;
    const uint16_t get_ignored_id_dirs_msk() const; // 0 - CAN1, 1 - CAN2
    const uint16_t get_overrided_id_dirs_msk() const; // 0 - CAN1, 1 - CAN2

    const can_override_filter get_filter(int index) const;
    const can_id get_ignored_ids(int index) const;
    const uint32_t get_int_ignored_ids(int index) const;
    const uint8_t get_override_msks(int index) const;

    void set_ignored_id_num(uint16_t value);
    void set_overrided_id_num(uint16_t value);
    void set_ignored_id_dirs_msk(uint16_t value); // 0 - CAN1, 1 - CAN2
    void set_overrided_id_dirs_msk(uint16_t value); // 0 - CAN1, 1 - CAN2

    void set_filter(int index, can_override_filter value);
    void set_ignored_ids(int index, can_id value);
    void set_ignored_ids(int index, uint32_t value);
    void set_override_msks(int index, uint8_t value);



    const QByteArray getRawData() const;
    friend class DeviceManager;

private:
    u_can_override_status m_ovr_status;
};




#endif // OVERRIDE_STATUS_H
