#ifndef LINBUSITEM_H
#define LINBUSITEM_H

/***********************************************************************
 *
 *
 *
 ************************************************************************/

#include "../../app_settings.h"
#include <QDebug>
#include <stdio.h>


//============== Exported from 'C' lin.h ======================

#define LIN_ITEM_DEFAULT      (uint8_t)0x00
#define LIN_ITEM_ROLE_MS_DATA (uint8_t)0x01
#define LIN_ITEM_ROLE_MS_RQST (uint8_t)0x02
#define LIN_ITEM_ROLE_SL_DATA (uint8_t)0x03
#define LIN_ITEM_ROLE_MS_IN   (uint8_t)0x04
#define LIN_ITEM_ROLE_SL_IN   (uint8_t)0x05

typedef struct LinItem {
    uint8_t role;
    uint8_t length;
    uint8_t id;
    uint8_t data[9];
} LinItem;

typedef union LinItemRaw {
    LinItem item;
    uint8_t data[12];
} LinItemRaw;

#define LIN_MSG_INFO_SZ        20

typedef struct lin_message_info{
    uint8_t start_char; // '@'
    uint8_t unused;
    uint16_t msec;
    uint32_t seconds;
    LinItemRaw lin_msg;
} lin_message_info; //creating new type

typedef union lin_message_info_raw{
    lin_message_info info;
    uint8_t raw_msg_data[LIN_MSG_INFO_SZ];
}lin_message_info_raw;

/*****************************************************************************************/
/***********                                                                   ***********/
/***********                           LIN bus Item                            ***********/
/***********                                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class LinBusItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString Time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString LIN READ lin WRITE setLin NOTIFY linChanged)
    Q_PROPERTY(QString ID READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString Length READ length WRITE setLength NOTIFY lengthChanged)
    Q_PROPERTY(QString Data READ data WRITE setData NOTIFY dataChanged)

public:
    explicit LinBusItem(QObject *parent = nullptr, QByteArray data = {}, bool isSelected = false) : QObject(parent){
        m_lin_msg = byteArrayToLinMsg(data);
        setIsSelected(isSelected);
        initTime();
        initLin();
        initId();
        initLength();
        initData();
    };

    ~LinBusItem( ){
    }

    //==================================== init =====================================
    static lin_message_info_raw byteArrayToLinMsg(const QByteArray data){
        lin_message_info_raw m_can_msg;
        memcpy(&m_can_msg.raw_msg_data, data.data(), LIN_MSG_INFO_SZ);
        return m_can_msg;
    }

    //=============================== Operators =====================================
    LinBusItem& operator=(const LinBusItem& t){
        lin_message_info_raw* oldCanMsg = &this->m_lin_msg;
        this->m_lin_msg = *oldCanMsg;
        bool oldSel = this->m_isSelected;
        this->m_isSelected = oldSel;
        return *this;
    }

    //================================= Sort ========================================
    static bool sortBySelection(const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b){
        if(a->isSelected() == true && b->isSelected() == false) return true;
        else return false;
    }

    static bool sortBySelectionReverse(const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b){
        if(a->isSelected() == false && b->isSelected() == true) return true;
        else return false;
    }

    //======================= Bool and Int Setters/Getters ===========================
    const int int_time() const;
    const int int_length() const;
    void setIntTime(int _time);
    const int intLin() const;
    void setIntLin(int dir);
    const int int_id() const;
    //bool bool_ext_ide() const; // is a msg id extended?

    bool isSelected() const;
    void setIsSelected(bool newIsSelected);

    const QByteArray getByteArray() const;

    static const QByteArray makeInvalidByteArray(){
        const QByteArray byteArray(sizeof(m_lin_msg), char(0xFF));
        return byteArray;
    }
    //=============================== Debug and print ================================
    void print() const;

    //========================== Class Setters/Getters ===============================
    const QString &time() const;
    void setTime(const QString &newTime);
    void initTime();
    const QString &lin() const;
    void setLin(const QString &newLin);
    void initLin();
    const QString &id() const;
    void setId(const QString &newId);
    void initId();
    const QString &length() const;
    void setLength(const QString &newLength);
    void initLength();
    const QString &data() const;
    void setData(const QString &newData);
    void initData();

signals:
    void isSelectedChanged();

    void timeChanged();
    void linChanged();
    void idChanged();
    void lengthChanged();
    void dataChanged();

protected:
    bool m_isSelected;
    QString m_time;
    QString m_lin; // CAN1 or CAN2
    QString m_id;
    QString m_length;
    QString m_data;

    //QString m_ide;
    lin_message_info_raw m_lin_msg;
};



/*****************************************************************************************/
/***********                                                                   ***********/
/***********                        LinBusItemMonitor                          ***********/
/***********                                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class LinBusItemMonitor: public QObject{
    Q_OBJECT

public:
    explicit LinBusItemMonitor(QObject *parent = nullptr, QByteArray data = {} ) : QObject(parent){
        set_lin_msg_data(LinBusItem::byteArrayToLinMsg(data));

    };
    ~LinBusItemMonitor( ){}
    //==================================== init =====================================
    void set_lin_msg_data(const lin_message_info_raw &_lin_msg_data);
    void initQStringValues();

    //=============================== Operators =====================================

    //================================= Sort ========================================

    //=============================== Debug and print ================================


    //======================= Bool and Int Setters/Getters ===========================
    const int int_id() const;
    const int int_time() const;


    //========================== Class Setters/Getters ===============================
    const QString &lin() const;
    void setLin(const QString &newLin);
    const QString &id() const;
    void setId(const QString &newId);
    const QString &length() const;
    void setLength(const QString &newLength);
    const QString &count() const;
    void setCount(const QString &newCount);
    const QString &period() const;
    void setPeriod(const QString &newPeriod);
    const QString &data() const;
    void setData(const QString &newData);

signals:
    void changed();

    void linChanged();
    void idChanged();
    void lengthChanged();
    void countChanged();
    void periodChanged();
    void dataChanged();

protected:
    QString m_lin;
    QString m_id;
    QString m_length;
    QString m_count;
    QString m_period;
    QString m_data;

    int m_iId;
    int m_ilast_time = 0;
    int m_icount = 0;
    int m_iperiod;

    lin_message_info_raw m_last_lin_msg;
private:
    Q_PROPERTY(QString lin READ lin WRITE setLin NOTIFY linChanged)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString length READ length WRITE setLength NOTIFY lengthChanged)
    Q_PROPERTY(QString count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString period READ period WRITE setPeriod NOTIFY periodChanged)
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)
};

#endif // LINBUSITEM_H
