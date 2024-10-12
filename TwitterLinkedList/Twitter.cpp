// Authors: Anthony Michaux-Morrow, Branlyn Roberson, Forrest Fishel, Drew Elliott, Victoria Kukahiko, Emely Cruz Ramirez
// Program to implement a very simplified list of tweets 
// from a single simulated Twitter account
// Tweets can be added, deleted, and liked

#include <iostream>
using namespace std;

const int MSGSIZE = 100;	// Maximum size for a tweet message

// Structure used to define a tweet entry
struct Tweet
{
	int id;
	char msg[MSGSIZE];
	int likes;
};

struct Node
{
	Tweet tweet;
	Node* next;
};


/*
* Prints out an entire timeline to the screen
* timeline = timeline of tweets to be printed
* usedSize = number of tweets in the timeline
* selected = position number of currently selected tweet
*/
void displayTimeline(Node* timeline, Node* selected);


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
void doEditTweet(Node* selected);


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
void doLikeTweet(Node* selected);


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
void doDeleteTweet(Node*& timeline, Node*& selected);


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
Node* doAddTweet(Node*& timeline);


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
Node* addTweet(Node*& timeline, const char message[]);


/*
* Returns the next available ID number
* timeline = timeline in which to find the highest ID
* usedSize = number of tweets in the timeline
* If timeline is empty, returns 100;
* otherwise, returns 1 + highest ID number in the timeline
*/
int getNextId(Node* timeline);


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
Node* selectTweet(Node* timeline); //was int

void deleteList(Node*& timeline);

int main()
{
	Node* timeline = NULL;		// Twitter timeline
	Node* selected;				// Currently selected tweet
	int choice;					// User's menu choice
	Node* tmp;					// Temporary variable

	// Add some starter entries for testing purposes
	selected = addTweet(timeline, "Where do they get the seeds to plant seedless watermelons?");
	selected = addTweet(timeline, "Waffles are just pancakes with convenient boxes to hold your syrup.");
	selected = addTweet(timeline, "Last night I even struck up a conversation with a spider. Turns out he's a web designer.");

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
			cin >> choice;
		}

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		// Should be used after getting any numeric input from the keyboard
		cin.ignore();

		switch (choice)
		{
		case 1:
			displayTimeline(timeline, selected);
			break;
		case 2:
			tmp = selectTweet(timeline);
			if (tmp != nullptr)
				selected = tmp;
			break;
		case 3:
			// if tweet was added, make it be the selected tweet;
			// otherwise leave it unchanged
			selected = doAddTweet(timeline);
			break;
		case 4:
			doEditTweet(selected);
			break;
		case 5:
			doLikeTweet(selected);
			break;
		case 6:
			doDeleteTweet(timeline, selected);
			break;
		}

	} while (choice != 7);

	deleteList(timeline);

	return 0;
}

/*If there is still room in the array,
asks the user to enter their tweet
Once tweet is entered, calls the addTweet function*/
Node* doAddTweet(Node*& timeline) //int& usedSize) //int
{

	cout << "Enter your tweet: ";
	char message[MSGSIZE];
	cin.getline(message, MSGSIZE);
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.getline(message, MSGSIZE);
	}	
	return addTweet(timeline, message);

}

// Prompts the user to enter an edited tweet for a selected tweet
// Saves the message in the selected node by using the snprintf function
// and replaces the tweet with the new message
void doEditTweet(Node* selected)
{
	// TODO: Write code for the function
	char msg[MSGSIZE];

	if (selected != nullptr)
	{
		cout << "Enter Tweet: ";
		cin.getline(msg, MSGSIZE);
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.getline(msg, MSGSIZE);
		}
		snprintf(selected->tweet.msg, MSGSIZE, "%s", msg);
	}
	else
		cout << "No tweet is selected.\n";
}

//if statement checks if input is a valid tweet and adds a like to selected (valid) tweet    
void doLikeTweet(Node* selected)
{
	if (selected != nullptr)
	{
		selected->tweet.likes++;
	}
	else
	{
		cout << "No tweet is selected" << endl;
	}

}

// uses printf to format menu easily 
// if loop to have the arrow placed at the correct tweet
void displayTimeline(Node* timeline, Node* selected)
{
	cout << "\nTweets: \n \n"; 
	
	printf("%-5s %4s %7s %7s\n", "Sel", "ID", "Likes", "Tweet");
	if (timeline == nullptr)
	{
		printf("        ***** Empty *****\n");
	}
	else
	{
		Node* current = timeline;
		while (current != nullptr)
		{
			if (current == selected)
			{
				printf("--> ");
			}
			else

			{
				printf("    ");
			}

			printf("%6d %7d   %s\n", current->tweet.id, current->tweet.likes, current->tweet.msg);
			current = current->next;
		}
	}
	
	cout << endl;
}

/*Checks to make sure there is still room to add another tweet.
If so, utilizes getNextId to identify the tweet. Copies the message,
to the end of the array and sets likes to 0. Increments used size by one.*/
Node* addTweet(Node*& timeline, const char message[])
{
	Node* newNode = new Node; //creates new node


	newNode->tweet.id = getNextId(timeline); //initializes ID
	
	snprintf(newNode->tweet.msg, MSGSIZE, "%s", message);
	newNode->tweet.likes = 0; // initializes likes
	if (timeline == nullptr || newNode->tweet.id < timeline->tweet.id) 
	{
		newNode->next = timeline;
		timeline = newNode; 
	}
	else
	{
		Node* current = timeline;
		Node* prev = nullptr;
		while (current != nullptr && current->tweet.id < newNode->tweet.id)
		{
			prev = current;
			current = current->next;
		}
		newNode->next = current;

		if (prev != nullptr)
		{
			prev->next = newNode;
		}
	}
		return newNode;
}

int getNextId(Node * timeline)
{
	if (timeline == nullptr)
	{
		return 100;
	}
	int maxId = timeline->tweet.id;
	Node* current = timeline;
	while (current != nullptr)
	{
		if (current->tweet.id > maxId)
		{
			maxId = current->tweet.id;
		}
		current = current->next;
	}
	return maxId + 1;
}

void doDeleteTweet(Node*& timeline, Node*& selected)
{
	if (selected == nullptr)
	{
		// If no tweet is selected, simply return, allowing the calling function to handle user feedback.
		return;
	}

	// If the selected tweet is the first node in the list
	if (selected == timeline)
	{
		Node* nextNode = selected->next;
		delete selected; // Delete the node
		timeline = nextNode; // Update the head of the list
		selected = nullptr; // Clear the selected pointer
		return;
	}

	// If the selected tweet is in the middle or end of the list
	Node* current = timeline;
	while (current != nullptr && current->next != selected)
	{
		current = current->next; // Traverse to find the node before the selected node
	}

	// If we found the node before the selected node
	if (current != nullptr)
	{
		Node* toDelete = current->next; // The node to delete
		current->next = toDelete->next; // Bypass the node to be deleted
		delete toDelete; // Delete the node
		selected = nullptr; // Clear the selected pointer
	}
}

Node* selectTweet(Node* timeline)
{
	if (timeline == nullptr)
	{
		cout << "Timeline is empty." << endl;
		return nullptr;
	}
	int id;
	cout << "Enter ID: ";
	while (!(cin >> id))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter ID: ";
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	Node* current = timeline;
	while (current != nullptr)
	{
		if (current->tweet.id == id)
		{
			return current;
		}
		current = current->next;
	}
	cout << "ID was not found\n";
	return nullptr;
}

// delete all nodes to clean up memory after program runs
void deleteList(Node*& timeline)
{
	Node* current = timeline;
	while (current != nullptr)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}
	timeline = nullptr;
}