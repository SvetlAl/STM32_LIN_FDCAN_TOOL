#ifndef FDCAN_CANBUSITEM_H
#define FDCAN_CANBUSITEM_H

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
#include "FDCAN_Macros.h"

/*****************************************************************************************/
/***********                                                                   ***********/
/***********                         FDCAN bus Item                            ***********/
/***********                                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class FDCAN_CanBusItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString Time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString CAN READ can WRITE setCan NOTIFY canChanged)
    Q_PROPERTY(QString ID READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString DLC READ dlc WRITE setDlc NOTIFY dlcChanged)
    Q_PROPERTY(int ByteCount READ ByteCount NOTIFY byteCountChanged)

    Q_PROPERTY(QString ESIflag READ ESIflag WRITE setESIflag NOTIFY ESIflagChanged)
    Q_PROPERTY(QString XTDflag READ XTDflag WRITE setXTDflag NOTIFY XTDflagChanged)
    Q_PROPERTY(QString FDFflag READ FDFflag WRITE setFDFflag NOTIFY FDFflagChanged)
    Q_PROPERTY(QString BRSflag READ BRSflag WRITE setBRSflag NOTIFY BRSflagChanged)

    Q_PROPERTY(QString Data READ data WRITE setData NOTIFY dataChanged)

    Q_PROPERTY(bool isSelected READ isSelected WRITE setIsSelected NOTIFY isSelectedChanged)
    Q_PROPERTY(QString Color READ color NOTIFY colorChanged)

public:
    explicit FDCAN_CanBusItem(QObject *parent = nullptr, QByteArray hdr_data = {}, QByteArray data = {}, bool isSelected = false) : QObject(parent){
        m_fdcan_hdr  = byteArrayToFDCanHdr(hdr_data);
        m_data_array = data;

        setIsSelected(isSelected);
        initTime();
        initCan();
        initId();
        initDlc();
        initEsi();
        initXtd();
        initFdf();
        initBrs();
        initData();
    };

    ~FDCAN_CanBusItem( ){
    }
    static inline const QString data_color_yl = "#FFCC22";
    static inline const QString data_color_wh = "#FFFFFF";
    static inline const QString data_color_df = "#CCCCCC";

    //==================================== init =====================================
    static fdcan_message_info_raw byteArrayToFDCanHdr(const QByteArray data){
        fdcan_message_info_raw _m_can_hdr;
        memcpy(&_m_can_hdr.raw_msg_data, data.data(), sizeof(fdcan_message_info));
        return _m_can_hdr;
    }

    //=============================== Operators =====================================
    FDCAN_CanBusItem& operator=(const FDCAN_CanBusItem& t){
        fdcan_message_info_raw* oldCanMsgHdr = &this->m_fdcan_hdr;
        this->m_fdcan_hdr = *oldCanMsgHdr;

        QByteArray* oldCanData = &this->m_data_array;
        this->m_data_array = *oldCanData;

        bool oldSel = this->m_isSelected;
        this->m_isSelected = oldSel;

        return *this;
    }

    //================================= Sort ========================================
    static bool sortBySelection(const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b){
        if(a->isSelected() == true && b->isSelected() == false) return true;
        else return false;
    }

    static bool sortBySelectionReverse(const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b){
        if(a->isSelected() == false && b->isSelected() == true) return true;
        else return false;
    }

    //======================= Bool and Int Setters/Getters ===========================
    bool isSelected() const;
    void setIsSelected(bool newIsSelected);

    const int int_time() const;
    void setIntTime(int _time);

    const int intCan() const;
    void setIntCan(int dir);

    const int int_dlc() const;  
    const int int_id() const;


    const QByteArray getByteArray() const;

    static const QByteArray makeInvalidByteArray(){
        const QByteArray byteArray = QByteArray(sizeof(fdcan_message_info_raw), char(0xFF));
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
    int ByteCount() const;

    const QString &data() const;
    void setData(const QString &newData);
    void initData();

    //================ FD only ================
    QString ESIflag() const;
    void setESIflag(const QString& newVal);
    void initEsi();

    QString XTDflag() const;
    void setXTDflag(const QString& newVal);
    void initXtd();

    QString FDFflag() const;
    void setFDFflag(const QString& newVal);
    void initFdf();

    QString BRSflag() const;
    void setBRSflag(const QString& newVal);
    void initBrs();


    const QByteArray &msg_data() const;
    void set_msg_data(const QByteArray &newData_array);

    QString color() const;

signals:
    void isSelectedChanged();
    void byteCountChanged();

    void timeChanged();
    void canChanged();
    void idChanged();
    void dlcChanged();
    void dataChanged();

    void ESIflagChanged();
    void XTDflagChanged();
    void FDFflagChanged();
    void BRSflagChanged();

    void colorChanged();


protected:
    bool m_isSelected;
    QString m_time;
    QString m_can; // CAN1 or CAN2
    QString m_dlc;
    QString m_id;
    QString m_data;

    QString m_xtd_flag;
    QString m_fdf_flag;
    QString m_esi_flag;
    QString m_brs_flag;

    fdcan_message_info_raw m_fdcan_hdr;
    QByteArray m_data_array;
};



/*****************************************************************************************/
/***********                                                                   ***********/
/***********                   FDCAN_CanBusItemMonitor                         ***********/
/***********                                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class FDCAN_CanBusItemMonitor: public QObject{
    Q_OBJECT

public:
    explicit FDCAN_CanBusItemMonitor(QObject *parent = nullptr, QByteArray hdr = {}, QByteArray data = {} ) : QObject(parent){
        set_fdcan_msg_hdr_and_data(FDCAN_CanBusItem::byteArrayToFDCanHdr(hdr), data);
    };
    ~FDCAN_CanBusItemMonitor( ){}

    //==================================== init =====================================
    void set_fdcan_msg_hdr_and_data(const fdcan_message_info_raw &_can_msg_hdr, const QByteArray _data);
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

    const QString &flags() const;
    void setFlags(const QString &newFlags);

    const QByteArray &msg_data() const;
    void set_msg_data(const QByteArray &newData_array);
    int ByteCount() const;

signals:
    void changed();

    void canChanged();
    void idChanged();
    void dlcChanged();
    void countChanged();
    void periodChanged();
    void dataChanged();

    void flagsChanged();
    void byteCountChanged();

protected:
    QString m_can;
    QString m_id;
    QString m_dlc;
    QString m_count;
    QString m_period;
    QString m_data;

    QString m_flags;

    int m_iId;
    int m_ilast_time = 0;
    int m_icount = 0;
    int m_iperiod;

    fdcan_message_info_raw m_last_fdcan_hdr;
    QByteArray m_last_data_array;

private:
    Q_PROPERTY(QString can READ can WRITE setCan NOTIFY canChanged)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString dlc READ dlc WRITE setDlc NOTIFY dlcChanged)
    Q_PROPERTY(QString count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString period READ period WRITE setPeriod NOTIFY periodChanged)
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)

    Q_PROPERTY(QString flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(int ByteCount READ ByteCount NOTIFY byteCountChanged)
};

#endif // FDCAN_CANBUSITEM_H
