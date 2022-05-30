#include "fileHandler.h"

fileHandler::fileHandler() {
	infHandler = 0;
	outfHandler = 0;
	tmpBuf = 0;
	inBufLen = 0;
	outBuf = 0;
	outBufLen = 0;
}

void fileHandler::readFileData(WCHAR* inFilePath) {
	infHandler = CreateFile(inFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (infHandler == INVALID_HANDLE_VALUE) {
		std::cout << "Open file returned error code: " << GetLastError() << std::endl;
		exit(1);
	}

	if (GetFileSizeEx(infHandler, &infSize) == INVALID_FILE_SIZE) {
		std::cout << "Cannot get file size!" << std::endl;
		exit(1);
	}
	inBufLen = infSize.QuadPart;
	tmpBuf = new char[infSize.QuadPart];
	inpBuf = new short[infSize.QuadPart+1];
	DWORD byteRead;
	if (!ReadFile(infHandler, tmpBuf, infSize.QuadPart, &byteRead, NULL)) {
		std::cout << "Cannot read file!" << std::endl;
		exit(1);
	}
	for (size_t i = 0; i < infSize.QuadPart; ++i) {
		inpBuf[i] = tmpBuf[i];
	}
	//WCHAR* b = (WCHAR*)tmpBuf;
}

void fileHandler::writeFileData(WCHAR* outFilePath) {
	outfHandler = CreateFile(outFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (outfHandler == INVALID_HANDLE_VALUE) {
		std::cout << "Open file returned error code: " << GetLastError() << std::endl;
		exit(1);
	}

	DWORD byteWritten;
	if (!infSize.QuadPart || !WriteFile(outfHandler, outBuf, infSize.QuadPart, &byteWritten, NULL)) {
		std::cout << "Cannot file write!" << std::endl;
		exit(1);
	}
}

short* fileHandler::getInpBuffer() {
	if (fileHandler::inpBuf) {
		return fileHandler::inpBuf;
	}
	std::cout << "Input data not loading in buffer!" << std::endl;
	exit(1);
}

short* fileHandler::getOutpBuffer() {
	if (fileHandler::outBuf) {
		return fileHandler::outBuf;
	}
	std::cout << "Output data not loading in buffer!" << std::endl;
	exit(1);
}

fileHandler::~fileHandler() {
	infHandler = 0;
	outfHandler = 0;
	tmpBuf = 0;
	outBuf = 0;
}