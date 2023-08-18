#include <stdio.h>

// Function prototype
int add(int a, int b);

// Preprocessor directive
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Enumeration
enum Day
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

// Structure
struct Point
{
    int x;
    int y;
};

// Typedef
typedef struct
{
    float real;
    float imag;
} Complex;

// Function with variable arguments
double average(int count, ...);

// Recursive function
unsigned long long factorial(unsigned int n);

int main()
{
    // Variables and basic data types
    int num = 42;
    float pi = 3.14159;
    char letter = 'A';
    double bigNum = 1234567890.12345;

    // Arithmetic operations
    int sum = num + 10;
    float circleArea = pi * 2 * 2;

    // Conditional statements
    if (sum > 50)
    {
        printf("Sum is greater than 50\n");
    }
    else
    {
        printf("Sum is not greater than 50\n");
    }

    // Loops
    for (int i = 0; i < 5; i++)
    {
        printf("Iteration %d\n", i);
    }

    // Function call and definition
    int result = add(20, 30);

    // Preprocessor macro
    int maxVal = MAX(num, sum);

    // Enumeration usage
    enum Day today = Wednesday;

    // Structure usage
    struct Point p1;
    p1.x = 5;
    p1.y = 10;

    // Typedef usage
    Complex c1;
    c1.real = 1.0;
    c1.imag = 2.0;

    // Variable arguments function
    double avg = average(3, 10, 20, 30);

    // Recursive function
    unsigned long long fact = factorial(5);

    printf("Result: %d\n", result);
    printf("Max value: %d\n", maxVal);
    printf("Today is day number: %d\n", today);
    printf("Point coordinates: (%d, %d)\n", p1.x, p1.y);
    printf("Complex number: %f + %fi\n", c1.real, c1.imag);
    printf("Average: %lf\n", avg);
    printf("Factorial: %llu\n", fact);

    return 0;
}

int add(int a, int b)
{
    return a + b;
}

double average(int count, ...)
{
    va_list args;
    va_start(args, count);

    double sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += va_arg(args, int);
    }

    va_end(args);
    return sum / count;
}

unsigned long long factorial(unsigned int n)
{
    if (n <= 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}
