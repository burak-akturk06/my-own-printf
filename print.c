#include <windows.h>
#include <stdarg.h>

#define MAX_ARRAY_LENGTH 1024

static int printFinalArray(char *text, int lengthOfArray);
static int countStringLength(char *arr);

int print(char *arr, ...)
{
/*     va_list ap;
    va_start(ap, arr);
    va_arg(ap, char);
    va_end(ap); 
    NOT IMPLEMENTED
    */

    int indexOfText = 0;
    int lengthOfArray = 0;
    char *ptrArray = arr;
    char text[MAX_ARRAY_LENGTH];


    while (*ptrArray != '\0')
    {
        if(*ptrArray != '%')
        {
            text[indexOfText] = *ptrArray;
            indexOfText += 1;
        }

        else if(*ptrArray == '%')
        {
            ptrArray += 1;
            switch (*ptrArray)
            {
                case '\0':
                    lengthOfArray = countStringLength(text);
                    return printFinalArray(text, lengthOfArray);
                    break;

                case '%':
                    text[indexOfText] = '%';
                    indexOfText += 1;
                    break;
                
                default:
                    break;
            }
        }
        ptrArray += 1;
    }
    lengthOfArray = countStringLength(text);
    return printFinalArray(text, lengthOfArray);

}

static int printFinalArray(char *text, int lengthOfArray)
{
    DWORD numberOfCharsWritten = -1;
    const HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (stdHandle != NULL && stdHandle !=INVALID_HANDLE_VALUE)
    {
        WriteConsoleA(stdHandle, text, lengthOfArray, &numberOfCharsWritten, NULL);
    }
    
    return numberOfCharsWritten;
}

static int countStringLength(char *arr)
{
    int stringLength = 0;
    while (*arr != '\0')
    {
        stringLength += 1;
        arr += 1;
    }
    return stringLength;
}







