#ifndef QVEHICLE_MODELPROPERTY_H
#define QVEHICLE_MODELPROPERTY_H

#include "../../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <stdio.h>
#include "QVehicle_ModelItem.h"
#include "../../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QRegExp>


/*****************************************************************************************/
/* QSerialPortConfigProperty is a model list, that incapsulates all supported car models */
/*****************************************************************************************/
/*****************************************************************************************/


class QVehicle_ModelProperty: public Obj_List_Model<QVehicle_ModelItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )
    Q_PROPERTY( QVariant current_item READ current_item NOTIFY changed )
    Q_PROPERTY( int current_index READ getCurrentIndex NOTIFY changed )


public:
    explicit QVehicle_ModelProperty(){
    };
    virtual ~QVehicle_ModelProperty(){};


    Q_INVOKABLE QVariant item( int i ) {
        if ( i < 0 || i >= count() ) return QVariant();
        auto obj = at( i ).data();
        QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );
        return QVariant::fromValue( obj );
    }

    Q_INVOKABLE QVariant current_item();
    Q_INVOKABLE int getCurrentIndex() const;
    Q_INVOKABLE void setCurrentIndex(int _index);

    int get_current_value();
    const QString get_current_name();
    const int get_property_value(const int i);
    const void set_property_value(const int _new_val, const int i);

    virtual void init (){};

Q_SIGNALS:
    void changed();

protected:
    virtual void emitChanged() {
        emit changed();
    }

    int current_index = 0;
    int default_index = 0;
};

/*****************************************************************************************/
/*********************       Model names property model      *****************************/
/*****************************************************************************************/

class QVehicleNames_ModelProperty: public QVehicle_ModelProperty{
    Q_OBJECT

public:
    explicit QVehicleNames_ModelProperty(): QVehicle_ModelProperty(){
    };
    virtual ~QVehicleNames_ModelProperty(){};


    void init () override;

    protected:
    private:
};

#endif // QVEHICLE_MODELPROPERTY_H
