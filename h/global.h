#pragma once
#include "library.h"
extern set<BookData> books;

int my_atoi(const char* const &);
double my_atof(const char* const &);
enum class FileStatus { SUCCESS, NOTEXIST, CANNOTOPEN, CANNOTCREATE };
void OpenFile();
void CreateFile();
void SaveFile();