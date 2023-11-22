//MyString.cpp
#include "MyString.h"
MyString::MyString()
{
	str = nullptr;
	length = 0;
}

MyString::MyString(const char* str)
{
	length = strlen(str);
	this->str = new char[length + 1];

	for (int i = 0; i < length; i++) {
		this->str[i] = str[i];
	}

	this->str[length] = '\0';
}

MyString::MyString(const MyString& other)
{
	this->length = other.length;

	this->str = new char[this->length + 1];

	for (int i = 0; i < this->length; i++) {
		this->str[i] = other.str[i];
	}

	this->str[this->length] = '\0';
}

MyString::~MyString()
{
	delete[] this->str;
}

char *MyString::GetStr()
{
    return strdup(this->str);
}

void MyString::Print()
{
	cout << this->str << endl;
}

int MyString::Length()
{
	return this->length;
}

void MyString::ToUpper()
{
	for (int i = 0; i < length; i++) {
		str[i] = toupper(str[i]);
	}
}

void MyString::ToLower()
{
	for (int i = 0; i < length; i++) {
		str[i] = tolower(str[i]);
	}
}

int MyString::Find(const MyString& other)
{
	int flag = 0;
	for (int i = 0; i + other.length <= this->length; i++) {
		flag = 1;
		for (int j = 0; j < other.length; j++) {
			if (this->str[i + j] != other.str[j]) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) return i;
	}
	return -1;
}

MyString& MyString::Insert(int index, const MyString& other)
{
	MyString temp;
	temp.length = this->length + other.length;
	temp.str = new char[this->length + other.length + 1];
	int i = 0;
	for (; i < index; i++) {
		temp.str[i] = this->str[i];
	}
	for (int j = 0; j < other.length; j++, i++) {
		temp.str[i] = other.str[j];
	}
	for (int k = index; k < length; k++) {
		temp.str[k + other.length] = this->str[k];
	}

	temp.str[temp.length] = '\0';

	delete[] this->str;
	this->length = temp.length;
	this->str = new char[this->length + 1];

	for (int k = 0; k < this->length; k++) {
		this->str[k] = temp.str[k];
	}

	this->str[this->length] = '\0';
	return *this;
}

MyString& MyString::Erase(const MyString& other)
{
	int index = this->Find(other.str);

	if (index == -1) return *this;

	for (int i = index; i < this->length; i++) {
		this->str[i] = this->str[i + other.length];
	}

	this->length = this->length - other.length;

	return *this;
}

MyString& MyString::ConcatWith(const MyString& other)
{
	MyString temp;
	temp.length = this->length + other.length;
	temp.str = new char[this->length + other.length + 1];

	int i = 0;
	for (; i < length; i++) {
		temp.str[i] = this->str[i];
	}

	for (int j = 0; j < other.length; i++, j++) {
		temp.str[i] = other.str[j];
	}

	temp.str[temp.length] = '\0';

	delete[] this->str;
	this->length = temp.length;
	this->str = new char[this->length + 1];

	for (int k = 0; k < length; k++) {
		this->str[k] = temp.str[k];
	}

	this->str[this->length] = '\0';
	return *this;
}

MyString& MyString::operator=(const MyString& other)
{
	this->length = other.length;

	if (this->str != nullptr) {
		delete[] this->str;
	}

	this->str = new char[this->length + 1];

	for (int i = 0; i < this->length; i++) {
		this->str[i] = other.str[i];
	}

	this->str[this->length] = '\0';
	return *this;
}

bool MyString::operator==(const MyString& other)
{
	return this->length == other.length && strcmp(this->str, other.str) == 0;
}

bool MyString::operator!=(const MyString& other)
{
	return !(this->length == other.length && strcmp(this->str, other.str) == 0);
}

bool MyString::operator<(const MyString& other)
{
	return this->str[0] < other.str[0];
}

bool MyString::operator<=(const MyString &other)
{
    return this->str[0] <= other.str[0];
}

bool MyString::operator>(const MyString& other)
{
	if (this->str == other.str) return false;
	return !(this->operator<(other));
}

bool MyString::operator>=(const MyString &other)
{
    return this->str[0] >= other.str[0];
}

MyString MyString::operator+(const MyString& other)
{
	MyString temp;
	temp.length = this->length + other.length;
	temp.str = new char[this->length + other.length + 1];

	int i = 0;
	for (; i < length; i++) {
		temp.str[i] = this->str[i];
	}

	for (int j = 0; j < other.length; i++, j++) {
		temp.str[i] = other.str[j];
	}

	temp.str[temp.length] = '\0';

	return temp;

}

MyString& MyString::operator+=(const MyString& other)
{
	*this = *this + other;
	return *this;
}

char& MyString::operator[](int index)
{
	return this->str[index];
}

MyString& MyString::operator++()
{
	char* temp = new char[(this->length) * 2 + 1];
	int i;
	for (i = 0; i < this->length; i++) {
		temp[i] = this->str[i];
	}
	for (int j = 0; j < this->length; j++) {
		temp[i++] = this->str[j];
	}
	temp[(this->length) * 2] = '\0';
	delete[] this->str;
	this->length = strlen(temp);
	this->str = temp;
	temp = nullptr;
	return *this;
}

MyString MyString::operator++(int xd)
{
	MyString posttemp(*this);
	++*this;
	return posttemp;
}

MyString::operator int()
{
	bool word = false;
	char* temp = new char[length];
	for (int i = 0; i < length; i++) {
		temp[i] = str[i];
		int c = temp[i] - '0';
		if (c < 0 || c > 9) {
			word = true;
			break;
		}
	}
	if (word) {
		delete[] temp;
		return -1;
	}
	else {
		int inttemp = atoi(temp);
		delete[]temp;
		return inttemp;
	}
}

MyString operator-(MyString& Str1, MyString& Str2)
{
	int index = Str1.Find(Str2);

	if (index == -1) return Str1;

	MyString temp = Str1;

	for (int i = index; i < Str1.length; i++) {
		temp[i] = Str1.str[i + Str2.length];
	}

	temp.length = Str1.length - Str2.length;

	return temp;
}

ostream& operator<<(ostream& os, const MyString& str)
{
	if (str.str == nullptr) return os;
	os << str.str;
	return os;
}

//Realization by char
istream& operator>>(istream& is, MyString& str)
{
	char buffer[1024];
	char ch;
	unsigned int i = 0;
	while (i < sizeof(buffer) - 1 && is.get(ch) && ch != '\n') {
		buffer[i] = ch;
		i++;
	}
	buffer[i] = '\0';
	MyString tempstr(buffer);
	str = tempstr;
	return is;
}

ofstream& operator<<(ofstream& ofs, const MyString& str)
{
	int len = str.length;
	ofs.write((char*)&len, sizeof(int));
	ofs.write(str.str, len);
	return ofs;
}

ifstream& operator>>(ifstream& ifs, MyString& str)
{
	int len;
	ifs.read((char*)&len, sizeof(int));
	char* buffer = new char[len + 1];
	ifs.read(buffer, len);
	buffer[len] = '\0';
	MyString tempstring(buffer);
	str = tempstring;
	delete[] buffer;
	return ifs;
}
