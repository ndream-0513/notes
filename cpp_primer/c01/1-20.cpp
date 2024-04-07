#include <iostream>
#include <string>

#include "Sales_item.h"

int main() {

    Sales_item book, currBook;

    int cnt = 0;
    std::string currIsbn = "";
    while (std::cin >> book) {
        if (book.isbn() == currIsbn) {
            currBook += book;
        } else if (currBook.isbn() != "") {
            std::cout << currBook << std::endl;
            ++cnt;
        } 
        currIsbn = book.isbn();
        currBook = book;
    }
    ++cnt;
    std::cout << currBook << std::endl;
    std::cout << "total " << cnt << std::endl;

    return 0;
}