/* Basic script to test that BlackLib.h can compile
To compile this, you must have a copy of the BlackLib-master directory in your current directory.
Compile with "g++ BBB.cpp -std=c++11" OR "g++ BBB.cpp -std=gnu++11"
Then run the program with "./a.out"
*/

// v3_0 is the latest version of BlackLib. v2 and v1 are in BlackLib-master incase they are needed.
#include "BlackLib-master/v3_0/BlackLib.h" 
#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
cout << "Hello World!" << endl;
return 0;
}
