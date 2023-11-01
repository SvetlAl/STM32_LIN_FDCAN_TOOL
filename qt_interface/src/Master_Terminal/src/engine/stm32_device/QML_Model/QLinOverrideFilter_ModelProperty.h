#ifndef QLINOVERRIDEFILTER_MODELPROPERTY_H
#define QLINOVERRIDEFILTER_MODELPROPERTY_H

/***********************************************************************
 * QLinOverrideFilter_ModelItem ==> QLinOverrideFilter_ModelProperty ==>
 *
 *
 *
 * QLinOverrideFilter_ModelProperty is a model list, that incapsulates override id filters
 *
 *
 *
 *
 ************************************************************************/

#include "../../../app_settings.h"
#include <QDebug>
#include <stdio.h>
#include "QLinOverrideFilter_ModelItem.h"
#include "../../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QRegExp>
#include "../Lin_filter.h"
//#include "../OverrideStatus.h"

class QLinOverrideFilter_ModelProperty: public Obj_List_Model<QLinOverrideFilter_ModelItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )

public:
    explicit QLinOverrideFilter_ModelProperty(){
    };
    virtual ~QLinOverrideFilter_ModelProperty(){};

    //==================================== init =======================================
    Q_INVOKABLE void init (){
        auto _item = QSharedPointer<QLinOverrideFilter_ModelItem> (new QLinOverrideFilter_ModelItem(this));
        this->append(_item);
        _item = QSharedPointer<QLinOverrideFilter_ModelItem> (new QLinOverrideFilter_ModelItem(this));
        _item->setDir_value(QLinOverrideFilter_ModelItem::dir_from_slave_to_master);
        this->append(_item);
     }

    //Q_INVOKABLE void fill_OverrideStatus(OverrideStatus* ovr_sts) const;
    //Q_INVOKABLE void update_model_from_OverrideStatus(OverrideStatus* ovr_sts);

    //================================ Setters/getters ================================
    Q_INVOKABLE QVariant item( int i ) {
        if ( i < 0 || i >= count() ) return QVariant();
        auto obj = at( i ).data();
        QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );
        return QVariant::fromValue( obj );
    }

    void set_lin_filter_values(const int i,lin_filter_raw* filter);
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

    //Q_INVOKABLE void enable_filter(const int i, bool _value);

Q_SIGNALS:
    void changed();

protected:
    virtual void emitChanged() {
        emit changed();
    }
};


#endif // QLINOVERRIDEFILTER_MODELPROPERTY_H
