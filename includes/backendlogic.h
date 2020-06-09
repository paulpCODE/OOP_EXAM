#pragma once
#include <QObject>
#include "SortAlgorithms.h"
#include "randomize.h"
#include <vector>
#include <QDebug>
#include "enumerations.h"
#include "MapContainer.h"
#include "Set.h"
using std::vector;


template <class T>
class SortFactory
{
private:
    SortFactory();
    SortFactory(SortFactory &other) = delete;
    SortFactory(const SortFactory &) = delete;

public:
    static SelectionSort<T> * selectionSort(){
        SelectionSort<T> * sort = new SelectionSort<T>;
        return sort ;
    }
    static SortAlgorithms<T> * insertionSort(){
        InsertionSort<T> * sort = new InsertionSort<T>;
        return sort ;
    }
    static SortAlgorithms<T> * quickSort(){
        QuickSort<T> * sort = new QuickSort<T>;
        return sort ;
    }
    static SortAlgorithms<T> * iterationMerge(){
        IterationMerge<T> * sort = new IterationMerge<T>;
        return sort ;
    }
    static SortAlgorithms<T> * recursiveMerge(){
        RecMerge<T> * sort = new RecMerge<T>;
        return sort ;
    }
};

class AbstractSortLogic: public QObject{
    Q_OBJECT
public:
    AbstractSortLogic(QObject *parent = nullptr):QObject(parent){}
    virtual void sort() = 0;
    virtual void selectSort(SortsEnums::SortChoice choosenSort) = 0;
};

template <class T>
class SortLogic :public AbstractSortLogic
{
public:
    SortLogic():AbstractSortLogic(),sortingStrategy(nullptr),vectorToSort({}){}
    ~SortLogic(){delete sortingStrategy;}

    SortAlgorithms<T> *sortingStrategy;
    vector<T> vectorToSort;

    void sort() override
    {
        if(!sortingStrategy){
            qDebug("m_strategy == nullptr .You need to select sort firstly");
        }
        else if(vectorToSort.empty()){
            qDebug("Your vector is empty.You need to create it firstly");
          }
        else{
            // замеры времени до
            sortingStrategy->sort(vectorToSort);
            // замеры времени после
        }
    }
    //void randomizeVectorInt(int howManyNumbers, int from, int to);
    void selectSort(SortsEnums::SortChoice choosenSort) override{
        // factory switch case based on enum
        // m_strategy = classCreatedByFactory
        switch (choosenSort) {
        case SortsEnums::SortChoice ::SELECTION_SORT : sortingStrategy = SortFactory<T>::selectionSort();
            break;
        case SortsEnums::SortChoice ::INSERTION_SORT : sortingStrategy = SortFactory<T>::insertionSort();
            break;
        case SortsEnums::SortChoice ::QUICK_SORT : sortingStrategy = SortFactory<T>::quickSort();
            break;
        case SortsEnums::SortChoice ::MERGE_RECURSIVE_SORT : sortingStrategy = SortFactory<T>::recursiveMerge();
            break;
        case SortsEnums::SortChoice ::MERGE_ITERATIVE_SORT : sortingStrategy = SortFactory<T>::iterationMerge();
            break;
        default:
            qDebug("Wrong enum");
            break;
        }
    }

};
