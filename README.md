# Word-Count-Wizard

## Introduction
In this project, I design and implement a Word Count Wizard! The system should can count the number of unique words in the entire text provided by the user, return the frequency of any word in that given text, among other operations. The wizard takes the input text and organizes it in a hash table. 

This program is created by utilizing object-oriented programming (OOP) principles and data structures (Hash Maps, Hash Tables, Heaps, Lists). All the data
structures are implemented manually  (no STL based containers used).

## Implementation

### Loading Phase: 
When the Word Count Wizard starts, the user is greeted and asked to provide: 
1) the full path of an input file
2) an optional choice of a hash function (the user is presented with a list of five possible hash functions to choose from).
If no choice is made (i.e., click enter directly), the default hash function will be used.

### Analytics: 
Next, the interface will display the count of collisions, the count of unique words and the total count of words for the hash function used, followed by a list of possible actions to invoke by the user: 
1) Find the frequency of a given word 
2) Find the word with the highest frequency
3) Quit the system.

### Functionalities:

1. The system can read and extract words (strings) from the input file and load them into a hash table.

2. The hash table data structure is implemented in a way that allows identification and storage of the unique words and their frequencies in the Wizard system. The most suitable structure of an (key, value) entry within the hash table in this case is the (word, frequency) entry pair. It is implemented as such.

3. Separate chaining is implemented to handle collisions.

4. Five different hash functions are designed and implemented. The default hash function for the system is determined by verifying performance (discussed in the Report.pdf) over a large sample of text files.
o The performance of each hash function is evaluated in terms of the number of collisions when applied on the same dataset files. The hash function causing the least number of collisions, on average across all the files, is set as the default hash function to use by the system.
o The Report.pdf documents the evaluation results of each hash function.
o A user can choose one of the other implemented hash functions to be used by the system instead of the default one if they choose to do so.

5. count_collisions method: returns the number of collisions caused by a hash function.

6. count_unique_words method: returns the number of unique words in the entire text.

7. count_words method: returns the total number of words in the text.

8. find_freq(word) method: searches for a word and returns its frequency, if it is found. Otherwise, it will return zero.

9. find_max() method: returns the word with the highest frequency. The running time of this method is O(1). The Heap data structure is used to represent the set of entries.

Tokenization:
● Each sentence is split by whitespace in order to extract words.
● Punctuation marks (“.”, “,”, “\” , “!”, “?”, “;”) attached to the end of a word are ignored.
● The cases of the alphabet are ignored (function tolower() used)
○ For example, "Token?" is counted as an instance of "token".
