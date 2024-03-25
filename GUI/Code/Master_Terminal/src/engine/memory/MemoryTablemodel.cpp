#include "MemoryTablemodel.h"

//---------------------------------------------------------------------------------------
MemoryTablemodel::MemoryTablemodel(QObject *parent) : QAbstractTableModel(parent){
    m_columnNames << "Address" << "0" << "4" << "8" << "C" << "Ascii";
}

//---------------------------------------------------------------------------------------
int MemoryTablemodel::rowCount(const QModelIndex &) const{

    return 20;
}

//---------------------------------------------------------------------------------------
int MemoryTablemodel::columnCount(const QModelIndex &) const{
    return ColumnCount;
}

//---------------------------------------------------------------------------------------
QVariant MemoryTablemodel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= rowCount() || col >= columnCount() || role !=  Qt::DisplayRole)
        return QVariant();

    switch (col)
    {
    case Address:
        return QString("Address");
    case B0:
        return QString("0");
    case B4:
        return QString("4");
    case B8:
        return QString("8");
    case BC:
        return QString("C");
    case ASCII:
        return QString("Ascii");
    }
    return QVariant();
}

//---------------------------------------------------------------------------------------
QVariant MemoryTablemodel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
        return QVariant();

    return m_columnNames.at(section);
}

//---------------------------------------------------------------------------------------
QHash<int, QByteArray> MemoryTablemodel::roleNames() const{
    return { {Qt::DisplayRole, "display"} };
}

//---------------------------------------------------------------------------------------
