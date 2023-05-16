#include "MemoryDataProperty.h"



//---------------------------------------------------------------------------------------
int MemoryDataProperty::columnCount(const QModelIndex &) const{
    return ColumnCount;
}



//---------------------------------------------------------------------------------------
QVariant MemoryDataProperty::headerData(int section, Qt::Orientation orientation, int role) const{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
        return QVariant();

    return m_columnNames.at(section);
}

//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
