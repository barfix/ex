/******************************************
* Bar Atuar
* 208648469
* 83-120-04
* Ex 1
******************************************/

#include <stdio.h>
#include <string.h>

#define STR_ARRAY_MAX_SIZE 30

bool compareStrings(char *pstringToCompare, char *pexitString);
bool stringLength(char *pfirstString, char *psecondString, int diffNum);
void DiffersInNChars(char *s1, char *s2, int n);

int main()
{
    char answer, firstString[STR_ARRAY_MAX_SIZE] = {0}, secondString[STR_ARRAY_MAX_SIZE] = {0}, exitString[] = "exit", buffer;
    char *panswer, *pfirstString, *psecondString, *pexitString = exitString;
    bool isContinue = true, isExit = false, isBigger = false;
    int diffNum;
    while (isContinue)
    {
        printf("do you want to exit (y/n)?\n");
        scanf(" %c", &answer);
        buffer = getchar(); // gets rid of the \n of the scanf function
        if (*panswer != 'y')
        {
            printf("please insert the first string (to exit please insert the word exit):\n");

            fgets(firstString, STR_ARRAY_MAX_SIZE, stdin);
            pfirstString = firstString;
            isExit = compareStrings(pfirstString, pexitString);
            if (!isExit)
            {
                printf("please insert the second string (to exit please insert the word exit):\n");
                fgets(secondString, STR_ARRAY_MAX_SIZE, stdin);
                psecondString = secondString;
                isExit = compareStrings(psecondString, pexitString);
                if (!isExit)
                {
                    printf("please insert difference number:\n");
                    scanf("%d", &diffNum);
                    buffer = getchar(); // gets rid of the \n of the scanf function
                    isBigger = stringLength(pfirstString, psecondString, diffNum);
                    if (!isBigger)
                    {
                        DiffersInNChars(pfirstString, psecondString, diffNum);
                    }
                    else
                        isContinue = !isContinue;
                }
                else
                    isContinue = !isContinue;
            }
            else
                isContinue = !isContinue;
        }
        else
            isContinue = !isContinue;
    }
    return 0;
}

/**
 * Compares the user inserted string to the string "exit", if they're the same returns true else, returns false.
 * @param pstringToCompare pointer to the user inserted string
 * @param pexitString pointer to the string "exit"
 */
bool compareStrings(char *pstringToCompare, char *pexitString)
{
    bool isExit = false;

    if (*pexitString == '\0' && *pstringToCompare == '\n')
        isExit = !isExit;
    else if (*pexitString == *pstringToCompare)
    {
        pstringToCompare++;
        pexitString++;
        isExit = compareStrings(pstringToCompare, pexitString);
    }
    return isExit;
}

/**
 * Checks if the user inserted number is bigger than the longer of the two user inserted strings.
 * @param pfirstString pointer to the first user inserted string
 * @param psecondString pointer to the second user inserted string
 * @param diffNum the user inserted number
 */
bool stringLength(char *pfirstString, char *psecondString, int diffNum)
{
    const char End_Of_String = '\n';
    int length = 0;
    bool isEndOfStrings = false, isBigger = false;
    while (!isEndOfStrings)
    {
        if (*pfirstString == End_Of_String && *pfirstString == End_Of_String)
            isEndOfStrings = !isEndOfStrings;

        else
        {
            if (*pfirstString != End_Of_String)
                pfirstString++;

            if (*psecondString != End_Of_String)
                psecondString++;

            length++;
        }
    }
    if (diffNum > length)
        isBigger = !isBigger;

    return isBigger;
}

/**
 * Checks if there is a difference of n characters between the two user inserted strings, prints "yes" if true and "no" if false.
 * @param s1 pointer to the first user inserted string
 * @param s2 pointer to the second user inserted string
 * @param n the number of different characters to check
 */
void DiffersInNChars(char *s1, char *s2, int n)
{
    const char End_Of_String = '\n';
    bool isEqual = false;
    if (*s1 == End_Of_String && *s2 == End_Of_String)
    {
        if (n == 0)
            printf("\"yes\"\n");
        else
            printf("\"no\"\n");
    }
    else
    {
        if (*s1 != *s2)
            n--;
        if (*s1 != End_Of_String)
            s1++;
        if (*s2 != End_Of_String)
            s2++;

        DiffersInNChars(s1, s2, n);
    }
}