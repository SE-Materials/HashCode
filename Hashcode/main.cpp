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



struct comp
{
    bool operator()(const BookPtr& b1, const BookPtr& b2)
    {
        return b1->score < b2->score;
    }
};

struct Library;
typedef shared_ptr<Library> LibraryPtr;

//unordered_map<BookPtr, int, BookPtrHasher> booksInWorkshop;
unordered_map<BookPtr, LibraryPtr, BookPtrHasher> booksInWorkshop;
long long int score = 0;

struct Library
{
    int id;
    int nBooks;
    int daysToSignup;
    int nBooksCanShipPerDay;
    priority_queue<BookPtr, vector<BookPtr>, comp> books;
    
    Library() {}
    Library(int id, int b, int d, int days) : id{id}, nBooks{b}, daysToSignup{d}, nBooksCanShipPerDay{days}
    {
    }
    
    unordered_set<BookPtr> uniqueBooks;
    void AddBooks(BookPtr book)
    {
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
        int size = books.size();
        
        int temp = nBooksCanShipPerDay;
        vector<BookPtr> booksToReturn;
        while (temp && !books.empty())
        {
            auto it = booksInWorkshop.find(books.top());
            if (it != booksInWorkshop.end())
            {
                booksFilteredOut.insert(books.top());
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
        auto currBooks = this->books;
        return !this->books.empty();
    }
};

struct LibraryPtrHasher
{
    std::size_t operator()(const LibraryPtr& lib) const
    {
        return lib->id;
    }
};

long long int AddBookToWorkShop(BookPtr book, LibraryPtr& l)
{
    booksInWorkshop[book] = l;
    score += book->score;
    
    //    booksInWorkshop.insert(make_pair(book, l));
    
    //    booksInWorkshop[book]++;
    //    if (booksInWorkshop[book] == 1)
    //        score += book->score;
    
    return score;
}

long long int RemoveBookFromWorkShop(BookPtr book)
{
    //    if (booksInWorkshop[book] == 0)
    //    {
    //        booksInWorkshop.erase(booksInWorkshop.find(book));
    //        score = score - book->score;
    //    }
    //    else
    //    {
    //        booksInWorkshop[book]--;
    //    }
    
    booksInWorkshop.erase(booksInWorkshop.find(book));
    score -= book->score;
    return score;
}




void solve(int D, vector<LibraryPtr>& libraries)
{
    
    vector<LibraryPtr> activeLibraries;
    
    // ----- your code here --------
    
    // Decide how to choose libraries (order basically)!
    // In a particular day : Many active libraries are there - choose set of books such it maximises for that day ?
    
    // Method 1:
    // Let's choose libraries sequentially now and books also sequentially
    
    int iday = 0;
    while (iday < D)
    {
        // Now this library can send books
        if (!libraries.empty() && libraries.back()->daysToSignup-- == 0)
        {
            activeLibraries.push_back(libraries.back());
            //            activeLibraries.back()->books = libraries.back().books;
            
            libraries.pop_back();
            
            if (!libraries.empty())
            {
                libraries.back()->daysToSignup--;
            }
        }
        
        
        // For all active libraries
        for (auto& lib : activeLibraries) {
            //if (lib.HaveBooks())
            {
                auto books = lib->GetBooks();
                if (!books.empty())
                {
                    for (auto& book : books) {
                        AddBookToWorkShop(book, lib);
                    }
                }
            }
        }
        
        iday++;
    }

    unordered_map<LibraryPtr, vector<BookPtr>> libraryToBooksUsed;
    for (auto& booksToLibrary : booksInWorkshop)
    {
        libraryToBooksUsed[booksToLibrary.second].push_back(booksToLibrary.first);
    }
    
    
    // Print
    cout << libraryToBooksUsed.size() << endl;
    for (auto& libtobooks : libraryToBooksUsed) {
        auto lib = libtobooks.first;
        auto books = libtobooks.second;
        
        cout << lib->id << " " << books.size() << endl;
        for (auto book : books) {
            cout << book->id << " ";
        }
        cout << endl;
    }
    
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/aniket/Documents/programming/SEMaterials/Hashcode/Hashcode/d_output.txt", "w", stdout);
    freopen("/Users/aniket/Documents/programming/SEMaterials/Hashcode/Hashcode/d.txt", "r", stdin);
    
    int B{}, L{}, D{};
    unordered_map<int, BookPtr> idToBooks;
    vector<LibraryPtr> libraries;
    
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
        libraries.push_back(make_shared<Library>(iLibrary, nbooks, daysTosignUp, nBooksCanShip));
        
        string line;
        cin >> ws;
        getline(cin, line);
        
        stringstream ss(line);
        int bookId;
        while (ss >> bookId)
            libraries[iLibrary]->AddBooks(idToBooks[bookId]);
    }
    
    solve(D, libraries);
    
    
    
    return 0;
}
