#include<iostream>
using namespace std;

class MyString
{
public:

	// Parameterless constructor
	MyString()
	{
		str = nullptr;
		length = 0;
	}

	// Constructor with parameters, when creating a class object, you pass a string to be stored
	MyString(const char* str)
	{
		length = strlen(str); // find out the number of characters in the received string


		/* 
		*  Allocate a dynamic array in memory since the length of the string is unknown in advance.
		*  The size of the array = the length of the received string + 1, since the called function ignores the character,
		*  we will need to add it.
		*/
		this->str = new char[length + 1];

		// Copy the received string into our array
		for (int i = 0; i < length; i++)
		{
			this->str[i] = str[i];
		}

		// Close the string with a terminating zero
		this->str[length] = '\0';
	}

	// Copy constructor, creates an exact copy of the class
	MyString(const MyString& other)
	{
		// Create an exact copy of the object, but in a different memory address
		length = strlen(other.str);
		this->str = new char[length + 1];

		for (int i = 0; i < length; i++)
		{
			this->str[i] = other.str[i];
		}

		this->str[length] = '\0';
	}

	// Move constructor
	MyString(MyString&& other)
	{
		// Passes the passed object values
		this->length = other.length;
		this->str = other.str;

		// Removes the pointer to the string field from the passed object
		other.str = nullptr;
	}

	// Destructor
	~MyString()
	{
		delete[] str;
	}



	// Overloaded assignment operator
	MyString operator = (const MyString& other)
	{
		/*
		* the logic is almost like in the copy constructor, 
		* but now we add a check on the object to which we assign for the presence of data data, if any, 
		* then we first release the object from the old data (to avoid a memory leak) 
		* and allocate new memory as in the copy constructor.
		*/

		if (this->str != nullptr)
		{
			delete[] str;
		}
		length = strlen(other.str);
		this->str = new char[length + 1];

		for (int i = 0; i < length; i++)
		{
			this->str[i] = other.str[i];
		}

		this->str[length] = '\0';

		return *this;
	}

	// Overloaded addition operator
	MyString operator + (const MyString& other)
	{
		// Create an empty object of the class, which will store the result of the performed operation
		MyString result;

		// Find out the size of each of the received parameters
		int length1 = strlen(this->str);
		int length2 = strlen(other.str);

		result.length = length1 + length2;

		// Allocate a new place in memory for a new string
		result.str = new char[length1 + length2 + 1];

		// Copy data from 2 strings into one
		int i = 0;
		for (; i < length1; i++)
		{
			result.str[i] = this->str[i];
		}
		for (int j = 0; j < length2; j++, i++)
		{
			result.str[i] = other.str[j];
		}

		result.str[length1 + length2] = '\0';

		// Return the result of the concatenation
		return result;
	}

	// Overloaded equality operator
	bool operator == (const MyString& other)
	{
		if (this->length != other.length) // if the strings are of different lengths, then they are no longer equal
		{
			return false;
		}

		for (int i = 0; i < this->length; i++)
		{
			if (this->str[i] != other.str[i]) // comparison character by character
			{
				return false;
			}
		}

		return true; // return yes / no answer
	}

	// Overloaded inequality check operator
	bool operator != (const MyString& other)
	{
		// To reduce the amount of code, the equality operator is simply called, the result of which is inverted
		return !(this->operator==(other));
	}

	// Overloaded index operator []
	char& operator [] (int index)
	{
		return this->str[index];
	}



	// String length counting method
	int GetLength()
	{
		return length;
	}

	// Method to print the string to the console
	void PrintString()
	{
		cout << str << endl;
	}

private:
	// Field description
	char* str;	// a pointer to a character array where the characters we are passing are stored
	int length; // variable for storing the length of the received char array + 1 (described in the constructor)

};

int main()
{
	// Testing the class string
	MyString name = "JohaN";
	MyString sername = "Libert";
	MyString result;

	result = name + sername;
	result.PrintString();

	name = result;
	name.PrintString();

	cout << name.GetLength() << endl;
	cout << sername.GetLength() << endl;
	cout << result.GetLength() << endl;

	bool equal = name == sername;
	bool EQual = name != sername;

	cout << name[4] << endl;
	name[4] = 'n';
	cout << name[4] << endl;

	return 0;
}