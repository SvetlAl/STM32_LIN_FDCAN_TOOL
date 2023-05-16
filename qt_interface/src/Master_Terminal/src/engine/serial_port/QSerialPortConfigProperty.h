#ifndef QSERIALPORTCONFIGPROPERTY_H
#define QSERIALPORTCONFIGPROPERTY_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <stdio.h>
#include "QSerialPortConfigItem.h"
#include "../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QRegExp>


/*****************************************************************************************/
/*** QSerialPortConfigProperty is a model list, that incapsulates all supported settings */
/***********                                                                   ***********/
/**********  Com Port Name (COM1, COM3, COM7)                                  ***********/
/***********                                                                   ***********/
/**********  Flow control                                                      ***********/
/*********** QSerialPort::FlowControl::NoFlowControl default                   ***********/
/*********** QSerialPort::FlowControl::HardwareControl                         ***********/
/*********** QSerialPort::FlowControl::SoftwareControl                         ***********/
/***********                                                                   ***********/
/**********  Stop Bits                                                         ***********/
/*********** QSerialPort::StopBits::OneStop default                            ***********/
/*********** QSerialPort::StopBits::OneAndHalfStop                             ***********/
/*********** QSerialPort::StopBits::TwoStop                                    ***********/
/***********                                                                   ***********/
/**********  Parity                                                            ***********/
/*********** QSerialPort::Parity::NoParity default                             ***********/
/*********** QSerialPort::Parity::EvenParity                                   ***********/
/*********** QSerialPort::Parity::OddParity                                    ***********/
/*********** QSerialPort::Parity::SpaceParity                                  ***********/
/*********** QSerialPort::Parity::MarkParity                                   ***********/
/***********                                                                   ***********/
/**********  Data Bits                                                         ***********/
/*********** QSerialPort::DataBits::Data5                                      ***********/
/*********** QSerialPort::DataBits::Data6                                      ***********/
/*********** QSerialPort::DataBits::Data7                                      ***********/
/*********** QSerialPort::DataBits::Data8 default                              ***********/
/***********                                                                   ***********/
/**********  Baud Rate                                                         ***********/
/*********** QSerialPort::BaudRate::Baud1200                                   ***********/
/*********** QSerialPort::BaudRate::Baud2400                                   ***********/
/*********** QSerialPort::BaudRate::Baud4800                                   ***********/
/*********** QSerialPort::BaudRate::Baud9600                                   ***********/
/*********** QSerialPort::BaudRate::Baud19200                                  ***********/
/*********** QSerialPort::BaudRate::Baud38400                                  ***********/
/*********** QSerialPort::BaudRate::Baud57600                                  ***********/
/*********** QSerialPort::BaudRate::Baud115200 default                         ***********/
/*********** +Custom setting                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/


class QSerialPortConfigProperty: public Obj_List_Model<QSerialPortConfigItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )
    Q_PROPERTY( QVariant current_item READ current_item NOTIFY changed )
    Q_PROPERTY( int current_index READ getCurrentIndex NOTIFY changed )


public:
    explicit QSerialPortConfigProperty(){
    };
    virtual ~QSerialPortConfigProperty(){};


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
        QSharedPointer<QSerialPortConfigItem> val_ptr = dataPtr(current_index);
        return val_ptr->value();
    }
    const QString get_current_name(){
        QSharedPointer<QSerialPortConfigItem> val_ptr = dataPtr(current_index);
        return val_ptr->name();
    }

    const int get_property_value(const int i){
        QSharedPointer<QSerialPortConfigItem> val_ptr = dataPtr(i);
        return val_ptr->value();
    }

    const void set_property_value(const int _new_val, const int i){
        QSharedPointer<QSerialPortConfigItem> val_ptr = dataPtr(i);
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

/*****************************************************************************************/
/*********************      Port number: COM1, COM2, COM3    *****************************/
/*****************************************************************************************/

class QSerialPortConfigProperty_PortNumber: public QSerialPortConfigProperty{
    Q_OBJECT

public:
    explicit QSerialPortConfigProperty_PortNumber(): QSerialPortConfigProperty(){
        QSerialPortConfigProperty_PortNumber::init();
    };
    virtual ~QSerialPortConfigProperty_PortNumber(){};

    void reinit(){
        clear();
        init ();
    }

protected:
    void init () override{

        QSerialPortInfo port_info;
        auto _index_count = 0;
        if(QSerialPortInfo::availablePorts().count() == 0){
            auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, "ports not found", 0));
            this->append(_item);
            current_index = default_index = 0;
            return;
        }

        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            QString _name = info.portName();
            int _value = 0;

            QString tmp = "";
            for (int i =0; i < _name.size(); i++){
                if (_name[i].isDigit()) // to check if it is number!!
                    tmp.append(_name[i]);
            }
            if(tmp != "") _value = tmp.toInt();

            auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, _name, _value));
            this->append(_item);
            if(info.productIdentifier() == App_settings::DEFAULT_DEVICE_PID){
                current_index = default_index = _index_count;
            }
            _index_count++;
        }
    }

private:

};

/*****************************************************************************************/
/*********************        FlowControl      *******************************************/
/*****************************************************************************************/

class QSerialPortConfigProperty_FlowControl: public QSerialPortConfigProperty{
    Q_OBJECT

public:
    explicit QSerialPortConfigProperty_FlowControl(): QSerialPortConfigProperty(){
        QSerialPortConfigProperty_FlowControl::init();
    };
    virtual ~QSerialPortConfigProperty_FlowControl(){};

protected:
    void init () override{
        const QString default_NoFlowControl = "NoFlowControl"; /* default name */

        QList<QString> _name_list = {
            default_NoFlowControl,
            "Hardware Control",
            "Software Control"};

        QMetaEnum e = QMetaEnum::fromType<QSerialPort::FlowControl>();

        auto enum_items_counter =  e.keyCount(); /* how many items in Enum */
        auto enum_items_to_go =  enum_items_counter;
        auto enum_items_passed =  0;

        auto k = 0; /* from 0 to max value in Enum */

        for (k = 0; k < enum_items_counter; k++){
            if( e.valueToKey(k) != NULL){
                QString _name = _name_list.at(enum_items_passed);

                auto _value = e.value(enum_items_passed);
                auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, _name, _value));
                this->append(_item);
                if(_name == default_NoFlowControl){
                    current_index = default_index = enum_items_passed;
                }
                enum_items_passed++;
                enum_items_to_go--;
            }
            else if(enum_items_to_go > 0){
                enum_items_counter++;
            }
        } /*** finished with presets ***/

    }

private:
};

/*****************************************************************************************/
/*********************        Baud rate: 1200-115200      ********************************/
/*****************************************************************************************/

class QSerialPortConfigProperty_BaudRate: public QSerialPortConfigProperty{
    Q_OBJECT
    Q_PROPERTY(int custom_value READ custom_value WRITE set_custom_value NOTIFY changed )
public:
    explicit QSerialPortConfigProperty_BaudRate(): QSerialPortConfigProperty(){
        QSerialPortConfigProperty_BaudRate::init();
    };
    virtual ~QSerialPortConfigProperty_BaudRate(){};

    const int get_custom_index(){
        return custom_index;
    }

    const int custom_value(){
        QSharedPointer<QSerialPortConfigItem> val_ptr = dataPtr(custom_index);
        return val_ptr->value();
    }

    const void set_custom_value(const int _new_val){
        QSharedPointer<QSerialPortConfigItem> val_ptr = dataPtr(custom_index);
        val_ptr->setValue(_new_val);
    }

protected:
    void init () override{
        const QString default_115200 = "115200 baud"; /* default name */

        QList<QString> _name_list = {
            "1200 baud",
            "2400 baud",
            "4800 baud",
            "9600 baud",
            "19200 baud",
            "38400 baud",
            "57600 baud",
            default_115200,
            "Custom" };

       QList<int> _value_list {
            QSerialPort::BaudRate::Baud1200,
            QSerialPort::BaudRate::Baud2400,
            QSerialPort::BaudRate::Baud4800,
            QSerialPort::BaudRate::Baud9600,
            QSerialPort::BaudRate::Baud19200,
            QSerialPort::BaudRate::Baud38400,
            QSerialPort::BaudRate::Baud57600,
            QSerialPort::BaudRate::Baud115200
        };
       auto k = 0;
       for (k = 0; k < _value_list.count(); k++){
           QString _name = _name_list.at(k);
           auto _value =_value_list.at(k);
           auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, _name, _value));
           this->append(_item);
           if(_name == default_115200){
               current_index = default_index = k;
           }
       } /*** finished with presets ***/

       QString _name = _name_list.at(k);
       auto _value = QSerialPort::BaudRate::Baud115200;
       auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, _name, _value));
       this->append(_item);
       custom_index = k;
    }

private:
    int custom_index = 0;
};

/*****************************************************************************************/
/*********************          Stop Bits      *******************************************/
/*****************************************************************************************/

class QSerialPortConfigProperty_StopBits: public QSerialPortConfigProperty{
    Q_OBJECT

public:
    explicit QSerialPortConfigProperty_StopBits(): QSerialPortConfigProperty(){
        QSerialPortConfigProperty_StopBits::init();
    };
    virtual ~QSerialPortConfigProperty_StopBits(){};

protected:
    void init () override{
        const QString default_StopBits = "1 Stop"; /* default name */

        QList<QString> _name_list = {
            default_StopBits,
            "1.5 Stop",
            "2 Stop"};

        QMetaEnum e = QMetaEnum::fromType<QSerialPort::StopBits>();


        auto enum_items_counter =  e.keyCount(); /* how many items in Enum */
        auto enum_items_to_go =  enum_items_counter;
        auto enum_items_passed =  0;

        auto k = 0; /* from 0 to max value in Enum */

        for (k = 0; k < enum_items_counter; k++){
            if( e.valueToKey(k) != NULL){
                QString _name = _name_list.at(enum_items_passed);

                auto _value = e.value(enum_items_passed);
                auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, _name, _value));
                this->append(_item);
                if(_name == default_StopBits){
                    current_index = default_index = enum_items_passed;
                }
                enum_items_passed++;
                enum_items_to_go--;
            }
            else if(enum_items_to_go > 0){
                enum_items_counter++;
            }
        } /*** finished with presets ***/
    }

private:
};


/*****************************************************************************************/
/*********************          Parity      **********************************************/
/*****************************************************************************************/

class QSerialPortConfigProperty_Parity: public QSerialPortConfigProperty{
    Q_OBJECT

public:
    explicit QSerialPortConfigProperty_Parity(): QSerialPortConfigProperty(){
        QSerialPortConfigProperty_Parity::init();
    };
    virtual ~QSerialPortConfigProperty_Parity(){};

protected:
    void init () override{
        const QString default_Parity = "No Parity"; /* default name */

        QList<QString> _name_list = {
            default_Parity,
            "Even Parity",
            "Odd Parity",
            "Space Parity",
            "Mark Parity"};

        QMetaEnum e = QMetaEnum::fromType<QSerialPort::Parity>();

        auto enum_items_counter =  e.keyCount(); /* how many items in Enum */
        auto enum_items_to_go =  enum_items_counter;
        auto enum_items_passed =  0;

        auto k = 0; /* from 0 to max value in Enum */

        for (k = 0; k < enum_items_counter; k++){
            if( e.valueToKey(k) != NULL){
                QString _name = _name_list.at(enum_items_passed);

                auto _value = e.value(enum_items_passed);
                auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, _name, _value));
                this->append(_item);
                if(_name == default_Parity){
                    current_index = default_index = enum_items_passed;
                }
                enum_items_passed++;
                enum_items_to_go--;
            }
            else if(enum_items_to_go > 0){
                enum_items_counter++;
            }
        } /*** finished with presets ***/
    }

private:
};


/*****************************************************************************************/
/*********************          DataBits      ********************************************/
/*****************************************************************************************/

class QSerialPortConfigProperty_DataBits: public QSerialPortConfigProperty{
    Q_OBJECT

public:
    explicit QSerialPortConfigProperty_DataBits(): QSerialPortConfigProperty(){
        QSerialPortConfigProperty_DataBits::init();
    };
    virtual ~QSerialPortConfigProperty_DataBits(){};

protected:
    void init () override{
        const QString default_DataBits = "Data 8"; /* default name */

        QList<QString> _name_list = {
            "Data 5",
            "Data 6",
            "Data 7",
            default_DataBits};

        QMetaEnum e = QMetaEnum::fromType<QSerialPort::DataBits>();

        auto enum_items_counter =  e.keyCount(); /* how many items in Enum */
        auto enum_items_to_go =  enum_items_counter;
        auto enum_items_passed =  0;

        auto k = 0; /* from 0 to max value in Enum */

        for (k = 0; k < enum_items_counter; k++){
            if( e.valueToKey(k) != NULL){
                QString _name = _name_list.at(enum_items_passed);

                auto _value = e.value(enum_items_passed);
                auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, _name, _value));
                this->append(_item);
                if(_name == default_DataBits){
                    current_index = default_index = enum_items_passed;
                }
                enum_items_passed++;
                enum_items_to_go--;
            }
            else if(enum_items_to_go > 0){
                enum_items_counter++;
            }
        } /*** finished with presets ***/
    }

private:
};


#endif // QSERIALPORTCONFIGPROPERTY_H
