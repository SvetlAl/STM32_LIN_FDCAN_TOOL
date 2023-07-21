#ifndef BUSDATAPROPERTY_H
#define BUSDATAPROPERTY_H

#include "../../app_settings.h"
#include <QDebug>
#include <stdio.h>
#include "CanBusItem.h"
#include "../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QRegExp>
#include "ParseFilter.h"

/*****************************************************************************************/

class CanBusTraceProperty: public Obj_List_Model<CanBusItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed)

public:
    explicit CanBusTraceProperty(){
        m_columnNames << " " << "Time" << "CAN" << "IDE" << "ID" << "DLC" << "Data";
    };

    ~CanBusTraceProperty(){};

    enum CollectionRole {
        BoolDataRole = (Qt::UserRole + 1)
    };

    enum {
        IsSelected = 0,
        Time ,
        CAN ,
        IDE,
        ID ,
        DLC ,
        Data ,
        ColumnCount
    };

    QHash<int, QByteArray> roleNames() const override {
        auto roles = QAbstractListModel::roleNames();
        roles[ItemDataRole] = ITEM_ROLE_NAME;
        roles[BoolDataRole] = BOOL_ROLE_NAME;
        return roles;
    }

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

        if (role == BoolDataRole ){
            switch (col)
            {
            case IsSelected:
                return b_isSelected(row);
            case IDE:
                return extIde(row);


            case Time:
                return false;
            case CAN:
                return false;
            case ID:
                return false;
            case DLC:
                return false;
            case Data:
                return false;
            }
        }

        if (role == Qt::DisplayRole ){
            switch (col)
            {   
            case IsSelected:
                return "";//getIsSelected(row);
            case Time:
                return getTime(row);
            case CAN:
                return getCan(row);
            case IDE:
                return getIde(row);
            case ID:
                return getId(row);
            case DLC:
                return getDlc(row);
            case Data:
                return getData(row);
            }
        }

        else if(role == ItemDataRole){
            return QVariant::fromValue<QObject*>(at( row ).data() );
        }
        return QVariant();
    }

    bool setData(const QModelIndex &item, const QVariant &value, int role) override{
        if (item.isValid() && role == Qt::EditRole) {
            auto row = item.row();
            auto col = item.column();

            if (role == Qt::EditRole ){

                switch (col)
                {
                case IsSelected:
                    setIsSelected(value.toBool(), row);
                    emit changed();
                    return true;
                case Time:
                    setTime(value.toString(), row);
                    emit changed();
                    return true;
                case CAN:
                    setCan(value.toString(), row);
                    emit changed();
                    return true;
                case IDE:
                    setIde(value.toString(),row);
                    emit changed();
                    return true;
                case ID:
                    setId(value.toString(),row);
                    emit changed();
                    return true;
                case DLC:
                    setDlc(value.toString(),row);
                    emit changed();
                    return true;
                case Data:
                    setData(value.toString(),row);
                    emit changed();
                    return true;
                }
            }
            emitChanged();
            return true;
        }
        return false;
    }



    Q_INVOKABLE QVariant item( int i ) {
        if ( i < 0 || i >= count() ) return QVariant();
        auto obj = at( i ).data();
        QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );
        return QVariant::fromValue( obj );
    }

    void addItem(const QByteArray &data, bool validate = false);
    void addItem(const QByteArray &data, const ParseFilter &filter, bool validate = false);

    void sortColumn(const int col, bool fromTopToBottom = true);
    void switchSortColumn(const int col);
    void deleteSelected();
    void deleteRange(int begin, int end);
    void setAllMsgsDirection(int id, int dir);
    void deductTimeStamp(uint32_t tmstmp);
    void deleteTimeStampRange(int start, int end);

    //=========================================================
    //=========================================================
    QString getIsSelected(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return (val_ptr->isSelected() ? "1" : "0");
    }
    Q_INVOKABLE bool b_isSelected(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return (val_ptr->isSelected());
    }
    const void setIsSelected(QVariant _new_val, const int i){
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        val_ptr->setIsSelected(_new_val.toBool());
       // emit selectChanged();
    }
    //=========================================================
    //=========================================================
    QString getIde(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return val_ptr->ide();
    }
    Q_INVOKABLE bool extIde(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return (val_ptr->bool_ext_ide());
    }
    const void setIde(const QString &_new_val, const int i){
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        val_ptr->setIde(_new_val);
       // emit selectChanged();
    }
    //=========================================================
    //=========================================================

    QString getTime(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return val_ptr->time();
    }
    const void setTime(const QString &_new_val, const int i){
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        val_ptr->setTime(_new_val);
    }
    //=========================================================
    //=========================================================
    Q_INVOKABLE const QString getCan(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return val_ptr->can();
    }

    const void setCan(const QString &_new_val, const int i){
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        val_ptr->setCan(_new_val);
    }
    //=========================================================
    const QString getId(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return val_ptr->id();
    }
    const void setId(const QString &_new_val, const int i){
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        val_ptr->setId(_new_val);
    }
    //=========================================================
    const QString getDlc(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return val_ptr->dlc();
    }
    const void setDlc(const QString &_new_val, const int i){
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        val_ptr->setDlc(_new_val);
    }
    //=========================================================
    const QString getData(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return val_ptr->data();
    }
    const void setData(const QString &_new_val, const int i){
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        val_ptr->setData(_new_val);
    }

    const QByteArray raw_data(const int i) const{
        QSharedPointer<CanBusItem> val_ptr = dataPtr(i);
        return val_ptr->getByteArray();
    }

    void debug() const{
        uint32_t i = (count() - 1);
        do{
            dataPtr(i)->print();
        }while(i--);
    }

    const QByteArray get_raw_data_for_cdc(int *start_pos, int msg_count, bool circular_mode) const{
        QByteArray arr;
        const int max_pos = count() - 1;
        int pos = *start_pos;
        int messages_to_send = msg_count;
        while(messages_to_send--){
            //qDebug() << "**************if(pos > max_pos)********************";
            //qDebug() << "circular_mode  " << circular_mode;
            // qDebug() << "******* pos **** " << pos << "   ******** max_pos *******  " << max_pos;


            if(pos > max_pos){// the end of a trace reached
                if(circular_mode) pos = 0;
                else{
                    qDebug() << "Making invalid";
                    arr.append(CanBusItem::makeInvalidByteArray());
                }
            }

            if(pos <= max_pos){
                arr.append(raw_data(pos++));
            }
        }
        *start_pos = pos;
        return arr;
    }

    uint32_t max_items() const;
    void setMax_items(uint32_t newMax_items);

Q_SIGNALS:
    void changed();
    // void selectChanged();
public slots:


protected:
    void emitChanged() override{
        emit changed();
    }

    void init (){};

    QRegularExpression regex;
    bool sort_dir[ColumnCount] = {true};

    QStringList m_columnNames; // << " " << "Time" << "CAN" << "IDE" << "ID" << "DLC" << "Data";
    uint32_t m_max_items = App_settings::DEFAULT_MAX_TRACE_ITEMS;

    constexpr static const char BOOL_ROLE_NAME[] = "boolData";
};

















class CanBusMonitorProperty: public Obj_List_Model<CanBusItemMonitor>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed)

public:
    explicit CanBusMonitorProperty(){
        m_monitorColumnNames << "CAN"  << "ID" << "DLC" << "Data" << "Period" << "Count";
    };
    ~CanBusMonitorProperty(){};

    enum CollectionRole {
     //   BoolDataRole = (Qt::UserRole + 1)
    };

    enum {
        CAN ,
        ID,
        DLC ,
        Data ,
        Period ,
        Count,
        ColumnCount
    };

    QHash<int, QByteArray> roleNames() const override {
        auto roles = QAbstractListModel::roleNames();
        roles[ItemDataRole] = ITEM_ROLE_NAME;
    //    roles[BoolDataRole] = BOOL_ROLE_NAME;
        return roles;
    }

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;


    QVariant data( const QModelIndex& index, int role ) const override {
        if (!index.isValid())
            return QVariant();

        auto row = index.row();
 //       auto col = index.column();

        if ( row < 0 || row >= count())
            return QVariant();

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

    void addItem(const QByteArray &_can_msg_data, bool validate = false);
    void addItem(const QByteArray &_can_msg_data, const ParseFilter &filter, bool validate = false);


    bool containsId(int id) const {
        return m_idSet.contains(id);
    }


    void reset(){
        m_idSet.clear();
        clear();
    }

Q_SIGNALS:
    void changed();
    // void selectChanged();

public slots:


protected:
    void emitChanged() override{
        emit changed();}

    void init (){};

    QRegularExpression regex;
    QStringList m_monitorColumnNames; // << "CAN"  << "ID" << "DLC" << "Data" << "Period" << "Count";
    QHash<int, int> m_idSet;

};





#endif // BUSDATAPROPERTY_H
