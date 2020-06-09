#include "includes/uicontroller.h"

std::string UiController::generateRandomString(std::size_t length)
{
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

Book UiController::generateRandomBook(){
    Book newBook(
                generateRandomString(5),
                generateRandomString(5),
                Randomizing::generateRandomInt(0,2020),
                generateRandomString(5),
                generateRandomString(5)
                );
    return newBook;
}

QString UiController::makeQString(const vector<int> &fromVector){
    QString newString;
    for(size_t i=0;i<fromVector.size();i++){
        if((i+1)!=fromVector.size()){
            newString.push_back(QString::number(fromVector[i]));
        }
        else{
            newString.push_back(QString::number(fromVector[i])+",");
        }
    }
    return newString;
}

QString UiController::makeQString(const vector<std::string> &fromVector){
    QString newString;
    for(size_t i=0;i<fromVector.size();i++){
        if((i+1)!=fromVector.size()){
            newString.push_back(QString::fromStdString(fromVector[i]));
        }
        else{
            newString.push_back(QString::fromStdString(fromVector[i])+",");
        }
    }
    return newString;
}

QString UiController::makeQString(const vector<Book> &fromVector){
    QString newString;
    Book currenBook;
    for(size_t i=0;i<fromVector.size();i++){
        currenBook= fromVector[i];
        if((i+1)!=fromVector.size()){
            newString.push_back("|| Title: " + QString::fromStdString(currenBook.bookTitle)
                                + "; Author: " + QString::fromStdString(currenBook.author)
                                + "; Genre: " + QString::fromStdString(currenBook.genre)
                                + "; Publisher: " + QString::fromStdString(currenBook.publisher)
                                + "; Year of publishing: " + QString::number(currenBook.yearOfPublishing)
                                + "||, "
                                );
        }
        else{
            newString.push_back("|| Title: " + QString::fromStdString(currenBook.bookTitle)
                                + "; Author: " + QString::fromStdString(currenBook.author)
                                + "; Genre: " + QString::fromStdString(currenBook.genre)
                                + "; Publisher: " + QString::fromStdString(currenBook.publisher)
                                + "; Year of publishing: " + QString::number(currenBook.yearOfPublishing)
                                + "|| "
                                );
        }
    }
    return newString;
}

UiController::UiController(QObject *parent) : QObject(parent)
{

}

QString UiController::vectorBefore() const
{
    return m_vectorBefore;
}

QString UiController::vectorAfter() const
{
    return m_vectorAfter;
}
//book
void UiController::addDataToSort(QString publisher, QString genre, int yearOfPublishing, QString author, QString bookTitle){
    adapterSort.booksToSort.push_back({publisher.toStdString(),genre.toStdString(),yearOfPublishing,author.toStdString(),bookTitle.toStdString()});
    // update Q_PROPERTY vectorBefore
    setVectorBefore(makeQString(adapterSort.booksToSort));
}
// string
void UiController::addDataToSort(QString newString){
    adapterSort.stringsToSort.push_back(newString.toStdString());
    // update Q_PROPERTY vectorBefore
    setVectorBefore(makeQString(adapterSort.stringsToSort));
}
//int
void UiController::addDataToSort(int newInt){
    adapterSort.intToSort.push_back(newInt);
    // update Q_PROPERTY vectorBefore
    setVectorBefore(makeQString(adapterSort.intToSort));
}

void UiController::fillSortVectorWithRandomData(int total)
{
    //update Q_PROPERTY vectorBefore
    switch (adapterSort.choosenSortType) {
    case DataTypesEnums::DataTypes::INT :{
        adapterSort.intToSort = generateRandomIntegers(total);
        setVectorBefore(makeQString(adapterSort.intToSort));
    }
        break;
    case DataTypesEnums::DataTypes::STRING :{
        adapterSort.stringsToSort = generateRandomStrings(total);
        setVectorBefore(makeQString(adapterSort.stringsToSort));
    }
        break;
    case DataTypesEnums::DataTypes::BOOK :{
        adapterSort.booksToSort = generateRandomBooks(total);
        setVectorBefore(makeQString(adapterSort.booksToSort));
    }
        break;
    default:  unreachable("Unhandled special enum constant!");
    }
}

void UiController::selectSortType(DataTypesEnums::DataTypes choosenType){
    if(adapterSort.sortRealization){
        delete adapterSort.sortRealization;
        adapterSort.sortRealization = nullptr;
    }
    switch (choosenType) {
    case DataTypesEnums::DataTypes::INT : adapterSort.sortRealization = new SortLogic<int>();
        break;
    case DataTypesEnums::DataTypes::STRING : adapterSort.sortRealization = new SortLogic<string>();
        break;
    case DataTypesEnums::DataTypes::BOOK : adapterSort.sortRealization = new SortLogic<Book>();
        break;
    default:  unreachable("Unhandled special enum constant!");
    }
    adapterSort.choosenSortType = choosenType;
    adapterSort.clearDataToSort();
}

void UiController::selectSort(SortsEnums::SortChoice choosenSort){
    adapterSort.sortRealization->selectSort(choosenSort);
}

void UiController::flushDataToSort(){
    AbstractSortLogic* baseClass;

    switch (adapterSort.choosenSortType) {
    case DataTypesEnums::DataTypes::INT :{
        baseClass = adapterSort.sortRealization;
        SortLogic<int>* intDerivedClass = dynamic_cast<SortLogic<int>*>(baseClass);
        intDerivedClass->vectorToSort = adapterSort.intToSort;
    }
        break;
    case DataTypesEnums::DataTypes::STRING :
    {
        baseClass = adapterSort.sortRealization;
        SortLogic<string>* stringDerivedClass = dynamic_cast<SortLogic<string>*>(baseClass);
        stringDerivedClass->vectorToSort = adapterSort.stringsToSort;
    }
        break;
    case DataTypesEnums::DataTypes::BOOK :
    {
        baseClass = adapterSort.sortRealization;
        SortLogic<Book>* BookDerivedClass = dynamic_cast<SortLogic<Book>*>(baseClass);
        BookDerivedClass->vectorToSort = adapterSort.booksToSort;
    }
        break;
    default:  unreachable("Unhandled special enum constant!");
    }
}

vector<std::string> UiController::recieveSortedVectorString()
{
    AbstractSortLogic* baseClass = adapterSort.sortRealization;
    SortLogic<string>* derivedClass = dynamic_cast<SortLogic<string>*>(baseClass);
    return derivedClass->vectorToSort;
}

vector<Book> UiController::recieveSortedVectorBook()
{
    AbstractSortLogic* baseClass = adapterSort.sortRealization;
    SortLogic<Book>* derivedClass = dynamic_cast<SortLogic<Book>*>(baseClass);
    return derivedClass->vectorToSort;
}

vector<int> UiController::recieveSortedVectorInt()
{
    AbstractSortLogic* baseClass = adapterSort.sortRealization;
    SortLogic<int>* derivedClass = dynamic_cast<SortLogic<int>*>(baseClass);
    return derivedClass->vectorToSort;
}

void UiController::startSort(){


    // TO DO time before
    adapterSort.sortRealization->sort();
    // TO DO time after

    //update Q_PROPERTY vectorAfter
    switch (adapterSort.choosenSortType) {
    case DataTypesEnums::DataTypes::INT : setVectorAfter(makeQString(recieveSortedVectorInt())) ;
        break;
    case DataTypesEnums::DataTypes::STRING :setVectorAfter(makeQString(recieveSortedVectorString())) ;
        break;
    case DataTypesEnums::DataTypes::BOOK :setVectorAfter(makeQString(recieveSortedVectorBook())) ;
        break;
    default:  unreachable("Unhandled special enum constant!");
    }
}

vector<int> UiController::generateRandomIntegers(int total, int from, int to){
    vector<int> newInts;
    for(int i = 0;i<total;i++){
        newInts.push_back(Randomizing::generateRandomInt(from,to));
    }
    return newInts;
}

vector<std::string> UiController::generateRandomStrings(int total, std::size_t lenght){
    vector<string> newStrings;
    for(int i = 0;i<total;i++){
        newStrings.push_back(generateRandomString(lenght));
    }
    return newStrings;
}

vector<Book> UiController::generateRandomBooks(int total){
    vector<Book> newBooks;
    for(int i = 0;i<total;i++){
        newBooks.push_back(generateRandomBook());
    }
    return newBooks;
}

void UiController::setVectorBefore(QString vectorBefore)
{
    if (m_vectorBefore == vectorBefore)
        return;

    m_vectorBefore = vectorBefore;
    emit vectorBeforeChanged(m_vectorBefore);
}

void UiController::setVectorAfter(QString vectorAfter)
{
    if (m_vectorAfter == vectorAfter)
        return;

    m_vectorAfter = vectorAfter;
    emit vectorAfterChanged(m_vectorAfter);
}

void UiController::sortStruct::clearDataToSort(){
    booksToSort.clear();
    intToSort.clear();
    stringsToSort.clear();
}
