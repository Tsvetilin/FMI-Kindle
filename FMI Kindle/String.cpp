#pragma warning(disable:4996)

#include "String.hpp"

#include <iostream>

const size_t BUFF_LENGTH = 4096;

void String::copyFrom(const String& other)
{
	string = new char[strlen(other.string) + 1];
	strcpy(string, other.string);
	length = other.length;
}

void String::free()
{
	delete[] string;
}

String::String(const char* data)
{
	if (data == nullptr)
	{
		string = new char[1];
		string[0] = '\0';
		length = 0;
		return;
	}

	length = strlen(data);
	string = new char[length + 1];
	strcpy(string, data);
}



String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

String& String::operator=(const char* const data)
{
	delete[] string;
	length = strlen(data);
	string = new char[length + 1];
	strcpy(string, data);

	return *this;
}

String::~String()
{
	free();
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

	string.length = strlen(buff);
	string.string = new char[string.length + 1];
	strcpy(string.string, buff);

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