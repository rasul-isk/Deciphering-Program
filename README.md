# Deciphering-Program
In this code I solving few exercises on C++ related to cyphering/decyphering code. Descriptions of exercises provided below.


# Part 1 - Caesar cipher:

Implement a console version of the Caesar cipher in which each letter in the plaintext is replaced by a letter some fixed number of positions down the alphabet. 
https://cryptii.com/pipes/caesar-cipher

Example

Plaintext 
this is a test for your code words are separated by one space and there is no punctuation the letters can be just lower case there are no numbers either just letters a to z

e.g.Replace with a letter 1 away from the input letter i.e a->b , b-> etc… z->a

Ciphertext

uijt jt b uftu gps zpvs dpef xpset bsf tfqbsbufe cz pof tqbdf boe uifsf jt op qvoduvbujpo uif mfuufst dbo cf kvtu mpxfs dbtf uifsf bsf op ovncfst fjuifs kvtu mfuufst b up a
Use a std::string to represent the plaintext. Only include the lowercase letters a to z, separated by a single space. 

Allow the user to input how much to right shift each letter. Output the ciphertext to the screen.

# Part 2 - Code Breaker: 

Write code to read in the ciphertext file and ‘guess’ what the original text is. Use the word.txt file in this folder on blackboard ( or find a better one) , add each word  to a “map<string,bool>” variable that you create.

Given the ciphertext recreate the plaintext by shifting each letter to the left rather than the right.
e.g. a->z , b->a 

The program must guess at the plaintext, it tries a value to left shift by and test if the resulting text yields many words that can be found in the map created form words.txt. 
It outputs the decoded text to screen and the user selects ‘y’ or ‘n’ to indicate if the text has been decoded correctly. 

If the user pressed ‘n’ then the program should come up with another ‘good’ guess.

# Part 3 - A better guess:

Write code that reads in a text file (each word in the file is separated by 1 space, and contains only lowercase letters ) and it produces word frequency and letter frequency using stl::map. 
 
Using letter frequency or word frequency from the above, write code that makes a guess on how much to shift the cyphertext in part 2 to produce the original plaintext .

