#include <iostream>
#include <vector> // used for an array that will be dynamically sizing and resizing the string. 
#include <fstream> // used for opening the txt file words.txt
#include <string> // library used for header files that have a string (or strings) in them. 
#include <time.h> // The time library. 
using namespace std;

// The print message void that will print the messages of the game on both the top and the bottom. 
void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
	// If the message is printed at the top, then the border of the top message will be printed.
	if (printTop){
		cout << "+---------------------------------+" << endl;
		cout << "|";
	}

	// If we don't print the top and the bottom. 
	else{
		cout << "|";
	}

	bool front = true; // Front is set to true. 

	/*
	For loop on when we go through the message
	while i < 33 (aka the number of +--------+ you can display)
	i increments.
	*/
	for (int i = message.length(); i < 33; i++)
	{
		// if front 
		if (front){
			message = " " + message; // placeholder for space in front of the message
		}

		// the message will be added in the back otherwise
		else{
			message = message + " ";
		}

		// front is equal to not front. 
		front = !front;
	}

	// print out the actual message. 
	cout << message.c_str();

	// If the message is printed at the bottom, then the border of the bottom message will be printed.
	if (printBottom){
		cout << "|" << endl;
		cout << "+---------------------------------+" << endl;
	}

	// If we don't print the top and the bottom. 
	else{
		cout << "|" << endl;
	}
}

// void function that draws the hang man with a amount of guesses counted. 
void DrawHangman(int guessCount = 0){

	// if guess count is greater than or equal to 1. 
	if (guessCount >= 1){
		PrintMessage("|", false, false); // The rope will appear. (NOTE: the two falses mean we won't print the top or the bottom borders.)
		
	}

	// Otherwise, don't print anything if there is no count. 
	else{
		PrintMessage("", false, false);
	}


	// if guess count is greater than or equal to 2. 
	if (guessCount >= 2){
		PrintMessage("O", false, false); // The head will appear. (NOTE: the two falses mean we won't print the top or the bottom borders.)
	}

	// Otherwise, don't print anything if there is no count. 
	else{
		PrintMessage("", false, false); // Print nothing. 
	}
	
	// if guess count is greater than or equal to 4. 
	if (guessCount == 3){
		PrintMessage("|", false, false); // The body will appear. (NOTE: the two falses mean we won't print the top or the bottom borders.)
	}


	// if guess count is greater than or equal to 5. 
	if (guessCount == 4){
		PrintMessage("/| ", false, false); // The body will appear. (NOTE: the two falses mean we won't print the top or the bottom borders.)
	}


	// if guess count is greater than or equal to 6. 
	if (guessCount >= 5){
		PrintMessage("/|\\", false, false); // The right arm will appear. (NOTE: the two falses mean we won't print the top or the bottom borders.)
	}

	else{
		PrintMessage("", false, false); // Print nothing
	}

	// if guess count is greater than or equal to 2. 
	if (guessCount == 6){
		PrintMessage("/  ", false, false); // The left leg will appear. (NOTE: the two falses mean we won't print the top or the bottom borders.)
	}


	// if guess count is greater than or equal to 6. 
	if (guessCount >= 7){
		PrintMessage("/ \\", false, false); // The right leg will appear. (NOTE: the two falses mean we won't print the top or the bottom borders.)
	}

	else{
		PrintMessage("", false, false); // Print nothing
	}

}

// function that prints the letters. (NOTE: the from and to characters are needed to display the letters A-Z) 
void PrintLetters(string input, char from, char to)
{
	// Represents an empty string
	string s;

	// For loop that allows us to go from A-Z
	for (char i = from; i <= to; i++){

		/*
		Once we loop through all the letters, we check
		if the input string contains the current character.

		If it does not contain a letter, then we write npos
		meaning that it didn't find the letter.
		*/
		if (input.find(i) == string::npos)
		{
			s += i; // we have a character
			s += " "; // adds space
		}

		/*
		If the letter is already in the input string, then
		we will just add an empty space.
		*/
		else
			s += "  ";
	}

	// Prints the message.
	PrintMessage(s, false, false);
}

// Function that will print out the available letters with the input parameter taken. 
void PrintAvailableLetters(string taken){
	PrintMessage("Available Letters"); // Message that lets the user know the amount of letters that are available. 
	PrintLetters(taken, 'A', 'M'); // Represents the letters guessed. (NOTE: A and M represent the first line of letters)
	PrintLetters(taken, 'N', 'Z'); // Represents the letters guessed. (NOTE: N and Z represent the second line of letters)
	PrintLetters(taken, 'a', 'm'); // Represents the letters guessed. (NOTE: a and m represent the second line of letters)
	PrintLetters(taken, 'n', 'z'); // Represents the letters guessed. (NOTE: n and z represent the second line of letters)
}

// Function that will print out the word and checks to see if the user guessed the right word. 
bool PrintWordAndCheckWin(string word, string guessed)
{
	bool wins = true; // Assumes that the user won the game.
	string s; // Declares a string that will display an empty space for the letter _

	// For loop that looks through all the characters used by the user to guess the word. 
	for (int i = 0; i < word.length(); i++)
	{
		// if the letter does not contain the letter for the word
		if (guessed.find(word[i]) == string::npos){
			wins = false; // The boolean wins will be set to false meaning that the user didn't win. 
			s = s + "_ "; // The blank space is displayed to where the current letter is not shown to the user. 
		}

		// if the character is already in the guessed string, then we will show the character to the user. 
		else {
			s = s + word[i];
			s = s + " ";
		}
	}
	PrintMessage(s, false); // Won't print the top border. 
	return wins; // returns the wins value. 
}

// function that loads a random word from the text file words.txt and return it. 
string LoadRandomWord(string path)
{
	int lineCount = 0; // line count set to zero
	string word; // word that will be loaded
	vector<string> v; // vector is a special type of array used for resizing
	ifstream reader(path); // used for file handling

	// if the reader is open
	if (reader.is_open())
	{

		/*
		go through the file by using the standard function getline,
		and pass the input string as the reader and store the line word.
		*/
		while (std::getline(reader, word))
			v.push_back(word); // we use the pushback function on the vector v. 

		int randomLine = rand() % v.size(); // randomizes the line to where we can have random words. Give from the number of zero to the random numer of lines. 

		word = v.at(randomLine); // says the word will be at the line that is randomly selected.

		reader.close(); // closes the reader so other files and other applications can use our file.
	}
	return word; // returns the word. 
}

// The amount of tries the user has left, and the function will contain the string word and guessed letters. 
int TriesLeft(string word, string guessed)
{
	int error = 0; // error is set to 0.

	// for loop for looking through all the guessed characters.
	for (int i = 0; i < guessed.length(); i++)
	{
		// if the word does not contain the guessed character.
		if (word.find(guessed[i]) == string::npos)
			error++; // we increment the errors (NOTE: That's when the user guesses the wrong letter)
	}
	return error; // we return the error value
}


int main()
{
	srand(time(0)); // string random time set to zero (aka it will return to the current time). 
	string guesses; // The amount of guesses the player makes 
	string wordToGuess; // word to guess
	wordToGuess = LoadRandomWord("words.txt"); // word to guess will be assigned to the load random word which will take a random string out of the text file words.txt
	int tries = 0; // integer variable representing the amount of tries the user has, and it is set to zero. 
	bool win = false; // win is set to false
	do
	{
		system("cls"); // clears the screen on windows (NOTE: If you are a MAC or Linux user, then modify it from system("cls") to system("clear"))
		PrintMessage("Hang 'Em High"); // Displays the title. 
		DrawHangman(tries); // This will draw out the man.
		PrintAvailableLetters(guesses); // Prints out available letters used by the user. 
		PrintMessage("Guess the word"); // Prints out message prompting the users to guess the word.
		win = PrintWordAndCheckWin(wordToGuess, guesses); // The word we guess. 

		// if the user has won, then we break the loop.
		if (win)
			break;

		// We need to load the character from the user if they haven't won. 
		char x;

		// Gets the user's input.
		cout << "TYPE LETTER: "; cin >> x;

		// If the user's input does not contain the character x
		if (guesses.find(x) == string::npos)
			guesses = guesses + x; // We will added to the list of character the user needs to guess. 

		// tries are updated
		tries = TriesLeft(wordToGuess, guesses);

	} while (tries < 8); // while tries are less than 8. 

	// If then else statement to determin if user wins or not. 
	if (win)
		PrintMessage("YOU WON!");
	else
		PrintMessage("GAME OVER");

	system("pause"); //this line wont work on Linux or MacOS so remove it if using thoses Operating Systems. 
	getchar();
	return 0;
}
