#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
void TitleInfo::SetName(const char * const &name)
{
	if (strlen(name) > 50)
		throw "书名不能超过50个字符！";
	strcpy(_name, name);
}
void TitleInfo::SetISBN(const char* const&isbn)
{
	if (strlen(isbn) > 13)
		throw "ISBN编号不能超过13个字符！";
	strcpy(_isbn, isbn);
}
void TitleInfo::SetAuthor(const char * const&auth)
{
	if(strlen(auth)>30)
		throw "作者不能超过30个字符!";
	strcpy(_author, auth);
	
}
void TitleInfo::SetPub(const char* const &Pub)
{
	if(strlen(Pub)>30)
		throw "出版社不能超过30个字符!";
	strcpy(_publisher ,Pub);
}
const char* TitleInfo::GetISBN()
{
	return _isbn;
}
const char* TitleInfo::GetName()
{
	return _name;
}
const char* TitleInfo::GetAuth()
{
	return _author;
}
const char* TitleInfo::GetPub()
{
	return _publisher;
}