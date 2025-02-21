#include "mydatastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

MyDataStore::MyDataStore() 
{

}

// destructor for mydatastore 
MyDataStore::~MyDataStore() 
{
    // declaration of an iterator, that iterates through products, and deallocates the memeory of each element 
    set<Product*>::iterator it1;
    for (it1 = products_.begin(); it1 != products_.end(); ++it1) 
    {
        delete *it1;
    }
    // declaration of an iterator, that iterates through users and deallocates the memeory of each element 
    map<string, User*>::iterator it2;
    for (it2 = users_.begin(); it2 != users_.end(); ++it2)
    {
        delete it2->second;
    }
}

void MyDataStore::addProduct(Product* p) 
{
    // checks if p is null, and simply returns 
    if (p == nullptr)
    {
        return;
    } 
     
     // inserts the product p, into the set of products 
    products_.insert(p);
    
    // declare a strings set of words, that holds the keywords of that product
    set<string> words = p->keywords();
    
    // declares an iterator and iterates through the set of words
    set<string>::iterator it3;
    for (it3 = words.begin(); it3 != words.end(); ++it3) 
    { 
         // these keywords are convereted to lower case - case sensitivity 
        string lower = convToLower(*it3);
        // inseretd into a map of keywords called keywordIndex
        keywordIndex_[lower].insert(p);
    }
}

void MyDataStore::addUser(User* u) 
{
    // checks if the user is null, and simply returns
    if (u == nullptr)
    {
         return;
    }

    // declares a string user, which holds the name of user (in lowercase )
    string user = convToLower(u->getName());
    users_[user] = u;
    // sets the cart at that user to a product, not defined specifically yet
    carts_[user] = vector<Product*>();
}


vector<Product*> MyDataStore::search(vector<string>& terms, int type) 
{
    
    lastSearch_.clear();
    // checks if the terms are empty, and just returns lastSearch which is empty at this point 
    if (terms.empty()) 
    {
        return lastSearch_;
    }

    // declaration of an iterator that iterates through terms and converts the elements for case sensitivity 
    vector<string>::iterator it4;
    for (it4 = terms.begin(); it4 != terms.end(); ++it4) 
    {
        *it4 = convToLower(*it4);
    }
     
    set<Product*> prodResults;
    
    //  checks if the type is 0, indicating an and search
    if (type == 0) 
    {
        // checks if the element at beginning of terms, is not equal to the end
        if (keywordIndex_.find(terms[0]) != keywordIndex_.end()) 
        {
             // sets product results to the term found in the keyword map
            prodResults = keywordIndex_[terms[0]];
            // iterates through terms, to clear product results if the terms[i] is in the keyword map
            for (size_t i = 1; i < terms.size(); i++) 
            {
                if (keywordIndex_.find(terms[i]) == keywordIndex_.end()) 
                {
                    prodResults.clear();
                    break;
                }
                // sets product results to the setintersection of the search terms
                prodResults = setIntersection(prodResults, keywordIndex_[terms[i]]);
            }
        }
        else
        {
          prodResults.clear();
        }
    }
    // carries out or search operation indiacting union
    else 
    {
        // declartion of an iterator and iterates through terms , to check if the element of the keyword map is not equal to end
        vector<string>::iterator it5;
        for (it5 = terms.begin(); it5 != terms.end(); ++it5) 
        {
            if (keywordIndex_.find(*it5) != keywordIndex_.end()) 
            {
               // set union called her to merge two input sets
                prodResults = setUnion(prodResults, keywordIndex_[*it5]);
            }
        }
    }

    // stores the results for ADD operation
    lastSearch_.assign(prodResults.begin(), prodResults.end());
    return lastSearch_;
}

void MyDataStore::dump(ostream& ofile) 
{
    // couts products and iterates through products to display with ofile
    ofile << "<products>" << endl;
    set<Product*>::iterator it6;

    for (it6 = products_.begin(); it6 != products_.end(); ++it6) 
    {
        (*it6)->dump(ofile);
    }

    ofile << "</products>" << endl;
    // displays users and iterates through users to display with ofile
    ofile << "<users>" << endl;
    map<string, User*>::iterator it7;
    for (it7 = users_.begin(); it7 != users_.end(); ++it7)
    {
        it7->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart( string& username, int hitIndex) 
{
    // declares a string for lower username
    string lowerU = convToLower(username);
    
    // checks if the product vector is empty, or if teh hit index is out of range
    if (lastSearch_.empty() || hitIndex < 0 || hitIndex >= static_cast<int>(lastSearch_.size())) 
    {
        cout << "Invalid request" << endl;
        return;
    }
    
    // checks if username is valid
    if (!isUserValid(lowerU))
    {
        cout << "Invalid request" << endl;     return;
    }
    
    // adding to cart operation, using push_back function
    carts_[lowerU].push_back(lastSearch_[hitIndex]);
}

void MyDataStore::viewCart( string& username) 
{
    // declares a string for lower username
    string lowerU2 = convToLower(username);
    
    //checks if the user is valid, and if not, displays error message 
    if (!isUserValid(lowerU2))
    {
        cout << "Invalid username" << endl;
        return;
    }
    
    // declaration of a cart
    const vector<Product*>& cart = carts_[lowerU2];
    // iterates through the cart, to display the items 
    for (size_t i = 0; i < cart.size(); i++) 
    {
        cout << "Item " << i + 1 << endl;
        cout << cart[i]->displayString() << endl;
        cout << endl;
    }
}

void MyDataStore::buyCart( string& username) 
{
    // declares a string for lower username
    string lowerU = convToLower(username);
    
    // checks if the user is valid, and if not an error message is displayed 
    if (!isUserValid(lowerU)) 
    {
        cout << "Invalid username" << endl;
        return;
    }
    
    // declaration of a user, cart and a vector varible named remaining
    User* user = users_[lowerU];
    vector<Product*>& cart = carts_[lowerU];
    vector<Product*> remaining;
    
    // iterates throgh the cart 
    vector<Product*>::iterator it8;
    for (it8 = cart.begin(); it8 != cart.end(); ++it8)
    {
        // checks if the quantity of the item is greater than 0, (it's in stock) and the user balance is greater than, equal to the price (customer can buy it)
        if ((*it8)->getQty() > 0 && user->getBalance() >= (*it8)->getPrice())
        {
            // price if deducted from the user 
            user->deductAmount((*it8)->getPrice());
            // quantity subtracted 
            (*it8)->subtractQty(1);
        }
        else
        {
            // put remaining items in remaining 
            remaining.push_back(*it8);
        }
    }
    
    cart = remaining;
}

// checks if the username is in the map of users 
bool MyDataStore::isUserValid(const string& username) const 
{
    return users_.find(username) != users_.end();
}


