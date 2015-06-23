#include "LogFile.h"


LogFile::LogFile(LPCWSTR infilename) {
	this->filename = infilename;
}

void LogFile::Write(TCHAR content[]) {

	hFile = CreateFile(
		filename,				// name of the write
		GENERIC_WRITE,			// open for writing
		0,						// do not share
		NULL,					// default security
		OPEN_ALWAYS,			// create mode
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBoxEx(NULL, _T("Error creating log file."), _T("Error"), MB_ICONERROR, NULL);
		return;
	}

	SetFilePointer(hFile, 0, NULL, FILE_END);
	
	DWORD dwBytesWritten = 0;

	bool bErrorFlag = WriteFile(
		hFile,           // open file handle
		content,         // start of data to write
		lstrlen(content),  // number of bytes to write
		&dwBytesWritten, // number of bytes that were written		
		NULL);           // no overlapped structure
	if (!bErrorFlag) {
		MessageBoxEx(NULL, _T("Error writing to log file."), _T("Error"), MB_ICONERROR, NULL);
	}

	CloseHandle(hFile);
}