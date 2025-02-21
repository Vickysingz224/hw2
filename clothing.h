#include "product.h"
#include <set>
#include <string>
#include "util.h"

class Clothing : public Product{
public:
    Clothing( std::string& name, std::string& size, std::string& brand, double price, int qty  );
    // declaration of functions  
    std::set<std::string> keywords() const ;
    std::string displayString() const ;
    void dump(std::ostream& os) const ;

private:
    std::string size_;
    std::string brand_;
    
};