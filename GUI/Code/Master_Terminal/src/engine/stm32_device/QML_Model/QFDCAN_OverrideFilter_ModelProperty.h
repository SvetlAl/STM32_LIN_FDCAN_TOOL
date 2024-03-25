#ifndef QFDCAN_OVERRIDEFILTER_MODELPROPERTY_H
#define QFDCAN_OVERRIDEFILTER_MODELPROPERTY_H

/***********************************************************************
 * QOverrideFilter_ModelItem ==> QOverrideFilter_ModelProperty ==>
 *
 *
 *
 *
 *
 *
 ************************************************************************/

#include "../../../app_settings.h"
#include <QDebug>
#include <stdio.h>
#include "QFDCAN_OverrideFilter_ModelItem.h"
#include "../../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QRegExp>
#include "../OverrideStatus.h"

class QFDCAN_OverrideFilter_ModelProperty: public Obj_List_Model<QFDCAN_OverrideFilter_ModelItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )

    Q_PROPERTY(QString id_begin READ id_begin WRITE set_id_begin NOTIFY changed)
    Q_PROPERTY(QString id_end READ id_end WRITE set_id_end NOTIFY changed)
    Q_PROPERTY(bool can1tocan2_dir READ can1tocan2_dir WRITE set_can1tocan2_dir NOTIFY changed)
    Q_PROPERTY(bool can2tocan1_dir READ can2tocan1_dir WRITE set_can2tocan1_dir NOTIFY changed)
    Q_PROPERTY(bool range_used READ range_used WRITE set_range_used NOTIFY changed)

public:
    explicit QFDCAN_OverrideFilter_ModelProperty(){
    };
    virtual ~QFDCAN_OverrideFilter_ModelProperty(){};

    //==================================== init =======================================
    Q_INVOKABLE void init (){
         for(size_t i = 0; i< App_settings::MAX_FDCAN_BYTES_COUNT; i++){
             auto _item = QSharedPointer<QFDCAN_OverrideFilter_ModelItem> (new QFDCAN_OverrideFilter_ModelItem(this, i,0,0,0,FDCAN_filter_method_default));
             this->append(_item);
         }
     }

    Q_INVOKABLE void fill_OverrideStatus(FDCAN_OverrideStatus* ovr_sts) const;
    Q_INVOKABLE void update_model_from_OverrideStatus(FDCAN_OverrideStatus* ovr_sts);

    //================================ Setters/getters ================================
    Q_INVOKABLE QVariant item( int i ) {
        if ( i < 0 || i >= count() ) return QVariant();
        auto obj = at( i ).data();
        QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );
        return QVariant::fromValue( obj );
    }

    QString id_begin ()const{return QString::number(m_fdcan_filter_hdr.id_begin, 16);}
    QString id_end ()const{return QString::number(m_fdcan_filter_hdr.id_end, 16);}
    bool can1tocan2_dir ()const{
        if((m_fdcan_filter_hdr.input_dir == FDCAN_filter_dir_both) || (m_fdcan_filter_hdr.input_dir == FDCAN_filter_dir_1i2o)) return true;
        else return false;
    };
    bool can2tocan1_dir ()const{
        if((m_fdcan_filter_hdr.input_dir == FDCAN_filter_dir_both) || (m_fdcan_filter_hdr.input_dir == FDCAN_filter_dir_2i1o)) return true;
        else return false;
    };

    void set_id_begin(const QString &newval){
        bool res = false;
        uint32_t new_int_value = newval.toInt(&res, 16);
        if(res & (new_int_value > 0x00)) {
            m_fdcan_filter_hdr.id_begin = new_int_value;
        }
        emit changed();
    }
    void set_id_end(const QString &newval){
        bool res = false;
        uint32_t new_int_value = newval.toInt(&res, 16);
        if(res & (new_int_value <= 0x1FFFFFFF)) {
            m_fdcan_filter_hdr.id_end = new_int_value;
        }
        emit changed();
    }
    void set_can1tocan2_dir(bool val){
        if(val == false){
            if(m_fdcan_filter_hdr.input_dir == FDCAN_filter_dir_both){
                m_fdcan_filter_hdr.input_dir = FDCAN_filter_dir_2i1o;
                emit changed();
            }
        }
        else{
            if(m_fdcan_filter_hdr.input_dir == FDCAN_filter_dir_2i1o){
                m_fdcan_filter_hdr.input_dir = FDCAN_filter_dir_both;
                emit changed();
            }
        }
    }

    void set_can2tocan1_dir(bool val){
        if(val == false){
            if(m_fdcan_filter_hdr.input_dir == FDCAN_filter_dir_both){
                m_fdcan_filter_hdr.input_dir = FDCAN_filter_dir_1i2o;
                emit changed();
            }
        }
        else{
            if(m_fdcan_filter_hdr.input_dir == FDCAN_filter_dir_1i2o){
                m_fdcan_filter_hdr.input_dir = FDCAN_filter_dir_both;
                emit changed();
            }
        }
    }
    bool range_used() const{return m_range_used;}

    void set_range_used(bool val){
        m_range_used = val;
        if(!m_range_used){
            m_fdcan_filter_hdr.id_end = m_fdcan_filter_hdr.id_begin;
        }
        emit changed();
    }


Q_SIGNALS:
    void changed();

protected:
    fdcan_filter_hdr m_fdcan_filter_hdr;
    bool m_range_used = false;
    virtual void emitChanged() {
        emit changed();
    }
};


#endif // QFDCAN_OVERRIDEFILTER_MODELPROPERTY_H
