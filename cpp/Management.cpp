#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
bool Management::FindISBN(set<BookData>const& books, set<BookData>::iterator &it,const char* const& isbn)
{
	BookData temp;
	try
	{
		temp.SetISBN(isbn);
	}
	catch (const char*)
	{
		return false;
	}
	it = books.find(temp);
	if (it == books.end())
		return false;
	else
		return true;
}
bool Management::FindISBN(set<BookData>const& books, const char* const& isbn)
{
	BookData temp;
	try
	{
		temp.SetISBN(isbn);
	}
	catch (const char*)
	{
		return false;
	}
	if (books.find(temp) == books.end())
		return false;
	else
		return true;
}

