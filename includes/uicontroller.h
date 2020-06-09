#pragma once
#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>
#include <string>
#include "includes/backendlogic.h"

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
    vector<Book> booksToSort;
   // vector<string>
    AbstractSortLogic* sortRealization; // move it to thread (or it's func sort)
public:
    explicit UiController(QObject *parent = nullptr);


public slots:
    void addBook(string publisher,string genre,int yearOfPublishing,string author,string bookTitle){
        booksToSort.push_back({publisher,genre,yearOfPublishing,author,bookTitle});
    }
//    void addString(string newString){

//    }
    void chooseSort(SortsEnums::SortChoice choosenSort,DataTypesEnums::DataTypes choosenType){
        if(sortRealization){
           delete sortRealization;
           sortRealization = nullptr;
        }
        switch (choosenType) {
        case DataTypesEnums::DataTypes::INT : sortRealization = new SortLogic<int>();
            break;
        case DataTypesEnums::DataTypes::STRING : sortRealization = new SortLogic<string>();
            break;
        case DataTypesEnums::DataTypes::BOOK : sortRealization = new SortLogic<Book>();
            break;
        default:qDebug()<<"not supported type";  break;
        }
        sortRealization->selectSort(choosenSort);
    }


    void startSort(){
        sortRealization->sort();
    }
};
