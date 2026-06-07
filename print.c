#include <windows.h>
#include <stdarg.h>

#define MAX_ARRAY_LENGTH 1024
#define ASCII_CHAR_INT_DIFF 48

static int printFinalArray(char *text, int lengthOfArray);
static int countStringLength(char *arr);
static int intToString(int integer, int indexOfText, char *arr);

int print(char *arr, ...)
{
    va_list ap;
    va_start(ap, arr);
    // va_arg(ap, char);
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
                    text[indexOfText] = '\0';
                    lengthOfArray = countStringLength(text);
                    return printFinalArray(text, lengthOfArray);
                    break;

                case '%':
                    text[indexOfText] = '%';
                    indexOfText += 1;
                    break;

                case 'i':
                {
                    int integer = va_arg(ap, int);
                    indexOfText = intToString(integer, indexOfText, text);
                    break;
                }

                case 'd':
                {
                    int integer = va_arg(ap, int);
                    indexOfText = intToString(integer, indexOfText, text);
                    break;
                }

                default:
                    break;
            }
        }
        ptrArray += 1;
    }
  
    va_end(ap);
    text[indexOfText] = '\0';
    lengthOfArray = countStringLength(text);
    return printFinalArray(text, lengthOfArray);

}

static int printFinalArray(char *text, int lengthOfArray)
{
    DWORD numberOfCharsWritten = 0;
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

static int intToString(int integer, int indexOfText, char *arr)
{
    int remainder = 0;
    char c;
    char tempArr[32];
    int index = 0;
    if(integer == 0)
    {
        c = '0';
        arr[indexOfText] = c;
        indexOfText += 1;
        return indexOfText;
    }

    if(integer < 0)
    {
        arr[indexOfText] = '-';
        indexOfText += 1;
        integer = -integer;
    }
    while (integer >= 1)
    {
        remainder = integer % 10;
        c = remainder + ASCII_CHAR_INT_DIFF;
        tempArr[index] = c;
        index += 1;
        integer /= 10;
    }
    tempArr[index] = '\0';

    for (int i = 0, j = index - 1; i < j; i++, j--)
    {
        char temp = tempArr[j];
        tempArr[j] = tempArr[i];
        tempArr[i] = temp;
    }
    
    for(int i = 0; i < index; i++)
    {
        arr[indexOfText] = tempArr[i];
        indexOfText += 1;
    }

    return indexOfText;
    
}
