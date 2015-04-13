// test_composant2.cpp : définit les fonctions exportées pour l'application DLL.
//

#include "stdafx.h"
#include <iostream>
#include <typeinfo> //to Use typeid().name()
#include <algorithm>
#include "Composant2.h"


using std::cout;
using std::endl;
using std::string;
using std::transform;

const int T = 504;
const int NB = 10;
int _tmain(int argc, char* argv[])
{
	bool correctBehaviour = true;
	string doMcErrors[4], getPathErrors[3], pricePathErrors[4], esperancePayOffErrors[3];
	int maturity[4], nbIterations[4];
	double strike[4];
	string payOff[4];

	getPathErrors[0] = "WRONG TYPE OF DATA",
		getPathErrors[1] = "NEGATIVE VALUE";
	getPathErrors[2] = "MISSED DATA";


	Composant2 *composant;
	double *returnedArray;
	int i = -1;

	//1 test the getPath Function
	cout << "GET PATH FUNCTION FUNCTIONNAL TESTS" << endl << "***********************************" << endl << endl;
	try
	{
		returnedArray = composant->getPath();
	}
	catch (string s)
	{
		transform(s.begin(), s.end(), s.begin(), ::toupper); // convert toUpper case a string
		if (s == getPathErrors[0])
		{
			bool wrongType = false;
			do
			{
				wrongType = (typeid(returnedArray[++i]).name() != "double");
			} while (i < T && !wrongType);
			correctBehaviour = wrongType;
			if (!correctBehaviour)
				cout << "FAILED : WRONG TYPE EXCEPTION UNTRIGGERED" << endl;
		}
		else if (getPathErrors[1] == s)
		{

			bool negativeValue = false;
			do
			{
				negativeValue = (returnedArray[++i] < 0);
			} while (i < T && !negativeValue);
			correctBehaviour = negativeValue;
			if (!correctBehaviour)
				cout << "FAILED : NEGATIVE VALUE EXCEPTION UNTRIGGERED" << endl;
		}

		else if (getPathErrors[2] == s)
		{
			bool missedValue = false;
			i = 0;
			do
			{
				missedValue = returnedArray[i] == NULL || returnedArray[i] == 0;
				i++;
			} while (i < T && !missedValue);
			correctBehaviour = missedValue;
			if (correctBehaviour)
				cout << "GET PATH TESTS OK" << endl << endl << endl;
			else
				cout << "FAILED : MISSING VALUES EXCEPTION UNTRIGGERED" << endl;
		}
	}

	//2 .. test the doMonteCarlo Function

	cout << "GET PATH FUNCTION FUNCTIONNAL TESTS" << endl << "***********************************" << endl << endl;
	int i = 0;
	// jeu de tests:
	maturity[0] = -1;
	maturity[1] = T;
	maturity[2] = T;
	maturity[3] = T;
	payOff[0] = "CALL";
	payOff[1] = "PUT";
	payOff[2] = "PUT";
	payOff[3] = "Ta SOEUR C PA UNE OPTION ?";
	nbIterations[0] = 3;
	nbIterations[1] = 2;
	nbIterations[2] = -3;
	nbIterations[3] = 1;
	strike[0] = 15;
	strike[1] = -5;
	strike[2] = 15;
	strike[3] = 15;
	doMcErrors[0] = "INCOMPLETED TABLE"; // IMPOSSIBLE TO TEST ==> This error has been detected sooner
	doMcErrors[1] = "WRONG TYPE OF DATA";
	doMcErrors[2] = "NEGATIVE VALUE";
	doMcErrors[3] = "MISSED DATA";// IMPOSSIBLE TO TEST ==> This error has been detected sooner
	do
	{
		// 1 test negative value exceptions for maturioty, number of trials, strike
		try
		{
			composant->doMonteCarlo(payOff[i], nbIterations[i], strike[i]);
		}
		catch (string s)
		{
			transform(s.begin(), s.end(), s.begin(), ::toupper); // convert toUpper case a string
			correctBehaviour = (s == doMcErrors[2]);
		}
		i++;
	} while (correctBehaviour && i < 3);
	// 2 test wrong data exceptions
	if (correctBehaviour)
	{
		cout << "PASSED" << endl;
		payOff[0] = "15";
		maturity[0] = 15;
		try
		{
			composant->doMonteCarlo(payOff[i], nbIterations[i], strike[i]);
		}
		catch (string s)
		{
			transform(s.begin(), s.end(), s.begin(), ::toupper); // convert toUpper case a string
			correctBehaviour = (s == doMcErrors[1]);
		}
		if (!correctBehaviour)
			cout << "FAILED : WRONG DATA EXCEPTION UNTRIGGERED" << endl;
	}
	else
		cout << "FAILED : NEGATIVE VALUE EXCEPTION UNTRIGGERED" << endl;

	//3..TESTS OF THE PRICE PATH FUNCTION
	cout << endl << "PRICE PATH PATH FUNCTION FUNCTIONNAL TESTS" << endl << "***********************************" << endl << endl;
	maturity[0] = T;
	maturity[1] = T;
	maturity[2] = T;
	maturity[3] = T;
	payOff[0] = "-1";
	payOff[1] = "PUT";
	payOff[2] = "PUT";
	payOff[3] = "CALL";
	strike[0] = 15;
	strike[1] = -5;
	strike[2] = 15;
	strike[3] = 15;
	pricePathErrors[0] = "WRONG TYPE OF DATA",
		pricePathErrors[1] = "NEGATIVE VALUE";
	pricePathErrors[2] = "MISSED DATA";
	pricePathErrors[3] = "VALUE GRATER THAN 1 000 000";
	double *path = new double[T];
	for (i = 0; i < T; i++)
		path[i] = 0.5;
	try
	{
		correctBehaviour = true;

		do
		{
			i = 0;
			try
			{
				composant->pricePath(payOff[i], path, strike[i], maturity[i]);
			}
			catch (string s)
			{
				transform(s.begin(), s.end(), s.begin(), toupper);
				correctBehaviour = (s == pricePathErrors[i]);
				if (!correctBehaviour)
					cout << "FAILED WITH SUBTEST N°" << i << endl;
			}
			i++;
		} while (correctBehaviour && i < 2);
		path[T / 2] = NULL;
		path[T + 50] = NULL;
		try
		{
			composant->pricePath(payOff[i], path, strike[i], maturity[i]);
		}
		catch (string s)
		{
			transform(s.begin(), s.end(), s.begin(), toupper);
			correctBehaviour = (s == pricePathErrors[i]);
			if (!correctBehaviour)
				cout << "FAILED : MISSING DATA EXCEPTION UNTRIGGERERD" << endl;
		}
		i = 3;
		path[T - 2] = 1000001;
		path[T + 50] = 100;
		try
		{
			composant->pricePath(payOff[i], path, strike[i], maturity[i]);
		}
		catch (string s)
		{
			transform(s.begin(), s.end(), s.begin(), toupper);
			correctBehaviour = (s == pricePathErrors[i]);
			if (!correctBehaviour)
				cout << "FAILED : VALUE > 1.10^6 EXCEPTION UNTRIGGERERD" << endl;
		}
		cout << endl << endl;


		//4..TEST THE CALCUL OF THE PAY OFF
		cout << "ESPERANCE PAY OFF FUNCTIONAL TESTS" << endl;
		cout << "**********************************" << endl << endl;
		esperancePayOffErrors[0] = "WRONG TYPE OF DATA";
		esperancePayOffErrors[1] = "NEGATIVE VALUE";
		esperancePayOffErrors[2] = "MISSED DATA";
		double *po = new double[NB];
		for (i = 0; i < NB; i += 2)
			po[i] = 15 + i;

		try
		{
			composant->esperancePayOff(po);
		}
		catch (string s)
		{
			correctBehaviour = (transform(s.begin(), s.end(), s.begin(), toupper) == esperancePayOffErrors[2]));
			if (!correctBehaviour)
				cout << "FAILED : MISSING DATA EXCEPTION UNTRIGGERED" << endl;
		}
		for (i = 0; i < NB; i++)
		{
			if (i % 2 == 0)
				po[i] = 15 + i;
			else
				po[i] = -i;
		}
		try
		{
			composant->esperancePayOff(po);
		}
		catch (string s)
		{
			transform(s.begin(), s.end(), s.begin(), toupper);
			correctBehaviour = (s == esperancePayOffErrors[1]));
		}
		return 0;
	}