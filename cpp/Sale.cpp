#include "../h/library.h"
double Sale::GetFax()
{
	return _fax_;
}
void Sale::SetFax(double fax)
{
	_fax_ = fax;
}
double Sale::_fax_ = 0.06;
