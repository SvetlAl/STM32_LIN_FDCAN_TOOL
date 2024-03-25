#ifndef MEMORYTABLEMODELVIEW_H
#define MEMORYTABLEMODELVIEW_H
//========================= UNUSED ==================================

#include <qqml.h>
#include <QAbstractTableModel>

class MemoryTablemodel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
 //   QML_ADDED_IN_MINOR_VERSION(1)

public:
    enum {
        Address = 0,
        B0 ,
        B4 ,
        B8 ,
        BC ,
        ASCII ,
        ColumnCount
    };

    MemoryTablemodel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QStringList m_columnNames;

};
#endif // MEMORYTABLEMODELVIEW_H
