#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    //Write your code here   
    const int MAXSIZE = 10000;
    char s[MAXSIZE];
    int numChar = 0;

    cin.getline(s, MAXSIZE);

    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (s[i] != ' ')
            numChar++;
        else if (s[i] == ' ')
        {
            for (int j = 1; j <= numChar; j++)
            {
                cout << s[i + j];

                if (j == numChar)
                {
                    cout << s[i];
                    numChar = 0;
                }
            }
        }
    }

    for (int i = 0; i < numChar; i++)
    {
        cout << s[i];
    }
    //use ascii table to find space by type casting each character as 
    //an integer, space = ascii.32
    //could have a counter variable that holds the index of the char array
    //where there is a space. another counter to count each character of 
    //the string, for loop that starts at end of char array
    //counts the number of characters until the counter reaches the space
    //when the space is reached print out the characters using the
    //index minus the number of chars

}