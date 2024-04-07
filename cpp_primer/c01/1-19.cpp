#include <iostream>

int main() {

    std::cout << "Ple enter two num: " << std::endl;
    int l1 = 0, r1 = 0;
    std::cin >> l1 >> r1;
    if (r1 < l1) std::cout << "input error range!!!" << std::endl;
    else
        for (; l1 <= r1; ++l1) std::cout << l1 << ' ';
    std::cout << std::endl;

    return 0;
}