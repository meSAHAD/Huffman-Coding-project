#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <windows.h>
#include <queue>
#include <map>
#include <functional>
#include "unordered_map"
#include "HuffStruct.hpp"
using namespace std;

int total;
string path = "";
int needed;
vector<string> v, store;
map<int, int> mm;
#include "Encode.hpp"
#include "Decode.hpp"
#include "BuildTree.hpp"

int main() {
    cout << fixed << showpoint;
    priority_queue<pair< double, MinHeap *>, vector<pair<double, MinHeap *> >, greater<pair< double, MinHeap *>> > q;
    map<char, pair<int, string> > mp;
    
    fstream file;
    file.open("in.txt", ios::in | ios::out); 
    if (file.is_open()) {
        string tp;
        while (getline(file, tp)) {
            int n = tp.end() - tp.begin();
            store.push_back(tp);
            for (int t=0;t<n;t++) {
                ++mp[tp[t]].first;
                ++total;
            }
        }
    }

    file.close();
    auto root = BuildTree(mp, q);
    cout << "Compressing..." << endl;
    Sleep(2000);
    root = Encode(mp, q, root);
    cout << "Decompressing..." << endl;
    Sleep(2000);
    Decode(root);

    FILE *fp = fopen("compressed.txt", "r");
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fclose(fp);

    cout << "Input File Size: " << total << " Bytes." << '\n';
    Sleep(2000);
    cout << "Output File Size: " << sz << " Bytes." << '\n';
    Sleep(2000);
    // cout << setprecision(5);
    cout << "Compression Rate: " << (long double)((long double)sz/(long double) total)*100 << " %";
    Sleep(2000);
}
