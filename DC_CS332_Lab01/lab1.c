#include <stdio.h>

int isPrime(int n){
  // isPrime(n): given an integer n, determine if it is a prime number
  // input: integer n representing the number to be determined is prime or not
  // output: integer one or zero representing true or false
  int i;
  for(i = 2; i < n;i++){
    if(n%i==0){
      return 0;
    }
  }
  return 1;
}

void main(){
    int result = 0;
    int i;
    printf(" Please enter an integer: ");
    scanf("%i", &i);
    if(isPrime(i) == 0){
        printf("%i is not prime. \n", i);
    }
    else{
        printf("%i is prime. \n", i);
    }
}