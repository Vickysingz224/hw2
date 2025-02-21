#include "datastore.h"
#include "product.h"
#include "user.h"
#include <map>
#include <vector>
#include <string>


class MyDataStore : public DataStore{
public:
   MyDataStore();
    virtual ~MyDataStore();

    virtual void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u);

    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    virtual void dump(std::ostream& ofile);
    
    void addToCart(std::string& username, int hitIdx);

    void viewCart(std::string& username);

    void buyCart(std::string& username);

private:

   // declaration of private variables 
   std::map<std::string, User*> users_;

   std::map<std::string, std::set<Product*>> keywordIndex_;

   std::map<std::string, std::vector<Product*>> carts_;

   std::set<Product*> products_;

   std::vector<Product*> lastSearch_;

   bool isUserValid(const std::string& username) const;

};
