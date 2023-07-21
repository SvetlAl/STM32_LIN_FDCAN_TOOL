#include "Version.h"

QString Version::version_string() const{
    if(isValid()){
        return QString("%1.%2.%3.%4")
            .arg(series)
            .arg(day, 2, 10, QChar('0'))
            .arg(month, 2, 10, QChar('0'))
            .arg(year, 2, 10, QChar('0')).append(isBeta() ? "beta" : "");
    }
    else return "";
}

void Version::print() const{
    qDebug() << "*** " << version_string() << " ***";
    if(isBeta()) qDebug() << "Beta";
    else  qDebug() << "not beta";
    if(isValid()) qDebug() << "Valid";
    else  qDebug() << "not valid";
    if(isDescribed()) qDebug() << "Described";
    else  qDebug() << "not described";
    qDebug() << "series";
    DEBUG_OUT_POD(series);
    qDebug() << "day";
    DEBUG_OUT_POD(day);
    qDebug() << "month";
    DEBUG_OUT_POD(month);
    qDebug() << "year";
    DEBUG_OUT_POD(year);
    qDebug() << "code";
    DEBUG_OUT_POD(code)
    qDebug() << "description";
    qDebug() << description;
    qDebug() << "errata";
    qDebug() << errata;
    qDebug() << "extra";
    qDebug() << extra;
    qDebug() << "design_code";
    if(design_code == Invalid){
        qDebug() << "Invalid";
    }
    else if(design_code == Device){
        qDebug() << "Device";
    }
    else if(design_code == Interface){
        qDebug() << "Interface";
    }
}

const QString &Version::getDescription() const
{
    return description;
}

void Version::setDescription(const QString &newDescription)
{
    description = newDescription;
}

const QString &Version::getErrata() const
{
    return errata;
}

void Version::setErrata(const QString &newErrata)
{
    errata = newErrata;
}

const QString &Version::getExtra() const
{
    return extra;
}

void Version::setExtra(const QString &newExtra)
{
    extra = newExtra;
}

uint8_t Version::getBeta_flag() const
{
    return beta_flag;
}

uint8_t Version::getSeries() const
{
    return series;
}

uint8_t Version::getDay() const
{
    return day;
}

uint8_t Version::getMonth() const
{
    return month;
}

uint8_t Version::getYear() const
{
    return year;
}

uint16_t Version::getCode() const
{
    return code;
}

Version::VerDesignCode Version::getDesign_code() const{
    return design_code;
}

QDate Version::getDate()const{
    QString dateString = QString("%1-%2-%3").arg(year, 2, 10, QChar('0'))
        .arg(month, 2, 10, QChar('0')).arg(day, 2, 10, QChar('0'));

    QDate date = QDate::fromString(dateString, "yy-MM-dd");
    return date;
}
