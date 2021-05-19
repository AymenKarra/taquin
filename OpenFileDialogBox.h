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
    CComPtr<IFileOpenDialog> pFolderDlg;
    pFolderDlg.CoCreateInstance(CLSID_FileOpenDialog);
    // Show the dialog modally.
    if (SUCCEEDED(pFolderDlg->Show(nullptr)))
    {
        // Get the path of the selected folder 

        CComPtr<IShellItem> pSelectedItem;
        pFolderDlg->GetResult(&pSelectedItem);

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
