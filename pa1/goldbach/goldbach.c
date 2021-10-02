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
 