//============================================================================
// Group : Shawn Egan, Justin Schnee
// TA :
// Date : 03/04/2018
// Lab : Three
//============================================================================

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void printArray(int *x, int length);
int *randHeapArray(int *a, int *b, int *c);
//int *randStackArray(int length);
void printArrayAddresses(int *x, int length);
void printDoubleArrayAddresses(double *x, int length);
int hanningWindow(int *array, int windowSize);
int *hanningFilter(int *array, int length, int windowSize);
void graphArray(int *array, int length, int high, int low);
int **twoDimensionalArray(int *intOne, int *intTwo);

int main() {
	cout << "Problem 1:" << endl;
	int y[9] = {1,2,3,4,5,6,7,8,9};
	printArray(y, 9);
	cout << "******************************" << endl;
	cout << "Problem 2:" << endl;
	int length = 0;
	int high = 0;
	int low = 0;
	int *heapArrayTest = randHeapArray(&length,&high,&low);
	printArray(heapArrayTest, length);
	cout << "******************************" << endl;
	cout << "Problem 3:" << endl;
	//int *stackArrayTest = randStackArray(36);
	//printArray(stackArrayTest, 36);
	//TODO : Explain why cannot return array from the stack
	cout << "******************************" << endl;\
	cout << "Problem 4:" << endl;
	printArrayAddresses(y,9);
	cout << "******************************" << endl;
	cout << "Problem 5:" << endl;
	double z[5] = {1.1,2.2,3.3,4.4,5.5};
	printDoubleArrayAddresses(z,5);
	cout << "******************************" << endl;
	cout << "Problem 6:" << endl;
	int weightedValue = hanningWindow(&y[1], 5);
	cout << weightedValue << endl;
	cout << "******************************" << endl;
	cout << "Problem 7:" << endl;
	int hanningTest[9] = {3,8,2,5,1,4,6,0,2};
	cout << "Unfiltered Array: ";
	printArray(hanningTest, 9);
	cout << "Filtered Array: ";
	int *array = hanningFilter(hanningTest, 9, 5);
	printArray(array, 9);
	cout << "******************************" << endl;
	cout << "Problem 8:" << endl;
	cout << "Random Array: ";
	printArray(heapArrayTest, length);
	cout << "Random Array Graph: " << endl;
	graphArray(heapArrayTest,length,high,low);
	cout << endl;
	cout << "Filtered Array: " << endl;
	int randomWindowSize = 2*(rand()%4 + 1) + 1;
	int *filteredRandom = hanningFilter(heapArrayTest, length, randomWindowSize);
	printArray(filteredRandom, length);
	cout << "Filtered Array Graph:" << endl;
	graphArray(filteredRandom,length, high,low);
	cout << "******************************" << endl;
	cout << "Problem 9:" << endl;
	int x = 0;
	int y2 = 0;
	int **array2D = twoDimensionalArray(&x, &y2);
	for(int i = 0; i < x; i++){
		printArray(array2D[i], y2);
	}
	cout << "******************************" << endl;
	return 0;
}

void printArray(int *x, int length){
	for(int i = 0; i < length; i++){
		cout << x[i] << ", ";
	}
	cout << endl;
}

int *randHeapArray(int *a, int *b, int *c){
	srand(time(NULL));
	int length = rand()%25 + 25;
	int *array;
	array = new int[length];
	int high = rand()%5 + 5;
	int low = rand()%5 - 9;
	for(int i = 0; i < length; i++){
		 int random = rand()%(high - low) + low;
		 array[i] = random;
	}
	*a = length;
	*b = high;
	*c = low;
	return array;
}

/*int *randStackArray(int length){
	int array[length];
	int high = rand()%5 + 5;
	int low = rand()%5 - 9;
	for(int i = 0; i < length; i++){
		int random = rand()%(high - low) + low;
		array[i] = random;
	}
	return array;
}*/

void printArrayAddresses(int *x, int length){
	for(int i = 0; i < length; i++){
		cout << &x[i] << ", ";
	}
	cout << endl;
}

void printDoubleArrayAddresses(double *x, int length){
	for(int i = 0; i < length; i++){
		cout << &x[i] << ", ";
	}
	cout << endl;
}

int hanningWindow(int *array, int windowSize){
	int sumWeighted = 0;
	int sumWeights = 0;
	int i = 0;
	while(i <= (windowSize/2)){
		if(i == (windowSize/2)){
			sumWeighted += (i+1)*array[i];
			sumWeights += (i+1);
		}else{
			sumWeighted += (i+1)*(array[i]+array[windowSize-i-1]);
			sumWeights += 2*(i+1);
		}

		i++;
	}
	return sumWeighted/sumWeights;
}

int *hanningFilter(int *array, int length, int windowSize){
	int *newArray = new int[length];

	for(int i = 0; i < windowSize/2; i++){
		newArray[i] = 0;
		newArray[length-i-1] = 0;
	}
	for(int i = (windowSize/2); i < (length-windowSize/2); i++){
		newArray[i] = hanningWindow(&array[i-windowSize/2], windowSize);
	}
	return newArray;
}

void graphArray(int *array, int length, int high, int low){
	for(int i = high; i >= low; i--){
		cout << i << ":";
		int spacesBefore = 0;
		int spaces = 0;
		int starsB4 = 0;
		int spacesCarryOver = 0;

		for(int j = 0; j < length; j++){
			if(array[j]==i){
				if(i > 10 || i<0){
					spaces = j;
				}else{
					spaces = j+1;
				}//if takes care of spacing between output *
				int spacesToPrint = spaces - spacesBefore - starsB4;
				spacesCarryOver = spacesToPrint;
				while(spacesToPrint > 0){
					cout << " ";
					spacesToPrint--;
				}//prints proper amount of spaces before *
				cout << "*";
				starsB4++;
				if(i > 10 || i<0){
					spacesBefore += spacesCarryOver;
				}else{
					spacesBefore += spacesCarryOver;
				}
			}//prints spacing and * where each number appears in array
		}//iterates through array to find values equivalent to the "line"
		//or number that the outer for loop is on
		cout << endl;//starts new line or new number
	}//prints the y-axis of the graph, and goes through the graph line
	//by line to print out the stars
}

int **twoDimensionalArray(int *intOne, int *intTwo){
	int x = rand()%5 + 5;
	int y = rand()%4 + 4;
	*intOne = x;
	*intTwo = y;
	int **array2D = new int*[x];
	for(int i = 0; i < x; i++){
		array2D[i] = new int[y];
	}
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			array2D[i][j] = 0;
		}
	}
	for(int i = 0; i < 5; i++){
		int randX = rand()%x;
		int randY = rand()%y;
		if(array2D[randX][randY] == 1){
			while(array2D[randX][randY] == 1){
				randX = rand()%x;
				randY = rand()%y;
			}
		}
		array2D[randX][randY] = 1;
	}
	return array2D;
}
