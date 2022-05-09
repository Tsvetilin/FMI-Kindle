#include <iostream>
#include "Kindle.hpp"
#include "String.hpp"
#include "Helper.hpp"

String pageInput() {
	String content;
	String tempInput;
	while (true) {
		getline(std::cin, tempInput);
		if (tempInput == "q") {
			break;
		}

		content.concat("\n");
		content.concat(tempInput);
	}

	return content;
}

int main()
{
	std::cout << "Welcome to FMI Kindle!\n";

	Kindle kindle;
/*
	std::cout << kindle.signup("Ivan", "Test") << std::endl;
	std::cout << kindle.signup("Petur", "Test") << std::endl;
	std::cout << kindle.login("Ivan", "Test") << std::endl;

	std::cout << kindle.writeBook("Book 1", "Some content") << std::endl;
	std::cout << kindle.addPage("Book 1", "Some more content") << std::endl;

		std::cout << kindle.logout() << std::endl;
		std::cout << kindle.login("Petur", "Test") << std::endl;
	*/
	String input;

	const String loginCmd("login");
	const String signupCmd("signup");
	const String logoutCmd("logout");
	const String viewCmd("view");
	const String readCmd("read");
	const String readPageCmd("readPage");
	const String rateCmd("rate");
	const String ratesCmd("rates");
	const String commentCmd("comment");
	const String commentsCmd("comments");
	const String writeCmd("write");
	const String editTitleCmd("editTitle");
	const String editPageCmd("editPage");
	const String addPageCmd("addPage");
	const String exitCmd("exit");

	while (true) {
		std::cout << ">>";
		getline(std::cin, input);
		String cmd = matchCmd(input);
		input = skipCmd(input);
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
			size_t currentPage = 1;
			if (!kindle.readBook(input, std::cout)) {
				std::cout << "Error reading a book! Either permissions denied or missing book!" << std::endl;
				continue;
			}
			String temp;
			while (true) {
				getline(std::cin, temp);
				if (temp == "p") {
					if (kindle.readBookPage(input, currentPage - 1, std::cout)) {
						--currentPage;
					}
					else {
						std::cout << "You reached the begining of the book!" << std::endl;
					}
				}
				else if (temp == "n") {
					if (kindle.readBookPage(input, currentPage + 1, std::cout)) {
						++currentPage;
					}
					else {
						std::cout<<"You reached the end of the book!" << std::endl;
					}
				}
				else if (temp == "q") {
					break;
				}
				else {
					std::cout << "Invalid command! Commands: q-exit, p-previous page, n-next page" << std::endl;
				}
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
				std::cout << "Error rating a book! Either permissions denied or missing book / invalid rate!" << std::endl;
			}
		}
		else if (cmd == ratesCmd) {
			int rating = kindle.getRating(input);
			if (rating >= 0) {
				std::cout << "Overall book rating: " << rating << std::endl;
				kindle.readRates(input, std::cout);
			}
			else if (rating == -1) {
				std::cout << "This book has no rates yet!" << std::endl;
			}
			else {
				std::cout << "Error viewing ratings for book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == commentCmd) {
			String comment = getAfterQuotes(input);
			if (kindle.commentBook(getQuotes(input), comment)) {
				std::cout << "Book commented!" << std::endl;
			}
			else {
				std::cout << "Error commenting a book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == commentsCmd) {
			if (!kindle.readComments(input, std::cout)) {
				std::cout << "Error reading comments for a book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == writeCmd) {
			std::cout << "Title: ";
			String title;
			getline(std::cin, title);

			std::cout << "Pages count: ";
			String count;
			getline(std::cin, count);
			size_t pagesCount = parseToUInt(count);
			while (pagesCount == 0) {
				std::cout << "You must write at least 1 page!" << std::endl;
				getline(std::cin, count);
				size_t pagesCount = parseToUInt(count);
			}
			std::cout << "Page 1:" << std::endl;
			if (kindle.writeBook(title, pageInput())) {
				for (size_t i = 0; i < pagesCount - 1; i++)
				{
					std::cout << "Page " << (i+2) << ":" << std::endl;
					if (!kindle.addPage(title, pageInput())) {
						std::cout << "Error saving page! Try again!" << std::endl;
						--i;
					}
				}

				std::cout << "Book saved successfully!" << std::endl;
			}
			else {
				std::cout << "Coldn't write book! Either permissions denied or book with the same title already exists!" << std::endl;
			}
		}
		else if (cmd == editTitleCmd) {
			if (kindle.editBook(getQuotes(input), getAfterQuotes(input)))
			{
				std::cout << "Success renaming book!" << std::endl;
			}
			else {
				std::cout << "Error renaming book! Either permission denied or invalid title!" << std::endl;
			}
		}
		else if (cmd == editPageCmd) {

			String title = getQuotes(input);
			size_t page = parseToUInt(getAfterQuotes(input));
			if (kindle.readBookPage(getQuotes(input), page, std::cout))
			{
				std::cout << "New page content:" << std::endl;
				if (kindle.editBookPage(title, page, pageInput())) {
					std::cout << "Page content edited successfully!" << std::endl;
					continue;
				}
			}
			std::cout << "Error editing page! Either permission denied or invalid title/page!" << std::endl;
		}
		else if (cmd == addPageCmd) {

			String title = getQuotes(input);
			if (kindle.addPage(title, pageInput())) {
				std::cout << "Page added successfully!" << std::endl;
			}
			else {
				std::cout << "Error adding page! Either permission denied or invalid title/page!" << std::endl;
			}
		}
		else if (cmd == exitCmd) {
			kindle.logout();
			kindle.save();
			std::cout << "Goodbye!" << std::endl;
			return 0;
		}
		else {
			std::cout << "Error! Invalid command!" << std::endl;
		}
	}







	/*
signup
Ceco
123
login
Ceco
123
write
Test
1
asd
dsa
sad
q
	*/

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