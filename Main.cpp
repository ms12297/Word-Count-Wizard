#include<iostream>
#include <string>
#include <iomanip>
#include<fstream>
#include<sstream>
#include<math.h>
#include "List.hpp"
#include "HashNode.hpp"
#include "Heap.hpp"
#include "HashTable.hpp"

using namespace std;

//helper function to get the capacity of the HashTable
bool isPrime(int N) {
	bool isPrime = true;
	for (int i = 2; i < N; i++) {
		if (N % i == 0) {
			isPrime = false;
			break;
		}
	}
	if (N < 2) {
		isPrime = false;
	}
	return isPrime;
}

//helper function to get the capacity of the HashTable
int next_prime(int N)
{
	//base case
	if (N <= 1)
		return 2;

	int x = N;
	bool flag = false;

	//finding the smallest prime number greater than N
	while (!flag) {
		x++;
		if (isPrime(x))
			flag = true;
	}

	return x;
}

string loadData(string path) { //Tokenization and Loading
	ifstream fin;
	fin.open(path);
	if (!fin) {
		cout << "Can not open the file with the specified path...!" << endl;
		exit(-1);
	}

	//Reading and storing data in a string 
	string keys = "";
	while (!fin.eof())
	{
		string line;
		getline(fin, line, '\n');
		int spacecount = 0;
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ' ') {
				spacecount++;
			}
		}
		stringstream b(line);
		for (int j = 0; j <= spacecount; j++) {
			string key;
			if (j == spacecount) {
				b >> key;
			}
			else {
				getline(b, key, ' ');
			}
			//base-case : ignore if it is an empty line
			if (key == "") {
				continue;
			}
			//checking if key contains just one or more words eg: key could be "http://example.com"
			//also making sure every letter is lowercase
			//also making sure every letter is alphanumeric
			//making sure every letter is lowercase

			int count = 0;
			bool isHyphen = false; //for example "Gutenberg-tm" is one word
			bool isperiodmiddle = false; //for example "U.S" is one word

			for (int i = 0; i < key.size(); i++) {
				//making sure every letter is lowercase
				key[i] = tolower(key[i]);

				if (!isalnum(key[i])) {
					//key[i] = ' '; //to let us know this character is not included - NOT HERE
					count++;
					if (key[i] == '-') {
						isHyphen = true;
					}
					if (key[i] == '.' && (i != key.size() - 1)) {
						isperiodmiddle = true;
					}
				}
			}
			if (count == key.size()) { //eg: "52512" or a number in general
				keys += key + " ";
				continue;
			}

			if (isperiodmiddle && count == (key.size() / 2)) { //accounting for cases like "U.S."
				keys += key + " ";
				continue;
			}
			if (isHyphen) {
				//accounting for cases like "the"
				if (!isalnum(key[key.size() - 1])) {
					key = key.substr(0, key.size() - 1); //reducing key to disinclude last character	
				}
				if (!isalnum(key[0])) {
					key = key.substr(1, key.size()); //reducing key to disinclude first character	
				}

				keys += key + " ";
				continue;
			}
			else {
				for (int i = 0; i < key.size(); i++) {
					if (!isalnum(key[i])) {
						if (key[i] == ',' && (i != key.size() - 1)) {
							continue;
						}
						if (int(key[i]) == 39) { //the apostrophe
							continue;
						}

						key[i] = ' '; //to let us know this character is not included
						//count++;
					}
				}
				//creating a filtered string that contains the separate words in key
				stringstream y(key);
				for (int i = 0; i <= count; i++) {
					string line_filtered;

					if (i == count) {
						y >> line_filtered;
					}
					else {
						getline(y, line_filtered, ' ');
					}
					//ignore if string empty
					if (line_filtered == "") {
						continue;
					}
					//cout << line_filtered << endl;
					keys += line_filtered + " ";
				}
			}
		}
	}
	return keys;
	fin.close();
}

//======================================================
int main()
{

	cout << "Welcome to the Word Count Wizard!\n";
	cout << "Enter the full path of the input file you want to read:\n>";
	string path;
	getline(cin, path);

	//string path = "/home/user/Desktop/373-0.txt";
	string keys = loadData(path); //returns string containing every word in the file, separated by ' '
	stringstream a(keys);
	string word;
	//getting number of words
	int inp_size = 0;
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == ' ') {
			inp_size++;
		}
	}

	//getting the prime number bigger than 1.333 times the inp_size (times 1.333 to reserve at least 33% more space in the HashTable than inp_size)
	int prime_size = next_prime(int(1.333 * inp_size)); //inp_size represents the totalwords, 
	//in the worst-case, all words can be different in a file, therefore instead of unique words, 
	//total words are used to determine HashTable capacity

	//making a new HashTable of capacity that is a valid prime number
	HashTable myHashTable(prime_size);


	//selecting the user-specified hash function
	cout << "Please enter an integer (1-5) to select the respective Hash Function from the following list:\n";
	cout << "Choice:  Hash Function:		 Average Number of Collisions:\n";
	cout << "1        ASCII Value Sum       \n";
	cout << "2        Polynomial Shift      \n";
	cout << "3        Cyclic Shift          \n";
	cout << "4        Squaring ASCII Value  \n";
	cout << "5        XOR Function          \n>";
	string hashFun;
	getline(cin, hashFun);
	myHashTable.select_hashFun(hashFun);


	//Loading into HashTable
	while (a.good()) {
		getline(a, word, ' ');
		if (word == "") {
			continue;
		}
		//cout << word << endl; //testing
		myHashTable.insert(word);
	}

	//Constructing MaxHeap of entries to get maximum frequency word later
	myHashTable.makeMaxHeap();

	//Displaying results
	cout << "===================================================" << endl;
	cout << "Number of Collisions = " << myHashTable.count_collisions() << endl;
	cout << "Count of Unique Words = " << myHashTable.get_unique_words() << endl;
	cout << "Total Count of Words = " << myHashTable.getTotalsize() << endl;
	cout << "===================================================" << endl;

	string user_input, command, argument1, argument2;

	//Listing available commands before prompting for input
	cout << "\nCommands available:\n";
	cout << "find_freq <word>      finds the frequency of the specified word in the text file\n";
	cout << "findmax               finds the word with the highest frequency in the text file\n";
	cout << "help                  displays the list of available commands\n";
	cout << "exit                  exit the Word Count Wizard" << endl;

	while (true)
	{
		cout << ">";
		//clearing cin buffer

		getline(cin, user_input);

		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, argument1, ',');
		getline(sstr, argument2);

		if (command == "find_freq") {
			if (argument1 == "") {
				cout << "Invalid input\n";
			}
			else {
				//in case the user inputs "The" to search for "the" for example
				for (int i = 0; i < argument1.size(); i++) {
					argument1[i] = tolower(argument1[i]);
				}
				cout << "The word - " << argument1 << " - appears " << myHashTable.find_freq(argument1) << " times" << endl;
			}
		}
		else if (command == "findmax") cout << "The word - " << myHashTable.find_max() << " - has the highest frequency of " << myHashTable.max_occ() << endl;
		else if (command == "help") {
			cout << "Commands available:\n";
			cout << "find_freq <word>      finds the frequency of the specified word in the text file\n";
			cout << "findmax               finds the word with the highest frequency in the text file\n";
			cout << "help                  displays the list of available commands\n";
			cout << "exit                  quit the Word Count Wizard" << endl;
		}
		else if (command == "exit")	  break;
		else cout << "Invalid command !!!" << endl;
	}
	return 0;
}