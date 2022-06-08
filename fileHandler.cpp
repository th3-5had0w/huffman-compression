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
	if (fileHandler::infHandler != 0) {
		if (CloseHandle(fileHandler::infHandler) == 0) {
			std::cout << "fileHandler::readFileData -> Failed deallocate fileHandle's memory - Error code: " << GetLastError() << std::endl;
			exit(1);
		}
		fileHandler::infHandler = 0;
	}
	fileHandler::infHandler = CreateFile(inFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandler::infHandler == INVALID_HANDLE_VALUE) {
		std::cout << "fileHandler::readFileData -> Open file returned error code: " << GetLastError() << std::endl;
		exit(1);
	}

	if (GetFileSizeEx(fileHandler::infHandler, &infSize) == INVALID_FILE_SIZE) {
		std::cout << "fileHandler::readFileData -> Cannot get file size!" << std::endl;
		exit(1);
	}
	inBufLen = fileHandler::infSize.QuadPart;
	if (fileHandler::inpBuf != 0) {
		delete[] fileHandler::inpBuf;
		fileHandler::inpBuf = 0;
	}
	if (fileHandler::tmpBuf != 0) {
		delete[] fileHandler::tmpBuf;
		fileHandler::tmpBuf = 0;
	}
	fileHandler::tmpBuf = new char[fileHandler::infSize.QuadPart];
	fileHandler::inpBuf = new short[fileHandler::infSize.QuadPart+1];
	if (fileHandler::tmpBuf == 0 || fileHandler::inpBuf == 0) {
		std::cout << "fileHandler::readFileData -> Error allocating memory for file data!" << std::endl;
		exit(1);
	}
	DWORD byteRead;
	if (!ReadFile(fileHandler::infHandler, fileHandler::tmpBuf, fileHandler::infSize.QuadPart, &byteRead, NULL)) {
		std::cout << "fileHandler::readFileData -> Cannot read from file!" << std::endl;
		exit(1);
	}
	for (size_t i = 0; i < fileHandler::infSize.QuadPart; ++i) {
		fileHandler::inpBuf[i] = fileHandler::tmpBuf[i];
	}
	CloseHandle(fileHandler::infHandler);
	fileHandler::infHandler = 0;
}

void fileHandler::writeFileData(WCHAR* outFilePath) {
	if (fileHandler::outfHandler != 0) {
		if (CloseHandle(fileHandler::outfHandler) == 0) {
			std::cout << "fileHandler::writeFileData -> Failed deallocate fileHandle's memory - Error code: " << GetLastError() << std::endl;
			exit(1);
		}
		fileHandler::outfHandler = 0;
	}
	fileHandler::outfHandler = CreateFile(outFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandler::outfHandler == INVALID_HANDLE_VALUE) {
		std::cout << "fileHandler::writeFileData -> Open file returned error code: " << GetLastError() << std::endl;
		exit(1);
	}

	DWORD byteWritten;
	if (!fileHandler::outBufLen || !WriteFile(fileHandler::outfHandler, fileHandler::outBuf, fileHandler::outBufLen, &byteWritten, NULL)) {
		std::cout << "fileHandler::writeFileData -> Cannot file write!" << std::endl;
		exit(1);
	}
	CloseHandle(fileHandler::outfHandler);
	fileHandler::outfHandler = 0;
}

short* fileHandler::getInpBuffer() {
	if (fileHandler::inpBuf) {
		return fileHandler::inpBuf;
	}
	std::cout << "fileHandler::getInpBuffer -> Input data was not loaded in buffer!" << std::endl;
	exit(1);
}

void fileHandler::setOutpBuffer(std::string bitstr) {
	if (fileHandler::outBuf != 0) {
		delete[] fileHandler::outBuf;
		fileHandler::outBuf = 0;
	}
	fileHandler::outBuf = new unsigned char[bitstr.size()];
	if (fileHandler::outBuf == 0) {
		std::cout << "fileHandler::setOutpBuffer -> Error allocating memory for bitstring!" << std::endl;
	}
	fileHandler::outBufLen = bitstr.size() / 8;
	for (size_t i = 0; i < bitstr.size() / 8; ++i) {
		std::cout << bitstr.substr(i * 8, 8) << std::endl;
		std::bitset<8> bStream(bitstr.substr(i * 8, 8));
		fileHandler::outBuf[i] = LOBYTE(bStream.to_ulong());
		std::cout << (bStream.to_ulong() & 0xff) << std::endl;
	}
	//std::cout << "Output data not loading in buffer!" << std::endl;
	//exit(1);
}

fileHandler::~fileHandler() {
	//CloseHandle(fileHandler::infHandler);
	//CloseHandle(fileHandler::outfHandler);
	delete[] fileHandler::tmpBuf;
	delete[] fileHandler::inpBuf;
	delete[] fileHandler::outBuf;
	fileHandler::infHandler = 0;
	fileHandler::outfHandler = 0;
	fileHandler::tmpBuf = 0;
	fileHandler::inpBuf = 0;
	fileHandler::inBufLen = 0;
	fileHandler::outBuf = 0;
	fileHandler::outBufLen = 0;
}