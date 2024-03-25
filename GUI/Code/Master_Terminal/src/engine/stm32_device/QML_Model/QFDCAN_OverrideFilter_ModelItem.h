#ifndef QFDCAN_OVERRIDEFILTER_MODELITEM_H
#define QFDCAN_OVERRIDEFILTER_MODELITEM_H

/***********************************************************************
 * QOverrideFilter_ModelItem ==> QOverrideFilter_ModelProperty ==>
 *
 *

 ************************************************************************/


#include "../../../app_settings.h"
#include "../../bus/FDCAN_Macros.h"
#include <QDebug>
#include <stdio.h>

/*
 * typedef enum{
    FDCAN_filter_method_default = (uint8_t)0x00,  // off
    FDCAN_filter_method_inc     = (uint8_t)0x01,  // increment
    FDCAN_filter_method_dec     = (uint8_t)0x02,  // decrement
    FDCAN_filter_method_const   = (uint8_t)0x03   // const
} eFdcanByteFilterMethod;

typedef struct fdcan_filter_byte{
    eFdcanByteFilterMethod method;
    uint8_t from_value;
    uint8_t to_value;
    uint8_t step;
}fdcan_filter_byte;
*/

class QFDCAN_OverrideFilter_ModelItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(bool active READ active WRITE set_active NOTIFY changed)
    Q_PROPERTY(int method READ method WRITE set_method NOTIFY changed)

    Q_PROPERTY(QString number READ number CONSTANT)

    Q_PROPERTY(QString begin_val READ begin_val WRITE set_begin_val NOTIFY changed)
    Q_PROPERTY(QString end_val READ end_val WRITE set_end_val NOTIFY changed)
    Q_PROPERTY(QString step READ step WRITE set_step NOTIFY changed)

public:
   explicit QFDCAN_OverrideFilter_ModelItem(QObject *parent = nullptr, int _num = 0, uint8_t from = 0, uint8_t to = 0, uint8_t step = 0, eFdcanByteFilterMethod method = FDCAN_filter_method_default) {
            m_count_num = _num;
            m_filter_byte.from_value = from;
            m_filter_byte.to_value = to;
            m_filter_byte.step = step;
            m_filter_byte.method = method;
        };


    ~QFDCAN_OverrideFilter_ModelItem( ){
    }


    //=========================== Class setters/getters ===============================
     bool active() const;
     void set_active(bool newval);

     int method() const;
     void set_method(int newval);

     QString number ()const;

     QString begin_val() const;
     void set_begin_val(const QString &newval);

     QString end_val() const;
     void set_end_val(const QString &newval);

     QString step() const;
     void set_step(const QString &newval);

     fdcan_filter_byte *get_filter_byte(){return &m_filter_byte;};

signals:
    void changed();

private:
    int m_count_num = 0;
    fdcan_filter_byte m_filter_byte;
    bool m_active = false;
};


#endif // QFDCAN_OVERRIDEFILTER_MODELITEM_H
