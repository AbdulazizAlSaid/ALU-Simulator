#include <iostream>
using namespace std;

#include <bitset> //library that initiates variables to be manipulated by logic functions and converted to strings
#include <time.h>

int l;
unsigned int accumulator, MQ0, s = 0;
unsigned int counter = 15; //counter for bit number, from 0-15


bitset<16> AC {accumulator};
bitset<16> result{ s };


int OneBitAlu(int x, int y, int carryin, string operation)//one bit alu simultor
{

	int carryout = 0;
	if (operation == "add") //add simulator
	{
		if (l <= 15)
		{
			result[l] = x ^ y ^ carryin;
			l++;
		}

		carryout = (x * y) + carryin * (x ^ y);
		return carryout;
	}
	else if (operation == "sub") //subtraction simulator 
	{
		if (y == 0)
		{
			y = 1;
		}

		else
		{
			y = 0;
		}
		if (l <= 15)
		{
			result[l] = x ^ y ^ carryin;
			l++;
		}

		carryout = (x * y) + carryin * (x ^ y);
		return carryout;
	}

}

int SixteenBitAlu(bitset<16> A, bitset<16> B, string operation)//16 bit ALU simulator
{
	int carry = 0;
	l = 0;
	result = 0;

	if (operation == "sub")
	{
		if (A[0] == 0 && B[0] == 1)
		{
			carry = 1;
		}
	}
	for (int y = 0; y <= 15; y++)
	{
		carry = OneBitAlu(A[y], B[y], carry, operation);
	}

	AC = result;
	return carry;
}

int Booths(bitset<16>MD, bitset<16> MQ) //Booths multiplier
{
	bitset<4> cycle_counter{ counter };
	bitset<1> OneBitMQ{ MQ0 };

	cout << "|Cycle-Counter|  	|MD|			|AD|  		|MQ|	    	      |OneBitMQ|	" << endl;
	cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << OneBitMQ << "      First step " << endl << endl;

	for (int k = 0; k < 16; k++)
	{
		int x;
		unsigned short dec = 1;
		if (MQ[0] == 0 && OneBitMQ[0] == 0)
		{
			AC = AC;
			cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << OneBitMQ << "  First step of iteration " << k << endl;
			OneBitMQ[0] = MQ[0];
			MQ = MQ >> 1;
			MQ[15] = AC[0];

			AC = AC >> 1;
			AC[15] = AC[14]; 


		}

		else if (MQ[0] == 0 && OneBitMQ[0] == 1)
		{
			SixteenBitAlu(AC, MD, "add");

			cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << OneBitMQ << "  First step of iteration " << k << endl;
			
			//arithmetic shift
			OneBitMQ[0] = MQ[0];
			MQ = MQ >> 1;
			MQ[15] = AC[0];

			AC = result;
			AC = AC >> 1;
			AC[15] = AC[14];
		}
		else if (MQ[0] == 1 && OneBitMQ[0] == 0)
		{
			SixteenBitAlu(AC, MD, "sub");
			cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << OneBitMQ << "  First step of iteration " << k << endl;

			//arithmetic shift
			OneBitMQ[0] = MQ[0];
			MQ = MQ >> 1;
			MQ[15] = AC[0];

			AC = AC >> 1;
			AC[15] = AC[14];


		}
		else if (MQ[0] == 1 && OneBitMQ[0] == 1)
		{
			AC = AC;
			cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << OneBitMQ << "  First step of iteration " << k << endl;

			//arithmetic shift
			OneBitMQ[0] = MQ[0];
			MQ = MQ >> 1;
			MQ[15] = AC[0];

			AC = AC >> 1;
			AC[15] = AC[14]; 

		}

		cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << OneBitMQ << "  Second step of iteration " << k << endl;
		cout << endl;
		counter--;
		cycle_counter = counter;
	}
	cout << endl << endl;
	cout << "The Answer is : " << AC << MQ << endl;

	return 0;

}

int main()
{
	bitset<16> bs1;
	bitset<16> bs2;

	cout << "Enter first number : " << endl;
	cin >> bs1;

	cout << "Enter Second number : " << endl;
	cin >> bs2;

	int overflow = Booths(bs1, bs2);

	cout << endl << endl;

	if (overflow == 1)
		cout << "OF = 1" << endl;
	else
		cout << "OF = 0" << endl << endl << endl;


	system("pause");
	return 0;

}