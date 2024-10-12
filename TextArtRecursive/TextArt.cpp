/*
* Authors: Drew Elliott, Victoria Kukahiko, Forrest Fishel, Branlyn Roberson, Emely Cruz Ramirez, Anthony Michaux-Morrow
* This program allows display and editing of text art (also called ASCII art).
* need to add comments for: edit
*/

#include <iostream>
#include <fstream>
#include <cctype>
#include <windows.h>
#include <conio.h>
#include "Definitions.h"
using namespace std;

int main()
{
	char canvas[MAXROWS][MAXCOLS], backup[MAXROWS][MAXCOLS];
	char oldCh, newCh, choice;
	bool animate = false;

	int row, col;

	// initialize canvas with spaces and copy it to backup
	initCanvas(canvas);
	copyCanvas(backup, canvas);

	do
	{
		// Display the canvas and canvas menu
		displayCanvas(canvas);
		cout << "\n<E>dit / ";
		cout << "<M>ove / ";
		cout << "<R>eplace / ";
		cout << "<D>raw / ";
		cout << "<C>lear / ";
		cout << "<U>ndo / ";
		cout << "<L>oad / ";
		cout << "<S>ave / ";
		cout << "<Q>uit: ";

		// Get the menu choice entry from the user
		cin >> choice;
		// Clear the line for follow up menu options
		clearLine(C_LINE, CHARS);
		// set user menu choice to upper case 
		choice = toupper(choice);
		// if the user chooses edit, move, or replace then create a backup
		if (choice == 'E' || choice == 'M' || choice == 'R' || choice == 'L')
		{
			copyCanvas(backup, canvas);
		}
		switch (choice)
		{
		case 'E':
			editCanvas(canvas);
			break;
		case 'M':
			cout << "Enter column units to move: ";
			cin >> col;
			cout << "Enter row units to move: ";
			cin >> row;
			moveCanvas(canvas, row, col);
			break;
		case 'R':
			cin.ignore();
			cout << "Enter character to replace: ";
			oldCh = cin.get();
			cin.ignore();
			cout << "Enter character to replace with: ";
			newCh = cin.get();
			replace(canvas, oldCh, newCh);
			break;
		case 'D':
			menuTwo(canvas, backup, animate);
			break;
		case 'C':
			initCanvas(canvas);
			break;
		case 'U':
			copyCanvas(canvas, backup);
			break;
		case 'L':
			loadCanvas(canvas);
			break;
		case 'S':
			saveCanvas(canvas);
			break;
		case 'Q':
			return 1;
		}
	} while (choice != 'Q');

	return 0;
}

// moves the cursor to the specified position on the console screen
void gotoxy(short row, short col)
{
	COORD pos = { col, row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// clears a specified line on the console by overwriting its content with spaces.
void clearLine(int lineNum, int numOfChars)
{
	// Move cursor to the beginning of the specified line on the console
	gotoxy(lineNum, 0);

	// Write a specified number of spaces to overwrite characters
	for (int x = 0; x < numOfChars; x++)
		cout << " ";

	// Move cursor back to the beginning of the line
	gotoxy(lineNum, 0);
}


/*
* This function takes the old character and replaces any instance of it
* within the array with the value of the new character
*/

void replace(char canvas[][MAXCOLS], char oldCh, char newCh)
{
	for (int row = 0; row < MAXROWS; row++)
	{
		for (int col = 0; col < MAXCOLS; col++)
		{
			if (canvas[row][col] == oldCh)
			{
				canvas[row][col] = newCh;
			}
		}
	}
}

void editCanvas(char canvas[][MAXCOLS])
{
	char input;
	int row = 0, col = 0;

	cout << "Press <ESC> to stop editing";

	// Move cursor to row,col and then get
	// a single character from the keyboard
	gotoxy(row, col);
	input = _getch();

	while (input != ESC)
	{
		if (input == SPECIAL)
		{
			input = _getch();
			if (input == DOWNARROW && row < MAXROWS - 1)
			{
				row++;
			}
			else if (input == UPARROW && row > 0)
			{
				row--;
			}
			else if (input == RIGHTARROW && col < MAXCOLS - 1)
			{
				col++;
			}
			else if (input == LEFTARROW && col > 0)
			{
				col--;
			}
			gotoxy(row, col);
		}
		else if (input == '\0')
		{
			input = _getch();
		}
		else if (input != SPECIAL && input != '\0')
		{
			input = _getch();
			if (input >= 32 && input <= 126)
			{
				cout << input;
				canvas[row][col] = input;
				gotoxy(row, col);
			}
		}
	}
}

/*function moves the content of a 2D character array (canvas)
by the specified row & column*/
void moveCanvas(char canvas[][MAXCOLS], int rowValue, int colValue)
{
	char temp[MAXROWS][MAXCOLS];
	int row, col;

	initCanvas(temp);

	//content is moved to a temporary array and then copied back to origianl array
	for (int i = 0; i < MAXROWS; ++i)
	{
		for (int j = 0; j < MAXCOLS; ++j)
		{
			row = rowValue + i;
			col = colValue + j;

			if (row >= 0 && row < MAXROWS && col >= 0 && col < MAXCOLS)
			{
				temp[row][col] = canvas[i][j];
			}
		}
	}
	copyCanvas(canvas, temp);
}

// This function sets every element in the canvas array to ' '.
void initCanvas(char canvas[][MAXCOLS])
{
	for (int row = 0; row < MAXROWS; row++)
	{
		for (int col = 0; col < MAXCOLS; col++)
		{
			canvas[row][col] = ' ';
		}
	}
}

//function displays content of a 2D character which represents a canvas
void displayCanvas(char canvas[][MAXCOLS])
{
	// Clear the screen
	system("cls");

	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			cout << canvas[i][j];
		}
		cout << "|\n";
	}

	for (int i = 0; i < MAXCOLS; i++)
	{
		cout << "-";
	}
}

//function copies the content of one 2D character array to another
void copyCanvas(char to[][MAXCOLS], char from[][MAXCOLS])
{
	for (int row = 0; row < MAXROWS; row++)
	{
		for (int col = 0; col < MAXCOLS; col++)
		{
			to[row][col] = from[row][col];
		}
	}
}


//function saves the content of a 2D character array (canvas) to a text file
void saveCanvas(char canvas[][MAXCOLS])
{
	char filename[FILENAMESIZE], filePath[FILENAMESIZE];

	ofstream outFile;

	cin.ignore();

	//asks user for filename, appends ".txt" to file name if not already present
	cout << "Enter the filename (don't enter 'txt'): ";
	cin.getline(filename, FILENAMESIZE);

	//saves file in "SavedFiles" directory
	int getSize = strlen(filename);
	snprintf(filename + getSize, FILENAMESIZE - PATH - getSize, ".txt");
	snprintf(filePath, FILENAMESIZE, "SavedFiles\\%s", filename);

	outFile.open(filePath);

	if (outFile.is_open())
	{
		// copies over content of array into txt file
		for (int i = 0; i < MAXROWS; i++)
		{
			for (int j = 0; j < MAXCOLS; j++)
			{
				outFile << canvas[i][j];
			}
			outFile << '\n';
		}
		cout << "File saved!" << endl;
		outFile.close();
	}
	else
	{
		cout << "ERROR: File cannot be written." << endl;
	}

	system("pause");
}

/*
* Gets a filename from the user. If file can be opened for reading,
* this function loads the file's contents into canvas.
* File is a TXT file located in the SavedFiles folder.
* If file cannot be opened, error message is displayed and
* canvas is left unchanged.
*/
void loadCanvas(char canvas[][MAXCOLS])
{
	// TODO: write code for the function
	// filename will hold the user inputted name of the file
	// filePath will hold the complete filepath including the folder dir and the file type
	char filename[FILENAMESIZE], filePath[FILENAMESIZE], c;

	cin.ignore();

	// Prompts user to enter the filename and stores it in the filename array
	cout << "Enter the filename (don't enter 'txt'): ";
	cin.getline(filename, FILENAMESIZE - PATH);

	// Creates an ifstream object
	ifstream inFile;

	// Combines the file directory, filename, and file type into one string
	int getSize = strlen(filename);
	snprintf(filename + getSize, FILENAMESIZE - getSize, ".txt");
	snprintf(filePath, FILENAMESIZE, "SavedFiles\\%s", filename);

	// Opens the file
	inFile.open(filePath);

	// Initializes the array
	initCanvas(canvas);

	// if the file cannot be opened then print an error message
	if (!inFile)
	{
		cerr << "ERROR: File cannot be read\n";
		system("pause");
	}
	// if the file can be opened then get all of the characters in the file 
	// and pad the remaining elements with spaces
	else
	{
		// loop to iterate through each row of the canvas
		for (int i = 0; i <= MAXROWS; i++)
		{
			// if we are at the bottom edge of the canvas then get characters 
			// until the eof but do not save them
			if (i == MAXROWS)
			{
				while (!inFile.eof())
				{
					inFile.get();
				}
			}
			// if not at the bottom edge then we need to process the columns in the current row
			else
			{
				// loop to iterate through every column in a row
				for (int j = 0; j <= MAXCOLS; j++)
				{
					// holds the character in the column
					c = inFile.get();

					// if we are at the right edge of the canvas then get the remaining characters
					// until we reach the next line but do not save them
					if (j == MAXCOLS)
					{
						while (c != '\n' && !inFile.eof())
						{
							c = inFile.get();
						}
					}
					// if not at right edge then detect if we are at the eof or if there is a next 
					// line character 
					else
					{
						// if the character is a next line character then pad the remaining columns 
						// with spaces in the array. 'x' is a counter that will count until the end
						// of the canvas, starting at j. once the space padding is complete for a given row
						// then j is updated to the position that x is currently at, which is the end of the row. 
						if (c == '\n' || inFile.eof())
						{
							canvas[i][j] = '\n';
							for (int x = j + 1; x < MAXCOLS; x++)
							{
								canvas[i][j] = ' ';
							}
							j = MAXCOLS;
						}
						// if not at the right or bottom edge of the canvas and the character is not a next
						// line character	then save the character in the array
						else
						{
							canvas[i][j] = c;
						}
					}
				}
			}
		}
	}
}