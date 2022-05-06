#include "Kindle.hpp"
#include "Helper.hpp"

#include <fstream>

const String DEFAULT_DATABASE_NAME("fmi-kindle.db");

void Kindle::copyFrom(const Kindle& other) {
	databaseName = other.databaseName;

	books = List<Book*>();
	users = List<User*>();

	size_t booksCount = other.books.getCount();
	size_t usersCount = other.users.getCount();

	for (size_t i = 0; i < booksCount; i++)
	{
		Book* book = new Book(*other.books[i]);
		books.add(book);
	}

	for (size_t i = 0; i < usersCount; i++)
	{
		User* user = new User(*other.users[i]);
		users.add(user);
	}

	if (other.currentLoggedUser == nullptr) {
		currentLoggedUser = nullptr;
	}
	else {
		for (size_t i = 0; i < usersCount; i++)
		{
			if (users[i]->getUsername() == other.currentLoggedUser->getUsername()) {
				currentLoggedUser = users[i];
				break;
			}
		}
	}
}

void Kindle::free() {
	size_t booksCount = books.getCount();
	size_t usersCount = users.getCount();

	for (size_t i = 0; i < booksCount; i++)
	{
		delete books[i];
	}

	for (size_t i = 0; i < usersCount; i++)
	{
		delete users[i];
	}
}

Book* Kindle::findBook(const String& title) const{
	for (size_t i = 0; i < books.getCount(); i++)
	{
		if (books[i]->getTitle() == title) {
			return books[i];
		}
	}

	return nullptr;
}

Kindle::Kindle() :Kindle(DEFAULT_DATABASE_NAME) {}

Kindle::Kindle(const String& databaseName) :currentLoggedUser(nullptr) {
	this->databaseName = databaseName;
	readDb();
}

Kindle::Kindle(const Kindle& other) {
	copyFrom(other);
}

Kindle& Kindle::operator= (const Kindle& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

bool Kindle::readDb() {
	std::ifstream db(databaseName.c_str(), std::ios_base::binary);

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

bool Kindle::saveDb() const{
	std::ofstream db(databaseName.c_str(), std::ios_base::out | std::ios_base::binary);

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
	free();
}

bool Kindle::login(const String& username, const String& password) {
	for (size_t i = 0; i < users.getCount(); i++)
	{
		if (username == users[i]->getUsername()) {
			return (users[i]->loginAttempt(password)) && (currentLoggedUser = users[i]);
		}
	}

	return false;
}

bool Kindle::signup(const String& username, const String& password) {
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

bool Kindle::writeBook(const String& title, const String& firstPageContent) {
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

	Book* book = new Book(currentLoggedUser->getUsername(), title, firstPageContent, books.getCount()-1);
	books.add(book);
	return currentLoggedUser->writeBook(book);
}

bool Kindle::readBook(const String& bookTitle, std::ostream& o) {
	return readBookPage(bookTitle, 1, o);
}

bool Kindle::readBookPage(const String& bookTitle, size_t page, std::ostream& o) {
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

bool Kindle::rateBook(const String& bookTitle, size_t rate) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->rateBook(book, rate);
}

bool Kindle::commentBook(const String& bookTitle, const String& comment) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->commentBook(book, comment);
}

bool Kindle::readComments(const String& bookTitle, std::ostream& o) const {
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

bool Kindle::readRates(const String& bookTitle, std::ostream& o) const {
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

double Kindle::getRating(const String& bookTitle) const {
	if (currentLoggedUser == nullptr) {
		return -2;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return -2;
	}

	return book->getRating();
}

bool Kindle::editBook(const String& bookTitle, const String& newTitle) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	if (bookTitle == newTitle) {
		return true;
	}

	Book* matchBook = findBook(newTitle);
	if (matchBook != nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->editTitle(book, newTitle);
}

bool Kindle::editBookPage(const String& bookTitle, size_t pageNumber, const String& content) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->editBook(book, pageNumber, content);
}

bool Kindle::addPage(const String& bookTitle, const String& content) {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	Book* book = findBook(bookTitle);
	if (book == nullptr) {
		return false;
	}

	return currentLoggedUser->addPageToBook(book, content);
}

bool Kindle::save() const{
	return saveDb();
}

bool Kindle::printBooks(std::ostream& o) const {
	if (currentLoggedUser == nullptr) {
		return false;
	}

	if (books.getCount() == 0)
	{
		std::cout << "No books written in the kindle!" << std::endl;
		return true;
	}

	for (size_t i = 0; i < books.getCount(); i++)
	{
		o << (i + 1) << ". " << books[i]->getTitle() << " by " << books[i]->getAuthor() << std::endl;
	}

	return true;
}
