#include "User.hpp"
#include "Helper.hpp"

User::User(String username, String password)
{
	this->username = username;
	this->password = password;
}

bool User::loginAttempt(String password) const {
	return password == this->password;
}

bool User::readBook(const Book* book) {
	readBooks.add(book);
	return true;
}

bool User::writeBook(Book* book) {
	writtenBooks.add(book);
	return true;
}

bool User::hasReadBook(const Book* book) const {
	return readBooks.contains(book);
}

bool User::isAuthor(Book* book) const {
	return writtenBooks.contains(book);
}

bool User::rateBook(Book* book, size_t rate) {
	if (!hasReadBook(book) || writtenBooks.contains(book)) {
		return false;
	}

	return book->rate(this->username, rate);
}

bool User::commentBook(Book* book, String comment) {
	if (!hasReadBook(book) && !isAuthor(book)) {
		return false;
	}

	return book->comment(this->username, comment);
}

String User::getUsername()const {
	return username;
}

bool User::editBook(Book* book, size_t pageNumber, String content) {
	if (!writtenBooks.contains(book)) {
		return false;
	}

	return book->editPage(pageNumber, content);
}

bool User::editTitle(Book* book, String newTitle) {
	if (!writtenBooks.contains(book)) {
		return false;
	}

	return book->setTitle(newTitle);
}

bool User::addPageToBook(Book* book, String content) {
	if (!writtenBooks.contains(book)) {
		return false;
	}

	return book->addPage(content);
}

void User::serialize(std::ostream& o) const{
	size_t countRead = readBooks.getCount();
	size_t countWritten = writtenBooks.getCount();

	serializeString(o, username);
	serializeString(o, password);

	serializePrimitive(o, countRead);
	for (size_t i = 0; i < countRead; i++)
	{
		serializePrimitive(o,readBooks[i]->getId());
	}

	serializePrimitive(o, countWritten);
	for (size_t i = 0; i < countWritten; i++)
	{
		serializePrimitive(o, writtenBooks[i]->getId());
	}
}

void User::deserialize(std::istream& i, const List<Book*> books){
	size_t countRead = 0;
	size_t countWritten = 0;
	size_t temp = 0;

	deserializeString(i, username);
	deserializeString(i, password);

	deserializePrimitive(i, countRead);
	for (size_t k = 0; k < countRead; k++)
	{
		deserializePrimitive(i,temp);
		readBooks.add(books[temp - 1]);
	}

	deserializePrimitive(i, countWritten);
	for (size_t k = 0; k < countWritten; k++)
	{
		deserializePrimitive(i, temp);
		writtenBooks.add(books[temp - 1]);
	}
}