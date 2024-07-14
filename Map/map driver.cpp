#include <iostream>
#include <string>
#include <list>
#include "Map.h"

using namespace std;
// Define a simple hash function
struct Hash {
    int operator()(const string& key) const {
        int hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return hash;
    }
};

int main() {
    // Create a Map instance with string keys and int values
    Map<string, int, Hash> myMap;

    cout << "putting some elements" << endl << endl;;
    // Insert some key-value pairs
    myMap.put("apple", 1);
    myMap.put("banana", 2);
    myMap.put("orange", 3);


    cout << "printing: " << endl;
    for (auto i : myMap)
        cout <<"    " << i.key() << ' ' << i.value() << endl;

    cout << endl << endl;
    cout << "search for apple value" << endl;
    Map<string, int, Hash>::Iterator it = myMap.find("apple");
    cout <<"    "<<"apple val is : " << (it.operator*()).value() << endl<<endl;

    cout << "deleting some elements" << endl;
    myMap.erase("apple");
    cout << "    apple deleted " << endl;
    myMap.erase("banana");
    cout << "    banana deleted " << endl<<endl;

    // do nothing 
    myMap.erase("rg");

    cout << "printing the remaining: " << endl<<"\t";
    for (auto i : myMap)
        cout << i.key() << ' ' << i.value() << endl<<endl;

    cout << "searching for orange" << endl;
    cout <<'\t' << (*myMap.find("orange")).key() << " " << (*myMap.find("orange")).value() << " " << endl << endl;

    cout << "checking [] operator on object does not exist: " << endl;
    cout <<'\t' << myMap["apple"] << endl << endl;;
    cout << "checking [] operator for something object: " << endl;
    cout << '\t' << myMap["orange"] << endl << endl;;

    return 0;
}
