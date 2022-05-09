#include "Page.hpp"
#include "Helper.hpp"

Page::Page() {
	number = 0;
}

Page::Page(const String& content, size_t number) {
	this->content = content;
	this->number = number;
}

String Page::getContent() const {
	return content;
}

bool Page::setContent(const String& content) {
	this->content = content;
	return true;
}

void Page::serialize(std::ostream& o) const{
	serializePrimitive(o, number);
	serializeString(o, content);
}

void Page::deserialize(std::istream& i) {
	deserializePrimitive(i, number);
	deserializeString(i, content);
}