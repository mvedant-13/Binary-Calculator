# Binary-Calculator
bc command of linux <br>
DSA mini project <br>

<b> Features: </b>
<b> 1. Basic Arithmetic Operations </b>
Supports the four fundamental arithmetic operations: Addition (+), Subtraction (-), Multiplication (*), and Division (/). <br>
Modulus Operation (%) to calculate the remainder. <br>
<b> 2. Exponentiation </b>
^ operator allows raising a number to the power of another, for performing exponential calculations.
3. Binary Operations
Bitwise Shift: << (left shift) and >> (right shift) for binary manipulations.
Bitwise XOR: ^ operator performs bitwise XOR (distinct from exponentiation).
4. High Precision and Unlimited Number Handling
Supports high-precision arithmetic to handle large integers and floating-point numbers. This feature is crucial for applications requiring exact calculations.
5. Variables and Assignment
Users can assign values to variables (e.g., x = 5) and use these variables in expressions throughout a session. Variable values are stored and accessible for reuse.
6. Mathematical Functions
Square Root: sqrt() function for calculating square roots.
Trigonometric Functions: Includes sine (sin), cosine (cos), and tangent (tan) functions, with results depending on the defined precision (scale).
7. Configurable Precision (Scale)
Users can set the precision (or “scale”) for decimal results, allowing control over the number of decimal places for division and trigonometric calculations. Example: scale = 10.
8. Expression Grouping with Parentheses
Support for grouping expressions with parentheses to manage order of operations accurately.
9. Built-in Constants
Pi (π): Provides a built-in constant for π, which is useful for trigonometric calculations.
10. History and Previous Expressions
Tracks past expressions and results, allowing users to reference or reuse them in new calculations.
11. Error Handling
Handles errors gracefully, including:
Division by zero.
Overflow or underflow errors for large numbers.
Undefined operations (e.g., square root of a negative number if complex numbers are not supported).
12. User-Defined Functions (Optional)
Future versions may support defining custom functions (e.g., define square(x) { return x * x }) for added flexibility.