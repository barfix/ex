/******************************************
* Bar Atuar
* 208648469
* 83-120-04
* Ex 1
******************************************/
#include <stdio.h>
#include <math.h>

void Welcome();

void Menu();
void Phone();
void David();
void Mersenne();
void Equation();

char gFirstName, gLastName;

/**
* The main function of the project
* Directs the user to the welcome and menu sequence
*/
int main()
{
	Welcome();
	Menu();
	return 1;
}

/**
* welcomes the user and asks for the first letter of the users first name and last name
*/
void Welcome()
{
	const char Upper_Case_Threshold = 90, Lower_Case_To_Upper_Case_Diff = 32;

	printf("Hello, what is the first letter of your name?\n");
	scanf_s(" %c", &gFirstName, 1);
	scanf_s(" %c", &gLastName, 1);
	if (gFirstName > Upper_Case_Threshold)
		gFirstName -= Lower_Case_To_Upper_Case_Diff;
	if (gLastName > Upper_Case_Threshold)
		gLastName -= Lower_Case_To_Upper_Case_Diff;
	printf("Hello %c. %c, welcome to our menu!\n", gFirstName, gLastName);
	return;
}

/**
* Shows the user the menu and directs him to the function of his chioce
*/
void Menu()
{
	int selection;

	while (1)
	{
		printf("Choose 1 for phone, 2 for David, 3 for Mersenne, 4 for equation, -1 for exit\n");
		scanf_s("%d", &selection);

		while(selection >4 || selection == 0 || selection <-1)
			scanf_s("%d", &selection);

		switch (selection)
		{
			case 1:
				Phone();
				break;

			case 2:
				David();
				break;

			case 3:
				Mersenne();
				break;

			case 4:
				Equation();
				break;

			case -1:
				printf("Thank you, %c. %c, have a nice day!\n", gFirstName, gLastName);
				return;
		}
	}
}

/**
*Asks the user for his phone number and checks its characteristics
*/
void Phone()
{
	const int Number_Of_Digits = 9;
	long int phoneNumber;
	int divisonByTen, numOfOddDigits = 0, numSum = 0, digits[9], repitition;
	int i,j;
	bool isEven = false, isLarge = false, isSmall = false, isSpecial = false, isVaried = false;

	printf("Enter phone number (9 digits)\n");
	scanf_s("%d", &phoneNumber);
	while (phoneNumber < 100000000|| phoneNumber > 999999999)
		scanf_s("%d", &phoneNumber);

	if (phoneNumber % 2 == 0)
		isEven = !isEven;

	for (i = 0;i < Number_Of_Digits;i++)
	{
		divisonByTen =(int) phoneNumber / pow(10, i);
		numOfOddDigits += divisonByTen % 2;
		numSum += divisonByTen % 10;
		digits[8-i] = divisonByTen % 10;
	}

	if (numSum > 40)
		isLarge = !isLarge;
	else if (numSum < 30)
		isSmall = !isSmall;

	if (numOfOddDigits > 6 || 9 - numOfOddDigits > 6)
		isSpecial = !isSpecial;

	for (i = 0;i < 9;i++)
	{
		repitition = 0;
		for (j = 0;j < 9;j++)
		{
			if (i != j)
			{
				if (digits[i] == digits[j])
					repitition++;
			}
		}
		if (repitition > 1)
			break;
		else if (i == 8)
			isVaried = !isVaried;
	}

	if (isEven)
		printf("The number is even\n");
	else
		printf("The number is odd\n");

	if (isLarge)
		printf("The number is large\n");
	else if (isSmall)
		printf("The number is small\n");
	else
		printf("The number is mediocre\n");
	
	if (isSpecial)
		printf("The number is special\n");
	else
		printf("The number is not special\n");

	if (isVaried)
		printf("The number is varied\n");
	else
		printf("The number is not varied\n");
	
	if (isEven & isLarge & isSpecial & isVaried)
		printf("The number is amazing!\n");

	return;
}

/**
* Prints to the screen Magen David with a user defined width(7<=width<=77)
*/
void David()
{
	const int Num_Of_Rows = 9;
	int row, column, n, M, width;

	printf("Enter size number:\n");
	scanf_s("%d", &n);
	while (n < 7 || n > 77 || n % 2 == 0)
		scanf_s("%d", &n);

	for (width = -1; width < 2;width++)
	{
		M = n + 2*width;
		for (row = 0; row < Num_Of_Rows; row++)
		{
			for (column = 0; column < 2 * M - 1;column++)
			{
				if (row == 0 || row == 8)
				{
					if (column + 1 == M)
						printf("O");
					else
						printf("-");
				}
				else if (row == 1 || row == 7)
				{
					if (column + 1 == M + 1 || column + 1 == M - 1)
						printf("O");
					else
						printf("-");
				}
				else if (row == 2 || row == 6)
				{
					printf("O");
				}
				else if (row == 3 || row == 5)
				{
					if (column + 1 == 2 * M - 2 || column + 1 == 2)
						printf("O");
					else
						printf("-");
				}
				else
				{
					if (column + 1 == 2 * M - 3 || column + 1 == 3)
						printf("O");
					else
						printf("-");
				}
			}
			printf("\n");
		}
		printf("\n");
	}
	return;
}

/**
* Accepts two numbers from the user and prints all of the mersenne numbers between them
*/
void Mersenne()
{
	int num1, num2, left, right, lowestPow, highestPow;
	int i;
	bool isExists = false;

	printf("Enter two numbers:\n");
	scanf_s("%d%d", &num1, &num2);
	while (num1 < 1 || num2 < 1)
		scanf_s("%d%d", &num1, &num2);

	if (num1 < num2)
	{
		left = num1;
		right = num2;
	}
	else
	{
		left = num2;
		right = num1;
	}

	lowestPow = (int)log2(left);
	highestPow = (int)log2(right);
	for (i = lowestPow;i < highestPow + 2;i++)
	{
		if (pow(2, i) - 1 >= left && pow(2, i) - 1 <= right)
		{
			if (!isExists)
				isExists = !isExists;
			printf("%g\n", pow(2, i) - 1);
		}
	}
	if (!isExists)
		printf("None\n");
	return;
}

/**
* Accepts the three coefficents of ax^2+bx+c=0 from the user and prints the solution
*/
void Equation()
{
	float delta, solutions[2], imaginary, real;
	int a, b, c;
	
	printf("Enter three numbers:\n");
	scanf_s("%d%d%d", &a, &b, &c);

	if (a != 0)
	{
		if (a == 1)
			printf("x^2 ");
		else if (a == -1)
			printf("- x^2 ");
		else
			printf("%dx^2 ", a);
	}
	if (b != 0)
	{
		if (b > 0)
		{
			if(a != 0)
				printf("+ ");

			if (b == 1)
				printf("x ");
			else
				printf("%dx ", b);
		}
		else
		{
			if (a != 0)
				printf("- ");
			else
				printf("-");

			if (b == 1)
				printf("x ");
			else
				printf("%dx ", -1 * b);
		}
	}
	if (c != 0)
	{
		if (c > 0)
		{
			if (a != 0 || b != 0)
				printf("+ ");
			printf("%d ", c);
		}
		else
		{
			if (a != 0 || b != 0)
				printf("- ");
			else
				printf("-");
			printf("%d ", -1 * c);
		}
	}

	printf("= 0\n");
		
	if (a == 0 && b == 0 && c == 0)
	{
		printf("0 = 0\n");
		printf("Infinite solutions!\n");
		return;
	}
	else if (a == 0 && b == 0)
	{
		printf("No solution!\n");
		return;
	}
	else if (a == 0)
	{
		solutions[0] = (float)-1 * c / b;
		printf("x1 = %0.3f\n", solutions[0]);
		return;
	}
	else
	{
		delta = (float)pow(b, 2) - 4 * a * c;
		if (delta >= 0)
		{
			solutions[0] = (float)(-b + sqrt(delta)) / (2 * a);
			solutions[1] = (float)(-b - sqrt(delta)) / (2 * a);
			if (solutions[0] > solutions[1])
				printf("x1 = %0.3f\nx2 = %0.3f\n", solutions[0], solutions[1]);
			else if(solutions[1]>solutions[0])
				printf("x1 = %0.3f\nx2 = %0.3f\n", solutions[1], solutions[0]);
			else
				printf("x1 = %0.3f\n", solutions[0]);
			return;
		}
		else
		{
			delta = -1 * delta;
			real = (float)(-1 * b) / (2 * a);
			imaginary = (float)sqrt(delta) / (2 * a);
			if (imaginary < 0)
				imaginary *= -1;
			if (real != 0)
			{
				printf("x1 = ");
				if (real != 0)
					printf("%0.3f + ", real);
				printf("%0.3fi\n", imaginary);

				printf("x2 = ");
				if (real != 0)
					printf("%0.3f ", real);
				printf("- %0.3fi\n", imaginary);
			}
			else
			{
				printf("x1 = %0.3fi\n", imaginary);
				printf("x2 = -%0.3fi\n", imaginary);
			}
			return;
		}
	}
}