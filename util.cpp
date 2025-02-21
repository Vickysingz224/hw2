#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/

// this function parses the input string of rawWords into words to be used in various operations in the program
std::set<std::string> parseStringToWords(string rawWords)
{
    // declare variables to store the set of words, the results will be stored in and a temp string
    std::set<std::string> wordSet;
    std::string temp;

    // this conversion is for case insensitivity
    rawWords = convToLower(rawWords);
     
     // iterate through the input string 
     for(size_t i=0; i < rawWords.size(); i++)
     {
      // declare a char to store each character of rawWords
      char a = rawWords[i];
      
      // cehck if the character is between a- z, or a valid number 0-9
      if((a >= 'a' && a <='z')||(a >= '0' && a <= '9'))
      { 
         // add to individual word
         temp += a;
      }
      // check if the word is greater than 2 characters, meaning it can be added to result set
      else
      {
         if(temp.size() >= 2)
         {
           wordSet.insert(temp);
         }
         
         temp.clear();
      }
     }
     // check outside of iteration if temp is gerater than 2, and add the word
     if(temp.size() >= 2)
     {
        wordSet.insert(temp);
     }

     return wordSet;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
