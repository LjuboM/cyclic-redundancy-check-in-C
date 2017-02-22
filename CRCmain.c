#include <stdio.h>
#include <stdlib.h>
#include "FunctionsForDivision.c"
void connectPolys(positionOfNext, positionOfNext);
void addZerosToRemainder(positionOfNext,int);
void setUsedOnZero(positionOfNext);
void areThereErrors(positionOfNext);
int  main()
{
	int bitValue=1,numberOfZeros,counter;
	Polynomial dividend1,dividend2,divisor,result1,result2,zeros;
	zeros.next=NULL;
	result1.next=NULL;
	result2.next=NULL;
	dividend1.next=NULL;
	dividend2.next=NULL;
	divisor.next=NULL;
	printf("Type in message in bits of 1 and 0\n%d\n",bitValue);
	while(bitValue==0 || bitValue==1)
	{
		addBitToPolynomial(&dividend1,bitValue);
		addBitToPolynomial(&dividend2,bitValue);
		scanf("%d",&bitValue);
	}
	printf("Type in secret key for checking the integrity of message (use 0 and 1 as well)\n");
	bitValue=1;
	printf("%d\n",bitValue);
	while(bitValue==0 || bitValue==1)
	{
		addBitToPolynomial(&divisor,bitValue);
		scanf("%d",&bitValue);
	}
	numberOfZeros=numberOfBitsofPolynomial(&divisor)-1;
	for(counter=0;counter<numberOfZeros;counter++)
	{
		addBitToPolynomial(&zeros,0);
	}
	connectPolys(&dividend1,&zeros);
	dividePolynomials(&dividend1,&divisor,&result1);
	addZerosToRemainder(&dividend1,numberOfZeros);
	setUsedOnZero(&dividend1);
	connectPolys(&dividend2,&dividend1);
	dividePolynomials(&dividend2,&divisor,&result2);
	printPolynomial(dividend2.next);
	areThereErrors(&dividend2);
return 0;	
}
void connectPolys(positionOfNext dividend1, positionOfNext addedPolynomial)
{
	while(addedPolynomial->next!=NULL)
	{
		addBitToPolynomial(dividend1,addedPolynomial->next->bitValue);
		addedPolynomial=addedPolynomial->next;	
	}
}
void addZerosToRemainder(positionOfNext dividend1,int numberOfZeros)
{
	positionOfNext temp;
	int position=numberOfZeros-1;
	int bitsOfRemainder=numberOfBitsofPolynomial(dividend1);
	while(bitsOfRemainder!=numberOfZeros)
	{
		temp=(positionOfNext)malloc(sizeof(Polynomial));
		temp->next=dividend1->next;
		dividend1->next=temp;
		temp->bitValue=0;
		temp->used=0;
		temp->position=position;
		position--;
		bitsOfRemainder++;
	}
}
void setUsedOnZero(positionOfNext Polynomial)
{
	while(Polynomial->next!=NULL)
	{
		Polynomial->next->used=0;
		Polynomial=Polynomial->next;	
	}
}
void areThereErrors(positionOfNext Polynomial)
{
	int error=0;
	while(Polynomial->next!=NULL)
	{
		if(Polynomial->next->bitValue==1)
		{error=1;}
		Polynomial=Polynomial->next;
	}
	if(error==0)
	printf("There wasn't an error in transition!");
	else
	printf("There was an error!");	
}
