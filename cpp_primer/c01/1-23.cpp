#include <iostream>
#include <string>
#include "Sales_item.h"

int main() {

    Sales_item book, currBook;

    int cnt = 1;
    std::string currIsbn = "";
    while (std::cin >> book) {
        if (book.isbn() == currIsbn) ++cnt;
        else if (currBook.isbn() != "") {
            std::cout << currBook.isbn() 
                << " sales " << cnt << std::endl;
            cnt = 1;
        } 
        currBook = book;
        currIsbn = currBook.isbn();
    }
    std::cout << currBook.isbn() 
        << " sales " << cnt << std::endl;
    
    return 0;
}