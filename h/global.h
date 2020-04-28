#pragma once
#include "library.h"
#include <bits/stdc++.h>
using namespace std;
typedef  map< string, shared_ptr<BookData> > Books;
typedef Books::iterator BooksIt;
extern Books books;
class System
{
public:
	double _fax;
};
int my_atoi(const char* const&);
double my_atof(const char* const&);
enum class FileStatus { SUCCESS, NOTEXIST, CANNOTOPEN, CANNOTCREATE };
void OpenFile();
void CreateFile();
void SaveFile();