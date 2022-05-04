#include "Book.hpp"

void Book::setAuthorName(String authorName) {
	this->authorName = authorName;
}

Book::Book(String authorName, String title, String firstPageContent, size_t uid) {
	addPage(firstPageContent);
	setTitle(title);
	setAuthorName(authorName);
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

bool Book::setTitle(String title) {
	this->title = title;
	return true;
}

Book::Book() {}

const size_t Book::getId() const {
	return id;
}


bool Book::rate(String user, size_t rate) {
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

bool Book::comment(String user, String comment) {
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

bool Book::printComments(std::ostream& o) {
	for (size_t i = 0; i < feedbacks.getCount(); i++)
	{
		feedbacks[i]->printComments(o);
	}

	return o.good();
}

bool Book::printRates(std::ostream& o) {
	for (size_t i = 0; i < feedbacks.getCount(); i++)
	{
		int r = feedbacks[i]->getRating();
		if (r != -1) {
			o << feedbacks[i]->getUser() << " rated " << r << " stars!";
		}
	}

	return o.good();
}

bool Book::editPage(size_t pageNumber, String content) {
	if (pageNumber > pages.getCount()) {
		return false;
	}

	return pages[pageNumber - 1]->setContent(content);
}

bool Book::addPage(String content) {
	Page* page = new Page(content, pages.getCount() + 1);
	pages.add(page);

	return true;
}

void Book::serialize(std::ostream& o) {
	size_t authorNameLen = authorName.getLength();
	size_t titleLen = title.getLength();
	size_t pagesCount = pages.getCount();
	size_t feedbacksCount = feedbacks.getCount();

	o.write((const char*)&id, sizeof(id));
	o.write((const char*)&rating, sizeof(rating));

	o.write((const char*)&pagesCount, sizeof(pagesCount));
	for (size_t i = 0; i < pagesCount; i++)
	{
		pages[i]->serialize(o);
	}

	o.write((const char*)&authorNameLen, sizeof(authorNameLen));
	o.write((const char*)authorName.c_str(), authorNameLen + 1);

	o.write((const char*)&titleLen, sizeof(titleLen));
	o.write((const char*)title.c_str(), titleLen + 1);

	o.write((const char*)&feedbacksCount, sizeof(feedbacksCount));
	for (size_t i = 0; i < feedbacksCount; i++)
	{
		feedbacks[i]->serialize(o);
	}
}