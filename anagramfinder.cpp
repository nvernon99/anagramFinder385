/*******************************************************************************
* Name        : anagramfinder.cpp
* Author      : Nolan Vernon
* Version     : 1.0
* Date        : 5/11/2020
* Description : Finds anagrams using a dictionary txt file.
* Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
unordered_map<string, vector<string>> keyMap;
size_t maxLen = 0;
bool exist = false;


void printAna(vector<vector<string>> v){
	sort(v.begin(), v.end());
	size_t count = 0;
	bool didPrint = false;
	for (auto ia = v.begin(); ia!=v.end(); ++ia){
		vector<string> vec = *ia;
		sort(vec.begin(), vec.end());
		for (auto ib = vec.begin(); ib != vec.end(); ++ib){
			cout << *ib << endl;
			didPrint = true;
		}
		count++;
		if (count < v.size() && didPrint){
			cout << endl;
		}
	}
}

void displayFinal() {
	//bool newL = false;
	if (!exist){
		cout << "No anagrams found."<< endl;
	} else {
		cout << "Max anagram length: " << maxLen << endl;
		vector<vector<string>> result;
		unordered_map<string, vector<string> >::iterator iter;
		for (iter = keyMap.begin(); iter != keyMap.end(); iter++) {
			vector<string> temp(iter->second);
			if (temp.size() > 1) {
				vector<string> s;
				for (size_t i = 0; i < temp.size(); i++) {
					if (temp[i].length()==maxLen){
						s.push_back(temp[i]);
						//s.push_back("\n");
						//newL = true;
					}
				}
				result.push_back(s);
				/*if (newL){
					cout << "\n";
				}*/
			}
		}
		printAna(result);
	}
}
void findMaxLen() {
	unordered_map<string, vector<string> >::iterator it;
	for (it = keyMap.begin(); it != keyMap.end(); it++) {
		vector<string> temp(it->second);
		//if there is more than one match for the key, there is an anagram
		if (temp.size() > 1) {
			exist = true;
			if (temp[0].length() > maxLen) {
				maxLen = temp[0].length();
			}
		}
	}
}

void mapWords(vector<string>& words) {
	//for each element in words
	for (size_t i = 0; i < words.size(); i++) {
		string s = words[i];
		for (size_t j = 0; j<s.length(); j++){
			int aVal = int(s[j]);
			if (!((aVal>64 && aVal<91) || (aVal>96 && aVal<123) || aVal == 39 || aVal == 45)){
				i++;
			}
			s[j]=tolower(s[j]);
		}
		sort(s.begin(), s.end());
		//if (s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'-"){}
		vector<string> v;
		if (keyMap.find(s) == keyMap.end()) {
			v.push_back(words[i]);
			keyMap.insert(make_pair(s, v));
		}
		else {
			v = keyMap[s];
			v.push_back(words[i]);
			keyMap[s] = v;
		}
	//delete &s;	
	//delete &v;
	}
	
	
}

bool load_words_from_file(const string &filename) {
	ifstream input_file(filename.c_str());
	//can't find file
	if (!input_file) {
		cerr << "Error: File '" << filename << "' not found." << endl;
		return false;
	}
	input_file.exceptions(ifstream::badbit);
	string line;
	vector<string> data;
	try {
		while (getline(input_file, line)) {
			//cout << line << endl;
			data.push_back(line);
		}
		input_file.close();
	}
	catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << filename << "'.";
		cout << "load_values returning false";
		return false;
	}
	//input_file.close();
	
	//data is now a vector of my dictionary words
	//return data;
	mapWords(data);
	data.clear();
	return true;
}

void clearMem(){
	keyMap.clear();

}

int main(int argc, char * const argv[]) {
	//incorrect number of arguments
	if (argc != 2){
		cerr << "Usage: ./anagramfinder <dictionary file>" << endl;
		return 1;
	}
	//load from file
	if (!load_words_from_file(argv[1])) {
		return 1;
	}
	/*vector<string> dict = load_words_from_file(argv[1]);
	if (dict == null){
		return 1;
	}*/
	//mapWords(dict);
	findMaxLen();;
	displayFinal();
	//clear up memory
	clearMem();
	return 0;
}