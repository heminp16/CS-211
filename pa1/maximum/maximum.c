#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void sortArr(int* arr, int malloc){
  int i,x;
  for ( i=0; i<malloc; i++){
    for(x=i+1; x<malloc; x++){
      if(arr[i]<arr[x]){
        int temp= arr[i];
        arr[i]= arr[x];
        arr[x]= temp;
      }
    }
  }
}
void printArr(int* arr, int malloc){
  int i;
  for (i=0; i<malloc; i++){
    printf("%d", arr[i]);

  }
}
int main(int argc, char* argv[]) {
  
  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }

  //fclose(fp);
  int i;
  int num;
  int size;
  fscanf(fp, "%d", &size);
  int nums[size];
  int numMax;
  fscanf(fp, "%d", &numMax);
  int counter=0;
  while (fscanf(fp, "%d", &num)==1){
    nums[counter]=num;
    counter++;
  }
  sortArr(nums,size);
  for (i=0; i<numMax; i++){
    printf("%d ", nums[i]);
  
  
  }
  return 0;
  fclose(fp);

}
