#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
void BookData::SetDateAdded(const char* const & date)
{
	
	strcpy(_date_added, date);
	
}
void BookData::SetQty(int qty)
{
	if (qty < 0)
		throw "¿â´æÊäÈë´íÎó£¡";
	_qty = qty;
}
void BookData::SetWholesale(double price)
{
	if (price < 0)
		throw "¼Û¸ñÊäÈë´íÎó£¡";
	_whosale = price;
}
void BookData::SetRetail(double price)
{
	if (price < 0)
		throw "¼Û¸ñÊäÈë´íÎó£¡";
	_retail = price;
}
const char* BookData::GetDateAdded()const
{
	return _date_added;
}
double BookData::GetWholesale()const
{
	return _whosale;
}
double BookData::GetRetail()const
{
	return _retail;
}
int BookData::GetQty()const 
{
	return _qty;
}
bool BookData::operator<(const BookData &rhs)const 
{
	return strcmp(_isbn, rhs.GetISBN())<0;
}