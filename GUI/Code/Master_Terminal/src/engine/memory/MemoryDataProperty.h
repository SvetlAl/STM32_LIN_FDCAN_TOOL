#ifndef MEMORYDATAROPERTY_H
#define MEMORYDATAROPERTY_H

/***********************************************************************
 * MemoryManager <== FlashSpiMemoryDataProperty
 *                   *MemoryDataProperty         <==  MemoryDataItem
 *
 *
 * MemoryDataProperty is a data model, that represents chip memory data as
 *  Address
 *  B0  (bytes 0-3)
 *  B4  (bytes 4-7)
 *  B8  (bytes 8-11)
 *  BC  (bytes 12-15)
 *  ASCII representation of B0-BC data
 *
 *
 *
 ************************************************************************/

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <stdio.h>
#include "MemoryDataItem.h"
#include "../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QRegExp>

/*****************************************************************************************/


class MemoryDataProperty: public Obj_List_Model<MemoryDataItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )

public:
    explicit MemoryDataProperty(){
        m_columnNames << "Address" << "0" << "4" << "8" << "C" << "Ascii";
    };

    virtual ~MemoryDataProperty(){};

    //================================= Static preset ==================================
    enum {
        Address = 0,
        B0 ,
        B4 ,
        B8 ,
        BC ,
        ASCII ,
        ColumnCount
    };

    //=================================== Init =========================================
    virtual void addItem(const QString &addr, const QString &value){
        QString _addr = addr;
        // Validate input strings

         regex.setPattern("[0-9A-F]{1,16}");
         if (!regex.match(addr).hasMatch()) {
             qDebug() << "Invalid address:" << addr;
             return;
         }
         else  _addr = addr;

         regex.setPattern("[0-9A-F]{32}");
         if (!regex.match(value).hasMatch()) {
             qDebug() << "Invalid value:" << value;
             return;
         }

         // Pad address with zeros if necessary
         if (_addr.length() < 16) {
             _addr.prepend(QString(16 - _addr.length(), '0'));
         }

        auto _item = QSharedPointer<MemoryDataItem>(new MemoryDataItem(this, _addr, value));
        this->append(_item);
    }

    //================================ Data access =====================================
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;


    QVariant data( const QModelIndex& index, int role ) const override {
        if (!index.isValid())
            return QVariant();

        auto row = index.row();
        auto col = index.column();

        if ( row < 0 || row >= count())
            return QVariant();

        if (role == Qt::DisplayRole ){
            switch (col)
            {
            case Address:
                return getAddress(row);
            case B0:
                return bytes0(row);
            case B4:
                return bytes4(row);
            case B8:
                return bytes8(row);
            case BC:
                return bytesC(row);
            case ASCII:
                return Ascii(row);
            }
        }

        else if(role == ItemDataRole){
            return QVariant::fromValue<QObject*>(at( row ).data() );
        }

        return QVariant();
    }


    Q_INVOKABLE QVariant item( int i ) {
        if ( i < 0 || i >= count() ) return QVariant();
        auto obj = at( i ).data();
        QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );
        return QVariant::fromValue( obj );
    }




    const QString getAddress(const int i) const{
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        return val_ptr->Address();
    }
    const void setAddress(const QString &_new_val, const int i){
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        val_ptr->setAddress(_new_val);
    }
    //=========================================================
    //=========================================================
    const QString bytes0(const int i) const{
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        return val_ptr->Byte0();
    }
    const void setBytes0(const QString &_new_val, const int i){
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        val_ptr->setByte0(_new_val);
    }
    //=========================================================
    const QString bytes4(const int i) const{
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        return val_ptr->Byte4();
    }
    const void setBytes4(const QString &_new_val, const int i){
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        val_ptr->setByte4(_new_val);
    }
    //=========================================================
    const QString bytes8(const int i) const{
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        return val_ptr->Byte8();
    }
    const void setBytes8(const QString &_new_val, const int i){
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        val_ptr->setByte8(_new_val);
    }
    //=========================================================
    const QString bytesC(const int i) const{
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        return val_ptr->ByteC();
    }
    const void setBytesC(const QString &_new_val, const int i){
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        val_ptr->setByteC(_new_val);
    }


    const QString Ascii(const int i) const{
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        return val_ptr->Ascii();
    }
    const void setAscii(const QString &_new_val, const int i){
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        val_ptr->setAscii(_new_val);
    }

    const QByteArray raw_data(const int i) const{
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        return val_ptr->raw_data();
    }
    const void setRaw_data(const QByteArray &_new_val, const int i){
        QSharedPointer<MemoryDataItem> val_ptr = dataPtr(i);
        val_ptr->setRaw_data(_new_val);
    }



Q_SIGNALS:
    void changed();

protected:
    void emitChanged() override{
        emit changed();
    }

    virtual void init (){};
    QRegularExpression regex;
    QStringList m_columnNames;
};





class FlashSpiMemoryDataProperty: public MemoryDataProperty{
    Q_OBJECT
public:
    explicit FlashSpiMemoryDataProperty(): MemoryDataProperty(){
    };
    virtual ~FlashSpiMemoryDataProperty(){};

    //=================================== Init =========================================
    void addItem(const QString &addr, const QString &value) override{
        QString _addr = addr;
        // Validate input strings

        QString addr_pattern = QString("[0-9A-F]{1,%1}").arg(addr_length);
         regex.setPattern(addr_pattern);
         if (!regex.match(addr).hasMatch()) {
             qDebug() << "Invalid address:" << addr;
             return;
         }
         else  _addr = addr;

         regex.setPattern("[0-9A-F]{32}");
         if (!regex.match(value).hasMatch()) {
             qDebug() << "Invalid value:" << value;
             return;
         }

         // Pad address with zeros if necessary
         if (_addr.length() < addr_length) {
             _addr.prepend(QString(addr_length - _addr.length(), '0'));
         }

        auto _item = QSharedPointer<MemoryDataItem>(new MemoryDataItem(this, _addr, value));
        this->append(_item);
    }


protected:
    const int addr_length = 9;
};



#endif // MEMORYDATAROPERTY_H
