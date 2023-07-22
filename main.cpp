#include <iostream>
#include <string>

int main()
{
    std::string data;
    std::cout << "Give string: ";
    std::getline(std::cin, data);
    std::cout << "Input: " << data;
    return 0;
}
