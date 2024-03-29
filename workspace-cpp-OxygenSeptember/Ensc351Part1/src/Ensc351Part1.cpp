//============================================================================
// Name        : Ensc351Part1.cpp
// Version     : September 3rd
// Copyright   : Copyright 2019, Craig Scratchley
// Description : Starting point for Part 1 of Multipart Project
//============================================================================

#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <iostream>

#include "SenderX.h"
#include "myIO.h"

using namespace std;

int testSenderX(const char* iFileName)
{
#ifdef __MINGW32__
	_fmode = _O_BINARY;  // needed for MinGW compiler which runs on MS Windows
#endif

	const char* oFileName = "xmodemSenderData.dat";
	mode_t mode = S_IRUSR | S_IWUSR; // | S_IRGRP | S_IROTH;
	int mediumD = myCreat(oFileName, mode);
	if(mediumD == -1) {
		cout /* cerr */ << "Error opening medium file named: " << oFileName << endl;
		ErrorPrinter("creat(oFileName, mode)", __FILE__, __LINE__, errno);
		return -1;
	}

	SenderX xSender(iFileName, mediumD);
	xSender.Crcflg = false; // test sending with checksum
	cout << "test sending with checksum" << endl;
	xSender.sendFile();
	cout << "Sender finished with result: " << xSender.result << endl << endl;

	SenderX xSender2(iFileName, mediumD);
	xSender2.Crcflg = true; // test sending with CRC
	cout << "test sending with CRC" << endl;
	xSender2.sendFile();
	cout << "Sender finished with result: " << xSender2.result << endl << endl;

	if (-1 == myClose(mediumD)) {
		ErrorPrinter("close(mediumD)", __FILE__, __LINE__, errno);
		return -1;
	}
	else
		return 0;
}

int main() {
	 testSenderX("fileDoesNotExist.txt");
	return testSenderX("inputTextFile.txt");
}
