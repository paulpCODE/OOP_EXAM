#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
template <class T>
void swapVec (T * a, T * b) {
    T tmp;
    tmp = * a;
    * a = * b;
    * b= tmp;
}

template <class T>
class SortAlgorithms {
public:
    virtual ~SortAlgorithms() {}
    virtual void sort(std::vector<T> &vec) = 0;

//    virtual void sort(std::vector<int> &vec) = 0;
};

/*!
 * \brief The SelectionSort class - represent the selection sort algorithm
 * inheritor of class sortAlgorithm
 */
template <class T>
class SelectionSort : public SortAlgorithms<T>
{
public:
    void sort(std::vector<T> &vec) override {
        unsigned int i, j, min_idx;

        //! One by one move boundary of unsorted subarray
        for (i = 0; i < vec.size() - 1; i++)  {

            //! Find the minimum element in unsorted array
            min_idx = i;
            for (j = i+1; j < vec.size(); j++)
            if (vec[j] < vec[min_idx])
                min_idx = j;

            //! Swap the found minimum element with the first element
            swapVec(&vec[min_idx], &vec[i]);            //!
        }
    }
};

//****************************************************************************************

/*!
 * \brief The insertionSort class - represent the insertion sort algorithm
 * inheritor of class sortAlgorithm
 */
template <class T>
class InsertionSort : public SortAlgorithms<T>
{
public:
    void sort(std::vector<T> &vec) override {
        T key;
        int j;
        for(unsigned int i = 1; i < vec.size(); i++){
            key = vec[i];
            j = i - 1;
            //! if previous element is bigger than current
            //! current = value of previous
            while((j >= 0) && (vec[j] > key)){
                vec[j+1] = vec[j];  //!
                j--;
            }
            vec[j+1] = key;         //!
        }
    }
};

//***************************************************************************************

/*!
 * \brief The quickSort class - represent the quick sort algorithm
 */
template <class T>
class QuickSort : public SortAlgorithms<T>
{
public:
    void sort(std::vector<T> &vec) override {
        quickSVec(vec, 0, vec.size()-1);
    }

    void quickSVec(std::vector<T> &vec, int l, int h) {
        if (l < h) {
            int line = partitionVec(vec, l, h);
            quickSVec(vec, l, line - 1);
            quickSVec(vec, line + 1, h);
        }
    }
    int partitionVec (std::vector<T> &vec, int l, int h) {
        T line = vec[h];
        int i = (l - 1);

        for (int j = l; j <= h - 1; j++) {
            if (vec[j] < line) {
                i++;
                swapVec (&vec[i], &vec[j]);    //!
            }
        }
        swapVec (&vec[i + 1], &vec[h]);        //!
        return (i + 1);
    }
};

//***************************************************************************************

/*!
 * \brief pattern Template Method
 * \details have class MergeSort      - main class of the pattern
 *                     RecMerge       - inheritor of class MergeSort that represent recursive merge sort
 *                     IterationMerge - inheritor of class MergeSort that represent iteration merge sort
 */
template <class T>
class MergeSort : public SortAlgorithms<T>
{
public:
    virtual void sort(std::vector<T> &vec) = 0;

    //make a constructor maybe
    void mergeVec(std::vector<T> &vec, int l, int c, int r) {
        int i, j, k;
        int n1 = c - l + 1;
        int n2 =  r - c;

        //!create temp arrays
        T L[n1], R[n2];

        //!Copy data to temp arrays L[] and R[]
        for (i = 0; i < n1; i++)
            L[i] = vec[l + i];
        for (j = 0; j < n2; j++)
            R[j] = vec[c + 1+ j];

        i = 0;   //!Initial index of first subarray
        j = 0;   //!Initial index of second subarray
        k = l;   //!Initial index of merged subarray

        //!Merge the temp arrays back into vec[l..r]
        while (i < n1 && j < n2) {
            if (L[i] < R[j]) {
                vec[k] = L[i];          //!
                i++;
            }
            else {
                vec[k] = R[j];          //!
                j++;
            }
            k++;
        }

        //!Copy the remaining elements of L[], if there are any
        while (i < n1) {
            vec[k] = L[i];
            i++;
            k++;
        }

        //!Copy the remaining elements of R[], if there are any
        while (j < n2)
        {
            vec[k] = R[j];
            j++;
            k++;
        }
    }
};

/*!
 * \brief The RecMerge class - recursive merge sort algorithm
 */
template <class T>
class RecMerge : public MergeSort<T>
{
public:
    void sort(std::vector<T> &vec) {
        mergeRecVec(vec, 0, vec.size()-1);
    }

    void mergeRecVec(std::vector<T> &vec, int left, int right) {
        if (left < right) {
            int center = left+(right-left)/2;

            //! Sort first and second halves
            mergeRecVec(vec, left, center);
            mergeRecVec(vec, center+1, right);

            MergeSort<T>::mergeVec(vec, left, center, right);
        }
    }
};

/*!
 * \brief The IterationMerge class - iterative merge sort algorithm
 */
template <class T>
class IterationMerge : public MergeSort<T>
{
public:
    void sort(std::vector<T> &vec) {
        int n = vec.size();
        int currSize;
        int lStart;
           for (currSize = 1; currSize <= n-1; currSize = 2 * currSize) {

               //! Pick starting point of different subarrays of current size
               for (lStart = 0; lStart < n-1; lStart += 2 * currSize) {

                   //!Find ending point of left subarray. mid+1 is starting
                   int mid = min(lStart + currSize - 1, n - 1);
                   int rEnd = min(lStart + 2 * currSize - 1, n - 1);

                   //! Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
                   MergeSort<T>::mergeVec(vec, lStart, mid, rEnd);
               }
           }
    }

    int min(int x, int y) { return (x<y)? x :y; }
};

//***************************************************************************************

///*!
// * \brief pattern Chain of Responsibility
// * \details have class Radix       - main class of pattern
// *                                   next - pointer to the class of choosen sort
// * make object of class Radix and give to the pointer "next" object of choosen class
// */
//template <class T>
//class Radix : public SortAlgorithms<T>
//{
//    Radix *next;
//public:
//    Radix() {}
//    Radix(Radix *n) {
//        next = n;
//    }
//    void sort(std::vector<int> &vec) override;
//    virtual void sorts(std::vector<int> &vec);
//};

///*!
// * \brief The MsdRadix class - msd radix sort algorithm
// * \details radix sort that go from first rank to the last (from hundreds to tenths)
// */
//template <class T>
//class MsdRadix : public Radix<T>
//{
//public:
//    void sorts(std::vector<int> &vec);

//    void msd_radix_sort(int *first, int *last, int msb = 31);
//};
///*!
// * \brief The Radix_test class - it is supporting class for MsdRadix::sort
// * (I recommend you don`t take\change\breathe on it)
// */
//template <class T>
//class Radix_test : public MsdRadix<T>
//{
//    const int bit;
//public:
//    Radix_test(int offset) : bit(offset) {}

//    bool operator()(int value) const
//    {
//        if (bit == 31)
//            return value < 0;
//        else return !(value & (1 << bit));
//    }
//};

///*!
// * \brief The LsdRadix class - lsd radix sort algorithm
// * \details radix sort that go from last rank to the first (from tenths to hundreds)
// */
//template <class T>
//class LsdRadix : public Radix<T>
//{
//public:
//    void sorts(std::vector<int> &vec);

//    void countSort(std::vector<int> &vec, int exp);
//    int getMax(std::vector<int> &vec);
//};

////***************************************************************************************

///*!
// * \brief Component pattern
// * \details have class HeadCount          - Component abstract base class with behavior common
// *  to primitive and composite objects
// *                     SimplAlgHeadCount  - primitive class that represent simple headcount sort
// *                     RobustAlgHeadCount - primitive class that represent robust headcount sort
// *                     CompositeHeadCount - Composite class stores primitives of the abstract type Component
// */

////! Component class
//template <class T>
//class HeadCount : public SortAlgorithms<T>
//{
//public:
//    virtual ~HeadCount() {}
//};

////! Primitive class
//template <class T>
//class SimplAlgHeadCount: public HeadCount<T>
//{
//public:
//    virtual void sort(std::vector<int> &vec);
//};
////! Primitive class
//template <class T>
//class RobustAlgHeadCount: public HeadCount<T>
//{
//public:
//    virtual void sort(std::vector<int> &vec);
//};

////! Composite class
///*!
// * \brief The CompositeHeadCount class - main class of this kind of sorting
// * (we will create objects of this class when use it)
// * \details classic function "sort" that will make some algorithm
// * and than call one of the primitive "sort"(function from classses SimplAlgHeadCount or RobustAlgHeadCount)
// */
//template <class T>
//class CompositeHeadCount: public HeadCount<T>
//{
//public:
//    void sort(std::vector<int> &vec) override;

//        CompositeHeadCount( HeadCount<T>* comp) { headCountStrategy = comp;}
//        ~CompositeHeadCount() { delete headCountStrategy; }
//private:
//    HeadCount<T>* headCountStrategy;
//};
