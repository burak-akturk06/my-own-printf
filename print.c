#include <windows.h>
#include <stdarg.h>

#define MAX_ARRAY_LENGTH 1024
#define ASCII_CHAR_INT_DIFF 48  //integer value of the char '0', also the integer difference between 0 and '0'

static int printFinalArray(char *text, int lengthOfArray);
static int countStringLength(char *arr);
static int intToString(int integer, int indexOfText, char *arr);
static int appendString(char* string, char* arr, int indexOfText);
static int floatToString(float flt, char* arr, int indexOfText);

int print(char *arr, ...)
{
    va_list ap;
    va_start(ap, arr);

    int indexOfText = 0; //the current index of the array text
    int lengthOfArray = 0; //length of the array text
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

                case 'f':
                {
                    int flt = va_arg(ap, float);
                    
                }

                case 's':
                {
                    char *str = va_arg(ap, char*);
                    indexOfText = appendString(str, text, indexOfText);
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
/**
* prints the character array to the console.
* @param text                   the character array to be printed
* @param lengthOfArray          length of the char array which will be printed
* @return numberOfCharsWritten  number of characters succesfully written to the console
*/
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

/**
*   calculates the character number in a character buffer. '\0' is not included in the count
*
* @param arr    a character buffer to calculate its length  
* @return       stringLength  length of the character buffer
*/
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

/**
* Converts an integer into a string and appends the string to a given character buffer.
* 
* @param integer       the integer we want to convert to string
* @param indexOfText   current index of the destination buffer
* @param arr           the destination character buffer where the string will be appended
* @return indexOfText  the updated index of the destination buffer after appending
*
*/

static int intToString(int integer, int indexOfText, char *arr)
{
    int remainder = 0;
    char c;
    char tempArr[32];
    int index = 0;
    if(integer == 0)
    {
        c = ASCII_CHAR_INT_DIFF;  
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

/** 
* appends a string to the given character buffer
*
* @param string         the appended string
* @param arr            the character buffer to append the string
* @param indexOfText    current index of arr when it is passed into the function
* @return indexOfText   current index of arr after string is appended
*/
static int appendString(char* string, char* arr, int indexOfText)
{
    
    while (*string != '\0')
    {
        arr[indexOfText] = *string;
        indexOfText += 1;
        string += 1;
    }
    
    return indexOfText;
}

/**
* converts a float number into a string and appends the string to the given character buffer
* @param flt            a floating point number to convert into string
* @param arr            the destination character buffer where the string will be appended
* @param indexOfText    current index of destination character buffer
* @return indexOfText   current index of destination character buffer after appending
*/
static int floatToString(float flt, char* arr, int indexOfText)
{

    return indexOfText;
}




