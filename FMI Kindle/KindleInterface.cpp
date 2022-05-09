#include "KindleInterface.hpp"
#include "Helper.hpp"

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

String pageInput(std::istream& inputStream) {
	String content;
	String tempInput;
	while (true) {
		getline(inputStream, tempInput);
		if (tempInput == "q") {
			break;
		}

		content.concat("\n");
		content.concat(tempInput);
	}

	return content;
}

void printKindleManual(std::ostream& outputStream) {
	outputStream << "Welcome to FMI Kindle!"<<std::endl;
	outputStream << "Available commands:" << std::endl;
	outputStream << "signup - To register in the kindle." << std::endl;
	outputStream << "login - To log in the kindle." << std::endl;
	outputStream << "logout - To log out of the kindle." << std::endl;
	outputStream << "view - To view the available books in the kindle." << std::endl;
	outputStream << "read <book title> - To start reading the book." << std::endl;
	outputStream << "readPage \"<book title>\" <page number> - To read a particular page of the book." << std::endl;
	outputStream << "rate \"<book title>\" <rate number> - To rate a read book from 0 to 10." << std::endl;
	outputStream << "rates <book title> - To view the rates a book has received." << std::endl;
	outputStream << "comment \"<book title>\" <comment> - To comment a read book from 0 to 10." << std::endl;
	outputStream << "comments <book title> - To view the comments a book has received." << std::endl;
	outputStream << "write - To start writing a book." << std::endl;
	outputStream << "addPage - To add a page to the book you are writing." << std::endl;
	outputStream << "editTitle - To edit the title of a book you have written." << std::endl;
	outputStream << "editPage - To edit the content of a page of a book you have written." << std::endl;
	outputStream << "exit - To save and close the kindle." << std::endl;
	outputStream << std::endl;

}

void useKindleHandler(Kindle& kindle, std::istream& inputStream, std::ostream& outputStream) {
	String input;

	while (true) {
		outputStream << ">>";
		getline(inputStream, input);
		String cmd = matchCmd(input);
		input = skipCmd(input);
		if (cmd == loginCmd) {
			outputStream << "Enter username: ";
			String username;
			getline(inputStream, username);

			outputStream << "Enter password: ";
			String password;
			getline(inputStream, password);

			if (kindle.login(username, password)) {
				outputStream << "Welcome, " << username << "!" << std::endl;
			}
			else {
				outputStream << "Error loging user! Please try again!" << std::endl;
			}
		}
		else if (cmd == signupCmd) {
			outputStream << "Enter username: ";
			String username;
			getline(inputStream, username);

			outputStream << "Enter password: ";
			String password;
			getline(inputStream, password);

			if (kindle.signup(username, password)) {
				outputStream << "User registered!" << std::endl;
			}
			else {
				outputStream << "Error registering user! Please try again!" << std::endl;
			}
		}
		else if (cmd == logoutCmd) {
			if (kindle.logout()) {
				outputStream << "Successfully logged out!" << std::endl;
			}
			else {
				outputStream << "Error logging out! Please try again!" << std::endl;
			}
		}
		else if (cmd == viewCmd) {
			if (!kindle.printBooks(outputStream)) {
				outputStream << "Permissions denied!" << std::endl;
			}
		}
		else if (cmd == readCmd) {
			size_t currentPage = 1;
			if (!kindle.readBook(input, outputStream)) {
				outputStream << "Error reading a book! Either permissions denied or missing book!" << std::endl;
				continue;
			}
			String temp;
			while (true) {
				getline(inputStream, temp);
				if (temp == "p") {
					if (kindle.readBookPage(input, currentPage - 1, outputStream)) {
						--currentPage;
					}
					else {
						outputStream << "You reached the begining of the book!" << std::endl;
					}
				}
				else if (temp == "n") {
					if (kindle.readBookPage(input, currentPage + 1, outputStream)) {
						++currentPage;
					}
					else {
						outputStream << "You reached the end of the book!" << std::endl;
					}
				}
				else if (temp == "q") {
					break;
				}
				else {
					outputStream << "Invalid command! Commands: q-exit, p-previous page, n-next page" << std::endl;
				}
			}
		}
		else if (cmd == readPageCmd) {
			if (!kindle.readBookPage(getQuotes(input), parseToUInt(getLastArgument(input)), outputStream)) {
				outputStream << "Error reading a book page! Either permissions denied or missing book/page!" << std::endl;
			}
		}
		else if (cmd == rateCmd) {
			size_t rate = parseToUInt(getLastArgument(input));
			if (kindle.rateBook(getQuotes(input), rate)) {
				outputStream << "Book rated " << rate << " stars!" << std::endl;
			}
			else {
				outputStream << "Error rating a book! Either permissions denied or missing book / invalid rate!" << std::endl;
			}
		}
		else if (cmd == ratesCmd) {
			double rating = kindle.getRating(input);
			if (rating >= 0) {
				outputStream << "Overall book rating: " << rating << std::endl;
				kindle.readRates(input, outputStream);
			}
			else if (rating == -1) {
				outputStream << "This book has no rates yet!" << std::endl;
			}
			else {
				outputStream << "Error viewing ratings for book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == commentCmd) {
			String comment = getAfterQuotes(input);
			if (kindle.commentBook(getQuotes(input), comment)) {
				outputStream << "Book commented!" << std::endl;
			}
			else {
				outputStream << "Error commenting a book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == commentsCmd) {
			if (!kindle.readComments(input, outputStream)) {
				outputStream << "Error reading comments for a book! Either permissions denied or missing book!" << std::endl;
			}
		}
		else if (cmd == writeCmd) {
			outputStream << "Title: ";
			String title;
			getline(inputStream, title);

			outputStream << "Pages count: ";
			String count;
			getline(inputStream, count);
			size_t pagesCount = parseToUInt(count);
			while (pagesCount == 0) {
				outputStream << "You must write at least 1 page!" << std::endl;
				getline(inputStream, count);
				size_t pagesCount = parseToUInt(count);
			}
			outputStream << "Page 1:" << std::endl;
			if (kindle.writeBook(title, pageInput(inputStream))) {
				for (size_t i = 0; i < pagesCount - 1; i++)
				{
					outputStream << "Page " << (i + 2) << ":" << std::endl;
					if (!kindle.addPage(title, pageInput(inputStream))) {
						outputStream << "Error saving page! Try again!" << std::endl;
						--i;
					}
				}

				outputStream << "Book saved successfully!" << std::endl;
			}
			else {
				outputStream << "Coldn't write book! Either permissions denied or book with the same title already exists!" << std::endl;
			}
		}
		else if (cmd == editTitleCmd) {
			if (kindle.editBook(getQuotes(input), getAfterQuotes(input)))
			{
				outputStream << "Success renaming book!" << std::endl;
			}
			else {
				outputStream << "Error renaming book! Either permission denied or invalid title!" << std::endl;
			}
		}
		else if (cmd == editPageCmd) {
			String title = getQuotes(input);
			size_t page = parseToUInt(getAfterQuotes(input));
			if (kindle.readBookPage(getQuotes(input), page, outputStream))
			{
				outputStream << "New page content:" << std::endl;
				if (kindle.editBookPage(title, page, pageInput(inputStream))) {
					outputStream << "Page content edited successfully!" << std::endl;
					continue;
				}
			}
			outputStream << "Error editing page! Either permission denied or invalid title/page!" << std::endl;
		}
		else if (cmd == addPageCmd) {
			String title = getQuotes(input);
			if (kindle.addPage(title, pageInput(inputStream))) {
				outputStream << "Page added successfully!" << std::endl;
			}
			else {
				outputStream << "Error adding page! Either permission denied or invalid title/page!" << std::endl;
			}
		}
		else if (cmd == exitCmd) {
			kindle.logout();
			kindle.save();
			outputStream << "Goodbye!" << std::endl;
			return;
		}
		else {
			outputStream << "Error! Invalid command!" << std::endl;
		}
	}
}