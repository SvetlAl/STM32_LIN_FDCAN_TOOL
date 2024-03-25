#ifndef QVEHICLE_MODELITEM_H
#define QVEHICLE_MODELITEM_H

/***********************************************************************
 *
 *
 * Vehicle Model Item describes a vehicle:
 *
 * model code (from vehicle.h of the firmware)
 * name
 * brand code (Toyota, Mitsubishi, Isuzu etc)
 *
 *
 ************************************************************************/

#include "../../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <stdio.h>
#include "../Vehicle.h"


class QVehicle_ModelItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY changed )
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY changed )
    Q_PROPERTY(int brand_code READ getBrand_code WRITE setBrand_code NOTIFY changed )

public:
    explicit QVehicle_ModelItem(QObject *parent = nullptr, QString a = "", int n = 0xFFFF, int b = Vehicle::ModelBrand::Default) :
        QObject(parent), m_name(a), m_hex_value(n), brand_code(b)  {};

    ~QVehicle_ModelItem( ){
    }

    //================================ Setters/Getters =============================
    const QString &name() const;
    void setName(const QString &newName);
    int value() const;
    void setValue(int newValue);

    int getBrand_code() const;
    void setBrand_code(int newBrand_code);

signals:
    void changed();

private:
    QString m_name;
    int m_hex_value;
    int brand_code;
};


#endif // QVEHICLE_MODELITEM_H
