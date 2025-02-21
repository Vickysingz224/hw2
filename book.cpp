#include "book.h"
#include "util.h"
#include "product.h"
#include <sstream>
#include <iomanip>

// constructor for book that inherits characteristics from Product
Book::Book(std::string& name, std::string& author, std::string& ISBN, double price, int qty)
    : Product ( "book", name, price,qty), ISBN_(ISBN), author_(author){}

// keywords function customized for books
std::set<std::string> Book::keywords() const 
{
    // declaration of set to store the book - name, parsed through
    std::set<std::string> book = parseStringToWords(name_);
     // declare a set to store the author
    std::set<std::string> author = parseStringToWords(author_);
    // insertion of the set, from beginning to end 
    book.insert(author.begin(), author.end());
    
    book.insert(ISBN_);
    return book;
}

// function to display book according to format, through a ostringstream
std::string Book::displayString() const
{
      std::ostringstream ostream;
      ostream  << name_ << "\n" << "Author: " << author_ << " ISBN: " << ISBN_  << "\n" <<  std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left." ;
      return ostream.str();
}

// function to dump characteristics of the book using ostringstream
void Book::dump(std::ostream& os) const 
{
   
   Product::dump(os);
   os<< ISBN_ << "\n" << author_ << "\n";
   
}