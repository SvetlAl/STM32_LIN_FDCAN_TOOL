#ifndef QDISCARDID_MODELITEM_H
#define QDISCARDID_MODELITEM_H

#include "../../../app_settings.h"
#include <QDebug>
#include <stdio.h>

/*****************************************************************************************/
/*****************************************************************************************/
/***********                     Discard ID filter                             ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class QDiscardId_ModelItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(bool isEnabled READ enabled WRITE setEnabled NOTIFY changed )
    Q_PROPERTY(bool isEditable READ editable WRITE setEditable NOTIFY changed )
    Q_PROPERTY(QString id_value READ str_id_value WRITE str_set_id_value NOTIFY changed )
    Q_PROPERTY(int dir_value READ dir_value WRITE setDir_value NOTIFY changed)

public:

    explicit QDiscardId_ModelItem(QObject *parent = nullptr){
        if(discard_id_count == 0)setEditable(true);
        else setEditable(false);
        discard_id_count++;
    };

    ~QDiscardId_ModelItem( ){
        if(discard_id_count != 0)discard_id_count--;
    }


/*** setters and getters ***/

    const QString str_id_value()const;
    void str_set_id_value(const QString &_id);
    int Id_value() const;
    void setId_value(int newId_value);
    bool enabled() const;
    void setEnabled(bool newEnabled);

    bool editable() const;
    void setEditable(bool newval);

    int dir_value() const;
    void setDir_value(int newDir_value);

signals:
    void changed();

private:
    static inline uint32_t discard_id_count = 0;
    int m_can_dir = 1;
    int m_Id_value = 0;
    bool m_enabled = false;
    bool m_editable;

};


#endif // QDISCARDID_MODELITEM_H
