#ifndef QLINCONFIGITEM_H
#define QLINCONFIGITEM_H

#include "../../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <stdio.h>

/*****************************************************************************************/
/*********   QLinConfigItem is a general class that can incapsulate LIN settings: ********/
/***********                                                                   ***********/
/*********** Baud Rate                                                         ***********/
/*********** Filter Preset                                                     ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class QLinConfigItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY changed )
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY changed )

public:

    explicit QLinConfigItem(QObject *parent = nullptr, QString a = "", int n = 0) : QObject(parent), m_name(a), m_value(n) {};
    QLinConfigItem(QString a, int n) : QObject(), m_name(a), m_value(n) {};

    ~QLinConfigItem( ){}


/*** setters and getters ***/
    const QString &name() const;
    void setName(const QString &newName);
    int value() const;
    void setValue(int newValue);

signals:
    void changed();

private:
    QString m_name;
    int m_value;
};


#endif // QLINCONFIGITEM_H
