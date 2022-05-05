#include "Feedback.hpp"
#include "Helper.hpp"

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
	size_t commentsCount = comments.getCount();

	serializeString(o, user);
	serializePrimitive(o, rating);
	serializePrimitive(o, commentsCount);

	for (size_t i = 0; i < commentsCount; i++)
	{
		serializeString(o, comments[i]);
	}
}

void Feedback::deserialize(std::istream& i) {
	size_t commentsCount = 0;

	deserializeString(i, user);
	deserializePrimitive(i, rating);
	deserializePrimitive(i, commentsCount);

	for (size_t k = 0; k < commentsCount; k++)
	{
		deserializeString(i, comments[k]);
	}
}