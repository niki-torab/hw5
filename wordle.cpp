#ifndef RECCHECK
// For debugging
// #include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
using namespace std;
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
#endif



void wordleHelper(const string& in, const string floating, const set<string>& dict, string curr_word, int pos, set<string>& res, int floatingCounter){


	string copiedFloat = floating;

	std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	// base case and check if conditions met
	if (pos == in.length()){
		if (dict.find(curr_word) != dict.end() && floatingCounter == 0){
			res.insert(curr_word);
		}
		return;	
	}
		
	// fixed characters
	else if (in[pos] != '-'){
			curr_word[pos] = in[pos];
			return wordleHelper(in, floating, dict, curr_word, pos + 1, res, floatingCounter);
		
		}
	

		
	else{

				// counts all the dashes 
				int counter = 0;
				for (int i = pos; i < curr_word.size(); i++){
				
					if (curr_word[i] == '-'){
						
						counter += 1;

					}
				}


				int size = floatingCounter;
				// checks if the counter is equal to the length of floating char
				if (counter == size){
					// if so, iterate thru floaters nad decrement the size and erase used characters
						for (int i = 0; i < copiedFloat.size(); i++) {
							curr_word[pos] = copiedFloat[i];
							copiedFloat.erase(copiedFloat.begin() + i);
							size -= 1;
						
							// recurse
							wordleHelper(in, copiedFloat, dict, curr_word, pos + 1, res, size);
							// set the OG variables
							copiedFloat = floating;
							size = floatingCounter;

					}
				}
				// cant be true so return
				else if (size > counter)
			{
					return;
			}			
		else{
				bool enter = false;
				// iterate thru alphabet
					for (size_t i = 0; i < alphabet.size(); i++){
						enter = false;
						// check if char is a floater
						for (int j = 0; j < size; j++){
							if (alphabet[i] == copiedFloat[j]){
									enter = true;
									// erase and decrement if so 
									curr_word[pos] = alphabet[i];
									copiedFloat.erase(copiedFloat.begin() + j);
									size -= 1;
									// recurse
									wordleHelper(in, copiedFloat, dict, curr_word, pos + 1, res, size);
									// recurse
									copiedFloat = floating;
									size = floatingCounter;
							}
						}
							if (enter == false){
									curr_word[pos] = alphabet[i];
									// recurse 
									wordleHelper(in, copiedFloat, dict, curr_word, pos + 1, res, floatingCounter);
									// reset
									copiedFloat = floating;
				}
			}
		}
	}
}
	

	



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

		string fixedWord = in;
		set<string> results;
		
		int counter = floating.size();


		int pos = 0;
		wordleHelper(in, floating, dict, fixedWord, pos, results, counter);
		return results;
		

}

// Define any helper functions here
