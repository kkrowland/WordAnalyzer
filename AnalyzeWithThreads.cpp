#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

// TODO::Update functions to return multiple results in the case that there are multiple 
// words with the same length, frequency, etc. 

vector<string> getWordList(string txtFileName);
void getLongestWord(vector<string> wordList);
void getShortestWord(vector<string> wordList);
void getMostFrequentWord(vector<string> wordList);
void getLeastFrequentWord(vector<string> wordList);
string removeSpecialCharacter(string s);
void getAverageWordLength(vector<string> wordList);
const string DIVIDER = "-----------------------------------------------------------\n";
int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    vector<string> wordList = getWordList("source.txt");
    thread longestWord(getLongestWord, wordList);
    thread shortestWord(getShortestWord, wordList);
    thread mostFrequentword(getMostFrequentWord, wordList);
    thread avgWordLength(getAverageWordLength, wordList);
    longestWord.join();
    shortestWord.join();
    mostFrequentword.join();
    avgWordLength.join();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Elapsed time in seconds: " << chrono::duration_cast<std::chrono::seconds> (end - begin).count() << endl;
}

vector<string> getWordList(string txtFileName)
{
    vector<string> wordList {};

    ifstream wordFile(txtFileName);
    string wordString {};
    string s {};
    if(wordFile.is_open())
    {
        string temp = {};
        while (getline(wordFile, temp))
        {
            wordString += " " + temp;
        }
    }
    stringstream ss(wordString);
    while (getline(ss, s, ' '))
    {
        s = removeSpecialCharacter(s);
        wordList.push_back(s);
    }

    return wordList;
}

string removeSpecialCharacter(string s)
{   
    string trimmedString = s;

    for (int i = 0; i < trimmedString.size(); i++) {
 
        // Finding the character whose
        // ASCII value fall under this
        // range
        if (trimmedString[i] < 'A' || trimmedString[i] > 'Z' && trimmedString[i] < 'a'
            || trimmedString[i] > 'z') {
            // erase function to erase
            // the character
            trimmedString.erase(i, 1);
            i--;
        }
    }
    return trimmedString;
}

void getLongestWord(vector<string> wordList)
{
    cout<<"Getting longest word..."<<endl;
    vector<string> returnWords {};
    map<string, int> wordIndex {};
    int longestLength  {-1};

    for (auto word : wordList)
    {
        int length = word.size();
        map<string, int>::iterator iter = wordIndex.find(word);
        if(iter == wordIndex.end())
        {
            wordIndex[word] = length;
        }

        if (length > longestLength)
        {
            longestLength = {length};
        }
    }

    map<string, int>::iterator iter = wordIndex.begin();
    for (iter; iter != wordIndex.end(); iter++)
    {
        if (iter->second == longestLength)
        {
            returnWords.push_back(iter->first);
        }
    }

    cout<<"Longest Words: ";
    for(auto word : returnWords)
    {
        cout << word << " ";
    }
    cout << endl << DIVIDER;

}

void getShortestWord(vector<string> wordList)
{
    cout<<"Getting shortest word..."<<endl;
    vector<string> returnWords {};
    map<string, int> wordIndex {};
    int shortestWordLength  {-1};

    for (auto word : wordList)
    {
        int length = word.size();
        map<string, int>::iterator iter = wordIndex.find(word);
        if(iter == wordIndex.end())
        {
            wordIndex[word] = length;
        }
        
        // 1. Word must be shorter than current shortest length
        // 2. Current shortest length can't be -1. If it is, that means this is our first word of the list. 
        // 3. Length must be greater than zero. We don't count empty strings
        // 4. Word cannot be a newline or any kind of special character. Need to update with some kinda regex to weed out all special characters.
        if ((length < shortestWordLength || shortestWordLength == -1) && (length > 0 && word != "\n"))
        {
            shortestWordLength = {length};
        }
    }

    map<string, int>::iterator iter = wordIndex.begin();
    for (iter; iter != wordIndex.end(); iter++)
    {
        if (iter->second == shortestWordLength)
        {
            returnWords.push_back(iter->first);
        }
    }
    
    cout << "Shortest words: ";
    for(auto word : returnWords)
    {
        cout << word << " ";
    }
    cout << endl << DIVIDER;
}

void getMostFrequentWord(vector<string> wordList)
{
    cout<<"Getting most frequent word..."<<endl;
    map<string, int> frequencyMap {};
    int highestFreq {};
    string mostFreqStr {};
    for (auto s : wordList)
    {   
        map<string, int>::iterator iter = frequencyMap.find(s);
        if (iter == frequencyMap.end())
        {
            frequencyMap[s] = 1;
        }
        else
        {
            iter->second += 1;
        }
    }

    //now iterate through the map to find the key with the highest value
    map<string, int>::iterator iter {};
    for (iter = frequencyMap.begin(); iter != frequencyMap.end(); iter++)
    {
        if (iter->second > highestFreq)
        {
            highestFreq = iter->second;
            mostFreqStr = iter->first;
        }
    }

    cout << "Most Frequent word: " << mostFreqStr << endl;
    cout << DIVIDER;
}

void getLeastFrequentWord(vector<string> wordList)
{
    
}

void getAverageWordLength(vector<string> wordList)
{
    cout<<"Getting average word length..."<<endl;
    int totalLength {};
    int avgLength {};
    int numWords {};

    for (auto s : wordList)
    {
        int len = s.size();
        totalLength += len;
        numWords++;
    }
    cout << "Num of words: " << to_string(numWords) << endl;
    avgLength = totalLength/numWords;

    cout << "Average word length: " << to_string(avgLength) << endl;
    cout << DIVIDER;
}
