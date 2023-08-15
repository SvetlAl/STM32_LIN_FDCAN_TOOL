#ifndef QDISCARDID_MODELPROPERTY_H
#define QDISCARDID_MODELPROPERTY_H

/***********************************************************************
 * QDiscardId_ModelItem ==> QDiscardId_ModelProperty ==>
 *
 *
 *
 * QDiscardId_ModelProperty is a model list, that incapsulates discard id filters
 *
 *
 *
 *
 ************************************************************************/

#include "../../../app_settings.h"
#include <QDebug>
#include <stdio.h>
#include "QDiscardId_ModelItem.h"
#include "../../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QRegExp>
#include "../OverrideStatus.h"

class QDiscardId_ModelProperty: public Obj_List_Model<QDiscardId_ModelItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )

public:
    explicit QDiscardId_ModelProperty(){
    };
    virtual ~QDiscardId_ModelProperty(){};

    //==================================== init =======================================
    Q_INVOKABLE void init (){
        /* check connection */
        /* if connected, fill the components */
        if(count() != 0) return;
        for(size_t i = 0; i < App_settings::MAX_DISCARD_ID_COUNT; i++){
            auto _item = QSharedPointer<QDiscardId_ModelItem> (new QDiscardId_ModelItem(this));
            this->append(_item);
        }
    }

    Q_INVOKABLE void deinit (){
        clear();
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

    Q_INVOKABLE void enable_filter(const int i, bool _value);
    Q_INVOKABLE void set_filter_can_value(const int i, int can);
    Q_INVOKABLE void set_filter_id_value(const int i, const QString &_new_val);


Q_SIGNALS:
    void changed();

protected:
    virtual void emitChanged() {
        emit changed();
    }
};



#endif // QDISCARDID_MODELPROPERTY_H
