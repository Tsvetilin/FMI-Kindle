#include "Feedback.hpp"

Feedback::Feedback(String user) {
	this->user = user;
	rating = -1;
}

bool Feedback::addComment(String comment) {
	comments.add(comment);
	return true;
}

size_t Feedback::getRating() const {
	return rating;
}

bool Feedback::setRating(size_t r) {
	if (r > 10) {
		return false;
	}

	rating = r;
	return true;
}

bool Feedback::printComments(std::ostream& o) const {
	for (size_t i = 0; i < comments.getCount(); i++)
	{
		o << user << " wrote: " << comments[i] << std::endl;
	}

	return true;
}

String Feedback::getUser() const{
	return user;
}

void Feedback::serialize(std::ostream& o) const{
	size_t userLen = user.getLength();
	size_t commentsCount = comments.getCount();

	o.write((const char*)&(userLen), sizeof(userLen));
	o.write((const char*)user.c_str(), sizeof(userLen) + 1);

	o.write((const char*)&rating, sizeof(rating));

	o.write((const char*)&commentsCount, sizeof(commentsCount));
	for (size_t i = 0; i < commentsCount; i++)
	{
		size_t l = comments[i].getLength();
		o.write((const char*)&l, sizeof(l));
		o.write((const char*)comments[i].c_str(), l + 1);
	}
}