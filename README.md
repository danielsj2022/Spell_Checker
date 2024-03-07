# Spell_Checker
Check for misspelled words in a file and present other words to replace it with. Coded in C++.

Using a self created hash table, a file of words is stored representing the 'dictionary'. The input file is read in line by line going word to word. If a word was found in the hashtable than it represents being spelled correctly. If a match was not found then it represents a mispelled word. When a mispelled word is found each letter is switched out 1 by 1 to create a new word and see if it is a match in the hashtable. If a match is found, it is then compared to another hashtable that contains ranked words based off usage. The lower the rank the more common. Potentail words are than stored in a vector based off rank, with the more common words in the front. Up to 10 replaceable words are presented to the user to make a change or leave as is. The file with changes is saved to output file.

To run: execute 'make' in a Unix enviroment to create the executable. The executable takes in 3 command line parameters: words.txt, input file and output file.
