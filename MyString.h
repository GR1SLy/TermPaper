//MyString.h
#pragma once

#ifndef _MYSTRING_H

#define _MYSTRING_H

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class MyString
{
private:
	char* str;
	int length;
public:

	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	virtual ~MyString();
	char* GetStr();
	virtual void Print();
	int Length();
	void ToUpper();
	void ToLower();
	int Find(const MyString& other);
	virtual MyString& Insert(int index, const MyString& other);
	virtual MyString& Erase(const MyString& other);
	virtual MyString& ConcatWith(const MyString& other);
	MyString& operator=(const MyString& other);
	bool operator==(const MyString& other);
	bool operator!=(const MyString& other);
	bool operator<(const MyString& other);
	bool operator<=(const MyString& other);
	bool operator>=(const MyString& other);
	bool operator>(const MyString& other);
	MyString operator+(const MyString& other);
	virtual MyString& operator+=(const MyString& other);
	char& operator[](int index);
	friend MyString operator-(MyString& str1, MyString& str2);
	virtual MyString& operator ++();
	virtual MyString operator ++(int xd);
	operator int();
	friend ostream& operator<<(ostream& os, const MyString& str);
	friend istream& operator>>(istream& is, MyString& str);
	friend ofstream& operator<<(ofstream& ofs, const MyString& str);
	friend ifstream& operator>>(ifstream& ifs, MyString& str);
};

#endif 
