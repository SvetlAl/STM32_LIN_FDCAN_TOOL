#ifndef VERSION_H
#define VERSION_H

/***********************************************************************
 *
 * Version contains a sorted information about firmware or interface:
 * Is it a device or interface info
 * Series
 * Date
 *
 *
 *
 ************************************************************************/

#include <stdlib.h>
#include <QDebug>
#include <QDate>
#include <iostream>
#include "../app_settings.h"

using namespace std;

// OBSOLETE
#define DEV_DEFAULT_CODE				(uint16_t)0x0000
#define DEV_SPD_CLBR_CODE_MSK			(uint16_t)0x0001
#define DEV_CANSCANNER_CODE_MSK			(uint16_t)0x0002
#define DEV_2CANSCANNER_CODE_MSK		(uint16_t)0x0004


class Version{
public:

    enum VerDesignCode {
        Invalid = 0,
        Device = 1,
        Interface = 2
    };

    explicit Version(){
    };

    Version(const QString &init_string, int designCode){
        bool isValidFormat = App_settings::get_DeviceSoftwareVersion_Regex().match(init_string).hasMatch();

        QStringList parts = init_string.split('.');
        if ((parts.size() != 5) | !isValidFormat) {
            beta_flag = 0;
            series = 0;
            day = 0;
            month = 0;
            year = 0;
            code = 0;
            design_code = Invalid;
        }
        else{
            QByteArray part0 = parts[0].toLatin1();
            const char* data = part0.data();

            beta_flag = data[0];
            parts[0] = parts[0].remove(0,1);
            series = parts[0].toUInt();
            day = parts[1].toUInt();
            month = parts[2].toUInt();
            year = parts[3].toUInt();
            code = parts[4].toUInt(nullptr, 16);
            design_code = static_cast<VerDesignCode>(designCode);
        }
    };

    ~Version(){
    };



    //=========================== Service data string functions =======================
    bool isValid() const {if(design_code != Invalid) return true; else return false;}
    bool isBeta() const {if(beta_flag == 'b') return true; else return false;}
    bool isDescribed() const {
        if((description != "") | (errata != "") | (extra != ""))return true;
        else return false;}
    QDate getDate()const;
    void print() const;

    QString version_string() const;

    void resetOnDisconnect(){
        beta_flag = 0;
        series = 0;
        day = 0;
        month = 0;
        year = 0;
        code = 0;
        design_code = Invalid;
        description = "";
        errata = "";
        extra = "";
    }


    //===================================== Operators ================================
    friend bool operator == (Version const& lhs, Version const& rhs);
    friend bool operator != (Version const& lhs, Version const& rhs);
    friend bool operator < (Version const& lhs, Version const& rhs);
    friend bool operator > (Version const& lhs, Version const& rhs);
    friend bool operator <= (Version const& lhs, Version const& rhs);
    friend bool operator >= (Version const& lhs, Version const& rhs);


    bool operator > (Version const& rhs) {
        if(this->series > rhs.series) return true;
        if(this->day > rhs.day) return true;
        if(this->month > rhs.month) return true;
        if(this->year > rhs.year) return true;
        if(this->beta_flag != 'b' && rhs.beta_flag == 'b') return true;
        else return false;
    }

    bool operator < (Version const& rhs) {
        if(this->series < rhs.series) return true;
        if(this->day < rhs.day) return true;
        if(this->month < rhs.month) return true;
        if(this->year < rhs.year) return true;
        if(this->beta_flag == 'b' && rhs.beta_flag != 'b') return true;
        else return false;
    }

    bool operator >= (Version const& rhs) {
        return !(*this < rhs);
    }

    bool operator <= (Version const& rhs) {
        return !(*this > rhs);
    }


    bool operator == (Version const& rhs) {
        if((this->beta_flag !=rhs.beta_flag) &
                (this->series !=rhs.series) &
                (this->day !=rhs.day) &
                (this->month !=rhs.month) &
                (this->year !=rhs.year) &
                (this->code !=rhs.code) &
                (this->design_code !=rhs.design_code)) return false;
        else return true;
    }

    bool operator != (Version const& rhs) {
        return !(*this ==rhs);
    }


    Version &operator = (Version const& rhs){
        this->beta_flag = rhs.beta_flag;
        this->series = rhs.series;
        this->day = rhs.day;
        this->month = rhs.month;
        this->year = rhs.year;
        this->code = rhs.code;
        this->design_code = rhs.design_code;

        this->description = rhs.description;
        this->errata = rhs.errata;
        this->extra = rhs.extra;

        return *this;
    }

    Version &operator = (QSharedPointer<Version> &rhs){
        this->beta_flag = rhs.data()->beta_flag;
        this->series = rhs.data()->series;
        this->day = rhs.data()->day;
        this->month = rhs.data()->month;
        this->year = rhs.data()->year;
        this->code = rhs.data()->code;
        this->design_code = rhs.data()->design_code;

        this->description = rhs.data()->description;
        this->errata = rhs.data()->errata;
        this->extra = rhs.data()->extra;

        return *this;
    }

    //=========================== Class setters/getters ==============================
    const QString &getDescription() const;
    void setDescription(const QString &newDescription);
    const QString &getErrata() const;
    void setErrata(const QString &newErrata);
    const QString &getExtra() const;
    void setExtra(const QString &newExtra);

    uint8_t getBeta_flag() const;
    uint8_t getSeries() const;
    uint8_t getDay() const;
    uint8_t getMonth() const;
    uint8_t getYear() const;
    uint16_t getCode() const;

    VerDesignCode getDesign_code() const;

private:
    uint8_t beta_flag = 0; // OBSOLETE
    uint8_t series = 0;
    uint8_t day = 0;
    uint8_t month = 0;
    uint8_t year = 0;
    uint16_t code = 0; // OBSOLETE

    QString description = "";
    QString errata = "";
    QString extra = "";

    VerDesignCode design_code = Invalid;
};


#endif // VERSION_H
