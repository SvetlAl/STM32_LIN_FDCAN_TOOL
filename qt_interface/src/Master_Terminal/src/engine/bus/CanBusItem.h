#ifndef CANBUSITEM_H
#define CANBUSITEM_H

/***********************************************************************
 * BusManager <== CanBusTraceProperty     <==  CanBusItem
 *            <== CanBusMonitorProperty   <==  CanBusItemMonitor
 *
 * Can Bus Item describes a CAN bus message for a trace model
 *
 * Can Bus Item Monitor describes a CAN bus message for a monitor model
 *
 *
 *
 ************************************************************************/

#include "../../app_settings.h"
#include <QDebug>
#include <stdio.h>


//============== Exported from 'C' cah.h ======================
#define STD_ID	0
#define EXT_ID	1

#define STD_CAN_ID(msg) (uint32_t)((msg.id.std_id.id_highbyte << 8) | msg.id.std_id.id_lowbyte)
#define EXT_CAN_ID(msg) (uint32_t)(msg.id.ext_id)
#define CAN_ID(msg) (uint32_t)(msg.ide == EXT_ID ? EXT_CAN_ID(msg) : STD_CAN_ID(msg))


typedef struct std_can_id{
    uint8_t id_highbyte;	// First number of an id 					(BXX)
    uint8_t id_lowbyte; 	// Second, third numbers of an id (XBB)
    uint16_t unused;
}std_can_id;

typedef union can_id{
    std_can_id std_id;
    uint32_t ext_id;
}can_id;

// Structure of a  CAN message
typedef struct can_message{
    can_id id;
    uint16_t ide;
    uint16_t dlc;
    uint8_t data[8];
} can_message;

/* Used for serial data trasmission */
typedef struct can_message_info{
    uint8_t start_char; // '@'
    uint8_t can_number;
    uint16_t msec;
    uint32_t seconds;
    can_message msg;
} can_message_info;

typedef union can_message_info_raw{
    can_message_info info;
    uint8_t raw_msg_data[24];
}can_message_info_raw;

/*****************************************************************************************/
/***********                                                                   ***********/
/***********                           CAN bus Item                            ***********/
/***********                                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class CanBusItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString Time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString CAN READ can WRITE setCan NOTIFY canChanged)
    Q_PROPERTY(QString IDE READ ide WRITE setIde NOTIFY ideChanged)
    Q_PROPERTY(QString ID READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString DLC READ dlc WRITE setDlc NOTIFY dlcChanged)
    Q_PROPERTY(QString Data READ data WRITE setData NOTIFY dataChanged)

    Q_PROPERTY(bool isSelected READ isSelected WRITE setIsSelected NOTIFY isSelectedChanged)

public:
    explicit CanBusItem(QObject *parent = nullptr, QByteArray data = {}, bool isSelected = false) : QObject(parent){
        m_can_msg = byteArrayToCanMsg(data);
        setIsSelected(isSelected);
        initTime();
        initCan();
        initId();
        initDlc();
        initData();
        initIde();
    };

    ~CanBusItem( ){
    }

    //==================================== init =====================================
    static can_message_info_raw byteArrayToCanMsg(const QByteArray data){
        can_message_info_raw m_can_msg;
        memcpy(&m_can_msg.raw_msg_data, data.data(), sizeof(can_message_info));
        return m_can_msg;
    }

    //=============================== Operators =====================================
    CanBusItem& operator=(const CanBusItem& t){
        can_message_info_raw* oldCanMsg = &this->m_can_msg;
        this->m_can_msg = *oldCanMsg;
        bool oldSel = this->m_isSelected;
        this->m_isSelected = oldSel;
        return *this;
    }

    //================================= Sort ========================================
    static bool sortBySelection(const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b){
        if(a->isSelected() == true && b->isSelected() == false) return true;
        else return false;
    }

    static bool sortBySelectionReverse(const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b){
        if(a->isSelected() == false && b->isSelected() == true) return true;
        else return false;
    }

    //======================= Bool and Int Setters/Getters ===========================
    const int int_time() const;
    const int int_dlc() const;
    void setIntTime(int _time);
    const int intCan() const;
    void setIntCan(int dir);
    const int int_id() const;
    bool bool_ext_ide() const; // is a msg id extended?

    bool isSelected() const;
    void setIsSelected(bool newIsSelected);

    const QByteArray getByteArray() const;

    static const QByteArray makeInvalidByteArray(){
        const QByteArray byteArray(sizeof(can_message_info_raw), char(0xFF));
        return byteArray;
    }
    //=============================== Debug and print ================================
    void print() const;

    //========================== Class Setters/Getters ===============================
    const QString &time() const;
    void setTime(const QString &newTime);
    void initTime();
    const QString &can() const;
    void setCan(const QString &newCan);
    void initCan();
    const QString &id() const;
    void setId(const QString &newId);
    void initId();
    const QString &dlc() const;
    void setDlc(const QString &newDlc);
    void initDlc();
    const QString &data() const;
    void setData(const QString &newData);
    void initData();
    const QString &ide() const;
    void setIde(const QString &newIde);
    void initIde();

signals:
    void isSelectedChanged();

    void timeChanged();
    void canChanged();
    void idChanged();
    void dlcChanged();
    void dataChanged();

    void ideChanged();

protected:
    bool m_isSelected;
    QString m_time;
    QString m_can; // CAN1 or CAN2
    QString m_id;
    QString m_dlc;
    QString m_data;

    QString m_ide;
    can_message_info_raw m_can_msg;
};



/*****************************************************************************************/
/***********                                                                   ***********/
/***********                        CanBusItemMonitor                          ***********/
/***********                                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class CanBusItemMonitor: public QObject{
    Q_OBJECT

public:
    explicit CanBusItemMonitor(QObject *parent = nullptr, QByteArray data = {} ) : QObject(parent){
        set_can_msg_data(CanBusItem::byteArrayToCanMsg(data));

    };
    ~CanBusItemMonitor( ){}
    //==================================== init =====================================
    void set_can_msg_data(const can_message_info_raw &_can_msg_data);
    void initQStringValues();

    //=============================== Operators =====================================

    //================================= Sort ========================================

    //=============================== Debug and print ================================


    //======================= Bool and Int Setters/Getters ===========================
    const int int_id() const;
    const int int_time() const;


    //========================== Class Setters/Getters ===============================
    const QString &can() const;
    void setCan(const QString &newCan);
    const QString &id() const;
    void setId(const QString &newId);
    const QString &dlc() const;
    void setDlc(const QString &newDlc);
    const QString &count() const;
    void setCount(const QString &newCount);
    const QString &period() const;
    void setPeriod(const QString &newPeriod);
    const QString &data() const;
    void setData(const QString &newData);

signals:
    void changed();

    void canChanged();
    void idChanged();
    void dlcChanged();
    void countChanged();
    void periodChanged();
    void dataChanged();

protected:
    QString m_can;
    QString m_id;
    QString m_dlc;
    QString m_count;
    QString m_period;
    QString m_data;

    int m_iId;
    int m_ilast_time = 0;
    int m_icount = 0;
    int m_iperiod;

    can_message_info_raw m_last_can_msg;
private:
    Q_PROPERTY(QString can READ can WRITE setCan NOTIFY canChanged)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString dlc READ dlc WRITE setDlc NOTIFY dlcChanged)
    Q_PROPERTY(QString count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString period READ period WRITE setPeriod NOTIFY periodChanged)
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)
};

#endif // CANBUSITEM_H
