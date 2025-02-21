#include "product.h"
#include <set>
#include <string>
#include "util.h"

class Movie : public Product{
public:
    Movie(std::string& name, double price, int qty, std::string& genre, std:: string& rating);
    // declaration of functions  
    std::set<std::string> keywords() const ;
    std::string displayString() const ;
    void dump(std::ostream& os) const ;

private:
    std::string genre_;
    std::string rating_;
};