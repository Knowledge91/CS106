/*
 * Program: warmup.cpp
 * --------------------
 * Program used to generate a hash code based on user's name.
 * As given, this code has two compiler errors you need to track down
 * and fix in order to get the program up and running.
 *
 * jzelenski Thu Apr  1 12:27:53 PST 2004
 */

#include <iostream>
#include "console.h"
#include "tokenscanner.h"

using namespace std;


int main ()
{
    string test = "<b><c>hallo</c></b>";
    TokenScanner scanner(test);
    while(scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        cout << token << endl;
    }
    return 0;
}
