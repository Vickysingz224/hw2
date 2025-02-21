#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
// this function iterates thrugh two sets and returns the instersection between the two
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
   // create a set to store the intersection
   std::set<T> resultSet;
   // declare an iterator that is equal to the start of the first set
   typename std::set<T>::const_iterator it1 = s1.begin();

  // loops while the iterator is not equal to the end of the first set
   while (it1 != s1.end())
   {
      // checks if that element in dereferenced it1 is in set2, and then adds to insersection result set
     if(s2.find(*it1) != s2.end())
     {
        resultSet.insert(*it1);
     }

     ++it1;
   }
   return resultSet;

}

template <typename T>
// this function iterates through set2 and adds its contents to set1, creating a union result set
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

  // declare a set equal to s1 to store the union
  std::set<T> resultSet = s1;

  // declare an iterator equal to start of set2
  typename std::set<T>::const_iterator it2 = s2.begin();

   // add the contents of s1 to s2, iterating through s2
   while (it2 != s2.end())
   {
     
        resultSet.insert(*it2);
        ++it2;
   }

  return resultSet;
       

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
