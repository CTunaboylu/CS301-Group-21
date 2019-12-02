// CS301_ShortestCommonSuperString.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

// Utility function to calculate minimum of two numbers 
int min(int a, int b)
{
	return (a < b) ? a : b;
}

// Function to calculate maximum overlap in two given strings
int findOverlappingPair(string str1, string str2, string &str) // Str coming from getShortestSuperString passed by reference 
{
	int max = INT_MIN; // Stores maximum overlap
	int len1 = str1.length();
	int len2 = str2.length();

	// check suffix of str1 matches with prefix of str2 
	for (int i = 1; i <= min(len1, len2); i++)
	{
		// compare last i characters in str1 with first i 
		// characters in str2 
		if (str1.compare(len1 - i, i, str2, 0, i) == 0)
		{
			if (max < i)
			{
				//update max and str 
				max = i;
				str = str1 + str2.substr(i);
			}
		}
	}

	// check prefix of str1 matches with suffix of str2 
	for (int i = 1; i <= min(len1, len2); i++)
	{
		// compare first i characters in str1 with last i 
		// characters in str2 
		if (str1.compare(0, i, str2, len2 - i, i) == 0)
		{
			if (max < i)
			{
				//update max and str 
				max = i;
				str = str2 + str1.substr(i);
			}
		}
	}

	return max;
}

// Function for calculating the shortest string that contains each string in the array as substring
string getShortestSuperString(string sampleArray[], int length) 
{
	// run length - 1 times because pairs are considered
	while (length != 1) 
	{
		int max = INT_MIN; // to be able to store maximum overlap
		int left = 0;
		int right = 0; // Left and right for storing indexes of strings involved in maximum overlap
		string resStr = ""; // Storing the resultant string after maximum overlap

		for (int i = 0; i < length; i++) 
		{
			for (int j = i + 1; j < length; j++)
			{
				string str = "";
				// res will store maximum length of the matching prefix and suffix str is passed by reference and 
				// will store the resultant string after maximum overlap of arr[i] and arr[j], if any. 
				int res = findOverlappingPair(sampleArray[i], sampleArray[j], str);

				// Check for maximum overlap
				if (max < res) 
				{
					max = res;
					resStr.assign(str);
					left = i;
					right = j;
				}
			}
		}
		length--; // ignore last element in next cycle

		// Handling no overlap condition
		if (max == INT_MIN) 
		{
			sampleArray[0] += sampleArray[length];
		} 
		else 
		{
			sampleArray[left] = resStr;
			sampleArray[right] = sampleArray[length];
		}
	}
	return sampleArray[0];
}

int main()
{
	string sample_array[] = { "catgc", "ctaagt", "gcta", "ttca", "atgcatc" };
	int length = sizeof(sample_array) / sizeof(sample_array[0]);

	cout << "The Shortest SuperString is: " << getShortestSuperString(sample_array, length) << endl;

	cin.clear();
	cin.get();
    return 0;
}

