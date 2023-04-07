#include <iostream>

using namespace std;

unsigned long long Fibonacci(int n) {
    int fib[n+1];
    fib[0] = 0;
    fib[1] = 1;
    for(int i=2; i<=n; i++){
        fib[i] = fib[i-1] + fib[i-2];
    }
    return fib[n];
}

int main (int argc, char *argv[])
{
	cout << Fibonacci(1000) << endl;
	return 0;
}
