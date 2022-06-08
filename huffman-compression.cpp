#include "compressor.h"
#include "fileHandler.h"

int huffmanProcess(fileHandler* fHandler, compressor* Compressor, WCHAR* inpFile, WCHAR* outFile) {
    fHandler->readFileData(inpFile);
    Compressor->getBuffer(fHandler);
    Compressor->calcCharFrequency();
    Compressor->huffmanBuild();
    fHandler->setOutpBuffer(Compressor->createFromChrMapTable());
    fHandler->writeFileData(outFile);
    return 0;
}

int wmain(int argc, WCHAR *argv[])
{
    fileHandler* fHandler = new fileHandler();
    compressor* Compressor = new compressor();
    WIN32_FIND_DATAW findStruct = { 0 };
    HANDLE findHandler = 0;
    std::wstring fNameIn = L".\\Uncompressed\\";
    std::wstring fNameOut = L".\\Compressed\\";

    // first 2 files are ./ and ../ so we don't need to process these.
    findHandler = FindFirstFileW(L".\\Uncompressed\\*", &findStruct);
    if (findHandler == INVALID_HANDLE_VALUE) {
        std::cout << "main -> FindFirstFileA returned: " << GetLastError() << std::endl;
        exit(1);
    }
    else {
        if (FindNextFileW(findHandler, &findStruct) == 0) {
            std::cout << "main -> FindNextFileA returned: " << GetLastError() << std::endl;
        }
    }

    while (FindNextFileW(findHandler, &findStruct) != 0) {
        fNameIn = L".\\Uncompressed\\";
        fNameOut = L".\\Compressed\\";
        fNameIn += findStruct.cFileName;
        fNameOut += findStruct.cFileName;
        fNameOut += L".cps";
        huffmanProcess(fHandler, Compressor, (WCHAR*)fNameIn.data(), (WCHAR*)fNameOut.data());
    }
    //std::wstring asdc = L"dcscdscsc";
    /*
    if (argc != 2) {
        std::wcout << "Usage: " << argv[0] << " <filepath>" << std::endl;
        exit(1);
    }
    
    compressor* fCompressor = new compressor(argv[1]);
    */
    /*
    fHandler->readFileData((WCHAR*)L"hehe.txt");
    Compressor->getBuffer(fHandler);
    Compressor->calcCharFrequency();
    Compressor->huffmanBuild();
    fHandler->setOutpBuffer(Compressor->createFromChrMapTable());
    fHandler->writeFileData((WCHAR*)L"hoho.txt");
    return 0;
    */
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
