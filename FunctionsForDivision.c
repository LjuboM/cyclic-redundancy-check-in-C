#include <stdio.h>
#include <stdlib.h>

typedef struct _polynomial *positionOfNext;

typedef struct _polynomial {
	int bitValue;
	int position;
	int used;
	positionOfNext next;
}Polynomial;

void dividePolynomials(positionOfNext,positionOfNext,positionOfNext);
void printPolynomial(positionOfNext);
int  numberOfBitsofPolynomial(positionOfNext);
void addBitToPolynomial(positionOfNext,int);
void removeFirstZerosFromDividend(positionOfNext,positionOfNext,int*,int *,int *);

void dividePolynomials(positionOfNext dividend, positionOfNext divisor, positionOfNext result)
{
	int help=0;
	int numberOfUsed=0;
	int numberOfUnused;
	int *numberOfUnusedPointer;
	int *numberOfUsedPointer;
	int numberOfBitesOfDivident=numberOfBitsofPolynomial(dividend);
	int numberOfBitesOfDivisor=numberOfBitsofPolynomial(divisor);
	int *bitoviDjeljenikaPok=&numberOfBitesOfDivident;
	numberOfUsedPointer=&numberOfUsed;
	numberOfUnusedPointer=&numberOfUnused; 
	positionOfNext temp1;
	positionOfNext temp2; 
	numberOfUnused=numberOfBitsofPolynomial(dividend);                                 
	temp1=dividend;
	temp2=divisor;
	while(numberOfUnused!=0 && numberOfBitesOfDivident>=numberOfBitesOfDivisor)
	{		
		dividend=dividend->next;
		divisor=divisor->next;
		help=0;
		while(help<numberOfBitesOfDivisor && numberOfUnused!=0  && numberOfBitesOfDivident>=numberOfBitesOfDivisor)
		{
			if(dividend->used==0)
			{
				dividend->used=1;
				numberOfUsed++;
				numberOfUnused--;	
				if(numberOfUsed==numberOfBitesOfDivisor)
				{
				 	addBitToPolynomial(result,1);		
				}
				else
				{
				 	addBitToPolynomial(result,0);		
				}
			}	
			dividend->bitValue=!(dividend->bitValue==divisor->bitValue);//XOR!!!
			help++;
			dividend=dividend->next;
			divisor=divisor->next;
		}	
		dividend=temp1;
		divisor=temp2;
		removeFirstZerosFromDividend(dividend,result,numberOfUsedPointer,numberOfUnusedPointer,bitoviDjeljenikaPok);
	}
	if(numberOfBitesOfDivident<numberOfBitesOfDivisor)
	{
		while(numberOfUnused!=0)
		{
			if(dividend->next->used==0)
			{
				addBitToPolynomial(result,0);
				numberOfUnused--;
			}
			dividend=dividend->next;
		}
		dividend=temp1;	
	}	
}
int numberOfBitsofPolynomial(positionOfNext divisor)
{
	int bits=0;
	while(divisor->next!=NULL)
	{
		bits++;
		divisor=divisor->next;
	}
	return bits;
}
void addBitToPolynomial(positionOfNext result,int bit)
{
	positionOfNext putNew=NULL;
	positionOfNext temp=result;
	while(result->next!=NULL)
	{
		result->next->position++;
		result=result->next;
	}
	putNew=(positionOfNext)malloc(sizeof(Polynomial));
	result->next=putNew;
	putNew->next=NULL;
	putNew->bitValue=bit;
	putNew->used=0;
	putNew->position=0;
	result=temp;
}
void removeFirstZerosFromDividend(positionOfNext dividend,positionOfNext result,int * numberOfUsed, int * numberOfUnused, int * numberOfBitesOfDivident)
{
	positionOfNext temp;
	temp->next=NULL;
	while(dividend->next->bitValue!=1)
	{	
		(*numberOfBitesOfDivident)--;
		if(dividend->next->used==0)
		{
			(*numberOfUnused)--;
			addBitToPolynomial(result,0);
		}
		else if(dividend->next->used==1)
		{
			(*numberOfUsed)--;

		}
		if(dividend->next->next!=NULL)
		{
			temp=dividend->next;
			dividend->next=temp->next;
			free(temp);
		}
		else
		return;
	}
return;
}
void printPolynomial(positionOfNext poli)
{
	while(poli->position!=0)
	{
	printf("%d*x^%d+\t",poli->bitValue,poli->position);
	poli=poli->next;
	}
	printf("%d*x^%d\n",poli->bitValue,poli->position);
}
