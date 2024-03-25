/* forked from https://github.com/koldoon/qt-listview-generic-cpp-model
@author Vadim Usoltsev */


#ifndef OBJ_LIST_MODEL_H
#define OBJ_LIST_MODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QVariant>
#include <QStringList>

template <typename T>
class Obj_List_Model : public QAbstractListModel, public QList<QSharedPointer<T>> {
    using ITEM = QSharedPointer<T>;
    using LIST = QList<ITEM>;

public:
    enum CollectionRole {
        ItemDataRole = Qt::UserRole
    };

    /************ override ************/
    int rowCount( const QModelIndex& parent ) const override {
        Q_UNUSED( parent )
        return LIST::count();
    }

    QVariant data( const QModelIndex& index, int role ) const override {
        auto row = index.row();

        if ( row < 0 || row >= LIST::count() )
            return QVariant();

        if ( role == ItemDataRole )
            return QVariant::fromValue<QObject*>( LIST::at( row ).data() );

        return QVariant();
    }

    ITEM dataPtr(int i) const{
        if ( i < 0 || i >= LIST::count() ) return LIST::at(0);

        return  LIST::at( i );
    }

    QHash<int, QByteArray> roleNames() const override {
        auto roles = QAbstractListModel::roleNames();
        roles[ItemDataRole] = ITEM_ROLE_NAME;
        return roles;
    }


    /************ data interaction ************/
    void insert( int i, const ITEM& item ) {
        if ( i < 0 || i > LIST::count() )
            return;

        beginInsertRows(QModelIndex(), i, i );
        LIST::insert( i, item );
        endInsertRows();
        emitChanged();
    }

    void append( const ITEM& item ) {
        auto i = LIST::count();
        beginInsertRows(QModelIndex(), i, i );
        LIST::append( item );
        endInsertRows();
        emitChanged();
    }

    void append( const LIST& list ) {
        if ( list.count() == 0 )
            return;

        auto start = LIST::count();
        auto end = LIST::count() + list.count() - 1;
        beginInsertRows(QModelIndex(), start, end );
        LIST::append( list );
        endInsertRows();
        emitChanged();
    }

    void removeAt( int i ) {
        if ( i < 0 || i > LIST::count() - 1 )
            return;

        beginRemoveRows(QModelIndex(), i, i );
        LIST::removeAt( i );
        endRemoveRows();
        emitChanged();
    }

    bool removeOne( const ITEM& item ) {
        int index = LIST::indexOf( item );
        if ( index != -1 ) {
            removeAt( index );
            return true;
        }
        return false;
    }

    void removeLast() {
        if ( LIST::count() == 0 )
            return;

        auto i = LIST::count() - 1;
        beginRemoveRows(QModelIndex(), i, i );
        LIST::removeAt( i );
        endRemoveRows();
        emitChanged();
    }

    void removeFirst() {
        if ( LIST::count() == 0 )
            return;

        beginRemoveRows(QModelIndex(), 0, 0 );
        LIST::removeAt( 0 );
        endRemoveRows();
        emitChanged();
    }

    void replace( int i, const ITEM& item ) {
        removeAt( i );
        insert( i, item );
        emitChanged();
    }

    void clear() {
        beginResetModel();
        LIST::clear();
        endResetModel();
        emitChanged();
    }

    Obj_List_Model& operator+=( const ITEM& t ) {
        append( t );
        return *this;
    }

    Obj_List_Model& operator<<( const ITEM& t ) {
        append( t );
        return *this;
    }

    Obj_List_Model& operator+=( const LIST& list ) {
        append( list );
        return *this;
    }

    Obj_List_Model& operator<<( const LIST& list ) {
        append( list );
        return *this;
    }

    protected:
        constexpr static const char ITEM_ROLE_NAME[] = "modelData";
        virtual void emitChanged() = 0;
};

/*
#define DECLARE_Q_OBJECT_LIST_MODEL( TYPE )                                                \
    class Obj_List_Model##TYPE : public Obj_List_Model<TYPE> { \
        Q_OBJECT                                                                           \
        Q_PROPERTY( int length READ count NOTIFY changed )                                 \
        Q_PROPERTY( int isEmpty READ isEmpty NOTIFY changed )                              \
                                                                                           \
    Q_SIGNALS:                                                                             \
        void changed();                                                                    \
                                                                                           \
    protected:                                                                             \
        virtual void emitChanged() {                                                       \
            emit changed();                                                                \
        }                                                                                  \
                                                                                           \
        Q_INVOKABLE QVariant item( int i ) {                                               \
            if ( i < 0 || i >= count() )                                                   \
                return QVariant();                                                         \
                                                                                           \
            auto obj = at( i ).data();                                                     \
            QQmlEngine::setObjectOwnership( obj, QQmlEngine::CppOwnership );               \
            return QVariant::fromValue( obj );                                             \
        }                                                                                  \
    };
*/
#endif /* OBJ_LIST_MODEL_H */
