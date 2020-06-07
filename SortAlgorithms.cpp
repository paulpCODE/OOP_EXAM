#include "includes/SortAlgorithms.h"
#include <algorithm>

///*!
// * \brief swapVec change values of two elements
// * \details it is used several times so it is here
// */
//template <class T>
//void swapVec (T * a, T * b) {
//    T tmp;
//    tmp = * a;
//    * a = * b;
//    * b= tmp;
//}

///*!
// * \brief SelectionSort::sort - algorith of selection sort
// * \param vec - vector that is needed to be sort
// */
////template <class T>
////void SelectionSort<T>::sort(std::vector<T> &vec)  {
////    unsigned int i, j, min_idx;

////    //! One by one move boundary of unsorted subarray
////    for (i = 0; i < vec.size() - 1; i++)  {

////        //! Find the minimum element in unsorted array
////        min_idx = i;
////        for (j = i+1; j < vec.size(); j++)
////        if (vec[j] < vec[min_idx])
////            min_idx = j;

////        //! Swap the found minimum element with the first element
////        swapVec(&vec[min_idx], &vec[i]);            //!
////    }
////}

////******************************************************************************************

///*!
// * \brief InsertionSort::sort - algorithm of insertion sort
// * \param vec - vector that is needed to be sorted
// */
//template <class T>
//void InsertionSort<T>::sort(std::vector<T> &vec){
//    T key;
//    int j;
//    for(unsigned int i = 1; i < vec.size(); i++){
//        key = vec[i];
//        j = i - 1;
//        //! if previous element is bigger than current
//        //! current = value of previous
//        while((j >= 0) && (vec[j] > key)){
//            vec[j+1] = vec[j];  //!
//            j--;
//        }
//        vec[j+1] = key;         //!
//    }
//}

////******************************************************************************************

///*!
// * \brief QuickSort::partitionVec
// * \param vec - vector that is needed to be sort
// * \param l - index of the firt element of the current vec
// * \param h - index of the last element of the current vec
// * \return index of element from which we divide the vector by 2 parts
// */
//template <class T>
//int QuickSort<T>::partitionVec(std::vector<T> &vec, int l, int h) {
//    T line = vec[h];
//    int i = (l - 1);

//    for (int j = l; j <= h - 1; j++) {
//        if (vec[j] < line) {
//            i++;
//            swapVec (&vec[i], &vec[j]);    //!
//        }
//    }
//    swapVec (&vec[i + 1], &vec[h]);        //!
//    return (i + 1);
//}

///*!
// * \brief QuickSort::quickSVec
// * \param l - index of the firt element of the current vec
// * \param h - index of the last element of the current vec
// */
//template <class T>
//void QuickSort<T>::quickSVec(std::vector<T> &vec, int l, int h) {
//    if (l < h) {
//        int line = partitionVec(vec, l, h);
//        quickSVec(vec, l, line - 1);
//        quickSVec(vec, line + 1, h);
//    }
//}

///*!
// * \brief QuickSort::sort main function that will call quickSVec
// */
//template <class T>
//void QuickSort<T>::sort(std::vector<T> &vec) {
//    quickSVec(vec, 0, vec.size()-1);
//}

////******************************************************************************************

///*!
// * \brief MergeSort::mergeVec - Merges two subarrays of vec[]
// * \details first subarray is vec[l..c]
// *          second subarray is vec[c+1..r]
// * \param vec
// * \param l - left index of first subarray
// * \param c - right index of first subarray
// * \param r - right index of second subarray
// */
//template <class T>
//void MergeSort<T>::mergeVec(std::vector<T> &vec, int l, int c, int r) {
//    int i, j, k;
//    int n1 = c - l + 1;
//    int n2 =  r - c;

//    //!create temp arrays
//    T L[n1], R[n2];

//    //!Copy data to temp arrays L[] and R[]
//    for (i = 0; i < n1; i++)
//        L[i] = vec[l + i];
//    for (j = 0; j < n2; j++)
//        R[j] = vec[c + 1+ j];

//    i = 0;   //!Initial index of first subarray
//    j = 0;   //!Initial index of second subarray
//    k = l;   //!Initial index of merged subarray

//    //!Merge the temp arrays back into vec[l..r]
//    while (i < n1 && j < n2) {
//        if (L[i] < R[j]) {
//            vec[k] = L[i];          //!
//            i++;
//        }
//        else {
//            vec[k] = R[j];          //!
//            j++;
//        }
//        k++;
//    }

//    //!Copy the remaining elements of L[], if there are any
//    while (i < n1) {
//        vec[k] = L[i];
//        i++;
//        k++;
//    }

//    //!Copy the remaining elements of R[], if there are any
//    while (j < n2)
//    {
//        vec[k] = R[j];
//        j++;
//        k++;
//    }
//}

///*!
// * \brief RecMerge::mergeRecVec - recursive merge vector
// * \param left is for left index of the sub-array of vec to be sorted
// * \param right is right index of the sub-array of vec to be sorted
// */
//template <class T>
//void RecMerge<T>::mergeRecVec(std::vector<T> &vec, int left, int right) {
//    if (left < right) {
//        int center = left+(right-left)/2;

//        //! Sort first and second halves
//        mergeRecVec(vec, left, center);
//        mergeRecVec(vec, center+1, right);

//        mergeVec(vec, left, center, right);
//    }
//}

///*!
// * \brief RecMerge::sort main function that will call mergeRecVec
// */
//template <class T>
//void RecMerge<T>::sort(std::vector<T> &vec) {
//    mergeRecVec(vec, 0, vec.size()-1);
//}

///*!
// * \brief IterationMerge::sort Merge subarrays in bottom up manner.
// * \details  First merge subarrays of size 1 to create sorted subarrays of size 2,
// *  then merge subarrays of size 2 to create sorted subarrays of size 4, and so on.
// */
//template <class T>
//void IterationMerge<T>::sort(std::vector<T> &vec) {
//    int n = vec.size();
//    int currSize;
//    int lStart;
//       for (currSize = 1; currSize <= n-1; currSize = 2 * currSize) {

//           //! Pick starting point of different subarrays of current size
//           for (lStart = 0; lStart < n-1; lStart += 2 * currSize) {

//               //!Find ending point of left subarray. mid+1 is starting
//               int mid = min(lStart + currSize - 1, n - 1);
//               int rEnd = min(lStart + 2 * currSize - 1, n - 1);

//               //! Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
//               mergeVec(vec, lStart, mid, rEnd);
//           }
//       }
//}

////******************************************************************************************
///*!
// * \brief helper - vector that is needed for realization algorithms
// */
//std::vector<int> helper{};

///*!
// * \brief CompositeHeadCount::sorts Composite sort that will call SimplAlgHeadCount::sorts or RobustAlgHeadCount::sorts
// * (it depends on object that will headCountStrategy consits)
// * \param vec - vector that is needed to be sort
// * \param c - supporting vector
// */
//template <class T>
//void CompositeHeadCount<T>::sort(std::vector<int> &vec) {
//    helper.clear();
//    int maxim = vec[0];
//    for (unsigned int i = 1; i < vec.size(); i++) {
//        if (maxim < vec[i]) maxim = vec[i];
//    }
//    //std::vector<int> c(maxim);
//    for (int i = 0; i <= maxim; i++) {
//        helper.push_back(0);
//    }
//    for (unsigned int i = 0; i < vec.size(); i++) {
//        helper[vec[i]] = helper[vec[i]] + 1;
//    }
//    headCountStrategy->sort(vec);
//}

///*!
// * \brief SimplAlgHeadCount::sorts simplest algorithm of headCount
// * \details it just go in vecHelp and gives indexes of it to  our vec (go to wiki for details)
// * \param vec - vector that is needed to be sort
// * \param vecHelp - supporting vector
// */
//template <class T>
//void SimplAlgHeadCount<T>::sort(std::vector<int> &vec) {
//    int b = 0;
//        for (unsigned int i = 0; i < helper.size(); i++){
//            for (int j = 0; j < helper[i]; j++) {

//                vec[b] = i;         //!
//                b = b + 1;
//            }
//        }
//}

///*!
// * \brief RobustAlgHeadCount::sorts "strong" algorithm
// * \details make sorted "finalvec" from elements of vector "vec"
// */
//template <class T>
//void RobustAlgHeadCount<T>::sort(std::vector<int> &vec) {
//    std::vector<int> finalVec;
//    for (unsigned int i = 0; i < vec.size(); i++){
//            finalVec.push_back(0);
//        }
//    for (unsigned int i = 1; i < helper.size(); i++){
//        helper[i] = helper[i] + helper[i - 1];
//    }
//    for (int j = vec.size() - 1; j >= 0; j--) {
//        helper[vec[j]] = helper[vec[j]] - 1;
//        finalVec[helper[vec[j]]] = vec[j];
//    }
//    for (unsigned int i = 0; i < vec.size(); i++) {
//        vec[i] = finalVec[i];
//    }
//}

////******************************************************************************************

///*!
// * \brief Radix::sort main function of class Radix
// */
//template <class T>
//void Radix<T>::sort(std::vector<int> &vec) {
//   sorts(vec);
//}

///*!
// * \brief Radix::sorts variable next(object of class of needed algorithm) call class MsdRadix or LsdRadix
// *  that represents needed algorithm
// */
//template <class T>
//void Radix<T>::sorts(std::vector<int> &vec) {
//    next->sorts(vec);
//}

///*!
// * \brief MsdRadix::msd_radix_sort - msd radix
// * \param first - first element of sub-array
// * \param last - last element of sub-array
// * \param msb - number of current bit
// */
//template <class T>
//void MsdRadix<T>::msd_radix_sort(int *first, int *last, int msb)
//{
//    if (first != last && msb >= 0)
//    {

//        int *mid = std::partition(first, last, Radix_test<T>(msb));

//        //! decrement most-significant-bit
//        msb--;

//        //!sort left partition
//        msd_radix_sort(first, mid, msb);

//        //!sort right partition
//        msd_radix_sort(mid, last, msb);
//    }
//}

///*!
// * \brief MsdRadix::sort - main function of msd radix sort
// */
//template <class T>
//void MsdRadix<T>::sorts(std::vector<int> &vec) {
//    int num[vec.size()];
//    std::copy( vec.begin(), vec.end(), num );

//    msd_radix_sort(num, num + vec.size());

//    for (unsigned int i = 0; i < vec.size(); i++) {
//        vec[i] = num[i];
//   }
//}

////******************************************************************************************

///*!
// * \brief LsdRadix::sort - main function of lsd radix sort
// * \param vec - vector that is needed to be sort
// */
//template <class T>
//void LsdRadix<T>::sorts(std::vector<int> &vec) {
//    int m = getMax(vec);

//    for (int exp = 1; m/exp > 0; exp *= 10)
//        countSort(vec, exp);
//}

///*!
// * \brief LsdRadix::countSort - a function to do counting sort of vec
// *  according to the digit represented by exp
// * \param exp - grade of number (tenth/hundreds)
// */
//template <class T>
//void LsdRadix<T>::countSort(std::vector<int> &vec, int exp) {
//    int n = vec.size();
//        int output[n]; // output array
//        int i, count[10] = {0};

//        for (i = 0; i < n; i++)
//            count[ (vec[i]/exp)%10 ]++;

//        for (i = 1; i < 10; i++)
//            count[i] += count[i - 1];

//        for (i = n - 1; i >= 0; i--)
//        {
//            output[count[ (vec[i]/exp)%10 ] - 1] = vec[i];
//            count[ (vec[i]/exp)%10 ]--;
//        }

//        for (i = 0; i < n; i++)
//            vec[i] = output[i];
//}

///*!
// * \brief LsdRadix::getMax - function that return maximum of vector
// * \return maximum of the vector
// */
//template <class T>
//int LsdRadix<T>::getMax(std::vector<int> &vec) {
//    int mx = vec[0];
//    for (int i = 1; i < vec.size(); i++)
//        if (vec[i] > mx)
//            mx = vec[i];
//    return mx;
//}
