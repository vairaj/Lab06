// SortedDriver.cpp


//MODIFIED BY 
//Jasmine Vaira
//COSC 2030, FALL 2018

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.

#include "stdafx.h"
#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator> //so can use 'next' 

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{	
	cout << "size: " << number.size() << endl;

	//most isolated number defaults to the first entry
	double mostIs = number.front();
	//the previous number in the vector
	double lastNum = 0;
	//nN = distance to nearest neighbor
	double nN = 0;
	//nL stores distance to left neighbor
	double nL = 0;
	//nR store distance to right neighbor
	double nR = 0;
	//lastNN stores the nearest neighbor of the previous number
	double lastNN = 0;
	//iterate through the vector and determine the most isolated number :0
	for (vector<double>::iterator it = number.begin(); it != number.end(); it++)
	{
		//pointer to the next item in the vector. 
		//note: at the end of the vector, this points to an out of bounds place and could cause problems in a real program.
		auto nextNum = next(it, 1);
		//set lastNN equal to nN
		lastNN = nN;
		//update nL and nR
		nL = abs(*it - lastNum);
		if (nextNum != number.end())
		{
			nR = abs(*nextNum - *it);
		}
		//update nN
		//note: nN is distance to the nearest neighbor
		if (nL > nR)
		{
			nN = nR;
		}
		else
		{
			nN = nL;
		}
		//update mostIs if the current number's nearest neighbor is farther than the last number's nn
		if (nN > lastNN)
		{
			mostIs = *it;
		}
		//update lastNum
		lastNum = *it;
	}
	return mostIs;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int unmatched(list<string> & A, list<string> & B)
{
	//using iterators as seen here: https://thispointer.com/c-how-to-get-element-by-index-in-list/
	list<string>::iterator aFence = A.begin();
	list<string>::iterator bFence = B.begin();
	//track number of elements in A not in B
	int temp = A.size();

	for (list<string>::iterator i = A.begin(), j = B.begin(); i != A.end() && j != B.end(); )
	{
		//TA helped with this part! I wanted to figure it out by incrementing through the lists with an iterator, he helped me make it actually work.
		if (*i == *j)
		{
			temp = temp - 1;
			++i;
		}
		else if (*i > *j)
		{
			++j;
		}
		else if (*i < *j)
		{
			++i;
		}
	}
	return  temp;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
