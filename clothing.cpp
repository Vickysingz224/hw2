#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Clothing::Clothing(std::string& name, std::string& size,std::string& brand, double price, int qty  ) 
    : Product("clothing", name, price,qty), size_(size), brand_(brand) {}


// keywords function customized for clothing
std::set<std::string> Clothing::keywords() const
{
    
     // declaration of set to store the clothing - name, parsed through
    std::set<std::string> clothes = parseStringToWords(name_);
    // declare a set to store the brand
    std::set<std::string> brand = parseStringToWords(brand_);
    // insertion of the set, from beginning to end 
    clothes.insert(brand.begin(), brand.end());
    return clothes;
}

// function to display clothing according to format, through a ostringstream
std::string Clothing::displayString() const
{
      std::ostringstream ostream;
      ostream <<   name_ << "\n" << "Size: " << size_ << " Brand: " << brand_  << "\n" <<  std::fixed << std::setprecision(2) << price_  << "  " << qty_ << " left." ;
      return ostream.str();
}

// function to dump characteristics of clothing using ostringstream
void Clothing::dump(std::ostream& os) const 
{
    
    Product::dump(os);
    os << size_ << "\n" << brand_ << "\n";
    
}