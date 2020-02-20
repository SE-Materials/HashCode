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
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;

struct Book
{
    int id;
    int score;
    Book() {}
    Book(int id, int score) : id{id}, score{score} {}
};

typedef shared_ptr<Book> BookPtr;
struct BookPtrHasher
{
    std::size_t operator()(const BookPtr& book) const
    {
        return book->score;
    }
};

unordered_map<BookPtr, int, BookPtrHasher> booksInWorkshop;
long long int score = 0;

long long int AddBookToWorkShop(BookPtr book)
{
    booksInWorkshop[book]++;
    if (booksInWorkshop[book] == 1)
        score += book->score;
    
    return score;
}

long long int RemoveBookFromWorkShop(BookPtr book)
{
    if (booksInWorkshop[book] == 0)
    {
        booksInWorkshop.erase(booksInWorkshop.find(book));
        score = score - book->score;
    }
    else
    {
        booksInWorkshop[book]--;
    }
    return score;
}

struct comp
{
    bool operator()(const BookPtr& b1, const BookPtr& b2)
    {
        return b1->score < b2->score;
    }
};


struct Library
{
    int nBooks;
    int daysToSignup;
    int nBooksCanShipPerDay;
    priority_queue<BookPtr, vector<BookPtr>, comp> books;
    
    Library(int b, int d, int days) : nBooks{b}, daysToSignup{d}, nBooksCanShipPerDay{days}
    {
    }
    
    void AddBooks(BookPtr book)
    {
        static unordered_set<BookPtr> uniqueBooks;
        auto it = uniqueBooks.find(book);
        
        if (it == uniqueBooks.end())
        {
            uniqueBooks.insert(book);
            books.push(book);
        }
        
    }
    
    unordered_set<BookPtr> booksFilteredOut;
    
    // can be 0,1, ...
    vector<BookPtr> GetBooks()
    {
        int temp = nBooksCanShipPerDay;
        vector<BookPtr> booksToReturn;
        while (temp && !books.empty())
        {
            auto it = booksFilteredOut.find(books.top());
            if (it != booksFilteredOut.end())
            {
                books.pop();
                continue;
            }
            
            booksToReturn.push_back(books.top());
            books.pop();
            temp--;
        }
        
        return booksToReturn;
    }
    
    bool HaveBooks()
    {
        return !books.empty();
    }
};

void solve(int D, const vector<Library>& libraries)
{
    
    int L = libraries.size();
    
    // your code here
    
    // In a particular day : Many libraries are there - choose set of books such it maximises for that day ?
    // 
    
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/aniket/Documents/programming/SEMaterials/Hashcode/Hashcode/a_output.txt", "w", stdout);
    freopen("/Users/aniket/Documents/programming/SEMaterials/Hashcode/Hashcode/a.txt", "r", stdin);
    
    int B{}, L{}, D{};
    unordered_map<int, BookPtr> idToBooks;
    vector<Library> libraries;
    
    cin >> B >> L >> D;
    
    idToBooks.clear();
    libraries.clear();
    
    
    for (int i=0; i<B; ++i)
    {
        int score;
        cin >> score;
        idToBooks.insert(make_pair(i, make_shared<Book>(i, score)));
    }
    
    for (int iLibrary=0; iLibrary<L; ++iLibrary)
    {
        int nbooks, daysTosignUp, nBooksCanShip;
        
        cin >> nbooks >> daysTosignUp >> nBooksCanShip;
        
        // ith library
        libraries.push_back(Library(nbooks, daysTosignUp, nBooksCanShip));
        
        string line;
        cin >> ws;
        getline(cin, line);
        
        stringstream ss(line);
        int bookId;
        while (ss >> bookId)
            libraries[iLibrary].AddBooks(idToBooks[bookId]);
    }
    
    solve(D, libraries);
    
    
    
    return 0;
}
