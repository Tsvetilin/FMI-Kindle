#include "Page.hpp"

Page::Page(String content, size_t number) {
	this->content = content;
	this->number = number;
}

String Page::getContent() const {
	return content;
}

bool Page::setContent(String content) {
	this->content = content;
	return true;
}

void Page::serialize(std::ostream& o) {
	size_t len = content.getLength();
	o.write((const char*)&len, sizeof(len));
	o.write((const char*)content.c_str(), len + 1);
}