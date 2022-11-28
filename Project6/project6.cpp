//Computing Structures
//Fall 2022
//Project 6
//Author: Aditya Narasimhan

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
    // we want to retain the ordering of arr for shell sort 
    for (int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
            // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
    int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last

    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i)
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                // the if condition where the comparison happens each time
                if (numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;


        while ((j >= 0) && (arr[j] > temp))
        {
            numComp++; // incrementing the number of comparisons done right before 
            // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arr; // return the not necessarily sorted array = approximately sorted array
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
    return arr;
}

//main function
int main()
{
    int n;
    cin >> n; // read the number of elements
    cout << "Number of elements: " << n << endl;

    int s, l, u, D;

    cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

    // generate n random elements with the seed s, within the lower and upper range 
    // store the randomly generated UNIQUE set of elements in an array 'A'

    // you may use the unordered set to help generate unique elements

    cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
    // display the array A
    int* A = new int(n);
    srand(s); // initialize the random number generator with seed s
    int range = u - l;
    unordered_set<int> set;
    for (int i = 0; i < n; i++) {
        //int random = l + (rand() % (range + 1));
        set.insert(l + (rand() % (range + 1)));
        //cout << random << " ";
        //A[i] = l + (rand() % range);
    }
    // cout << endl;
    int index = 0;
    // convert set to array
    for (const auto& iterSet : set) {
        A[index] = iterSet;
        index++;
    }
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 
    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
    // display the completely sorted array 
    int* sorted = bubbleSort(A, n, n*n);
    for (int i = 0; i < n; i++) {
        cout << sorted[i] << " ";
    }
    cout << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;
    int* bubResult = bubbleSort(A, n, D);
    
    // display bubResult
    for (int i = 0; i < n; i++) {
        cout << bubResult[i] << " ";
    }
    cout << endl;
    
    // find both the quality metrics for bubResult

    // find the number of inversions
    int bubInversion = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bubResult[j] < bubResult[i]) {
                bubInversion++;
            }
        }
    }
    cout << "Number of inversions in bubResult: " << bubInversion;
    cout << endl;

    // find the Chebyshev distance
    int* bubDistance = new int(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sorted[j] == bubResult[i]) {
                bubDistance[i] = abs(i - j);
            }
        }
    }

    // find the max from the distance array
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (bubDistance[i] > max) {
            max = bubDistance[i];
        }
    }
    
    cout << "Chebyshev distance in bubResult: " << max << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    int* shellResult = shellSort(A, n, D);
    
    // display shellResult
    for (int i = 0; i < n; i++) {
        cout << shellResult[i] << " ";
    }
    cout << endl;

    // find both the quality metrics for shellResult
    // find the number of inversions
    int shellInversion = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (shellResult[j] < shellResult[i]) {
                shellInversion++;
            }
        }
    }
    cout << "Number of inversions in shellResult: " << shellInversion;
    cout << endl;

    // find the Chebyshev's distance
    int* shellDistance = new int(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sorted[j] == shellResult[i]) {
                shellDistance[i] = abs(i - j);
            }
        }
    }

    // find the max element from the distance array
    max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (shellDistance[i] > max) {
            max = shellDistance[i];
        }
    }

    cout << "Chebyshev distance in shellResult: " << max << endl;

    return 0;
}
