#ifndef FDCAN_INJECTION_MESSAGE_H
#define FDCAN_INJECTION_MESSAGE_H

/***********************************************************************
 *
 *
 *
 *
 ************************************************************************/
#include <QDebug>



class FDCAN_injection_message: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString data_00 READ data_00 WRITE set_data_00 NOTIFY changed)
    Q_PROPERTY(QString data_01 READ data_01 WRITE set_data_01 NOTIFY changed)
    Q_PROPERTY(QString data_02 READ data_02 WRITE set_data_02 NOTIFY changed)
    Q_PROPERTY(QString data_03 READ data_03 WRITE set_data_03 NOTIFY changed)
    Q_PROPERTY(QString data_04 READ data_04 WRITE set_data_04 NOTIFY changed)
    Q_PROPERTY(QString data_05 READ data_05 WRITE set_data_05 NOTIFY changed)
    Q_PROPERTY(QString data_06 READ data_06 WRITE set_data_06 NOTIFY changed)
    Q_PROPERTY(QString data_07 READ data_07 WRITE set_data_07 NOTIFY changed)

    Q_PROPERTY(QString data_08 READ data_08 WRITE set_data_08 NOTIFY changed)
    Q_PROPERTY(QString data_09 READ data_09 WRITE set_data_09 NOTIFY changed)
    Q_PROPERTY(QString data_10 READ data_10 WRITE set_data_10 NOTIFY changed)
    Q_PROPERTY(QString data_11 READ data_11 WRITE set_data_11 NOTIFY changed)
    Q_PROPERTY(QString data_12 READ data_12 WRITE set_data_12 NOTIFY changed)
    Q_PROPERTY(QString data_13 READ data_13 WRITE set_data_13 NOTIFY changed)
    Q_PROPERTY(QString data_14 READ data_14 WRITE set_data_14 NOTIFY changed)
    Q_PROPERTY(QString data_15 READ data_15 WRITE set_data_15 NOTIFY changed)

    Q_PROPERTY(QString data_16 READ data_16 WRITE set_data_16 NOTIFY changed)
    Q_PROPERTY(QString data_17 READ data_17 WRITE set_data_17 NOTIFY changed)
    Q_PROPERTY(QString data_18 READ data_18 WRITE set_data_18 NOTIFY changed)
    Q_PROPERTY(QString data_19 READ data_19 WRITE set_data_19 NOTIFY changed)
    Q_PROPERTY(QString data_20 READ data_20 WRITE set_data_20 NOTIFY changed)
    Q_PROPERTY(QString data_21 READ data_21 WRITE set_data_21 NOTIFY changed)
    Q_PROPERTY(QString data_22 READ data_22 WRITE set_data_22 NOTIFY changed)
    Q_PROPERTY(QString data_23 READ data_23 WRITE set_data_23 NOTIFY changed)

    Q_PROPERTY(QString data_24 READ data_24 WRITE set_data_24 NOTIFY changed)
    Q_PROPERTY(QString data_25 READ data_25 WRITE set_data_25 NOTIFY changed)
    Q_PROPERTY(QString data_26 READ data_26 WRITE set_data_26 NOTIFY changed)
    Q_PROPERTY(QString data_27 READ data_27 WRITE set_data_27 NOTIFY changed)
    Q_PROPERTY(QString data_28 READ data_28 WRITE set_data_28 NOTIFY changed)
    Q_PROPERTY(QString data_29 READ data_29 WRITE set_data_29 NOTIFY changed)
    Q_PROPERTY(QString data_30 READ data_30 WRITE set_data_30 NOTIFY changed)
    Q_PROPERTY(QString data_31 READ data_31 WRITE set_data_31 NOTIFY changed)

    Q_PROPERTY(QString data_32 READ data_32 WRITE set_data_32 NOTIFY changed)
    Q_PROPERTY(QString data_33 READ data_33 WRITE set_data_33 NOTIFY changed)
    Q_PROPERTY(QString data_34 READ data_34 WRITE set_data_34 NOTIFY changed)
    Q_PROPERTY(QString data_35 READ data_35 WRITE set_data_35 NOTIFY changed)
    Q_PROPERTY(QString data_36 READ data_36 WRITE set_data_36 NOTIFY changed)
    Q_PROPERTY(QString data_37 READ data_37 WRITE set_data_37 NOTIFY changed)
    Q_PROPERTY(QString data_38 READ data_38 WRITE set_data_38 NOTIFY changed)
    Q_PROPERTY(QString data_39 READ data_39 WRITE set_data_39 NOTIFY changed)

    Q_PROPERTY(QString data_40 READ data_40 WRITE set_data_40 NOTIFY changed)
    Q_PROPERTY(QString data_41 READ data_41 WRITE set_data_41 NOTIFY changed)
    Q_PROPERTY(QString data_42 READ data_42 WRITE set_data_42 NOTIFY changed)
    Q_PROPERTY(QString data_43 READ data_43 WRITE set_data_43 NOTIFY changed)
    Q_PROPERTY(QString data_44 READ data_44 WRITE set_data_44 NOTIFY changed)
    Q_PROPERTY(QString data_45 READ data_45 WRITE set_data_45 NOTIFY changed)
    Q_PROPERTY(QString data_46 READ data_46 WRITE set_data_46 NOTIFY changed)
    Q_PROPERTY(QString data_47 READ data_47 WRITE set_data_47 NOTIFY changed)

    Q_PROPERTY(QString data_48 READ data_48 WRITE set_data_48 NOTIFY changed)
    Q_PROPERTY(QString data_49 READ data_49 WRITE set_data_49 NOTIFY changed)
    Q_PROPERTY(QString data_50 READ data_50 WRITE set_data_50 NOTIFY changed)
    Q_PROPERTY(QString data_51 READ data_51 WRITE set_data_51 NOTIFY changed)
    Q_PROPERTY(QString data_52 READ data_52 WRITE set_data_52 NOTIFY changed)
    Q_PROPERTY(QString data_53 READ data_53 WRITE set_data_53 NOTIFY changed)
    Q_PROPERTY(QString data_54 READ data_54 WRITE set_data_54 NOTIFY changed)
    Q_PROPERTY(QString data_55 READ data_55 WRITE set_data_55 NOTIFY changed)

    Q_PROPERTY(QString data_56 READ data_56 WRITE set_data_56 NOTIFY changed)
    Q_PROPERTY(QString data_57 READ data_57 WRITE set_data_57 NOTIFY changed)
    Q_PROPERTY(QString data_58 READ data_58 WRITE set_data_58 NOTIFY changed)
    Q_PROPERTY(QString data_59 READ data_59 WRITE set_data_59 NOTIFY changed)
    Q_PROPERTY(QString data_60 READ data_60 WRITE set_data_60 NOTIFY changed)
    Q_PROPERTY(QString data_61 READ data_61 WRITE set_data_61 NOTIFY changed)
    Q_PROPERTY(QString data_62 READ data_62 WRITE set_data_62 NOTIFY changed)
    Q_PROPERTY(QString data_63 READ data_63 WRITE set_data_63 NOTIFY changed)

    Q_PROPERTY(bool fdf_flag READ fdf_flag WRITE set_fdf_flag NOTIFY changed)
    Q_PROPERTY(bool brs_flag READ brs_flag WRITE set_brs_flag NOTIFY changed)
    Q_PROPERTY(bool xtd_flag READ xtd_flag WRITE set_xtd_flag NOTIFY changed)

    Q_PROPERTY(QString id READ id WRITE set_id NOTIFY changed)

    Q_PROPERTY(int dlc READ dlc WRITE set_dlc NOTIFY changed)

public:
    explicit FDCAN_injection_message(QObject *parent = nullptr): QObject(parent){
        m_data.resize(64);
        m_id = "0x1AC";
        m_dlc = 8;
        m_fdf_flag = false;
        m_brs_flag = false;
        m_xtd_flag = false;
        m_data[0] = "0x12";
        m_data[1] = "0x23";
        m_data[2] = "0x34";
        m_data[3] = "0x45";

        m_data[4] = "0x56";
        m_data[5] = "0x67";
        m_data[6] = "0x78";
        m_data[7] = "0x89";
        for(uint8_t i = 8; i < 64; i++){
            m_data[i] = "0xAA";
        }

    };
    ~FDCAN_injection_message(){ }

    //==================================== init =====================================


    //========================== Class setters/getters ===============================
    const QString &data_00() const{return m_data.at(0);}
    const QString &data_01() const{return m_data.at(1);}
    const QString &data_02() const{return m_data.at(2);}
    const QString &data_03() const{return m_data.at(3);}
    const QString &data_04() const{return m_data.at(4);}
    const QString &data_05() const{return m_data.at(5);}
    const QString &data_06() const{return m_data.at(6);}
    const QString &data_07() const{return m_data.at(7);}
    const QString &data_08() const{return m_data.at(8);}
    const QString &data_09() const{return m_data.at(9);}
    const QString &data_10() const{return m_data.at(10);}
    const QString &data_11() const{return m_data.at(11);}
    const QString &data_12() const{return m_data.at(12);}
    const QString &data_13() const{return m_data.at(13);}
    const QString &data_14() const{return m_data.at(14);}
    const QString &data_15() const{return m_data.at(15);}
    const QString &data_16() const{return m_data.at(16);}
    const QString &data_17() const{return m_data.at(17);}
    const QString &data_18() const{return m_data.at(18);}
    const QString &data_19() const{return m_data.at(19);}
    const QString &data_20() const{return m_data.at(20);}
    const QString &data_21() const{return m_data.at(21);}
    const QString &data_22() const{return m_data.at(22);}
    const QString &data_23() const{return m_data.at(23);}
    const QString &data_24() const{return m_data.at(24);}
    const QString &data_25() const{return m_data.at(25);}
    const QString &data_26() const{return m_data.at(26);}
    const QString &data_27() const{return m_data.at(27);}
    const QString &data_28() const{return m_data.at(28);}
    const QString &data_29() const{return m_data.at(29);}
    const QString &data_30() const{return m_data.at(30);}
    const QString &data_31() const{return m_data.at(31);}

    const QString &data_32() const{return m_data.at(32);}
    const QString &data_33() const{return m_data.at(33);}
    const QString &data_34() const{return m_data.at(34);}
    const QString &data_35() const{return m_data.at(35);}
    const QString &data_36() const{return m_data.at(36);}
    const QString &data_37() const{return m_data.at(37);}
    const QString &data_38() const{return m_data.at(38);}
    const QString &data_39() const{return m_data.at(39);}
    const QString &data_40() const{return m_data.at(40);}
    const QString &data_41() const{return m_data.at(41);}
    const QString &data_42() const{return m_data.at(42);}
    const QString &data_43() const{return m_data.at(43);}
    const QString &data_44() const{return m_data.at(44);}
    const QString &data_45() const{return m_data.at(45);}
    const QString &data_46() const{return m_data.at(46);}
    const QString &data_47() const{return m_data.at(47);}
    const QString &data_48() const{return m_data.at(48);}
    const QString &data_49() const{return m_data.at(49);}
    const QString &data_50() const{return m_data.at(50);}
    const QString &data_51() const{return m_data.at(51);}
    const QString &data_52() const{return m_data.at(52);}
    const QString &data_53() const{return m_data.at(53);}
    const QString &data_54() const{return m_data.at(54);}
    const QString &data_55() const{return m_data.at(55);}
    const QString &data_56() const{return m_data.at(56);}
    const QString &data_57() const{return m_data.at(57);}
    const QString &data_58() const{return m_data.at(58);}
    const QString &data_59() const{return m_data.at(59);}
    const QString &data_60() const{return m_data.at(60);}
    const QString &data_61() const{return m_data.at(61);}
    const QString &data_62() const{return m_data.at(62);}
    const QString &data_63() const{return m_data.at(63);}


    void set_data_00(const QString &val){ m_data[0] = val; emit changed();}
    void set_data_01(const QString &val){ m_data[1] = val; emit changed();}
    void set_data_02(const QString &val){ m_data[2] = val; emit changed();}
    void set_data_03(const QString &val){ m_data[3] = val; emit changed();}
    void set_data_04(const QString &val){ m_data[4] = val; emit changed();}
    void set_data_05(const QString &val){ m_data[5] = val; emit changed();}
    void set_data_06(const QString &val){ m_data[6] = val; emit changed();}
    void set_data_07(const QString &val){ m_data[7] = val; emit changed();}
    void set_data_08(const QString &val){ m_data[8] = val; emit changed();}
    void set_data_09(const QString &val){ m_data[9] = val; emit changed();}

    void set_data_10(const QString &val){ m_data[10] = val; emit changed();}
    void set_data_11(const QString &val){ m_data[11] = val; emit changed();}
    void set_data_12(const QString &val){ m_data[12] = val; emit changed();}
    void set_data_13(const QString &val){ m_data[13] = val; emit changed();}
    void set_data_14(const QString &val){ m_data[14] = val; emit changed();}
    void set_data_15(const QString &val){ m_data[15] = val; emit changed();}
    void set_data_16(const QString &val){ m_data[16] = val; emit changed();}
    void set_data_17(const QString &val){ m_data[17] = val; emit changed();}
    void set_data_18(const QString &val){ m_data[18] = val; emit changed();}
    void set_data_19(const QString &val){ m_data[19] = val; emit changed();}

    void set_data_20(const QString &val){ m_data[20] = val; emit changed();}
    void set_data_21(const QString &val){ m_data[21] = val; emit changed();}
    void set_data_22(const QString &val){ m_data[22] = val; emit changed();}
    void set_data_23(const QString &val){ m_data[23] = val; emit changed();}
    void set_data_24(const QString &val){ m_data[24] = val; emit changed();}
    void set_data_25(const QString &val){ m_data[25] = val; emit changed();}
    void set_data_26(const QString &val){ m_data[26] = val; emit changed();}
    void set_data_27(const QString &val){ m_data[27] = val; emit changed();}
    void set_data_28(const QString &val){ m_data[28] = val; emit changed();}
    void set_data_29(const QString &val){ m_data[29] = val; emit changed();}


    void set_data_30(const QString &val){ m_data[30] = val; emit changed();}
    void set_data_31(const QString &val){ m_data[31] = val; emit changed();}
    void set_data_32(const QString &val){ m_data[32] = val; emit changed();}
    void set_data_33(const QString &val){ m_data[33] = val; emit changed();}
    void set_data_34(const QString &val){ m_data[34] = val; emit changed();}
    void set_data_35(const QString &val){ m_data[35] = val; emit changed();}
    void set_data_36(const QString &val){ m_data[36] = val; emit changed();}
    void set_data_37(const QString &val){ m_data[37] = val; emit changed();}
    void set_data_38(const QString &val){ m_data[38] = val; emit changed();}
    void set_data_39(const QString &val){ m_data[39] = val; emit changed();}

    void set_data_40(const QString &val){ m_data[40] = val; emit changed();}
    void set_data_41(const QString &val){ m_data[41] = val; emit changed();}
    void set_data_42(const QString &val){ m_data[42] = val; emit changed();}
    void set_data_43(const QString &val){ m_data[43] = val; emit changed();}
    void set_data_44(const QString &val){ m_data[44] = val; emit changed();}
    void set_data_45(const QString &val){ m_data[45] = val; emit changed();}
    void set_data_46(const QString &val){ m_data[46] = val; emit changed();}
    void set_data_47(const QString &val){ m_data[47] = val; emit changed();}
    void set_data_48(const QString &val){ m_data[48] = val; emit changed();}
    void set_data_49(const QString &val){ m_data[49] = val; emit changed();}

    void set_data_50(const QString &val){ m_data[50] = val; emit changed();}
    void set_data_51(const QString &val){ m_data[51] = val; emit changed();}
    void set_data_52(const QString &val){ m_data[52] = val; emit changed();}
    void set_data_53(const QString &val){ m_data[53] = val; emit changed();}
    void set_data_54(const QString &val){ m_data[54] = val; emit changed();}
    void set_data_55(const QString &val){ m_data[55] = val; emit changed();}
    void set_data_56(const QString &val){ m_data[56] = val; emit changed();}
    void set_data_57(const QString &val){ m_data[57] = val; emit changed();}
    void set_data_58(const QString &val){ m_data[58] = val; emit changed();}
    void set_data_59(const QString &val){ m_data[59] = val; emit changed();}

    void set_data_60(const QString &val){ m_data[60] = val; emit changed();}
    void set_data_61(const QString &val){ m_data[61] = val; emit changed();}
    void set_data_62(const QString &val){ m_data[62] = val; emit changed();}
    void set_data_63(const QString &val){ m_data[63] = val; emit changed();}

    bool fdf_flag() const{return m_fdf_flag;}
    bool brs_flag() const{return m_brs_flag;}
    bool xtd_flag() const{return m_xtd_flag;}

    void set_fdf_flag(bool val){m_fdf_flag = val; emit changed();}
    void set_brs_flag(bool val){m_brs_flag = val; emit changed();}
    void set_xtd_flag(bool val){m_xtd_flag = val; emit changed();}

    const QString &id() const{return m_id;}
    void set_id(const QString &val){ m_id = val; emit changed();}

    int dlc() const{return m_dlc;}
    void set_dlc(const int val){ m_dlc = val; emit changed();}

    Q_PROPERTY(int dlc READ dlc WRITE set_dlc NOTIFY changed)


    uint8_t makeFlags()const;
    QString makeData()const;


signals:
    void changed();
private:
    QStringList m_data;
    bool m_fdf_flag;
    bool m_brs_flag;
    bool m_xtd_flag;
    QString m_id;
    int m_dlc;
};


#endif // FDCAN_INJECTION_MESSAGE_H
