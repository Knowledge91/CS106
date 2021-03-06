/*
 * Program: warmup.cpp
 * --------------------
 * Program used to generate a hash code based on user's name.
 * As given, this code has two compiler errors you need to track down
 * and fix in order to get the program up and running.
 *
 * jzelenski Thu Apr  1 12:27:53 PST 2004
 */

#include <QDebug>
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "random.h"
#include "gwindow.h"
#include "gevents.h"
#include <cmath>
#include "map.h"
#include <typeinfo>
#include "ctype.h"
#include <fstream>

using namespace std;

#define MAX_HASH_CODE	10000	// Upper bound for hash codes generated by program

/* Function prototypes */
int Hash(string s, int maxCode);
bool isPerfect(int number);

/*
 * Function: Hash
 * Usage: hash_number = Hash(key, max_hash);
 * -----------------------------------------
 * This function takes the key and uses it to derive a hash code,
 * which is an integer in the range [0, maxCode - 1].  The hash
 * code is computed using a method called linear congruence.
 */
#define Multiplier -1664117991L		// Multiplier used in Hash function

int Hash(string s, int maxCode)
{
    unsigned long hashcode = 0;
    for (int i = 0; i < s.length(); i++)
        hashcode = hashcode * Multiplier + s[i];
   return (hashcode % maxCode);
}

//Function: isPerfect
//Usage: isNumberPerfect = isPerfect(number);
//-------------------------------------------
//This function takes a number and returns true if the number is a perfect number and false else.
bool isPerfect(int number) {
    int sum = 0;
    for(int i=1; i<number; i++) {
        if((number % i) == 0){
            sum += i;
        }
    }
   if(sum == number) {
       return true;
   } else {
       return false;
   }
}

//Problem 2
bool isInvalidVote(int &numberVoter, double &percentageSpread, double &votingErrorPercentage) {
    double numberSpreadVotes;
    int winner;
    int looser;
    int invLooser = 0;
    int invWinner = 0;
    int newWinner;
    int newLooser;
    numberSpreadVotes = numberVoter * percentageSpread;
    winner = numberVoter / 2 + numberSpreadVotes;
    looser = numberVoter / 2 - numberSpreadVotes;

    for(int i=1; i<=looser; i++) {
        if(randomChance(votingErrorPercentage))
            invLooser++;
    }
    for(int i=1; i<=winner; i++) {
        if(randomChance(votingErrorPercentage))
            invWinner++;
    }
    newWinner = winner - invWinner + invLooser;
    newLooser = looser - invLooser + invWinner;
    if(newLooser > newWinner)
        return true;
    else
        return false;
}

double invalidElectionChance(int &trials, int &numberVoter, double &percentageSpread, double &votingErrorPercentage) {
    int countInvalidVotes = 0;
    for(int i=1; i<= trials; i++) {
        if(isInvalidVote(numberVoter, percentageSpread, votingErrorPercentage))
            countInvalidVotes++;
    }
    return (countInvalidVotes / (double) trials) * 100.0;
}

string soundex(string s) {
    string output = "";
    int i=0;
    output += toupper(s[0]);
    i++;
    Map<char, string> rules;
    rules['A'] = rules['E'] = rules['I'] = rules['O'] = rules['U'] = rules['H'] = rules['W'] = rules['Y'] = "0";
    rules['B'] = rules['F'] = rules['P'] = rules['V'] = "1";
    rules['C'] = rules['G'] = rules['J'] = rules['K'] = rules['Q'] = rules['S'] = rules['X'] = rules['Z'] = "2";
    rules['D'] = rules['T'] = "3";
    rules['M'] = rules['N'] = "4";
    rules['L'] = "5";
    rules['R'] = "6";

//    Dictionary
    for(i; i<s.length(); i++) {
        output += rules[toupper(s[i])];
    }
//    truncate consecutive duplicates
    for(i=1; i<output.length(); i++) {
        if(output[i] == output[i+1]) {
            output.erase(i,1);
            i--;
        }
    }

    for(i=1; i<output.length(); i++) {
        if(output[i] == '0') {
            output.erase(i,1);
            i--;
        }
    }

    while(output.length() <= 3) {
        output += '0';
    }
    return output;
}

void plotHistogram(ifstream &file) {
    string line;
    Vector<int> vec;
    for(int i=0; i<=9; i++) {
        vec.add(0);
    }
    while(true) {
        getLine(file, line);
        if(file.fail()) break;
        int bucket = line[0] - '0';
        vec[bucket]++;
    }
    string X;
    for(int i=0; i<10; i++) {
        for(int j=1; j<=vec[i]; j++) {
            X += "X";
        }
        if(i==0)
            cout << "0-9: " << X << endl;
        else
            cout << i << "0-" << i << "9: " << X << endl;
        X = "";
    }
}

int main ()
{
    qDebug() << "Programm START" << endl;
//    Warmup
//    cout << "Please enter your name: ";
//    string name = getLine();
//    cout << name << endl;
//    int hashcode = Hash(name, MAX_HASH_CODE);
//    cout << "The hash code for your name is " << hashcode << "." <<endl;

//    Problem 1
//    int count = 0;
//    for(int i=1; i<=10000; i++) {
//        if(isPerfect(i)) {
//            count++;
//            qDebug() << i << "-" << isPerfect(i) << endl;
//        }
//    }
//    qDebug() << "Count of perfect numbers: " << count << endl;

//    Problem 2
//    int numberTrials = 500;
//    cout << "Enter number of voters:";
//    int numberVoters = getInteger();
//    cout << "Enter percentage between candidates:";
//    double percentageSpread = getDoubleBetween("", 0.0, 1.0);
//    cout << "Enter voting error percentage: ";
//    double votingErrorPercentage = getDoubleBetween("", 0.0, 1.0);
//    cout << endl << endl << "Chance of an invalid election result after " << numberTrials << "trials = " <<  invalidElectionChance(numberTrials, numberVoters, percentageSpread, votingErrorPercentage) << "%";

////      Problem 3
//    GWindow window(500, 500);
//    window.setColor("White");
//    window.clear();
//    window.setWindowTitle("Sample Project");
//    window.setColor("Black");

////    Construct and draw Triangular
//    cout << "Draw a triangle by clicking three times." << endl;
//    Vector<GPoint> triangular;
//    while(triangular.size() - 1 < 3) {
//        GMouseEvent e = waitForEvent();
//        if (e.getEventType() == MOUSE_PRESSED) {
//            triangular.add(GPoint( e.getX(), e.getY()));
//        }
//    }
//    GPoint A = triangular.get(0);
//    GPoint B = triangular.get(1);
//    GPoint C = triangular.get(2);
//    window.drawLine(A, B);
//    window.drawLine(B, C);
//    window.drawLine(C, A);

////    Chaos Game
//    GPoint start = triangular.get(randomInteger(0,2));
//    window.fillOval( start.getX(), start.getY(),  1,  1);
//    double px, py;
//    for(int i=0; i<=100000; i++ ) {
//        GPoint target = triangular.get(randomInteger(0,2));
//        double halfDifferenceX = (abs(target.getX() - start.getX())) /2;
//        double halfDifferenceY = (abs(target.getY() - start.getY()))/2;
//        if (target.getX() > start.getX())
//            px = start.getX() + halfDifferenceX;
//        else
//            px = start.getX() - halfDifferenceX;
//        if (target.getY() > start.getY())
//            py = start.getY() + halfDifferenceY;
//        else
//            py = start.getY() - halfDifferenceY;
//        GPoint p = GPoint(px, py);
//        window.fillOval( p.getX(), p.getY(),  3,  3);
//        start = p;
//    }


//    Problem 4
//    while(true) {
//        cout << "Enter surname: ";
//        string surname = getLine();
//        if(surname == "") break;
//        cout << soundex(surname) << endl;
//    }
//    cout << "Over and out!" << endl;


//    Problem 5
    string filename;
    ifstream file;
    while(true) {
        cout << "Enter filename:";
        filename = getLine();
        file.open(filename);
        if(file.is_open()) break;
    }
    plotHistogram(file);
    cout << "Over and out!" << endl;


    return 0;
}
