//source: https://stackoverflow.com/a/52617785
#include <iostream>
#include <ShlObj.h>
#include <atlbase.h>  // for CComPtr, CComHeapPtr
#include <string.h>

using namespace std;
struct ComInit
{
    ComInit() { CoInitialize(nullptr); }
    ~ComInit() { CoUninitialize(); }
};
string open_file() {
    // Initialize COM to be able to use classes like IFileOpenDialog.
    ComInit com;
    string str;

    // Create an instance of IFileOpenDialog.
    CComPtr<IFileOpenDialog> pDlg;
    pDlg.CoCreateInstance(CLSID_FileOpenDialog);
    COMDLG_FILTERSPEC aFileTypes[] = {
    { L"photo", L"*.jpg;*.jpeg;*.bmp;*.png;*.gif;*.tiff;*.psd" }
    };

    pDlg->SetFileTypes(_countof(aFileTypes), aFileTypes);
    pDlg->SetTitle(L"A Single-Selection Dialog");
    // Show the dialog modally.
    if (SUCCEEDED(pDlg->Show(nullptr)))
    {
        // Get the path of the selected folder 

        CComPtr<IShellItem> pSelectedItem;
        pDlg->GetResult(&pSelectedItem);

        CComHeapPtr<wchar_t> pPath;
        pSelectedItem->GetDisplayName(SIGDN_FILESYSPATH, &pPath);

        //change the path to string 
        wstring ws(pPath);
        str=string(ws.begin(), ws.end());

        return str;
    }
    return str;


    // The destructor of ComInit calls CoUninitialize() here after all
    // other objects have been destroyed. 
}
