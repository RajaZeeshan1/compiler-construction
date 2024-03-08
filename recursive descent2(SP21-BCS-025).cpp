#include <iostream>
#include <stdlib.h>
#include <conio.h> // This header is not standard in C++. Please consider using alternatives.
using namespace std;

/*
Grammar:
E -> TE'
E' -> +TE' | -TE' | null
T -> FT'
T' -> *FT' | /FT' | null
F -> id | num | (E)
*/

int count = 0; // Global variable to keep track of the position in the input string

void E();   // Function to handle non-terminal E
void Ed();  // Function to handle non-terminal E'
void T();   // Function to handle non-terminal T
void Td();  // Function to handle non-terminal T'
void F();   // Function to handle non-terminal F

string expr; // Input expression

int main() {
  cin >> expr; // Read the input expression
  int l = expr.length();
  expr += "$"; // Add end marker to the input
  E(); // Start parsing from the start symbol E
  if (l == count) {
    cout << "Accepted" << endl; // If the entire input is parsed, accept the expression
    getchar(); // Wait for user input before exiting
  } else
    cout << "Rejected" << endl; // If there are still characters left in the input after parsing, reject the expression
  getchar(); // Wait for user input before exiting
}

// Function to parse non-terminal E
void E() {
  cout << "E -> TE'" << endl;
  getchar(); // Wait for user input
  T(); // Parse T
  Ed(); // Parse E'
}

// Function to parse non-terminal E'
void Ed() {
  if (expr[count] == '+') { // If next symbol is '+'
    count++; // Move to the next symbol
    cout << "E' -> +TE'" << endl;
    getchar(); // Wait for user input
    T(); // Parse T
    Ed(); // Parse E' recursively
  } else if (expr[count] == '-') { // If next symbol is '-'
    count++; // Move to the next symbol
    cout << "E' -> -TE'" << endl;
    getchar(); // Wait for user input
    T(); // Parse T
    Ed(); // Parse E' recursively
  } else {
    cout << "E' -> null" << endl; // If next symbol is neither '+' nor '-', E' is null
    getchar(); // Wait for user input
  }
}

// Function to parse non-terminal T
void T() {
  cout << "T -> FT'" << endl;
  getchar(); // Wait for user input
  F(); // Parse F
  Td(); // Parse T'
}

// Function to parse non-terminal T'
void Td() {
  if (expr[count] == '*') { // If next symbol is '*'
    count++; // Move to the next symbol
    cout << "T' -> *FT'" << endl;
    getchar(); // Wait for user input
    F(); // Parse F
    Td(); // Parse T' recursively
  } else if (expr[count] == '/') { // If next symbol is '/'
    count++; // Move to the next symbol
    cout << "T' -> /FT'" << endl;
    getchar(); // Wait for user input
    F(); // Parse F
    Td(); // Parse T' recursively
  } else {
    cout << "T' -> null" << endl; // If next symbol is neither '*' nor '/', T' is null
    getchar(); // Wait for user input
  }
}

// Function to parse non-terminal F
void F() {
  if (isalpha(expr[count])) { // If next symbol is alphabetic (id)
    count++; // Move to the next symbol
    cout << "F -> id" << endl;
    getchar(); // Wait for user input
  } else if (isdigit(expr[count])) { // If next symbol is numeric (num)
    count++; // Move to the next symbol
    cout << "F -> digit" << endl;
    getchar(); // Wait for user input
  } else if (expr[count] == '(') { // If next symbol is '('
    count++; // Move to the next symbol
    cout << "F -> (E)" << endl;
    getchar(); // Wait for user input
    E(); // Parse E
    if (expr[count] != ')') { // If next symbol is not ')', reject the expression
      cout << "Rejected" << endl;
      getchar(); // Wait for user input
      exit(0); // Exit the program
    }
    count++; // Move to the next symbol
  } else { // If next symbol is none of the above, reject the expression
    cout << "Rejected" << endl;
    getchar(); // Wait for user input
    exit(0); // Exit the program
  }
}
