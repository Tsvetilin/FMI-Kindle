#include <iostream>
#include "Kindle.hpp"
#include "KindleInterface.hpp"

int main()
{
	Kindle kindle;
	printKindleManual(std::cout);
	useKindleHandler(kindle, std::cin, std::cout);

	return 0;
}