#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
void BookData::SetDateAdded(const char* const & date)
{
	if (strlen(date)!=10||!(date[4] == '-' && date[7] == '-'))
	{
		throw "日期格式不合法，日期格式XXXX-XX-XX";
	}
	else
	{
		strcpy(_date_added, date);
	}
	
}
void BookData::SetQty(int qty)
{
	if (qty < 0)
		throw "库存输入错误！";
	_qty = qty;
}
void BookData::SetWholesale(double price)
{
	if (price < 0)
		throw "价格输入错误！";
	_whosale = price;
}
void BookData::SetRetail(double price)
{
	if (price < 0)
		throw "价格输入错误！";
	_retail = price;
}
const char* BookData::GetDateAdded()
{
	return _date_added;
}
double BookData::GetWholesale()
{
	return _whosale;
}
double BookData::GetRetail()
{
	return _retail;
}
int BookData::GetQty()
{
	return _qty;
}