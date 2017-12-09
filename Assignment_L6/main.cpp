#include <iostream>
#include "array.h"
#include <memory>



using namespace std;

int main()
{

    try{

        Array * pA = new Array(5);
        shared_ptr<Array> sh(pA);

        int a; cin >> a;

        if (a < 0){
            throw 1;
        }
    }
    catch(int a){
        cout << "catch    "<< endl;
    }



    cout << "Hello World!" << endl;
    return 0;
}
