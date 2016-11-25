#include <iostream> 
#include <fstream> 
#include <string>
using namespace std;


class Code
{
private:
	int totalLines, commentLines, bracketLines, codeLines, blankLines;
public:
	Code();
	int getTotalLines();
	int getCommentLines();
	int getBracketLines();
	int getCodeLines();
	int getBlankLines();
	void setTotalLines(int total);
	void setCommentLines(int comments);
	void setBracketLines(int brackets);
	void setCodeLines(int code);
	void setBlankLines(int blanks);
};



// Non-class functions
void displayMenu()
{
	cout << "\n\n------------------------------- MAIN MENU -------------------------------" << endl;
	cout << "1. New File Count" << "\n2. View Count Records"  << "\nYour choice (0 to exit):" << endl;
}



// Keeps getting the next char in a file until it's not a white space character
void skipWhiteSpace(ifstream& codeFile, char& currentCharacter)
{
	while (currentCharacter == '\t' || currentCharacter == ' ' || currentCharacter == '\r' || currentCharacter == '\v')
	{
		codeFile.get(currentCharacter);
	} 
}



int countLines(Code currentCode, string fileName, ifstream& codeFile)
{
	string line;
	int lineCount = 0;

	codeFile.open(fileName);

	if (codeFile.is_open())
	{
		cout << "File successfully opened, counting lines...\n";

		// Until the end of the file, get a line and add one to the counter for each one.
		while (!codeFile.eof())
		{
			getline(codeFile, line);
			lineCount++;
		}

		codeFile.close();
	}

	// If there was a problem opening the file print an error message
	else
	{
		cout << endl << "Sorry, there was a problem opening the file to count the lines." << endl;
	}

	return lineCount;
}



int countComments(Code currentCode, string fileName, ifstream& codeFile)
{
	// Initalise lastCharacter to be a new line so that the start of the file is recognised as the beginning 
	// of a line when checking if the only thing preceding a comment is white space/the beginning of the line
	char currentCharacter, lastCharacter = '\n';
	int commentCount = 0;


	codeFile.open(fileName);


	if (codeFile.is_open())
	{
		cout << "File successfully opened, counting comments...\n";

		while (!codeFile.eof())
		{
			// Get the next non-white-space character
			codeFile.get(currentCharacter);
			skipWhiteSpace(codeFile, currentCharacter);
			
			// If there's no code on the line prior to any possible comment
			if (lastCharacter == '\n' && currentCharacter == '/')
			{

				// get the next char and +1 to the count if it's also a slash
				codeFile.get(currentCharacter);
				if (currentCharacter == '/')
				{
					commentCount++;
				}
				// Or if it's the start of a block of code, until the end of the comment block is found...
				else if (currentCharacter == '*')
				{
					do
					{
						// Get the next non-white-space character
						lastCharacter = currentCharacter;
						codeFile.get(currentCharacter);
						skipWhiteSpace(codeFile, currentCharacter);

						// If it's a new line or we've reached the eof, +1 to the comment line count
						if (currentCharacter == '\n' || codeFile.peek() == EOF)
						{
							commentCount++;

							// If it was a blank line, -1 as it will be included in the blank line count
							if (lastCharacter == '\n')
							{
								commentCount--;
							}
						}							
					} while ((lastCharacter != '*') || (currentCharacter != '/'));


					// Get the next non-white-space character after the end of the comment block
					codeFile.get(currentCharacter);
					skipWhiteSpace(codeFile, currentCharacter);


					// If there was nothing else in the line but white space, include this line in the count
					if (currentCharacter == '\n' || codeFile.peek() == EOF)
					{
						commentCount++;
					}
				}
			}
			lastCharacter = currentCharacter;
		}
		codeFile.close();
	}
	else
	{
		cout << endl << "Sorry, there was a problem opening the file to count the comment lines." << endl;
	}

	return commentCount;
}




int countBrackets(Code currentCode, string fileName, ifstream& codeFile)
{
	// Initalise lastCharacter to be a new line so that the start of the file is recognised as the beginning 
	// of a line when checking if the only thing preceding the bracket in the line is white space
	char currentCharacter, lastCharacter = '\n';
	int bracketLineCount = 0;


	codeFile.open(fileName);

	if (codeFile.is_open())
	{
		cout << "File successfully opened, counting bracket lines...\n";
		
		while (!codeFile.eof())
		{
			// Get the next non-white-space character
			codeFile.get(currentCharacter);
			skipWhiteSpace(codeFile, currentCharacter);


			// If the last non-white-space character was a new line and current one is a bracket
			if (lastCharacter == '\n' && (currentCharacter == '{' || currentCharacter == '}'))
			{

				// Find the next non-white-space character
				codeFile.get(currentCharacter);
				skipWhiteSpace(codeFile, currentCharacter);

				// If it's also a new line or eof, i.e. there was no other code in the line, +1 to the count
				if (currentCharacter == '\n' || codeFile.peek() == EOF)
				{
					bracketLineCount++;
				}
				// Or, if it's the ; after a closing class bracket
				else if (currentCharacter == ';')
				{
					// Find the next non-white-space character again and +1 if it's a new line/eof
					codeFile.get(currentCharacter);
					skipWhiteSpace(codeFile, currentCharacter);

					if (currentCharacter == '\n' || codeFile.peek() == EOF)
					{
						bracketLineCount++;
					}
				}
			}
			lastCharacter = currentCharacter;
		}
		codeFile.close();
	}
	else
	{
		cout << endl << "Sorry, there was a problem opening the file to count the bracket lines." << endl;
	}

	return bracketLineCount;
}




int countBlankLines(Code currentCode, string fileName, ifstream& codeFile)
{
	// Initalise lastCharacter to be a new line so that the start of the file is recognised as the beginning 
	// of a line when checking if the last (non-white-space) thing was also a newline
	char currentCharacter, lastCharacter = '\n';
	int blankLineCount = 0;

	codeFile.open(fileName);

	if (codeFile.is_open())
	{
		cout << "File successfully opened, counting blank lines...\n";
		
		while (!codeFile.eof())
		{
			// Get the first non-white-space character
			codeFile.get(currentCharacter);
			skipWhiteSpace(codeFile, currentCharacter);


			// If the last non-white-space char was a new line...
			if (lastCharacter == '\n')
			{
				// and the current is also a new line, or is white space and eof is next, +1 to the count
				if (currentCharacter == '\n' || (codeFile.peek() == EOF && isspace(currentCharacter)))
				{
					blankLineCount++;
				}
			}
			lastCharacter = currentCharacter;
		}
		codeFile.close();
	}
	else
	{
		cout << endl << "Sorry, there was a problem opening the file to count the blank lines." << endl;
	}

	return blankLineCount;
}



int calculateCodeLines(int comments, int brackets, int total, int blanks) 
{
	cout << "Calculating the number of code lines..." << endl << endl;
	return (total - (brackets + comments + blanks));
}



bool countEverything(Code& currentCode, string fileName, ifstream& codeFile) 
{
	int total, blanks;

	// Count all the different types of lines that shouldn't count as code
	currentCode.setTotalLines(countLines(currentCode, fileName, codeFile));
	currentCode.setCommentLines(countComments(currentCode, fileName, codeFile));
	currentCode.setBracketLines(countBrackets(currentCode, fileName, codeFile));
	currentCode.setBlankLines(countBlankLines(currentCode, fileName, codeFile));

	
	// If all counts came back 0 i.e. the file couldn't be opened for counting, return failure
	if ((currentCode.getTotalLines() + currentCode.getCommentLines() + currentCode.getBracketLines() + currentCode.getBlankLines()) == 0)
	{
		return false;
	}
	// Otherwise, return that the file was counted successfully
	else
	{
		// Calculate and set the actual lines of code
		currentCode.setCodeLines(calculateCodeLines((currentCode.getCommentLines()), (currentCode.getBracketLines()), currentCode.getTotalLines(), currentCode.getBlankLines()));

		/* (Although this line could be split up, it allows 2 important features to be implemented within the line count
		including user inputting code filenames in run time and preventing writing records when the file couldn't
		be opened, and so was considered an acceptable and hopefully only readability sacrifice for the line count) */

		return true;
	}
}



void recordCodeCount(Code currentCode, string recordFileName, ofstream& countRecords, string codeFileName)
{
	countRecords.open(recordFileName, ios::app);

	if (countRecords.is_open())
	{
		// Write the results of all of the counts and calculations for line numbers to the records file
		countRecords << "--- Code File Name: " << codeFileName << " ---\nTotal lines: " << currentCode.getTotalLines() << endl;
		countRecords << "Comment lines: " << currentCode.getCommentLines() << "\nBracket lines: " << currentCode.getBracketLines() << endl;
		countRecords << "Blank lines: " << currentCode.getBlankLines() << "\nCode lines: " << currentCode.getCodeLines() << endl << endl;
		countRecords.close();

		cout << "The count results have been saved in the record file. Select 2 at the main menu to view them." << endl;
	}
	else
	{
		cout << endl << "Sorry, there was a problem opening the records file to write the count results to." << endl;
	}
}



void viewRecords(string fileName, ifstream& countRecords)
{
	string outputLine;
	
	// Open the file
	countRecords.open(fileName);
	
	// Until the end of the file is reached...
	if (countRecords.is_open())
	{
		while (!countRecords.eof())
		{
			// Get each line from file and print it out to screen
			getline(countRecords, outputLine);
			cout << outputLine << endl;
		}
		countRecords.close();
	}
	else
	{
		cout << endl << "Sorry, there was a problem opening the records file to read from." << endl;
	}
}



// Main program/menu
int main() 
{
	int choice;
	string fileName, recordsFileName = "Records.txt";
	ifstream codeFile, readRecordsFile;
	ofstream writeRecordsFile;
	Code currentCode = Code();

	cout << "Welcome! This program will count and record the number of different lines in your code (cpp or txt) file." << endl << endl;

	// Menu loop
	do
	{
		displayMenu();
		cin >> choice;

		// Get a new choice if the input was invalid
		while (!(choice >= 0) && !(choice < 3))
		{
			cout << "\nThat's not a valid choice, please enter 1-2, or 0 to exit: " << endl;
			cin >> choice;

		}


		switch (choice)
		{
		case 1:
			// Get the file the user wants to test
			cout << "\n\nPlease enter the name of the code file (\"Test.txt\", \"Code Line Counter.cpp\" to test): ";
			cin.clear();
			cin.ignore();
			getline(cin, fileName);

			// Take in a new code file and count all line types, then write the results to a count record file.
			if (countEverything(currentCode, fileName, codeFile))
			{
				recordCodeCount(currentCode, recordsFileName, writeRecordsFile, fileName);
			}
			break;

		case 2:
			// View the records of all code files' line counts done so far.
			viewRecords(recordsFileName, readRecordsFile);
			break;

		case 0:
			// If the user just wants to exit, don't print default error message and just break
			break;

		default:
			// If not an expected entry, get a new choice number
			cout << "That's not a valid choice, please enter 1-2, or 0 to exit: " << endl;
			cin >> choice;
			break;
		}

		//end of main menu
	} while (choice != 0);

	return 0;
}



// All Code class method definitions
Code::Code()
{
	totalLines = 0,	commentLines = 0, bracketLines = 0,	codeLines = 0;
}

int Code::getTotalLines()
{
	return totalLines;
}

int Code::getCommentLines()
{
	return commentLines;
}

int Code::getBracketLines()
{
	return bracketLines;
}

int Code::getCodeLines()
{
	return codeLines;
}

int Code::getBlankLines()
{
	return blankLines;
}

void Code::setTotalLines(int total)
{
	totalLines = total;
}

void Code::setCommentLines(int comments)
{
	commentLines = comments;
}

void Code::setBracketLines(int brackets)
{
	bracketLines = brackets;
}

void Code::setCodeLines(int code)
{
	codeLines = code;
}

void Code::setBlankLines(int blanks)
{
	blankLines = blanks;
}