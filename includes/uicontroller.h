#pragma once
#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>
#include <string>
#include "backendlogic.h"
#include <QString>

#ifndef NDEBUG
#define unreachable(MSG) \
    (assert(0 && MSG), abort())
#else
#define unreachable(MSG) \
    (std::fprintf(stderr, "UNREACHABLE executed at %s:%d\n", \
    __FILE__, __LINE__), abort())
#endif

using std::vector;
using std::string;

class Book{
public:
    string publisher;
    string genre;
    int yearOfPublishing;
    string author;
    string bookTitle;
    Book(){
        this->publisher = "";
        this->genre = "";
        this->yearOfPublishing = 0;
        this->author = "";
        this->bookTitle = "";
    }
    Book(string publisher,string genre,int yearOfPublishing,string autor,string bookTitle){
        this->publisher = publisher;
        this->genre = genre;
        this->yearOfPublishing = yearOfPublishing;
        this->author = autor;
        this->bookTitle = bookTitle;
    }
    bool operator==(const Book& rhs) const {
        return (this->bookTitle == rhs.bookTitle);
    }
    bool operator!=(const Book& rhs) const {
        return !(*this == rhs);
    }
    bool operator<=(const Book& rhs) const {
        return ( this->bookTitle <= rhs.bookTitle);
    }
    bool operator<(const Book& rhs) const {
        return (this->bookTitle < rhs.bookTitle);
    }
    bool operator>(const Book& rhs) const {
        return (this->bookTitle > rhs.bookTitle);
    }
    bool operator>=(const Book& rhs) const {
        return ( this->bookTitle >= rhs.bookTitle);
    }
    Book& operator= (const Book &other)
    {
        publisher = other.publisher;
        genre = other.genre;
        yearOfPublishing = other.yearOfPublishing;
        author = other.author;
        bookTitle = other.bookTitle;
        return *this;
    }
    Book(const Book &other)
    {
        publisher = other.publisher;
        genre = other.genre;
        yearOfPublishing = other.yearOfPublishing;
        author = other.author;
        bookTitle = other.bookTitle;
    }
};



class UiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString vectorBefore READ vectorBefore WRITE setVectorBefore NOTIFY vectorBeforeChanged)
    Q_PROPERTY(QString vectorAfter READ vectorAfter WRITE setVectorAfter NOTIFY vectorAfterChanged)
    Q_PROPERTY(int timePassed READ timePassed WRITE setTimePassed NOTIFY timePassedChanged)

    // random objects generation
    std::string generateRandomString(std::size_t length);
    Book generateRandomBook();

    // vector generators
    vector<int> generateRandomIntegers(int total,int from=0,int to=1000000);
    vector<string> generateRandomStrings(int total,std::size_t lenght=5);
    vector<Book> generateRandomBooks(int total);

    // make QStrings from vectors
    QString makeQString(const vector<int>& fromVector);
    QString makeQString(const vector<string>& fromVector);
    QString makeQString(const vector<Book>& fromVector);




    //------------------------------------sorting-------------------------------------------------------
    struct sortStruct{
        vector<Book> booksToSort;
        vector<int> intToSort;
        vector<string> stringsToSort;
        AbstractSortLogic* sortRealization; // move it to thread (or it's func sort)
        sortStruct():sortRealization(nullptr){}
        ~sortStruct(){delete sortRealization;}
        //clear all vectors with data so that they can be ready for new data
        void clearDataToSort();
    }adapterSort;

    // recieve new sorted vector after sort
    vector<int> recieveSortedVectorInt();
    vector<string> recieveSortedVectorString();
    vector<Book> recieveSortedVectorBook();




    //------------------------------------container------------------------------------------------------
    struct containerStruct{
        DataTypesEnums::DataTypes choosenSortType;
        AbstractContainerLogic* containerRealization; // move to thread latter

        containerStruct():containerRealization(nullptr){}
        ~containerStruct(){delete containerRealization;}
    }adapterContainer;

    DataTypesEnums::DataTypes choosenDataType;

    QString m_vectorBefore;

    QString m_vectorAfter;

    int m_timePassed;

public:
    explicit UiController(QObject *parent = nullptr);


    QString vectorBefore() const;

    QString vectorAfter() const;

    int timePassed() const
    {
        return m_timePassed;
    }

public slots:
    //------------------------------For every structure-------------------------------------------------
    // select data type Int String Book
    // need to be done at FIRST place
    void selectDataType(DataTypesEnums::DataTypes choosenType);

    //--------------------------------------------------------------------------------------

    //------------------------------container logic------------------------------------------------------
    void addDataToContainer(QString publisher,QString genre,int yearOfPublishing,QString author,QString bookTitle){

    }
    void addKey(QString publisher,QString genre,int yearOfPublishing,QString author,QString bookTitle){

    }
    void addValue(QString publisher,QString genre,int yearOfPublishing,QString author,QString bookTitle){

    }






    //-------------------------------add elements to sort-------------------------------------------------

    //add book
    void addDataToSort(QString publisher,QString genre,int yearOfPublishing,QString author,QString bookTitle);
    //add string
    void addDataToSort(QString newString);
    // add int
    void addDataToSort(int newInt);

    // generates vector with data and pushes it in adapter vector,
    // where it will be stored until flush
    void fillSortVectorWithRandomData(int total);




    //--------------------------------Basic sort logic---------------------------------------------------

    // select sort
    void selectSort(SortsEnums::SortChoice choosenSort);

    //flush our data to sort class, so that we can start sorting
    void flushDataToSort();

    // start sort
    // time tracking
    // in the end updates Q_PROPERTY vectorAfter
    void startSort();

    //-----------------------------------------


    //To Do clear all data if exit to main menu


    void setVectorBefore(QString vectorBefore);
    void setVectorAfter(QString vectorAfter);

    void setTimePassed(int timePassed)
    {
        if (m_timePassed == timePassed)
            return;

        m_timePassed = timePassed;
        emit timePassedChanged(m_timePassed);
    }

signals:
    void vectorBeforeChanged(QString vectorBefore);
    void vectorAfterChanged(QString vectorAfter);
    void timePassedChanged(int timePassed);
};
