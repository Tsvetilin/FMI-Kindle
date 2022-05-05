#include "Kindle.hpp"
#include "Helper.hpp"

#include <fstream>

const char* const DATABASE_NAME = "fmi-kindle.db";

Book* Kindle::findBook(String title) {
	for (size_t i = 0; i < books.getCount(); i++)
	{
		if (books[i]->getTitle() == title) {
			return books[i];
		}
	}

	return nullptr;
}

Kindle::Kindle() :currentLoggedUser(nullptr), uidGeneration(0) {
	readDb();
}

bool Kindle::readDb() {
	std::ifstream db(DATABASE_NAME, std::ios_base::binary);

	if (!db.is_open()) {
		return false;
	}

	size_t booksCount = 0;
	size_t usersCount = 0;

	deserializePrimitive(db, booksCount);
	for (size_t i = 0; i < booksCount; i++)
	{
		Book* book = new Book();
		book->deserialize(db);
		books.add(book);
	}

	deserializePrimitive(db, usersCount);
	for (size_t i = 0; i < usersCount; i++)
	{
		User* user = new User();
		user->deserialize(db, books);
		users.add(user);
	}

	db.close();

	return db.good();
}

bool Kindle::saveDb() {
	std::ofstream db(DATABASE_NAME, std::ios_base::out | std::ios_base::binary);

	if (!db.is_open()) {
		return false;
	}

	size_t booksCount = books.getCount();
	size_t usersCount = users.getCount();

	serializePrimitive(db, booksCount);
	for (size_t i = 0; i < booksCount; i++)
	{
		books[i]->serialize(db);
	}

	serializePrimitive(db, usersCount);
	for (size_t i = 0; i < usersCount; i++)
	{
		users[i]->serialize(db);
	}

	db.close();

	return db.good();
}

Kindle::~Kindle() {

}

bool Kindle::login(String username, String password) {
	for (size_t i = 0; i < users.getCount(); i++)
	{
		if (username == users[i]->getUsername()) {
			return (users[i]->loginAttempt(password)) && (currentLoggedUser = users[i]);
		}
	}

	return false;
}

bool Kindle::signup(String username, String password) {
	for (size_t i = 0; i < users.getCount(); i++)
	{
		if (username == users[i]->getUsername()) {
			return false;
		}
	}

	User* user = new User(username, password);
	users.add(user);
	return true;
}

bool Kindle::logout() {
	saveDb();
	currentLoggedUser = nullptr;
	return true;
}

bool Kindle::writeBook(String title, String firstPageContent) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	for (size_t i = 0; i < books.getCount(); i++)
	{
		if (books[i]->getAuthor() == currentLoggedUser->getUsername() &&
			books[i]->getTitle() == title) {
			return false;
		}
	}

	Book* book = new Book(currentLoggedUser->getUsername(), title, firstPageContent, uidGeneration);
	books.add(book);
	return currentLoggedUser->writeBook(book);
}

bool Kindle::readBook(String bookTitle, std::ostream& o) {
	return readBookPage(bookTitle, 1, o);
}

bool Kindle::readBookPage(String bookTitle, size_t page, std::ostream& o) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	currentLoggedUser->readBook(book);

	if (!o.good()) {
		return false;
	}

	o << book->getPage(page - 1)->getContent();
	return o.good();
}

bool Kindle::rateBook(String bookTitle, size_t rate) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->rateBook(book, rate);
}

bool Kindle::commentBook(String bookTitle, String comment) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->commentBook(book, comment);
}

bool Kindle::readComments(String bookTitle, std::ostream& o) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	if (!o.good()) {
		return false;
	}

	return book->printComments(o);
}

bool Kindle::readRates(String bookTitle, std::ostream& o) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	if (!o.good()) {
		return false;
	}

	return book->printRates(o);
}

double Kindle::getRating(String bookTitle) {
	if (currentLoggedUser == nullptr) {
		return -2;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return -2;
	}

	return book->getRating();
}

bool Kindle::editBook(String bookTitle, String newTitle) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->editTitle(book, newTitle);
}

bool Kindle::editBookPage(String bookTitle, size_t pageNumber, String content) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->editBook(book, pageNumber, content);
}

bool Kindle::addPage(String bookTitle, String content) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->addPageToBook(book, content);
}

bool Kindle::save() {
	return saveDb();
}

void Kindle::printBooks(std::ostream& o) {
	for (size_t i = 0; i < books.getCount(); i++)
	{
		o << (i + 1) << ". " << books[i]->getTitle() << " by " << books[i]->getAuthor() << std::endl;
	}
}
