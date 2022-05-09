/* Copyright awinsyspro.com 2019-2020*/

#include<Windows.h>
#include<iostream>
using namespace std;
int main()
{
    //Local Variable
    HANDLE hProcess;
    HANDLE hThread;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessID;
    DWORD dwThreadID;
    BOOL bProcess;
    //Fills block of structure memory with zero
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    //STEP-1 Create Process Function

    wchar_t commandline_args[] = L"\"C:\Program Files\Sandboxie-Plus\\Start.exe\" C:\\Windows\\system32\\notepad.exe";

    bProcess = CreateProcess(
        NULL,//App Name 
        commandline_args,//Command Line
        NULL,//Not Inheritable Process Handle
        NULL,//Not Inheritable Thread Handle
        FALSE,//Handle Inheritance FALSE
        0, //No Creation Flag
        NULL,// Parent's Environment Block
        NULL,//Parent's Process Directory
        &si,//STARTUPINFO Structure
        &pi);//PROCESS_INFORMATION Structure
   //STEP-2 Check Process has created or not.
    if (bProcess == FALSE)
    {
        cout << "Create Process Failed" << endl;
        cout << "Error No - " << GetLastError() << endl;
    }
    cout << "Create Process Success" << endl;
    //STEP-3 Print Process ID and Thread ID
    cout << "Process ID - " << pi.dwProcessId << endl;
    cout << "Thread ID - " << pi.dwThreadId << endl;
    cout << "Process ID - " << GetProcessId(pi.hProcess) << endl;
    cout << "Thread ID - " << GetThreadId(pi.hThread) << endl;
    //STEP-4 Wait until child process Exit
    WaitForSingleObject(pi.hProcess, INFINITE);
    //STEP-5 Close the open Handle for Process and its Primary Thread
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    system("PAUSE");
    return 0;
}