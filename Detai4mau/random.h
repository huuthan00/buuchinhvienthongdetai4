#pragma once
#include <stdio.h>
#include <time.h>

#define m 2147483648 //modulus 2^31
#define a 1103515245 //multilier
#define c 12345		 //increment
//#define a 214013	//multilier
//#define c 2531011	//increment

#define MAXLENGTHID 14
#define MAXLENGSOURCEID 62

int result = 0;
char SOURCEID[MAXLENGSOURCEID + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

void sMyRand(unsigned int seed) {
	result = seed;
}

/*
* Linear congruential generator (lcg)
* Xn+1 = (a*Xn + c) mod m
*/
int myRand()
{
	result = (result * a + c) % m;
	//printf("\nresult= %d\n", result);
	return result;
}

int getRand(int min, int max) {
	
	return min + myRand() % (max - min + 1);
}

int Generate_id() {
	sMyRand((int)time(0));
	return myRand();
	/*sMyRand((int)time(0));

	for (int i = 0; i < MAXLENGTHID; i++) {

		ID[i] = SOURCEID[getRand(0, MAXLENGSOURCEID - 1)];
	}

	ID[MAXLENGTHID] = '\0';*/
}
