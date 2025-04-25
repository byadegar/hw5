#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helpBuildWords(const string& in, string curr, int i, string floating, const set<string>& dict, set<string>& endResults); 
//pattern string, word being built, cur position, remaning floating letters, dict of words, final set that works


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> endResults; 
    helpBuildWords(in, "", 0, floating, dict, endResults); 
    return endResults; 

}

// Define any helper functions here
void helpBuildWords(const string& in, string curr, int i, string floating, const set<string>& dict, set<string>& endResults){
    //base case 
    //finished building the word 
    if (i == in.size()){
        if (floating.empty() && dict.find(curr)!= dict.end()){//if all floating letters have been used, and its in dict
            endResults.insert(curr); //add it to the end results of words
        }
        return; // your out bc you did it 
    }
    //check if position is fixed or not when your building 
    if (in[i] != '-'){
      helpBuildWords(in, curr + in[i], i+1, floating, dict, endResults); //recursive call bc you dont wanna tocuh that
    }
    else {
      //start going through the letters in the alphabet 
      for (char character = 'a'; character <= 'z'; character++){
        string next = curr + character; //build next version
        string copyFloating = floating; //copy to save so we can modify

        //chekc if character isinside of the floating string 
        bool foundInString = false; 
        int indextoRemove = 0; 
        for (int i = 0; i < copyFloating.size(); i++){
          if (copyFloating[i] == character){
            foundInString = true; 
            indextoRemove = i; 
            break; 
          }
        }
        if (foundInString == true){
          //remove the used floarting letter 
          copyFloating.erase(indextoRemove, 1); 
          helpBuildWords(in, next, i+1, copyFloating, dict, endResults); 
        }
        else {
          //letter is not floating 
          //check blanks 
          int dashesRemaining = 0; 
          for (int j = i+1; j <in.size(); j++){ //go through word to count blanks
            if (in[j] == '-'){
              dashesRemaining++; 
            }
          }
          if ((int)floating.size() <= dashesRemaining){
            //you have enough room to place more letters so you call again
            helpBuildWords(in, next, i+1, floating, dict, endResults); 
          }
        }
      }
    }
}

