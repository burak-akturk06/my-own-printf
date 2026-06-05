#include <windows.h>

int print(char *arr)
{
    DWORD numberOfCharsWritten;
    const HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (stdHandle != NULL && stdHandle !=INVALID_HANDLE_VALUE)
    {
        WriteConsoleA(stdHandle, arr, strlen(arr),&numberOfCharsWritten ,NULL);
    }
    
    return numberOfCharsWritten;
}







