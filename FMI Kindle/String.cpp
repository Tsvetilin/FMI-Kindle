#pragma warning(disable:4996)

#include "String.hpp"

#include <iostream>

const size_t BUFF_LENGTH = 4096;

String::String(const char* data) : string(nullptr)
{
	if (data == nullptr)
	{
		setString("");
		return;
	}

	setString(data);
}

String::String(const String& other) : string(nullptr)
{
	setString(other.string);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		setString(other.string);
	}
	return *this;
}

String& String::operator=(const char* const data)
{
	setString(data);
	return *this;
}

String::~String()
{
	delete[] string;
}


size_t String::getLength() const
{
	return length;
}

void String::concat(const String& other)
{
	length += other.length;

	char* temp = new char[length + 1];
	strcpy(temp, string);
	strcat(temp, other.string);

	delete[] string;
	string = temp;
}

String String::substr(size_t index, size_t length = 0) {
	if (index + length > this->length) {
		length = this->length - index;
	}

	char* data = new char[length + 1];
	length += index;
	for (size_t i = index; i < length; i++)
	{
		data[i - index] = string[i];
	}

	String result(data);

	delete[] data;
	return result;
}

const char* String::c_str() const
{
	return string;
}

String& String::operator+=(const String& other)
{
	concat(other);
	return *this;
}

String String::operator+(const String& other)
{
	String left(*this);
	left += other;
	return left;
}

std::ostream& operator<<(std::ostream& o, const String& string)
{
	o << string.string;
	return o;
}

std::istream& operator>>(std::istream& i, String& string)
{
	delete[] string.string;
	char buff[BUFF_LENGTH];
	i >> buff;
	string.setString(buff);
	return i;
}

bool String::operator==(const String& other)
{
	return strcmp(string, other.c_str()) == 0;
}

bool String::operator>(const String& other)
{
	return strcmp(string, other.c_str()) > 0;
}
bool String::operator>=(const String& other)
{
	return strcmp(string, other.c_str()) >= 0;
}

bool String::operator<(const String& other)
{
	return strcmp(string, other.c_str()) < 0;
}

bool String::operator<=(const String& other)
{
	return strcmp(string, other.c_str()) <= 0;
}

std::istream& getline(std::istream& i, String& str) {
	char buff[BUFF_LENGTH];
	std::cin.getline(buff, BUFF_LENGTH);
	str.setString(buff);

	return i;
}

void String::setString(const char* const str) {
	delete[] string;
	length = strlen(str);
	string = new char[length + 1];
	strcpy(string, str);
}