/*
 * encrypt.c
 * This program will encrypt user's message. 
 * Fatih Yılmaz
 */

#include <stdio.h>

int main (int argc, char *argv[]) {
	/* argv[1] is the key string*/
	/* argv[2] is the msg string */
	char palpha[36]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char calpha[36];
	
	int keysize = 0; /* size of the key */
	int msgsize = 0; /* size of the msg */

	while(argv[1][keysize] != '\0'){
		keysize++; 
	}
	while(argv[2][msgsize] != '\0'){
		msgsize++;
	}
	
	/*Converting to lower characters to upper characters*/	
	for (int i=0; i<=keysize; i++) 
	{
		if (argv[1][i]>96)
		{	
			if (argv[1][i]<123) 
			{
				argv[1][i] = argv[1][i]-32;
			}
		}
	}
	
	char checkKey[keysize];/*This is a array to check repetition of Key*/
	int isThere = 0;/*This is the result of repetition's control*/
	int absKey=0;/*absKey is the length of the key without repetition*/

	/*Removing repetition*/
	for (int i=0; i<keysize; i++) 
	{
		for (int j=0; j<=i; j++)
		{	
			if (argv[1][i] != checkKey[j]) 
			{
				isThere = 0;/*if ith value of argv[1] is not equals to jth value of checkKey value of isThere 0*/
			}
			else
			{
				isThere = 1;/*if ith value of argv[1] is equals to jth value of checkKey value of isThere 1*/
				break;/*And also break the loop 'cause we don't need to check others*/
			}	
		}
		if (isThere==0)
		{
			checkKey[absKey] = argv[1][i];/*If value of isThere 0 add ith value of a as absKeyth value of checkKey*/
			absKey++; /*Also increase value of absKey 'cause for the next loop we should rewrite on checkKey*/
		}
	}
	checkKey[absKey+1] = '\0';/*We need to add \0 to end of the string*/

	/*Addition of key to the ciphertext*/
	for (int i=0; i<=absKey; i++)
	{
		calpha[i] = checkKey[i];
	}

	/*Addition of unwritten letter in key to the ciphertext*/
	for (int i=0; i<36; i++) 
	{
		for (int j=0; j<=absKey; j++)
		{	
			if (palpha[i] != calpha[j]) 
			{
				isThere = 0;
			}
			else
			{
				isThere = 1;
				break;
			}	
		}
		if (isThere==0)
		{
			calpha[absKey] = palpha[i];
			absKey++;
		}
	}
	calpha[absKey+1] = '\0';/*Adding \0 to end of the string*/
	
	/*Converting message to uppercase*/
	for (int i=0; i<msgsize; i++) 
	{
		if (argv[2][i]>96)
		{	
			if (argv[2][i]<123) 
			{
				argv[2][i] = argv[2][i]-32;
			}
		}
	}
	
	/*Substitution of message characters with caplha*/
	for (int i=0; i<msgsize; i++)
	{
		for (int j=0;j<36;j++) 
		{
			if (argv[2][i]==palpha[j]) 
			{
				argv[2][i]=calpha[j];
				break;
			}
		}
	}
	
	/*Printing of enrypted message*/
	for (int i=0; i<msgsize; i++) 
	{
		printf("%c", argv[2][i]);
	}
	printf("\n");

	return 0;
}
