#include <iostream>
#include "Kindle.hpp"

int main()
{
    std::cout << "Hello FMI Kindle!\n";

    Kindle kindle;

    std::cout<< kindle.signup("Ivan", "Test") <<std::endl;
    std::cout << kindle.signup("Petur", "Test") << std::endl;
    std::cout << kindle.login("Ivan", "Test") << std::endl;

    std::cout << kindle.writeBook("Book 1", "Some content") << std::endl;
    std::cout << kindle.addPage("Book 1", "Some more content") << std::endl;

    std::cout << kindle.rateBook("Book 1", 2) << std::endl;
    std::cout << kindle.commentBook("Book 1", "My comment") << std::endl;

    std::cout << kindle.editBook("Book 1", "First book") << std::endl;
    std::cout << kindle.editBookPage("First book", 1,"New content on first page!") << std::endl;


    kindle.printBooks(std::cout);
    std::cout << kindle.logout() << std::endl;

    std::cout << kindle.login("Petur", "Test") << std::endl;

    std::cout << kindle.readBook("First book",std::cout) << std::endl;
    std::cout << kindle.readBookPage("First book", 2 , std::cout) << std::endl;

    std::cout << kindle.rateBook("First book", 2) << std::endl;
    std::cout << kindle.commentBook("First book", "My comment") << std::endl;

    std::cout << kindle.readComments("First book",std::cout) << std::endl;
    std::cout << kindle.readRates("First book", std::cout) << std::endl;
    std::cout << kindle.getRating("First book") << std::endl;    
}
