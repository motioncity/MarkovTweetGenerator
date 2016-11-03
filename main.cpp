#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include<unordered_map>
#include <algorithm>
#include <time.h>


using namespace std;


vector<string> wordvector;
string startString;
string startofEnd;
unordered_map<string, vector<string> > chainMap;
string endString = "THE END";


/*Function responsible for the creation of the markov chains, which are of length 1*/
void makeChains(vector<string>& wVector)
{
  startString = wVector[0] + " " + wVector[1];
  startofEnd = wVector[1];
  string currentString = wVector[0] + " " + wVector[1];
  chainMap.insert(make_pair(currentString, vector<string>()));

    for (int i=0; i<wVector.size()-3;i++){

        if(currentString != wVector[i+2] +" " +wVector[i+3])
        {
            chainMap[currentString].push_back(wVector[i+2]);
            if ( chainMap.find(wVector[i+1] +" " +wVector[i+2]) == chainMap.end() ) {
                // not found
                currentString = wVector[i+1] + " "+wVector[i+2];
                chainMap.insert(make_pair(currentString, vector<string>()));
                } 
            else {
            
                currentString = wVector[i+1] + " " +wVector[i+2];
            }
        }
        else
        {
         chainMap[currentString].push_back(wVector[i+2]);   
        }
       
    }
     chainMap[currentString].push_back("THE_END");
     
}

/*Function needed for creating the tweets*/
void generateTweet()
{
    string tweet = startString;
    
   
    string currentWord = startString;
    vector <string> currentVector = chainMap[currentWord];
    
    
    srand(time(NULL));
    while((currentWord != "THE_END" ) || (tweet.size()<140))
    {

        currentWord = currentVector[rand() % currentVector.size()];
        string possibleTweet = tweet + currentWord;
        
         if ((currentWord == "THE_END") || (possibleTweet.size()>138))
        {
            tweet+=".";
            break;
        }
        
        tweet = tweet + " " + currentWord;
        currentVector = chainMap[startofEnd+" "+currentWord];
        startofEnd = currentWord;

    }
    
    cout << tweet << endl;
    cout <<  tweet.size() << endl;
}

int main(int argc, char* argv[])
{
    
      
       ifstream file;
       file.open (argv[1]);
       
       
       
    if (!file.is_open()) return(0);
    string word;
    while (file >> word)
    {
         for (int i = 0, len = word.size(); i < len; i++)
    {
        if (ispunct(word[i]))
        {
            word.erase(i--, 1);
            len = word.size();
        }
                word[i] = tolower(word[i]);
            }
    
       wordvector.push_back(word);

          }
        wordvector.push_back("THE_END");
        
        makeChains(wordvector);
        
        generateTweet();
     
  }




