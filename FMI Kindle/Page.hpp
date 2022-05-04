#pragma once
#pragma warning(disable:4996)

#include <iostream>

#include "String.hpp"

class Page
{
	String content;
	size_t number;

public:
	Page(String content, size_t number) {
		this->content = content;
		this->number = number;
	}

	String getContent() const {
		return content;
	}

	bool setContent(String content) {
		this->content = content;
		return true;
	}

	void serialize(std::ostream& o) {
		size_t len = content.getLength();
		o.write((const char*)&len, sizeof(len));
		o.write((const char*)content.c_str(), len + 1);
	}
};
