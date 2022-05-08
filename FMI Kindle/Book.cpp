#include "Book.hpp"
#include "Helper.hpp"

Book::Book(const String& authorName, const String& title, const String& firstPageContent, size_t uid) {
	addPage(firstPageContent);
	setTitle(title);
	this->authorName = authorName;
	id = uid;
}

String Book::getAuthor() const {
	return authorName;
}

String Book::getTitle()const {
	return title;
}

double Book::getRating() const {
	if (feedbacks.getCount() == 0) {
		return -1;
	}

	double ratingSum = 0;
	size_t ratingCount = 0;
	for (size_t i = 0; i < feedbacks.getCount(); i++)
	{
		int currentRating = feedbacks[i]->getRating();
		if (currentRating > 0) {
			++ratingCount;
			ratingSum += currentRating;
		}
	}

	if (ratingCount == 0) {
		return -1;
	}

	return ratingSum / ratingCount;
}

bool Book::setTitle(const String& title) {
	this->title = title;
	return true;
}

Book::Book() {}

void Book::copyFrom(const Book& other) {
	authorName = other.authorName;
	title = other.title;
	id = other.id;

	size_t pagesCount = other.pages.getCount();
	size_t feedbacksCount = other.feedbacks.getCount();
	pages = List<Page*>();
	feedbacks = List<Feedback*>();

	for (size_t i = 0; i < pagesCount; i++)
	{
		Page* page = new Page(*other.pages[i]);
		pages.add(page);
	}

	for (size_t i = 0; i < feedbacksCount; i++)
	{
		Feedback* feedback = new Feedback(*other.feedbacks[i]);
		feedbacks.add(feedback);
	}
}

void Book::free() {
	size_t pagesCount = pages.getCount();
	size_t feedbacksCount = feedbacks.getCount();

	for (size_t i = 0; i < pagesCount; i++)
	{
		delete pages[i];
	}

	for (size_t i = 0; i < feedbacksCount; i++)
	{
		delete feedbacks[i];
	}
}

Book::Book(const Book& other) {
	copyFrom(other);
}

Book& Book::operator= (const Book& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Book::~Book() {
	free();
}


const size_t Book::getId() const {
	return id;
}


bool Book::rate(const String& user, size_t rate) {
	for (size_t i = 0; i < feedbacks.getCount(); i++)
	{
		if (feedbacks[i]->getUser() == user) {
			return feedbacks[i]->setRating(rate);
		}
	}

	Feedback* f = new Feedback(user);
	feedbacks.add(f);
	return f->setRating(rate);
}

bool Book::comment(const String& user, const String& comment) {
	for (size_t i = 0; i < feedbacks.getCount(); i++)
	{
		if (feedbacks[i]->getUser() == user) {
			return feedbacks[i]->addComment(comment);
		}
	}

	Feedback* f = new Feedback(user);
	feedbacks.add(f);
	return f->addComment(comment);
}

const Page* const Book::getPage(size_t pageNo) const {
	return pages[pageNo];
}

bool Book::printComments(std::ostream& o) const {
	for (size_t i = 0; i < feedbacks.getCount(); i++)
	{
		feedbacks[i]->printComments(o);
	}

	return o.good();
}

bool Book::printRates(std::ostream& o)const {
	for (size_t i = 0; i < feedbacks.getCount(); i++)
	{
		int r = feedbacks[i]->getRating();
		if (r != -1) {
			o << feedbacks[i]->getUser() << " rated " << r << " stars!"<<std::endl;
		}
	}

	return o.good();
}

bool Book::editPage(size_t pageNumber, const String& content) {
	if (pageNumber > pages.getCount()) {
		return false;
	}

	return pages[pageNumber - 1]->setContent(content);
}

bool Book::addPage(const String& content) {
	Page* page = new Page(content, pages.getCount() + 1);
	pages.add(page);

	return true;
}

void Book::serialize(std::ostream& o) const {
	size_t pagesCount = pages.getCount();
	size_t feedbacksCount = feedbacks.getCount();

	serializePrimitive(o, id);

	serializePrimitive(o, pagesCount);
	for (size_t i = 0; i < pagesCount; i++)
	{
		pages[i]->serialize(o);
	}

	serializeString(o, authorName);
	serializeString(o, title);

	serializePrimitive(o, feedbacksCount);
	for (size_t i = 0; i < feedbacksCount; i++)
	{
		feedbacks[i]->serialize(o);
	}
}

void Book::deserialize(std::istream& i) {
	size_t pagesCount = 0;
	size_t feedbacksCount = 0;

	deserializePrimitive(i, id);

	deserializePrimitive(i, pagesCount);
	for (size_t k = 0; k < pagesCount; k++)
	{
		Page* page = new Page();
		page->deserialize(i);
		pages.add(page);
	}

	deserializeString(i, authorName);
	deserializeString(i, title);

	deserializePrimitive(i, feedbacksCount);
	for (size_t k = 0; k < feedbacksCount; k++)
	{
		Feedback* feedback = new Feedback();
		feedback->deserialize(i);
		feedbacks.add(feedback);
	}
}