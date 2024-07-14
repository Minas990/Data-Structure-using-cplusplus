#include <iostream>
#include "DICTIONARY.h"
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


int main()
{
    Dictionary<string, int, Hash> mina;
    mina.insert("mina",10);
    mina.insert("mina",1000);
    mina.insert("mina",100);
    mina.insert("beb",1000);
    mina.erase("mina");
    cout << mina.operator[]("mina") << endl;
    auto it = mina.findAll("mina");
    for (auto i : it)
        cout << i.value()<<' ';
}