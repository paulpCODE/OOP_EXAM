#pragma once
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

using std::vector;

class HashTableTypeClass: public QObject{
    Q_GADGET
public:
    enum HashTableType{
        SeparateChaining,
        LinearProbing
    };
    Q_ENUM(HashTableType)
    static void registerInQml(){
        qmlRegisterUncreatableType<HashTableTypeClass>("Exam",1,0,"HashTableType",
                                               QStringLiteral("This object should not be created in qml"));
        qRegisterMetaType<HashTableTypeClass::HashTableType>("HashTableTypeClass::HashTableType");
    }
};
class BalancedTreeTypeClass: public QObject{
    Q_GADGET
public:
    enum BalancedTreeType{
        RedBlack,
        Splay,
        AVL
    };
    Q_ENUM(BalancedTreeType)
    static void registerInQml(){
        qmlRegisterUncreatableType<BalancedTreeTypeClass>("Exam",1,0,"BalancedTreeTypeClass",
                                               QStringLiteral("This object should not be created in qml"));
        qRegisterMetaType<BalancedTreeTypeClass::BalancedTreeType>("BalancedTreeTypeClass::BalancedTreeType");
    }
};

class SortsEnums : public QObject{
    Q_GADGET
public:
    enum SortChoice{
        SELECTION_SORT,
        INSERTION_SORT,
        QUICK_SORT,
        MERGE_RECURSIVE_SORT,
        MERGE_ITERATIVE_SORT,
    };
    Q_ENUM(SortChoice)
    static void registerInQml(){
        qmlRegisterUncreatableType<SortsEnums>("Exam",1,0,"SortChoice",
                                               QStringLiteral("This object should not be created in qml"));
        qRegisterMetaType<SortsEnums::SortChoice>("SortEnums::SortChoice");
    }
};
class DataTypesEnums : public QObject{
    Q_GADGET
public:
    enum DataTypes{
        INT,
        STRING,
        BOOK
    };
    Q_ENUM(DataTypes)
    static void registerInQml(){
        qmlRegisterUncreatableType<DataTypesEnums>("Exam",1,0,"DataTypes",
                                                   QStringLiteral("This object should not be created in qml"));
        qRegisterMetaType<DataTypesEnums::DataTypes>("DataTypesEnums::DataTypes");
    }
};
