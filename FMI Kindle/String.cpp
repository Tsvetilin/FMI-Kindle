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

String String::substr(size_t index, size_t length = 0) const {
	if (index + length > this->length) {
		length = this->length - index;
	}
	else if (index + length == this->length) {
		return String(string + index);
	}

	char* data = new char[length + 1];
	for (size_t i = 0; i < length; i++)
	{
		data[i] = string[i + index];
	}

	data[length] = '\0';

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

String String::operator+(const String& other) const
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

bool String::operator==(const String& other) const
{
	return strcmp(string, other.c_str()) == 0;
}

bool String::operator>(const String& other) const
{
	return strcmp(string, other.c_str()) > 0;
}
bool String::operator>=(const String& other) const
{
	return strcmp(string, other.c_str()) >= 0;
}

bool String::operator<(const String& other) const
{
	return strcmp(string, other.c_str()) < 0;
}

bool String::operator<=(const String& other) const
{
	return strcmp(string, other.c_str()) <= 0;
}

bool String::operator!=(const String& other) const
{
	return strcmp(string, other.c_str()) != 0;
}

void getline(std::istream& i, String& str) {
	char buff[BUFF_LENGTH];
	std::cin.getline(buff, BUFF_LENGTH);
	str.setString(buff);
}

void String::setString(const char* const str) {
	delete[] string;
	length = strlen(str);
	string = new char[length + 1];
	strcpy(string, str);
}

void serializeString(std::ostream& o, const String& str) {
	o.write((const char*)&str.length, sizeof(str.length));
	o.write((const char*)str.string, str.length);
}

void deserializeString(std::istream& i, String& str) {
	i.read((char*)&str.length, sizeof(str.length));
	char* temp = new char[str.length + 1];
	i.read(temp, str.length);
	temp[str.length] = '\0';
	str.setString(temp);
}

const char& String::operator[](size_t index) const {
	if (index > length) {
		throw "Index out of range exception!";
	}

	return string[index];
}

void String::trim() {
	size_t leadingSpaces = 0;
	while (string[leadingSpaces] == ' ') {
		++leadingSpaces;
	}

	size_t followingSpaces = 0;
	while (string[length - 1 - followingSpaces] == ' ') {
		++followingSpaces;
	}

	*this = substr(leadingSpaces, length - leadingSpaces - followingSpaces);
}

int String::indexOf(char c) {
	for (size_t i = 0; i < length; i++)
	{
		if (string[i] == c) {
			return i;
		}
	}

	return -1;
}