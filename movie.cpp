#include "movie.h"
#include "util.h"
#include <iomanip>
#include <sstream>

Movie::Movie( std::string& name, double price, int qty, std::string& genre, std::string& rating) 
    : Product("movie", name, price,qty), genre_(genre), rating_(rating) {}

// keywords function customized for movie
std::set<std::string> Movie::keywords() const 
{
   // declaration of set to store the movie - name, parsed through 
    std::set<std::string> movie = parseStringToWords(name_);
    // declare a set to store the genre
    std::set<std::string> genre = parseStringToWords(genre_);
    // insertion of the set, from beginning to end 
    movie.insert(genre.begin(), genre.end());
    movie.insert(rating_);

    
    return movie;
}

// function to display the movie according to format, through a ostringstream
std::string Movie::displayString() const
{
      std::ostringstream ostream;
      ostream << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ <<  "\n" <<  std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left." ;
      return ostream.str();
}

// function to dump characteristics of the movie using ostringstream
void Movie::dump(std::ostream& os) const 
{
    
    Product::dump(os);

   os<< genre_ << "\n" << rating_ << "\n";
}