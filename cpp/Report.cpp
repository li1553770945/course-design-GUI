#include "../h/library.h"
#include "../h/global.h"
vector <shared_ptr<BookData>> Report:: _book_vec;
void Report::SetBookVec()
{
	_book_vec.clear();
	for (auto book : books)
	{
		_book_vec.push_back(book.second);
	}
}
void Report::Sort(const char* key)
{
	if (key == "name")
	{
		
	}
}