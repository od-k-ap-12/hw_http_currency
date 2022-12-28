#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <codecvt>
#pragma comment(lib, "urlmon.lib")
#include <windows.h>
using namespace std;


wstring JSONFind(wstring& Text, wstring& Find);

int main()
{
    SetConsoleOutputCP(65001); //Set console encoding to utf8

    setlocale(LC_ALL, "ru");
    // the URL to download from
    const char* srcURL1 = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";

    // the destination file
    const char* destFile1 = "currencybankgovua.txt";

    // URLDownloadToFile returns S_OK on success
    if (S_OK == URLDownloadToFileA(NULL, srcURL1, destFile1, 0, NULL))
    {
        cout << "Saved to " << destFile1 << "\n";
    }

    const char* srcURL2 = "https://api.privatbank.ua/p24api/pubinfo?exchange&coursid=5";

    // the destination file
    const char* destFile2 = "currencyprivatbankua.txt";

    // URLDownloadToFile returns S_OK on success
    if (S_OK == URLDownloadToFileA(NULL, srcURL2, destFile2, 0, NULL))
    {
        cout << "Saved to " << destFile2 << "\n";
    }




    wstring txt = TEXT("\"txt\"");
    wstring rate = TEXT("\"rate\"");
    wstring ccy = TEXT("\"ccy\"");
    wstring baseccy = TEXT("\"base_ccy\"");
    wstring buy = TEXT("\"buy\"");
    wstring sale = TEXT("\"sale\"");
    wstring TextFile;
    wstring Line;
    wifstream File;
    File.open("currencybankgovua.txt");
    File.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    while (getline(File, Line)) {
        TextFile += Line;
        TextFile += TEXT(" ");
        wcout<<JSONFind(Line,txt);
        cout << " ";
        wcout<<JSONFind(Line, rate);
        cout << endl;
    }
    File.close();

    File.open("currencyprivatbankua.txt");
    File.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    while (getline(File, Line)) {
        TextFile += Line;
        TextFile += TEXT(" ");
        cout << "ccy: ";
        wcout << JSONFind(Line, ccy);
        cout << " base_ccy: ";
        wcout << JSONFind(Line, baseccy);
        cout << " buy: ";
        wcout << JSONFind(Line, buy);
        cout << " sale:";
        wcout << JSONFind(Line, sale);
        cout << endl;
    }
    File.close();
}

wstring JSONFind(wstring& Text, wstring& Find) {
    wstring Data;
    if (Text.find(Find) == wstring::npos) return TEXT("");
    for (auto i = Text.begin() + Text.find(Find) + Find.length() + 1; *i != ','&&*i!='}'; i++) {
        Data += *i;
    }
    return Data;
}