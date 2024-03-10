/*Wellcome to JavaScript tutorial.*/

console.log("Hello from JavaScript");


//-----------------------------1st Lesson, practice with .map()-------------------------------

let arr = [1,2,3,4];

arr.map(value => {
	value = value * value,
	console.log(value)
});

//-----------------------------1.1 Data Types-------------------------------

/*
Data Types:
undefined, null, boolean, string, symbol, number and object
				true/false		smth unique	
*/

var myName = "Daniel" // Use within the whole programm

myName = 8

let ourName = "freeCodeCamp" // Will be used only within the scope where we declared that

const pi = 3.14 // After declaration you cannot change it's value, you will get an error



//-----------------------------1.2 Assignment Operator------------------------------

var a;
var b = 2; // Where 2 is assigned to the "b" variable

console.log(a) // Here output will be "null"

a = 7; // By assigning to an variable a value, you initialize it

b = a;

console.log(a) // Here it will output "7"

//-----------------------------1.3 Initialization of variables------------------------------

var a = 5; // At the start they was not initialized
var b = 10;
var c = "I am a";

//Do not change code bellow this line

a = a + 1;
b = b + 5;
c = c + " String!";


//-----------------------------1.4 Case Sensitivity in Variables------------------------------


// Declarations
var StUdLyCapVaR;
var properCamelCase;
var TitleCaseOver;

// Assignments
STUDLYCAPVAR = 10;
PRoperCAmelCAse = "A String";
tITLEcASEoVER = 9000;

// That is totally wrong because js is key sensitive and we should use allways the same case, Me personally love camelCase



//-----------------------------1.5 Basic Math------------------------------

// Adding

var sum = 10 + 10;
console.log(sum)

// Substracting

var difference = 45 - 3;

// Multiplication

var product = 8 * 0;

// Dividing Numbers

var quotient = 66 / 0;

// Incrementing Numbers

var myVar = 87;
myVar = myVar + 1;
myvar++; // Quicker way, same as in C

// Decrementing Numbers

var myVar = 11;
myVar = myVar - 1;
myVar--; // Same way


// Decimal Numbers (Also reffered as Floats or Floating Point Numbers)

var ourDecimal = 5.7;
var myDecimal = 0.009;

// Multiply 2 Decimal Numbers

var product = 2.0 * 2.5; // Is equal to 5

// Dividing 2 Decimal Numbers

var quotient = 4.4 / 2.0; // Is equal to 2.2

// Finding a Remainder

var remainder; // Is used often to understand if an number is even or odd
remainder = 11 % 3; // Will be stored 2 in variable, 11 - 3*3 = 2

// Augmented Math Operations

var a = 3;
var b = 17;
var c = 12;

/* This is the simple form:
a = a + 12;
b = 9 + b;
c = c + 7;
Try to use the more complex one:*/


a += 12;
b += 9;
c += 7;

// Same way with the substraction, multiplying and dividing

a -= 6;
a /= 3;
b -= 4;
b *= 2;
c -= 12;


//-----------------------------1.6 Declare String Variables------------------------------

var firstName = "Alan";
var lastName = "Turing";

// Test

var myFirstName = "Daniel";
var myLastName = "Moscalu";


//-----------------------------1.7 Escaping Literal Quotes------------------------------

var myStr = "I am a \"double quoted\" string inside \"double quotes\""; // Same thing as in BASH

// Quoting strings with Single Quotes

var myStr = "<a href=\"http://www.example.com\" target=\"_blank\">Link</a>";
var myStr = '<a href="http://www.example.com" target="_blank">Link</a>'; // Like in BASH this is more ellegant approach
var myStr = `'<a href="http://www.example.com" target="_blank">Link</a>'`; // Also you can use backquotes to escape singe quote characters


/******
CODE OUTPUT
\'	single quote
\"	double quote
\\	backslash
\n 	new line
\r 	carriage return
\t 	tab
\b 	backspace
\f 	form feed
******/

var myStr = "FirstLine\n\t\\SecondLine\nThirdLine";































