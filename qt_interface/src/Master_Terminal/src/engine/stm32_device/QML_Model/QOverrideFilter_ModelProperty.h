#ifndef QOVERRIDEFILTER_MODELPROPERTY_H
#define QOVERRIDEFILTER_MODELPROPERTY_H

/***********************************************************************
 * QOverrideFilter_ModelItem ==> QOverrideFilter_ModelProperty ==>
 *
 *
 *
 * QOverrideFilter_ModelProperty is a model list, that incapsulates override id filters
 *
 *
 *
 *
 ************************************************************************/

#include "../../../app_settings.h"
#include <QDebug>
#include <stdio.h>
#include "QOverrideFilter_ModelItem.h"
#include "../../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QRegExp>
#include "../OverrideStatus.h"

class QOverrideFilter_ModelProperty: public Obj_List_Model<QOverrideFilter_ModelItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )

public:
    explicit QOverrideFilter_ModelProperty(){
    };
    virtual ~QOverrideFilter_ModelProperty(){};

    //==================================== init =======================================
    Q_INVOKABLE void init (){
         for(size_t i = 0; i< App_settings::MAX_DISCARD_ID_COUNT; i++){
             auto _item = QSharedPointer<QOverrideFilter_ModelItem> (new QOverrideFilter_ModelItem(this));
             this->append(_item);
         }
     }

    Q_INVOKABLE void fill_OverrideStatus(OverrideStatus* ovr_sts) const;
    Q_INVOKABLE void update_model_from_OverrideStatus(OverrideStatus* ovr_sts);

    //================================ Setters/getters ================================
    Q_INVOKABLE QVariant item( int i ) {
        if ( i < 0 || i >= count() ) return QVariant();
        auto obj = at( i ).data();
        QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );
        return QVariant::fromValue( obj );
    }

    const void set_str_id_value(const int i, const QString &_new_val);
    const void set_byte0_value(const int i, const QString &_new_val);
    const void set_byte1_value(const int i, const QString &_new_val);
    const void set_byte2_value(const int i, const QString &_new_val);
    const void set_byte3_value(const int i, const QString &_new_val);
    const void set_byte4_value(const int i, const QString &_new_val);
    const void set_byte5_value(const int i, const QString &_new_val);
    const void set_byte6_value(const int i, const QString &_new_val);
    const void set_byte7_value(const int i, const QString &_new_val);
    const void enable_byte0(const int i, bool _on);
    const void enable_byte1(const int i, bool _on);
    const void enable_byte2(const int i, bool _on);
    const void enable_byte3(const int i, bool _on);
    const void enable_byte4(const int i, bool _on);
    const void enable_byte5(const int i, bool _on);
    const void enable_byte6(const int i, bool _on);
    const void enable_byte7(const int i, bool _on);

    Q_INVOKABLE void enable_filter(const int i, bool _value);

Q_SIGNALS:
    void changed();

protected:
    virtual void emitChanged() {
        emit changed();
    }
};


#endif // QOVERRIDEFILTER_MODELPROPERTY_H
