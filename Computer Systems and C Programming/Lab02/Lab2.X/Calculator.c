/* Kunal Shah kgshah@ucsc.edu
 * File:   part0.c
 * Author: kgshah
 *
 * Created on January 4, 2022, 11:54 AM
 */

// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
//double Tangent(double operand);
//add more prototypes here
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
double CelciusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double Tangent(double operand);
int Round(double operand);


void CalculatorRun(void)
{
    printf("\n\nWelcome to Kunal's calculator program! Compiled at %s %s\n",__DATE__, __TIME__);
    
    //initialize vars
    char op;
    double op1;
    double op2;
    double result;

    // Your code here
    while (1){//while loop that re-prompts user for new input
        printf("\nEnter a mathematical operation to preform (*,/,+,-,v,a,c,f,t,r): ");//user input prompt
        scanf(" %c", &op);//scanning for user input
        printf("    Character received was: '%c'\n",op);//echo user input
        if (op == '*'){//if user wants to multiply
            printf("    Enter the first operand: ");
            scanf(" %lf", &op1);
            printf("    Enter the second operand: ");
            scanf(" %lf", &op2);
            result = Multiply(op1, op2);
            printf("    You input %lf * %lf", op1, op2);
            printf("\n    Result of (%lf * %lf): %lf\n", op1, op2, result);
        }
        else if (op == '/'){//if user wants to divide
            printf("    Enter the first operand: ");
            scanf(" %lf", &op1);
            printf("    Enter the second operand: ");
            scanf(" %lf", &op2);
            result = Divide(op1, op2);
            printf("    You input %lf / %lf", op1, op2);
            printf("\n    Result of (%lf / %lf): %lf\n", op1, op2, result);
        }
        else if (op == '+'){//if user wants to add
            printf("    Enter the first operand: ");
            scanf(" %lf", &op1);
            printf("    Enter the second operand: ");
            scanf(" %lf", &op2);
            result = Add(op1, op2);
            printf("    You input %lf + %lf", op1, op2);
            printf("\n    Result of (%lf + %lf): %lf\n", op1, op2, result);
        }
        else if (op == '-'){//if user wants to subtract
            printf("    Enter the first operand: ");
            scanf(" %lf", &op1);
            printf("    Enter the second operand: ");
            scanf(" %lf", &op2);
            result = Subtract(op1, op2);
            printf("    You input %lf - %lf", op1, op2);
            printf("\n    Result of (%lf - %lf): %lf\n", op1, op2, result);
        }
        else if (op == 'a'){//if user wants to find the absolute value
            printf("    Enter the operand: ");
            scanf(" %lf", &op1);
            result = AbsoluteValue(op1);
            printf("    You input |%lf|", op1);
            printf("\n    Result of |%lf|: %lf\n", op1, result);
        }
        else if (op == 'v'){//if user wants to average 2 numbers
            printf("    Enter the first operand: ");
            scanf(" %lf", &op1);
            printf("    Enter the second operand: ");
            scanf(" %lf", &op2);
            result = Average(op1, op2);
            printf("    You input Average(%lf, %lf)", op1, op2);
            printf("\n    Result of Average(%lf, %lf): %lf\n", op1, op2, result);
        }
        else if (op == 'c'){//if user wants to convert fahrenheit to celsius
            printf("    Enter the operand: ");
            scanf(" %lf", &op1);
            result = FahrenheitToCelsius(op1);
            printf("    You input (%lf deg->C)", op1);
            printf("\n    Result of (%lf deg->C): %lf\n", op1, result);
        }
        else if (op == 'f'){//if user wants to convert from celsius to fahrenheit
            printf("    Enter the operand: ");
            scanf(" %lf", &op1);
            result = CelciusToFahrenheit(op1);
            printf("    You input (%lf deg->F)", op1);
            printf("\n    Result of (%lf deg->F): %lf\n", op1, result);
        }
        else if (op == 't'){//if user wants to find tangent using degrees as input
            printf("    Enter the operand: ");
            scanf(" %lf", &op1);
            result = Tangent(op1);
            printf("    You input tan(%lf)", op1);
            printf("\n    Result of tan(%lf): %lf\n", op1, result);
        }
        else if (op == 'r'){//if user wants to round towards zero
            printf("    Enter the operand: ");
            scanf(" %lf", &op1);
            result = Round(op1);
            printf("    You input round(%lf)", op1);
            printf("\n    Result of round(%lf): %lf\n", op1, result);
        }
        else{//if user input nonsensical initial input
            printf("    This is not a valid response, please try again by "
                    "entering a valid symbol as seen below");
        }
    }
    BOARD_End();
    while (1);
}



/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
    return operand1 + operand2;// addition function/logic
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
	return operand1 - operand2;// subtraction function/logic
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
	return operand1 * operand2;// Multiplication function/logic
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
	return operand1 / operand2;// Division function
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{
	if (operand < 0){// Absolute Value function/logic
        return -operand;
    }
    else{
        return operand;
    }
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
	return ((operand - 32.0) * (5.0/9.0));// FahrenheitToCelsius function/logic
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelciusToFahrenheit(double operand)
{
	return ((operand * (9.0/5.0)) + 32.0);
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
	return (operand1 + operand2) / 2;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand)
{
	return tan(operand * (M_PI / 180));
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
int Round(double operand)
{
    if (operand<0){
        operand = operand + 0.5;
    }
    return (int) operand;
}


