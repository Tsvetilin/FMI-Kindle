#include <iostream>
#include "Kindle.hpp"
#include "String.hpp"
#include "Helper.hpp"

int main()
{
	std::cout << "Welcome to FMI Kindle!\n";

	Kindle kindle;

	String input;

	const String loginCmd("login");
	const String signupCmd("signup");
	const String logoutCmd("logout");
	const String viewCmd("view");
	const String readCmd("read");
	const String readPageCmd("readPage");
	const String rateCmd("rate");
	const String ratesCmd("rates");
	const String commentCmd("commet");
	const String commentsCmd("commets");
	const String writeCmd("write");
	const String editCmd("edit");
	const String addPageCmd("addPage");

	while (true) {
		std::cout << ">>";
		getline(std::cin, input);
		String cmd = matchCmd(input);
		if (cmd == loginCmd) {
			std::cout << "Enter username: ";
			String username;
			getline(std::cin, username);

			std::cout << "Enter password: ";
			String password;
			getline(std::cin, password);

			if (kindle.login(username, password)) {
				std::cout << "Welcome, " << username << "!" << std::endl;
			}
			else {
				std::cout << "Error loging user! Please try again!" << std::endl;
			}
		}
		else if (cmd == signupCmd) {
			std::cout << "Enter username: ";
			String username;
			getline(std::cin, username);

			std::cout << "Enter password: ";
			String password;
			getline(std::cin, password);

			if (kindle.signup(username, password)) {
				std::cout << "User registered!" << std::endl;
			}
			else {
				std::cout << "Error registering user! Please try again!" << std::endl;
			}
		}
		else if (cmd == logoutCmd) {
			if (kindle.logout()) {
				std::cout << "Successfully logged out!" << std::endl;
			}
			else {
				std::cout << "Error logging out! Please try again!" << std::endl;
			}
		}
		else if (cmd == viewCmd) {
			if (!kindle.printBooks(std::cout)) {
				std::cout << "Permissions denied!" << std::endl;
			}
		}
		else if (cmd == readCmd) {
			if (!kindle.readBook(skipCmd(input), std::cout)) {
				std::cout << "Error reading a book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == readPageCmd) {
			if (!kindle.readBookPage(getQuotes(input), parseToUInt(getLastArgument(input)), std::cout)) {
				std::cout << "Error reading a book page! Either permissions denied or missing book/page!" << std::endl;
			}
		}
		else if (cmd == rateCmd) {
			size_t rate = parseToUInt(getLastArgument(input));
			if (kindle.rateBook(getQuotes(input), rate)) {
				std::cout << "Book rated " << rate << " stars!" << std::endl;
			}
			else {
				std::cout << "Error rating a book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == ratesCmd) {
			String book = skipCmd(input);
			int rating = kindle.getRating(book);
			if (rating >= 0) {
				std::cout << "Overall book rating: " << rating << std::endl;
				kindle.readRates(book, std::cout);
			}
			else if (rating == -1) {
				std::cout << "This book has no rates yet!" << std::endl;
			}
			else {
				std::cout << "Error viewing ratings for book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == commentCmd) {
			String comment = getLastArgument(input);
			if (kindle.commentBook(getQuotes(input), comment)) {
				std::cout << "Book commented!"<< std::endl;
			}
			else {
				std::cout << "Error commenting a book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == viewCmd) {
			kindle.printBooks(std::cout);
		}
		else if (cmd == viewCmd) {
			kindle.printBooks(std::cout);
		}
		else if (cmd == viewCmd) {
			kindle.printBooks(std::cout);
		}
	}









	/*String s;

	getline(std::cin,s);

	std::cout << s <<std::endl;

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

	std::cout << kindle.save()<< std::endl;
	*/
}
