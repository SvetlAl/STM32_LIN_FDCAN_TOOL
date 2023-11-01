#ifndef QLINCONFIGPROPERTY_H
#define QLINCONFIGPROPERTY_H

#include "../../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <stdio.h>
#include "QLinConfigItem.h"
#include "../../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QRegExp>

/*****************************************************************************************/
/*** QLinConfigProperty is a model list, that incapsulates all supported LIN settings  ***/
/***********                                                                   ***********/
/**********  Filter preset                                                     ***********/
/***********   OFF                                                             ***********/
/**********    USER                                                            ***********/
/***********   MODEL_LIST                                                      ***********/
/*****************************************************************************************/
/**********  Baud Rate                                                         ***********/
/*********** LIN_1200    0x00                                                  ***********/
/*********** LIN_2400    0x01                                                  ***********/
/*********** LIN_4800    0x02                                                  ***********/
/*********** LIN_9600    0x03                                                  ***********/
/*********** LIN_19200   0x04                                                  ***********/
/*********** LIN_38400   0x05                                                  ***********/
/*********** LIN_57600   0x06                                                  ***********/
/*********** LIN_115200  0x07                                                  ***********/
/*********** LIN_921600  0x08                                                  ***********/
/*****************************************************************************************/
/*****************************************************************************************/


class QLinConfigProperty: public Obj_List_Model<QLinConfigItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )
    Q_PROPERTY( QVariant current_item READ current_item NOTIFY changed )
    Q_PROPERTY( int current_index READ getCurrentIndex NOTIFY changed )


public:
    explicit QLinConfigProperty(){
    };
    virtual ~QLinConfigProperty(){};


    Q_INVOKABLE QVariant item( int i ) {
        if ( i < 0 || i >= count() ) return QVariant();
        auto obj = at( i ).data();
        QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );
        return QVariant::fromValue( obj );
    }

    Q_INVOKABLE QVariant current_item() {
        return item(current_index);
    }

    Q_INVOKABLE int getCurrentIndex() const{
        return current_index;
    }

    Q_INVOKABLE void setCurrentIndex(int _index){
        current_index = _index;
    }
    void setDefaultIndex(int _index){
            default_index = _index;
    }

    int get_current_value(){
        QSharedPointer<QLinConfigItem> val_ptr = dataPtr(current_index);
        return val_ptr->value();
    }
    const QString get_current_name(){
        QSharedPointer<QLinConfigItem> val_ptr = dataPtr(current_index);
        return val_ptr->name();
    }

    const int get_property_value(const int i){
        QSharedPointer<QLinConfigItem> val_ptr = dataPtr(i);
        return val_ptr->value();
    }

    const void set_property_value(const int _new_val, const int i){
        QSharedPointer<QLinConfigItem> val_ptr = dataPtr(i);
        val_ptr->setValue(_new_val);
    }


Q_SIGNALS:
    void changed();

protected:
    virtual void emitChanged() {
        emit changed();
    }

    virtual void init (){};
    int current_index = 0;
    int default_index = 0;
};

#endif // QLINCONFIGPROPERTY_H
