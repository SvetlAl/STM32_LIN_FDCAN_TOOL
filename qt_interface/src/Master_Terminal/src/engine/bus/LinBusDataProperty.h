#ifndef LINBUSDATAPROPERTY_H
#define LINBUSDATAPROPERTY_H

/***********************************************************************
 *
 *
 *
 *
 ************************************************************************/

#include "../../app_settings.h"
#include <QDebug>
#include <stdio.h>
#include "LinBusItem.h"
#include "../Obj_list_model.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QQmlEngine>
#include <QVariant>
#include <QRegExp>
#include "ParseFilter.h"

/*****************************************************************************************/

class LinBusTraceProperty: public Obj_List_Model<LinBusItem>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed)

public:
    explicit LinBusTraceProperty(){
        m_columnNames << " " << "Time" << "LIN" << "ID" << "Length" << "Data";
    };

    ~LinBusTraceProperty(){};

    //=============================== Static preset =================================

    enum CollectionRole {
        BoolDataRole = (Qt::UserRole + 1)
    };

    enum {
        IsSelected = 0,
        Time ,
        LIN ,
        ID ,
        Length ,
        Data ,
        ColumnCount
    };

    // Two extra roles added
    QHash<int, QByteArray> roleNames() const override {
        auto roles = QAbstractListModel::roleNames();
        roles[ItemDataRole] = ITEM_ROLE_NAME;
        roles[BoolDataRole] = BOOL_ROLE_NAME;
        return roles;
    }
    //=================================== Init ======================================
    void addItem(const QByteArray &data, bool validate = false);
    void addItem(const QByteArray &data, const ParseFilter &filter, bool validate = false);

    //================================ Data access ==================================
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

            case Time:
                return false;
            case LIN:
                return false;
            case ID:
                return false;
            case Length:
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
            case LIN:
                return getLin(row);
            case ID:
                return getId(row);
            case Length:
                return getLength(row);
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
                case LIN:
                    setLin(value.toString(), row);
                    emit changed();
                    return true;
                case ID:
                    setId(value.toString(),row);
                    emit changed();
                    return true;
                case Length:
                    setLength(value.toString(),row);
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

    //=========================================================
    //=========================================================
    QString getIsSelected(const int i) const{
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        return (val_ptr->isSelected() ? "1" : "0");
    }
    Q_INVOKABLE bool b_isSelected(const int i) const{
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        return (val_ptr->isSelected());
    }
    const void setIsSelected(QVariant _new_val, const int i){
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        val_ptr->setIsSelected(_new_val.toBool());
       // emit selectChanged();
    }
    //=========================================================
    //=========================================================

    QString getTime(const int i) const{
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        return val_ptr->time();
    }
    const void setTime(const QString &_new_val, const int i){
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        val_ptr->setTime(_new_val);
    }
    //=========================================================
    //=========================================================
    Q_INVOKABLE const QString getLin(const int i) const{
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        return val_ptr->lin();
    }

    const void setLin(const QString &_new_val, const int i){
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        val_ptr->setLin(_new_val);
    }
    //=========================================================
    const QString getId(const int i) const{
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        return val_ptr->id();
    }
    const void setId(const QString &_new_val, const int i){
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        val_ptr->setId(_new_val);
    }
    //=========================================================
    const QString getLength(const int i) const{
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        return val_ptr->length();
    }
    const void setLength(const QString &_new_val, const int i){
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        val_ptr->setLength(_new_val);
    }
    //=========================================================
    const QString getData(const int i) const{
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        return val_ptr->data();
    }
    const void setData(const QString &_new_val, const int i){
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        val_ptr->setData(_new_val);
    }

    const QByteArray raw_data(const int i) const{
        QSharedPointer<LinBusItem> val_ptr = dataPtr(i);
        return val_ptr->getByteArray();
    }

    Q_INVOKABLE QVariant item( int i ) {
        if ( i < 0 || i >= count() ) return QVariant();
        auto obj = at( i ).data();
        QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );
        return QVariant::fromValue( obj );
    }

    //================================= Edit model ==================================
    void sortColumn(const int col, bool fromTopToBottom = true);
    void switchSortColumn(const int col);
    void deleteSelected();
    void deleteRange(int begin, int end);
    void setAllMsgsDirection(int id, int dir);
    void deductTimeStamp(uint32_t tmstmp);
    void deleteTimeStampRange(int start, int end);



    //================================= Print and debug ===============================
    void debug() const;

    //================================= Class service ==================================
    const QByteArray get_raw_data_for_cdc(int *start_pos, int msg_count, bool circular_mode) const;

    //============================= Class setters/getters ==============================
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

    // how to call bool data role from QML
    constexpr static const char BOOL_ROLE_NAME[] = "boolData";
};






class LinBusMonitorProperty: public Obj_List_Model<LinBusItemMonitor>{
    Q_OBJECT
    Q_PROPERTY( int length READ count NOTIFY changed )
    Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed)

public:
    explicit LinBusMonitorProperty(){
        m_monitorColumnNames << "LIN"  << "ID" << "Length" << "Data" << "Period" << "Count";
    };
    ~LinBusMonitorProperty(){};

    //=============================== Static preset =================================
    enum CollectionRole {
     //   BoolDataRole = (Qt::UserRole + 1)
    };

    enum {
        LIN ,
        ID,
        Length ,
        Data ,
        Period ,
        Count,
        ColumnCount
    };

    QHash<int, QByteArray> roleNames() const override {
        auto roles = QAbstractListModel::roleNames();
        roles[ItemDataRole] = ITEM_ROLE_NAME;
        return roles;
    }
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;


    //=================================== Init =========================================
    void addItem(const QByteArray &_lin_msg_data, bool validate = false);
    void addItem(const QByteArray &_lin_msg_data, const ParseFilter &filter, bool validate = false);
    void reset();

    //================================ Data access =====================================
    QVariant data( const QModelIndex& index, int role ) const override {
        if (!index.isValid())
            return QVariant();
        auto row = index.row();
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

    //================================= Edit model =====================================
    //================================= Print and debug ================================
    //================================= Class service ==================================
    //============================= Class setters/getters ==============================
    bool containsId(int id) const;

Q_SIGNALS:
    void changed();
    // void selectChanged();

public slots:

protected:
    void emitChanged() override{
        emit changed();}

    void init (){};

    QRegularExpression regex;
    QStringList m_monitorColumnNames; // << "CAN"  << "ID" << "Length" << "Data" << "Period" << "Count";
    QHash<int, int> m_idSet;

};





#endif // LINBUSDATAPROPERTY_H
