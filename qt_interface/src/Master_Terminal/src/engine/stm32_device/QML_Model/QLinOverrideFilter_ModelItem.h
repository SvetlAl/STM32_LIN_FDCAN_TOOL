#ifndef QLINOVERRIDEFILTER_MODELITEM_H
#define QLINOVERRIDEFILTER_MODELITEM_H

/***********************************************************************
 * QLinOverrideFilter_ModelItem ==> QLinOverrideFilter_ModelProperty ==>
 *
 *
 *
 * QLinOverrideFilter_ModelItem represent an override LIN filter of the firmware
 *
 * An override filter contains:
 *  Editable Status: Enabled or disabled
 *  ID
 *  Byte 0
 *  Byte 1
 *  Byte 2
 *  Byte 3
 *  Byte 4
 *  Byte 5
 *  Byte 6
 *  Byte 7
 *  Mask
 *
 * Example:
 * If the override filter
 *  ID 0x30
 *  Byte 0 0x00
 *  Byte 1 0x00
 *  Byte 2 0x00
 *  Byte 3 0x03
 *  Byte 4 0x00
 *  Byte 5 0x00
 *  Byte 6 0x00
 *  Byte 7 0x07
 *  Mask 0b00010001
 * is enabled, all messages with id 0x30 coming in a certain direction would have the bytes 3 and 7 replaced with the values 0x03 and 0x07
 *
 ************************************************************************/


#include "../../../app_settings.h"
#include <QDebug>
#include <stdio.h>


class QLinOverrideFilter_ModelItem: public QObject{
    Q_OBJECT
    // Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY changed)
    Q_PROPERTY(bool dir_value READ dir_value WRITE setDir_value NOTIFY changed)
    //Q_PROPERTY(bool isEditable READ editable WRITE setEditable NOTIFY changed )
    Q_PROPERTY(QString id_value READ str_id_value WRITE str_set_id_value NOTIFY changed )

    Q_PROPERTY(QString str_byte0 READ str_byte0 WRITE setStr_byte0 NOTIFY changed)
    Q_PROPERTY(QString str_byte1 READ str_byte1 WRITE setStr_byte1 NOTIFY changed)
    Q_PROPERTY(QString str_byte2 READ str_byte2 WRITE setStr_byte2 NOTIFY changed)
    Q_PROPERTY(QString str_byte3 READ str_byte3 WRITE setStr_byte3 NOTIFY changed)
    Q_PROPERTY(QString str_byte4 READ str_byte4 WRITE setStr_byte4 NOTIFY changed)
    Q_PROPERTY(QString str_byte5 READ str_byte5 WRITE setStr_byte5 NOTIFY changed)
    Q_PROPERTY(QString str_byte6 READ str_byte6 WRITE setStr_byte6 NOTIFY changed)
    Q_PROPERTY(QString str_byte7 READ str_byte7 WRITE setStr_byte7 NOTIFY changed)
    Q_PROPERTY(bool byte0_on READ byte0_on WRITE setByte0_on NOTIFY changed)
    Q_PROPERTY(bool byte1_on READ byte1_on WRITE setByte1_on NOTIFY changed)
    Q_PROPERTY(bool byte2_on READ byte2_on WRITE setByte2_on NOTIFY changed)
    Q_PROPERTY(bool byte3_on READ byte3_on WRITE setByte3_on NOTIFY changed)
    Q_PROPERTY(bool byte4_on READ byte4_on WRITE setByte4_on NOTIFY changed)
    Q_PROPERTY(bool byte5_on READ byte5_on WRITE setByte5_on NOTIFY changed)
    Q_PROPERTY(bool byte6_on READ byte6_on WRITE setByte6_on NOTIFY changed)
    Q_PROPERTY(bool byte7_on READ byte7_on WRITE setByte7_on NOTIFY changed)

public:
    explicit QLinOverrideFilter_ModelItem(QObject *parent = nullptr) {
      //  if(ovrfltr_id_count == 0)setEditable(true);
      //  else setEditable(false);
      //  ovrfltr_id_count++;
    };

    ~QLinOverrideFilter_ModelItem( ){
      //  if(ovrfltr_id_count != 0)ovrfltr_id_count--;
    }

    static const bool dir_from_master_to_slave = true;
    static const bool dir_from_slave_to_master = false;

    //=========================== Class setters/getters ===============================
    // bool editable() const;
    // void setEditable(bool newval);

    bool dir_value() const;
    void setDir_value(bool dir);

    const QString str_byte0() const;
    void setStr_byte0(const QString &_val);
    bool byte0_on() const;
    void setByte0_on(bool isOn);

    const QString str_byte1() const;
    void setStr_byte1(const QString &_val);
    bool byte1_on() const;
    void setByte1_on(bool isOn);

    const QString str_byte2() const;
    void setStr_byte2(const QString &_val);
    bool byte2_on() const;
    void setByte2_on(bool isOn);

    const QString str_byte3() const;
    void setStr_byte3(const QString &_val);
    bool byte3_on() const;
    void setByte3_on(bool isOn);

    const QString str_byte4() const;
    void setStr_byte4(const QString &_val);
    bool byte4_on() const;
    void setByte4_on(bool isOn);

    const QString str_byte5() const;
    void setStr_byte5(const QString &_val);
    bool byte5_on() const;
    void setByte5_on(bool isOn);

    const QString str_byte6() const;
    void setStr_byte6(const QString &_val);
    bool byte6_on() const;
    void setByte6_on(bool isOn);

    const QString str_byte7() const;
    void setStr_byte7(const QString &_val);
    bool byte7_on() const;
    void setByte7_on(bool isOn);


    const QString str_id_value()const;
    void str_set_id_value(const QString &_id);
    int Id_value() const;
    void setId_value(int newId_value);

    bool enabled() const;
    void setEnabled(bool newEnabled);
    uint8_t byte0() const;
    void setByte0(uint8_t newByte0);
    uint8_t byte1() const;
    void setByte1(uint8_t newByte1);
    uint8_t byte2() const;
    void setByte2(uint8_t newByte2);
    uint8_t byte3() const;
    void setByte3(uint8_t newByte3);
    uint8_t byte4() const;
    void setByte4(uint8_t newByte4);
    uint8_t byte5() const;
    void setByte5(uint8_t newByte5);
    uint8_t byte6() const;
    void setByte6(uint8_t newByte6);
    uint8_t byte7() const;
    void setByte7(uint8_t newByte7);
    uint8_t msk() const;
    void setMsk(uint8_t newMsk);
    void addMsk(uint8_t newMsk);
    void clearMsk(uint8_t newMsk);

signals:
    void changed();

private:
    //static inline uint32_t ovrfltr_id_count = 0;

    // bool m_editable = false;
    // bool m_enabled = false;

    bool m_lin_dir = dir_from_master_to_slave;
    int m_Id_value = 0;

    uint8_t m_byte0 = 0;
    uint8_t m_byte1 = 0;
    uint8_t m_byte2 = 0;
    uint8_t m_byte3 = 0;

    uint8_t m_byte4 = 0;
    uint8_t m_byte5 = 0;
    uint8_t m_byte6 = 0;
    uint8_t m_byte7 = 0;

    uint8_t m_msk = 0;

};


#endif // QLINOVERRIDEFILTER_MODELITEM_H
