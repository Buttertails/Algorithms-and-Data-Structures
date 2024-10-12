#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Definitions.h"
using namespace std;

Point::Point(DrawPoint p)
{
	row = (int)round(p.row);
	col = (int)round(p.col);
}

// https://math.stackexchange.com/questions/39390/determining-end-coordinates-of-line-with-the-specified-length-and-angle
DrawPoint findEndPoint(DrawPoint start, int len, int angle)
{
	DrawPoint end;
	end.col = start.col + len * cos(degree2radian(angle));
	end.row = start.row + len * sin(degree2radian(angle));
	return end;
}


// Use this to draw characters into the canvas, with the option of performing animation
void drawHelper(char canvas[][MAXCOLS], Point p, char ch, bool animate)
{
	// Pause time between steps (in milliseconds)
	const int TIME = 50;

	// Make sure point is within bounds
	if (p.row >= 0 && p.row < MAXROWS && p.col >= 0 && p.col < MAXCOLS)
	{
		// Draw character into the canvas
		canvas[p.row][p.col] = ch;

		// If animation is enabled, draw to screen at same time
		if (animate)
		{
			gotoxy(p.row, p.col);
			printf("%c", ch);
			Sleep(TIME);
		}
	}
}


// Fills gaps in a row caused by mismatch between match calculations and screen coordinates
// (i.e. the resolution of our 'canvas' isn't very good)
void drawLineFillRow(char canvas[][MAXCOLS], int col, int startRow, int endRow, char ch, bool animate)
{
	// determine if we're counting up or down
	if (startRow <= endRow)
		for (int r = startRow; r <= endRow; r++)
		{
			Point point(r, col);
			drawHelper(canvas, point, ch, animate);
		}
	else
		for (int r = startRow; r >= endRow; r--)
		{
			Point point(r, col);
			drawHelper(canvas, point, ch, animate);
		}
}


// Draws a single line from start point to end point
void drawLine(char canvas[][MAXCOLS], DrawPoint start, DrawPoint end, bool animate)
{
	char ch;

	Point scrStart(start);
	Point scrEnd(end);

	// vertical line
	if (scrStart.col == scrEnd.col)
	{
		ch = '|';

		drawLineFillRow(canvas, scrStart.col, scrStart.row, scrEnd.row, ch, animate);
	}
	// non-vertical line
	else
	{
		int row = -1, prevRow;

		// determine the slope of the line
		double slope = (start.row - end.row) / (start.col - end.col);

		// choose appropriate characters based on 'steepness' and direction of slope
		if (slope > 1.8)  ch = '|';
		else if (slope > 0.08)  ch = '`';
		else if (slope > -0.08)  ch = '-';
		else if (slope > -1.8) ch = '\'';
		else ch = '|';

		// determine if columns are counting up or down
		if (scrStart.col <= scrEnd.col)
		{
			// for each column from start to end, calculate row values
			for (int col = scrStart.col; col <= scrEnd.col; col++)
			{
				prevRow = row;
				row = (int)round(slope * (col - start.col) + start.row);

				// draw from previous row to current row (to fill in row gaps)
				if (prevRow > -1)
				{
					drawLineFillRow(canvas, col, prevRow, row, ch, animate);
				}
			}
		}
		else
		{
			// for each column from start to end, calculate row values
			for (int col = scrStart.col; col >= scrEnd.col; col--)
			{
				prevRow = row;
				row = (int)round(slope * (col - start.col) + start.row);

				// draw from previous row to current row (to fill in row gaps)
				if (prevRow > -1)
				{
					drawLineFillRow(canvas, col, prevRow, row, ch, animate);
				}
			}
		}
	}
}


// Draws a single box around a center point
void drawBox(char canvas[][MAXCOLS], Point center, int height, bool animate)
{
	int sizeHalf = height / 2;
	int ratio = (int)round(MAXCOLS / (double)MAXROWS * sizeHalf);

	// Calculate where the four corners of the box should be
	DrawPoint points[4];
	points[0] = DrawPoint(center.row - sizeHalf, center.col - ratio);
	points[1] = DrawPoint(center.row - sizeHalf, center.col + ratio);
	points[2] = DrawPoint(center.row + sizeHalf, center.col + ratio);
	points[3] = DrawPoint(center.row + sizeHalf, center.col - ratio);

	// Draw the four lines of the box
	for (int x = 0; x < 3; x++)
	{
		drawLine(canvas, points[x], points[x + 1], animate);
	}
	drawLine(canvas, points[3], points[0], animate);

	// Replace the corners with a better looking character
	for (int x = 0; x < 4; x++)
	{
		drawHelper(canvas, points[x], '+', animate);
	}
}

// Menu for the drawing tools
void menuTwo(char canvas[][MAXCOLS], char backupCanvas[][MAXCOLS], bool& animate)
{
	char v = 'N', choice, sel;
	int height, b_ang;
	Point coord, s;

	clearLine(C_LINE, CHARS);

	do
	{
		if (animate == true)
			v = 'Y';
		else
			v = 'N';

		displayCanvas(canvas);
		printf("\n<A>nimate: %c / <F>ill / <L>ine / <B>ox / <N>ested Boxes / <T>ree / <M>ain Menu: ", v);
		cin >> choice;
		choice = toupper(choice);
		if (choice != 'A' && choice != 'M')
		{
			clearLine(C_LINE, CHARS);
		}
		switch (choice)
		{
		case 'A':
			if (animate == false)
				animate = true;
			else
				animate = false;
			break;
		case 'F':
		{
			cout << "Enter character to fill with from current location / <ESC> to cancel";
			sel = getPoint(coord);
			clearLine(C_LINE, CHARS);
			if (sel != ESC)
			{
				copyCanvas(backupCanvas, canvas);
				fillRecursive(canvas, coord.row, coord.col, canvas[coord.row][coord.col], sel, animate);
			}
		}
		break;
		case 'L':
		{
			cout << "Type any letter to choose start point / <ESC> to cancel";
			char startPointChar = getPoint(coord);
			if (startPointChar != ESC)
			{
				s = coord;
				copyCanvas(backupCanvas, canvas);
				drawHelper(canvas, coord, startPointChar, animate);
				displayCanvas(canvas);
				cout << "\nType any letter to choose end point / <ESC> to cancel";
				char endPointChar = getPoint(coord);
				if (endPointChar != ESC)
				{
					drawHelper(canvas, coord, endPointChar, animate);
					drawLine(canvas, s, coord, animate);
				}
				drawHelper(canvas, s, ' ', animate);
			}
		}
		break;
		case 'B':
		{
			cout << "Enter size: ";
			cin >> height;
			clearLine(C_LINE, CHARS);
			cout << "Type any letter to choose box center, or <C> for screen center / <ESC> to cancel ";
			sel = getPoint(coord);
			clearLine(C_LINE, CHARS);
			if (sel != ESC)
			{
				if (toupper(sel) == 'C')
				{
					coord.col = COLCENT;
					coord.row = 11;
				}
				copyCanvas(backupCanvas, canvas);
				drawBox(canvas, coord, height, animate);
			}
		}
		break;
		case 'N':
		{
			clearLine(C_LINE + 1, CHARS);
			//sets curser to beginning, prompts user entry
			gotoxy(C_LINE, 0);
			printf("Enter size of largest box: ");
			cin >> height;
			//checks entry
			if (cin.fail())
			{
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			}
			//calls getPoint for placement
			clearLine(C_LINE, CHARS);
			printf("Type any letter to <C> for center / <ESC> to cancel ");
			sel = getPoint(coord);
			clearLine(C_LINE, CHARS);
			//calls function to draw boxes if esc not selected
			if (sel != ESC)
			{
				//checks to see if selected center, places in center
				if (toupper(sel) == 'C')
				{
					coord.col = COLCENT;
					coord.row = MAXROWS / 2;
				}
				copyCanvas(backupCanvas, canvas);
				drawBoxesRecursive(canvas, coord, height, animate);
			}
		}
		break;
		case 'T':
		{
			printf("Enter approximate tree height: ");
			cin >> height;
			clearLine(C_LINE, CHARS);
			printf("Enter branch angle: ");
			cin >> b_ang;
			clearLine(C_LINE, CHARS);
			printf("Type any letter to choose start point, or <C> for bottom center / <ESC> to cancel ");
			sel = getPoint(coord);
			clearLine(C_LINE, CHARS);
			if (sel != ESC)
			{
				if (toupper(sel) == 'C')
				{
					coord.col = COLCENT;
					coord.row = 21;
				}
				copyCanvas(backupCanvas, canvas);
				treeRecursive(canvas, coord, height, 270, b_ang, animate);
			}
		}
		break;
		case 'M':
			break;
		}
	} while (choice != 'M');
}

// Get a single point from screen, with character entered at that point
char getPoint(Point& pt)
{
	int passback;
	gotoxy(0, 0); //starting point
	pt.row = 0, pt.col = 0; //initializes the coordinates

	while (true)
	{
		passback = _getch(); //retrieves character from user input
		if (passback == 0 || passback == 224) //checks for function key vs arrow key
		{
			passback = _getch(); //identifies special key
			//user navigation using arrow keys
			switch (passback)
			{
			case DOWNARROW:
				if (pt.row < MAXROWS - 1) pt.row++;
				break;
			case UPARROW:
				if (pt.row > 0) pt.row--;
				break;
			case RIGHTARROW:
				if (pt.col < MAXCOLS - 1) pt.col++;
				break;
			case LEFTARROW:
				if (pt.col > 0) pt.col--;
				break;
			}
			gotoxy(pt.row, pt.col);
		}
		else if (passback == ESC) //checks if ESC was pressed
		{
			return ESC; //exits
		}
		else
		{
			if (passback >= 32 && passback <= 126) //check for printable character
			{
				return (char)passback; //returns that printable character 
			}
		}
	}
}

// Recursively fill a section of the screen
void fillRecursive(char canvas[][MAXCOLS], int row, int col, char oldCh, char newCh, bool animate)
{
	// TODO: Write the code for the function

	Point p(row, col);

	// Base Case
	// returns if at the bounds of the canvas or if the char doesn't match the one being replaced
	if (row < 0 || row >= MAXROWS || col < 0 || col >= MAXCOLS || canvas[row][col] != oldCh)
		return;
	// if point is a valid spot then draw the character there
	else
		drawHelper(canvas, p, newCh, animate);

	// Recursive Step
	// if we have replaced the previous character with the new character then navigate around the point
	if (canvas[row][col] == newCh)
	{
		fillRecursive(canvas, row, col - 1, oldCh, newCh, animate);
		fillRecursive(canvas, row - 1, col, oldCh, newCh, animate);
		fillRecursive(canvas, row, col + 1, oldCh, newCh, animate);
		fillRecursive(canvas, row + 1, col, oldCh, newCh, animate);
	}

}

// Recursively draw a tree
//treeRecursive is called twice to draw the left & right branches, and drawLine is used to make the vertical lines.
void treeRecursive(char canvas[][MAXCOLS], DrawPoint start, int height, int startAngle, int branchAngle, bool animate)
{
	DrawPoint end = findEndPoint(start, height / 3, startAngle);
	//Base Case
	if (!((height <= 2) || (int)start.row < 0 || (int)start.row > MAXROWS || (int)start.col < 0 || (int)start.col > MAXCOLS || (startAngle % 360 < 0 || startAngle % 360 > 360)))
	{
		//Recursive Case
		drawLine(canvas, start, end, animate);
		treeRecursive(canvas, end, height - 2, startAngle + branchAngle, branchAngle, animate);
		treeRecursive(canvas, end, height - 2, startAngle - branchAngle, branchAngle, animate);
	}
}
// draws nested boxes on a canvas recursively.
void drawBoxesRecursive(char canvas[][MAXCOLS], Point center, int height, bool animate)
{
	// Base case:
	if (height < 2)
	{
		return;
	}
	// draw  box
	drawBox(canvas, center, height, animate);

	//calculate new box
	int x = height - 2;

	// draw nested box by recursion 
	drawBoxesRecursive(canvas, center, x, animate);

}