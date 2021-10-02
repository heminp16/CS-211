#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//Function declerations
bool is_prime(int n){
    int i;
    if (n < 2)
        return false;
    for (i = 2; i *i <= n; ++i) 
        if (n % i ==0)
            return false;
    return true;
    
}

int main(int argc, char* argv[]) {
  int num = atoi(argv[1]);
  bool found = false;
  int x, y, z, i, h, temp;

  if (num%2==0 || num < 7){
      printf("Sorry, %d cannot be executed. Please enter another digit.", num);
      return 0;
  }
  for (i=2; i < num; i++){
      if (is_prime(i)){
          x =i;
          temp = num -i;
          for (h=2; h<temp; h++){
              if (is_prime(h) && is_prime(temp-h)){
                  y = h;
                  z= temp-h;
                  found= true;
                  break;
              }
          }
        if (found)
            break;

      }
  }
   printf("%d = %d + %d + %d\n", num, x, y, z);
   return 0;

}

//broken codes 
 //   for (i = 2; i *i <= n; ++i) {
 //       if (checkPrime(i) == 1) {  
 //           if (checkPrime(x) == 1) {
 //               if(checkPrime(n-4)==1){
 //                   printf("%d = %d + %d + %d\n", n, i, x, n-4);
  //                  flag = 1;
  // printf("%d = %d + %d + %d\n", n, i, x, n-4);
   


//for (i = 2; i *i <= n; ++i) {
//for (i = 2; i <= n / 2; ++i) {

//though process

//which states that every odd number greater than !!5!! is the sum of three primes.
// write this ->  ./goldbach 7
//7 = 2 + 2 + 3
//ans= x + y + z
//ANYY prime numbers 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61
// odd numbers 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31 