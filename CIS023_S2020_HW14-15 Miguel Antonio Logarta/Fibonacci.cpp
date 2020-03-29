// Module:  Fibonacci.h
// Author:  Miguel Antonio Logarta
// Date:    March 29, 2020
// Purpose: Header file for Fibonacci class
//			Calculate the nth number of the Fibonacci sequence through recursion

#include "CIS023_S2020_HW14-15 Miguel Antonio Logarta.h"

Fibonacci::Fibonacci(HWND hWnd, int iA, int iB, int iN)
{
	if (iN == 1)					// If asked for the first number
	{
		InttoTCHAR(iA, szMessage);	// Turn into TCHAR for output

		SetWindowText(hWnd,			// Set output text
			szMessage);
	}
	else if (iN == 2)				// If asked for the second number
	{ 
		InttoTCHAR(iB, szMessage);	// Turn into TCHAR for output

		SetWindowText(hWnd,			// set output text
			szMessage);
	}
	else
	{
		// Create two objects 
		Fibonacci Fib1(hWnd, iA, iB, iN - 1);
		Fibonacci Fib2(hWnd, iA, iB, iN - 2);

		// Get member value from objects
		int iFib1 = TCHARtoInt(Fib1.szMessage);
		int iFib2 = TCHARtoInt(Fib2.szMessage);

		InttoTCHAR(iFib1 + iFib2, szMessage);

		SetWindowText(hWnd,			// Set output text
			szMessage);
	}
}
