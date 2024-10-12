// Authors: Anthony Michaux-Morrow, Branlyn Roberson, Forrest Fishel, Drew Elliott, Victoria Kukahiko, Emely Cruz Ramirez
// Program to implement a very simplified list of tweets 
// from a single simulated Twitter account
// Tweets can be added, deleted, and liked

#include <iostream>
using namespace std;

const int MSGSIZE = 100;	// Maximum size for a tweet message
const int CAPACITY = 10;	// Maximum number of tweets

// Structure used to define a tweet entry
struct Tweet
{
	int id;
	char msg[MSGSIZE];
	int likes;
};


/*
* Prints out an entire timeline to the screen
* timeline = timeline of tweets to be printed
* usedSize = number of tweets in the timeline
* selected = position number of currently selected tweet
*/
void displayTimeline(const Tweet timeline[], int usedSize, int selected);


/*
* Edits currently selected tweet
* with a new message entered by the user.
* timeline = timeline in which the tweet is to be edited
* usedSize = number of tweets in the timeline
* selected = position number of currently selected tweet
* If 'selected' represents a valid array position, the
* selected tweet will be updated.
* If 'selected' is not valid a 'no tweet is selected message' will be
* displayed and no changes will be made.
*/
void doEditTweet(Tweet timeline[], int usedSize, int selected);


/*
* Adds a like to the currently selected tweet.
* timeline = timeline in which the tweet is to be edited
* usedSize = number of tweets in the timeline
* selected = position number of currently selected tweet
* If 'selected' represents a valid array position, the
* selected tweet will be updated.
* If 'selected' is not valid a 'no tweet is selected message' will be
* displayed and no changes will be made.
*/
void doLikeTweet(Tweet timeline[], int usedSize, int selected);


/*
* Deleted currently selected tweet.
* timeline = timeline in from which the entry is to be deleted
* usedSize = number of tweets in the timeline
* If 'selected' represents a valid array position:
*   the selected tweet will be deleted
*   usedSize will be updated to reflect the updated number of tweets in the timeline
*   selected will be updated to -1
* If 'selected' is not valid a 'no tweet is selected message' will be
* displayed and no changes will be made.
*/
void doDeleteTweet(Tweet timeline[], int& usedSize, int& selected);


/*
* If there is room in the timeline for new tweets, then this gets
* a new tweet from the user and adds it to the timeline.
* timeline = timeline in which the tweet is to be added
* usedSize = number of tweets in the timeline
* If tweet was able to be added, returns the position number in the
* timeline of where the item was added, and usedSize will be
* updated to reflect the number of tweets now in the timeline.
* If tweet was not able to be added, returns -1, and usedSize
* remains unchanged.
*/
int doAddTweet(Tweet timeline[], int& usedSize);


/*
* Adds a new tweet to the list
* timeline = timeline in which the entry is to be added
* usedSize = number of tweets in the timeline
* message = tweet message to be added
* If tweet was able to be added, returns the position number in the
* timeline of where the item was added, and usedSize will be
* updated to reflect the number of tweets now in the timeline.
* If tweet was not able to be added, returns -1, and usedSize
* remains unchanged.
*/
int addTweet(Tweet timeline[], int& usedSize, const char message[]);


/*
* Returns the next available ID number
* timeline = timeline in which to find the highest ID
* usedSize = number of tweets in the timeline
* If timeline is empty, returns 100;
* otherwise, returns 1 + highest ID number in the timeline
*/
int getNextId(Tweet timeline[], int usedSize);


/*
* Gets a tweet id from the user. Searches a timeline to try
* to find the specified tweet by its id.
* timeline = timeline to be searched
* usedSize = number of tweets in the timeline
* If the tweet is found, the position number of where the tweet
* is stored in the timeline will be returned.  If the tweet is
* not found, a 'not found message' will be printed, and
* the value -1 will be returned.
* If timeline is empty, an 'empty' message will be printed, and
* the value -1 will be returned.
*/
int selectTweet(const Tweet timeline[], int usedSize);



int main()
{
	Tweet timeline[CAPACITY];	// Twitter timeline
	int choice;					// User's menu choice
	int usedSize = 0;			// Num of tweets in the timeline
	int selected = -1;			// Currently selected tweet
	int tmp;					// Temporary variable

	// Add some starter entries for testing purposes
	selected = addTweet(timeline, usedSize, "Where do they get the seeds to plant seedless watermelons?");
	selected = addTweet(timeline, usedSize, "Waffles are just pancakes with convenient boxes to hold your syrup.");
	selected = addTweet(timeline, usedSize, "Last night I even struck up a conversation with a spider. Turns out he's a web designer.");

	do
	{
		cout << "1. Display Timeline\n";
		cout << "2. Select Tweet\n";
		cout << "3. Add New Tweet\n";
		cout << "4. Edit Selected Tweet\n";
		cout << "5. Like Selected Tweet\n";
		cout << "6. Delete Tweet\n";
		cout << "7. Exit\n";
		cout << endl;
		cout << "Select: ";

		// Get the numeric entry from the menu
		cin >> choice;

		// Corrects issues where user might enter a non-integer value
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Select: ";
			cin >> choice;
		}

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		// Should be used after getting any numeric input from the keyboard
		cin.ignore();

		switch (choice)
		{
		case 1:
			displayTimeline(timeline, usedSize, selected);
			break;
		case 2:
			tmp = selectTweet(timeline, usedSize);
			// if selected tweet exists, update selected variable;
			// otherwise leave it unchanged
			if (tmp > -1)
				selected = tmp;
			break;
		case 3:
			tmp = doAddTweet(timeline, usedSize);
			// if tweet was added, make it be the selected tweet;
			// otherwise leave it unchanged
			if (tmp > -1)
				selected = tmp;
			break;
		case 4:
			doEditTweet(timeline, usedSize, selected);
			break;
		case 5:
			doLikeTweet(timeline, usedSize, selected);
			break;
		case 6:
			doDeleteTweet(timeline, usedSize, selected);
			break;
		}

	} while (choice != 7);

	return 0;
}

/*If there is still room in the array,
asks the user to enter their tweet
Once tweet is entered, calls the addTweet function*/
int doAddTweet(Tweet timeline[], int& usedSize)
{
	if (usedSize < CAPACITY)

	{
		cout << "Enter your tweet: ";
		char message[MSGSIZE];
		cin.getline(message, MSGSIZE);
		return addTweet(timeline, usedSize, message);

	}
	

	cout << "ERROR: Timeline is full\n";
	return -1;

}

// Prompts the user to enter an edited tweet for a selected tweet
// Saves the message in a char array and uses the snprintf function
// to replace the tweet with the new message
void doEditTweet(Tweet timeline[], int usedSize, int selected)
{
	// TODO: Write code for the function
	char msg[MSGSIZE];

	if (selected > -1)
	{
		cout << "Enter Tweet: ";
		cin.getline(msg, MSGSIZE);

		snprintf(timeline[selected].msg, MSGSIZE, "%s", msg);
	}
	else
	{
		cout << "No tweet is selected.\n";
	}
}

//if statement checks if input is a valid tweet and adds a like to selected (valid) tweet    
void doLikeTweet(Tweet timeline[], int usedSize, int selected)
{
	// TODO: Write code for the function
	if (selected >= 0 && selected < usedSize)
	{
		timeline[selected].likes++;
	}
	else
	{
		cout << "No tweet is selected" << endl;
	}
}

// uses printf to format menu easily 
// if loop to have the arrow placed at the correct tweet
void displayTimeline(const Tweet timeline[], int usedSize, int selected)
{
	printf("\nTweets: \n\nSel \t  ID \t Likes \t Tweet\n");
	if (usedSize == 0)
	{
		printf("\t  ***** Empty *****\n");
	}
	else if (usedSize > 0)
	{
		for (int i = 0; i < usedSize; i++)
		{
			if (i == selected)
			{
				printf("-->");
			}
			else

			{
				printf("");
			}

			printf("\t %d \t %5d \t %s \n", timeline[i].id, timeline[i].likes, timeline[i].msg);
		}
	}
	cout << endl;
}

/*Checks to make sure there is still room to add another tweet.
If so, utilizes getNextId to identify the tweet. Copies the message,
to the end of the array and sets likes to 0. Increments used size by one.*/
int addTweet(Tweet timeline[], int& usedSize, const char message[])
{

	if (usedSize < CAPACITY)
	{
		int id = getNextId(timeline, usedSize);
		timeline[usedSize].id = id;

		snprintf(timeline[usedSize].msg, MSGSIZE, "%s", message);

		timeline[usedSize].likes = 0;
		usedSize++;

		return usedSize - 1;
	}

	return -1;

}


int getNextId(Tweet timeline[], int usedSize)
{
	if (usedSize == 0)
	{
		return 100;
	}
	else
	{
		// Initialize MaxID w/ ID of first tweet
		int MaxID = timeline[0].id;
		// Loop through the timeline aray to find largest ID
		for (int i = 1; i < usedSize; ++i)
		{
			// If current tweet ID value > MaxID update MaxID
			if (timeline[i].id > MaxID)
			{
				MaxID = timeline[i].id;
			}
		}
		return MaxID + 1;
	}
}

//if a tweet is selected, removes the selected tweet, and aligns all the values from the deleted position to the end
//otherwise a message printed saying a tweet needs to be selected
void doDeleteTweet(Tweet timeline[], int& usedSize, int& selected)
{
	if ((selected != -1) && (selected > -1 && selected < usedSize))
	{
		if (selected == usedSize)
		{
			usedSize--;
			selected = -1;
		}
		else
		{
			for (int i = selected; i < usedSize; i++)
			{
				timeline[i].id = timeline[i + 1].id;
				timeline[i].likes = timeline[i + 1].likes;
				snprintf(timeline[i].msg, MSGSIZE, timeline[i + 1].msg);
			}
			usedSize--;
			selected = -1;
		}
	}
	else
	{
		printf("No tweet is selected.\n");
	}
}

int selectTweet(const Tweet timeline[], int usedSize)
{
	if (usedSize == 0)
	{
		cout << "Timeline is empty\n";
		return -1;
	}
	else
	{
		int id;
		cout << "Please enter the ID of desired tweet: ";
		cin >> id;
		// check if valid ID
		if (!cin)
		{
		// Clear error state
			cin.clear();
		}
		//Ignore until new line
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		// Loop through all tweets in the timeline
		for (int i = 0; i < usedSize; ++i)
		{
		// If matching ID is found return index
			if (timeline[i].id == id)
			{
				return i;
			}
		}
		cout << "No tweet is selected\n";
		return -1;
	}
}