#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h"
#include <fstream>
#include "random.h"
#include <map>

using namespace std;
typedef map<string, Vector<char> > Map;


string generateText(ifstream &file, int numCharacters, int markovOrder);
void buildMarkovMap(ifstream &file, Map &markovMap, int markovOrder);
string getSeed(map<string, Vector<char> > &markovMap);


int main ()
{
    ifstream file;
    while(true) {
        cout << "Enter filename: ";
        string filename = getLine();
        if(filename == "") {
            filename = "readme.txt";
            file.open(filename);
            break;
        }
        file.open(filename);
        if(file.fail())
            cout << "Could not open " << filename << endl;
        else
            break;

    }

    cout << generateText(file, 2000, 10) << endl;

    cout << "Over and out!" << endl;
    return 0;
}

void buildMarkovMap(ifstream &file, Map &markovMap, int markovOrder) {
    string keyString;
    while(true) {
        char c = file.get();
        if(file.fail())
            break;
        // Start with reading markovOrder Chars
        if(keyString.size() < markovOrder)
            keyString += c;
        else {
            markovMap[keyString].add(c);
            keyString.erase(0,1);
            keyString += c;
        }
    }

    return;
}

string generateText(ifstream &file, int numCharacters, int markovOrder) {
    Map markovMap;
    buildMarkovMap(file, markovMap, markovOrder);
    string text;
    string seed = getSeed(markovMap);
    cout << "Seed : " << seed << endl;
    text += seed;
    for(int i=0; i<numCharacters; i++) {
        if(markovMap[seed].isEmpty()) break;
        int rnd = randomInteger(0, markovMap[seed].size()-1);
//        cout << "RND: " << rnd << " makovSize " << markovMap[seed].size;
        char c = markovMap[seed][rnd];
        seed.erase(0, 1);
        seed += c;
        text += c;
    }
    return text;
}

string getSeed(map<string, Vector<char> > &markovMap) {
    string key, iKey;
    for (map<string, Vector<char> >::iterator it = markovMap.begin(); it != markovMap.end(); ++it) {
//        cout << it->first << it->second.size() << endl;
        iKey = it->first;
        if(key == "")
            key = iKey;
        if(markovMap[iKey].size() > markovMap[key].size())
            key = iKey;
    }

    return key;
}


