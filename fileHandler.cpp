#include "fileHandler.h"

fileHandler::fileHandler() {
	fileHandler::infHandler = 0;
	fileHandler::outfHandler = 0;
	fileHandler::tmpBuf = 0;
	fileHandler::inpBuf = 0;
	fileHandler::inBufLen = 0;
	fileHandler::outBuf = 0;
	fileHandler::outBufLen = 0;
}

void fileHandler::readFileData(WCHAR* inFilePath) {
	fileHandler::infHandler = CreateFile(inFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandler::infHandler == INVALID_HANDLE_VALUE) {
		std::cout << "Open file returned error code: " << GetLastError() << std::endl;
		exit(1);
	}

	if (GetFileSizeEx(fileHandler::infHandler, &infSize) == INVALID_FILE_SIZE) {
		std::cout << "Cannot get file size!" << std::endl;
		exit(1);
	}
	inBufLen = fileHandler::infSize.QuadPart;
	fileHandler::tmpBuf = new char[fileHandler::infSize.QuadPart];
	fileHandler::inpBuf = new short[fileHandler::infSize.QuadPart+1];
	DWORD byteRead;
	if (!ReadFile(fileHandler::infHandler, fileHandler::tmpBuf, fileHandler::infSize.QuadPart, &byteRead, NULL)) {
		std::cout << "Cannot read file!" << std::endl;
		exit(1);
	}
	for (size_t i = 0; i < fileHandler::infSize.QuadPart; ++i) {
		fileHandler::inpBuf[i] = fileHandler::tmpBuf[i];
	}
}

void fileHandler::writeFileData(WCHAR* outFilePath) {
	fileHandler::outfHandler = CreateFile(outFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandler::outfHandler == INVALID_HANDLE_VALUE) {
		std::cout << "Open file returned error code: " << GetLastError() << std::endl;
		exit(1);
	}

	DWORD byteWritten;
	if (!fileHandler::infSize.QuadPart || !WriteFile(fileHandler::outfHandler, fileHandler::outBuf, fileHandler::infSize.QuadPart, &byteWritten, NULL)) {
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

void fileHandler::setOutpBuffer(std::string bitstr) {
	for (size_t i = 0; i < bitstr.size() / 8; ++i) {
		std::cout << bitstr.substr(i * 8, 8) << std::endl;
		std::bitset<8> bStream(bitstr.substr(i * 8, 8));
		std::cout << bStream.to_ulong() << std::endl;
	}
	//std::cout << "Output data not loading in buffer!" << std::endl;
	//exit(1);
}

fileHandler::~fileHandler() {
	fileHandler::infHandler = 0;
	fileHandler::outfHandler = 0;
	fileHandler::tmpBuf = 0;
	fileHandler::inpBuf = 0;
	fileHandler::inBufLen = 0;
	fileHandler::outBuf = 0;
	fileHandler::outBufLen = 0;
}