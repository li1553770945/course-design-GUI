#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
set<BookData>::iterator Management::FindISBN(set<BookData>::iterator const& begin, set<BookData>::iterator const& end,const char* const& isbn)
{
	return find_if(begin, end, [isbn](const BookData& rhs) {return !strcmp(rhs.GetISBN(), isbn); });
}
set<BookData>::iterator Management::FindName(set<BookData>::iterator const& begin, set<BookData>::iterator const& end,const char* const& name)
{
	return find_if(begin, end, [name](const BookData& rhs) {return !strcmp(rhs.GetName(), name); });
}
set<BookData>::iterator Management::FuzzySearch(set<BookData>::iterator const& begin, set<BookData>::iterator const& end, const char* const& name)
{
	return find_if(begin, end, [name](const BookData& rhs) {return string(rhs.GetName()).find(name)!=string::npos|| string(rhs.GetAuth()).find(name) != string::npos || string(rhs.GetPub()).find(name) != string::npos; });
}
set<BookData>::iterator Management::FuzzySearchName(set<BookData>::iterator const& begin, set<BookData>::iterator const& end, const char* const& name)
{
	return find_if(begin, end, [name](const BookData& rhs) {return string(rhs.GetName()).find(name) != string::npos; });
}
