//
//  main.cpp
//  Hashcode
//
//  Created by Aniket Bhushan on 20/02/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Library
{
    int nBooks;
    int daysToSignup;
    int nBooksCanShipPerDay;
    vector<int> books;
    
    explicit Library(int b, int d, int days) : nBooks{b}, daysToSignup{d}, nBooksCanShipPerDay{days}
    {
    }
    
    void AddBooks(int bookId)
    {
        books.push_back(bookId);
    }
};

void solve(int D, const vector<int>& bookScores, const vector<Library*>& libraries)
{
    int B = bookScores.size();
    int L = libraries.size();
    
    // your code here
    
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/aniket/Documents/programming/SEMaterials/Hashcode/Hashcode/output.txt", "w", stdout);
    freopen("/Users/aniket/Documents/programming/SEMaterials/Hashcode/Hashcode/a_example.txt", "r", stdin);
    
    int B{}, L{}, D{};
    vector<int> bookScores;
    vector<Library*> libraries;
    
    cin >> B >> L >> D;
    
    // Books
    bookScores.clear();
    bookScores.resize(B);
    
    // Libraries
    libraries.clear();
    libraries.resize(L);
    
    
    for (int i=0; i<B; ++i)
    {
        cin >> bookScores[i];
    }
    
    for (int iLibrary=0; iLibrary<L; ++iLibrary)
    {
        int nbooks, daysTosignUp, nBooksCanShip;
        
        cin >> nbooks >> daysTosignUp >> nBooksCanShip;
        
        // ith library
        libraries[iLibrary] = new Library(nbooks, daysTosignUp, nBooksCanShip);
        
        string line;
        cin >> ws;
        getline(cin, line);
        
        stringstream ss(line);
        int bookId;
        while (ss >> bookId)
            libraries[iLibrary]->AddBooks(bookId);
    }
    
    solve(D, bookScores, libraries);
    
    return 0;
}
