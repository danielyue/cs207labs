#include <stdio.h>

int fib(int n){
	if (n == 1) {
		return 0;
	}
	else if (n == 2) {
		return 1;
	}
	else{
		return fib(n-1) + fib(n-2);
	}
}

// for the question, call with value of 8
int main(void){
	int x;
	x = fib(8);
	printf("%d",x);
	return 1;
}