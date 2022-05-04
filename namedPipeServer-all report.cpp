#include <Windows.h>
#include <iostream>
#include <string>
#include<vector>

using namespace std;
int main()
{
    cout << "\t\t....NAMED PIPE SERVER...." << endl;
    //Named Pipe Local Variable
    HANDLE hCreateNamedPipe = INVALID_HANDLE_VALUE;
    char   szInputBuffer[1023] = { 0 };
    char   szOutputBuffer[1023] = { 0 };
    DWORD  dwszInputBuffer = sizeof(szInputBuffer);
    DWORD  dwszOutputBuffer = sizeof(szOutputBuffer);
    //ConnectNamedpipe Local Variable
    BOOL bConnectNamedPipe = FALSE;
    //WriteFile Local Variable
    BOOL  bWritefile = FALSE;
    char  szWriteFileBuffer[1023] = "Hello From NamedPipe Server!!";
    DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
    DWORD dwNoBytesWrite = 0;

    //FlushBuffer
    BOOL bFlushFIleBuffer = FALSE;
    //ReadFile Local Variable
    BOOL  bReadfile = FALSE;
    char  szReadFileBuffer[1023] = { 0 };
    std::string myString;
    myString.resize(1023);
    DWORD dwReadBufferSize = sizeof(szWriteFileBuffer);
    DWORD dwNoBytesRead = 0;

    //STEP-4 Flush the File Buffer - 
    //bFlushFIleBuffer = FlushFileBuffers(hCreateNamedPipe);
    //if (bFlushFIleBuffer == FALSE)
    //{
     //   cout << "FLushfileBuffer Failed & Error No - " << GetLastError() << endl;
    //}
    //cout << "FLushfileBuffer Success" << endl;
    //STEP-5 ReadFile Operation
    //bConnectNamedPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
    //if (bConnectNamedPipe == FALSE)
    //{
    //    cout << "Connection Failed & Error No - " << GetLastError() << endl;
    //}
    //else {

    //    cout << "Connection Success" << endl;
    //}

    uint32_t counter = 1;
    while (true)
    {
        //STEP-1 Create the Named Pipe 
        hCreateNamedPipe = CreateNamedPipe(
            L"\\\\.\\pipe\\LogAPI",//Pipe Name
            PIPE_ACCESS_DUPLEX,//Open Mode
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,//Max Instances
            dwszOutputBuffer,//Output Buffer
            dwszInputBuffer,//Input Buffer
            0, //Default Time Out
            NULL); //Security Attributes
        if (hCreateNamedPipe == INVALID_HANDLE_VALUE)
        {
            cout << "NamedPipe Creation Failed " << endl;

            cout << "Error No - " << GetLastError() << endl;
        }
        cout << "NamedPipe Creation Success" << endl;
        //STEP-2 Connect the Named Pipe
        if (ConnectNamedPipe(hCreateNamedPipe, NULL) != false) {
            cout << "Connection Success" << endl;
            //std::vector<std::string> logVec;
            std::string logVec;
            while (true) {
                bReadfile = ReadFile(
                    hCreateNamedPipe,//Named Pipe Handle
                    szReadFileBuffer,//Read Buffer
                    dwReadBufferSize,//Read Buffer Size
                    &dwNoBytesRead,//No.of bytes Read from
                    NULL);//Overlapped Parameters
                if (bReadfile == FALSE)
                {
                    cout << "ReadFile Failed = " << GetLastError() << endl;
                    break;
                }
                else {
                    //cout << "ReadFile Success" << endl;
                }

                //cout << " DATA READING FROM CLIENT -> " << szReadFileBuffer << endl;
                /*std::string checkWriteFile{ "WriteFile" };
                std::string checkCreateFile{ "CreateFile" };
                std::string checkCreateFileW{ "CreateFileW" };
                std::string checkCreateProcess{ "CreateProcess" };
                std::string checkCreateProcessW{ "CreateProcessW" };
                std::string test{ szReadFileBuffer };
                if (test.find(checkWriteFile ) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }
                if (test.find(checkCreateFile) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }
                if (test.find(checkCreateFileW) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }
                if (test.find(checkCreateProcess) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }
                if (test.find(checkCreateProcessW) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }*/
                std::string test{ szReadFileBuffer };
                cout << test << " \r\n";
                logVec.append(test);
                logVec.append("\r\n");

            }

            // STEP-6 Disconnect the Named Pipe 
            DisconnectNamedPipe(hCreateNamedPipe);//Named Pipe Handle

            std::string nama_file{ "logApp-" };
            nama_file.append(std::to_string(counter));
            nama_file.append(".txt");
            std::wstring namaFileW{ nama_file.begin(),nama_file.end() };
            HANDLE nHandle = CreateFile(namaFileW.c_str(), GENERIC_WRITE, FILE_SHARE_READ,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL ); // Create file
            if (nHandle == INVALID_HANDLE_VALUE)
            {
                std::cout << "Create File failed with error :" << GetLastError() << " \r\n";
            }
            else {
                DWORD dwBytes = logVec.length();
                LPDWORD apaan = 0;
                LPDWORD apaan2 = 0;
                auto bWrite = WriteFile(nHandle,logVec.data(), dwBytes,apaan , NULL); // Write to File
                if (bWrite == false) {
                    std::cout << "Write fails with error :" << GetLastError() << "\r\n";
                }
                counter++;
            }
            cout << "Connection ended" << endl;
            // STEP-7 CloseHandle 
            CloseHandle(hCreateNamedPipe);
        }
        else {
            std::cout << "connection fail\r\n";
        }
    }
   

    //system("PAUSE");
    return 0;
}