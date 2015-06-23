#pragma once
#include "stdafx.h"

class LogFile;
typedef LogFile * PLogFile;

class LogFile {
private:
	HANDLE hFile;
	LPCWSTR filename;
public:
	LogFile(LPCWSTR infilename);
	void Write(LPWSTR content);
};

