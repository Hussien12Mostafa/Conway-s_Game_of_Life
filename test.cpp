

#include <iostream>

using namespace std;

int main(){

    

    

    for (int x = 0; x < 3; x++) 

    {

        // Type casting the result to float

        cout << (float) rand()/RAND_MAX << endl;

    }

    return 0;

}