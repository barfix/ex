/******************************************
* Bar Atuar
* 208648469
* 83-120-04
* Ex 1
******************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
	int a, b;
	int i, j;
	int intPassword[4];
	char password[4];
	int fourDigitNum, swappedNum=0;
	int phoneNumber;
	printf("\"%%%%%% hello \\/\\/orld %%%%%% \"%%s\"\n");
	
	/*printf("Enter 2 numbers\n");
	scanf("%d%d", &a, & b);
	printf("The sum of %d and %d is: %d\n",a,b,a + b);
	printf("The sub of %d and %d is: %d\n", a, b, a - b);
	printf("The mul of %d and %d is: %d\n", a, b, a * b);
	printf("The div of %d and %d is: %d\n", a, b, a / b);
	printf("The mod of %d and %d is: %d\n", a, b, a % b);

	printf("Enter four numbers as password\n");
	for ( i = 0; i < 4 ; i++)
	{
		scanf("%d", &intPassword[i]);
		password[i] = intPassword[i];
		if (i == 3)
		{
			printf("Your password is: ");
			for ( j = 0; j < 4; j++)
			{
				printf("%c", password[j]);
			}
			printf("\n");
		}
	}
	
	printf("Enter number with 4 digits\n");
	scanf("%d", &fourDigitNum);
	for ( i = 0; i < 4;i++)
	{
		swappedNum += (fourDigitNum % 10) *(1000/pow(10,i));
		fourDigitNum =fourDigitNum/ 10;
	}
	printf("%d\n",swappedNum);
	
	printf("Enter phone number\n");
	scanf("%d", &phoneNumber);
	printf("Internal number: 0-%d\n", phoneNumber);
	printf("Universal number: +972-%d\n", phoneNumber);*/
	return 1;
}