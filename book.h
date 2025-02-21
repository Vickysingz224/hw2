#include "product.h"
#include <string>
#include <set>
#include "util.h"

class Book : public Product{
public:
     
    Book( std::string& name,std::string& author,  std::string& ISBN,  double price, int qty);
    // declaration of functions  
    std::set<std::string> keywords() const ;
    std::string displayString() const ;
    void dump(std::ostream& os) const ;

private:
    
    std::string ISBN_;
    std::string author_;
};