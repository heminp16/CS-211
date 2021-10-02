#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
 
int main(int argc,char* argv[])
{
   unsigned char i=0;
   unsigned char x=0;
   unsigned char z=0;
     
   FILE* matrix_a_fp = fopen(argv[1],"r");
   if(!matrix_a_fp){
      perror("fopen failed");
      return EXIT_FAILURE;
   }
   char buff[256];
   
   fscanf(matrix_a_fp,"%s",buff);
   char length_l = atoi(buff);
   int** matrix_a = malloc( length_l * sizeof(int*) );   
   
   fscanf(matrix_a_fp,"%s",buff);
   char length_m = atoi(buff);
    //-----//
   for(i=0; i<length_l; i++){
      matrix_a[i]=malloc( length_m * sizeof(int) );
      for(x=0; x<length_m; x++){
         fscanf(matrix_a_fp,"%s",buff);
         matrix_a[i][x]=atoi(buff);
      }
   }  
    //fclose(matrix_a_fp);
    //for ( unsigned char i=0; i<length_l; i++ ) {
    //free( matrix_a[i] );
    //free( matrix_a );
   FILE* matrix_a_fp2 = fopen(argv[2],"r");
   if(!matrix_a_fp2){
      perror("fopen failed");
      return EXIT_FAILURE;
   }
   fscanf(matrix_a_fp2,"%s",buff);
   char length_l2 = atoi(buff);
   int** matrix_a2 =malloc( length_l2 * sizeof(int*) );
   fscanf(matrix_a_fp2,"%s",buff);
   char length_m2 = atoi(buff);
   for(i=0; i<length_l2; i++){
      matrix_a2[i]=malloc( length_m2 * sizeof(int) );
      for(x=0; x<length_m2; x++){
         fscanf(matrix_a_fp2,"%s",buff);
         matrix_a2[i][x]=atoi(buff);
      }
   }
   int** matrix=malloc( length_l * sizeof(int*) );
   for(i=0; i<length_l; i++){
      matrix[i]=malloc( length_m2 * sizeof(int) ); 
      for( x=0; x<length_m2; x++){
         matrix[i][x]=0;   
         for(z=0; z<length_l2; z++) {
         matrix[i][x]+=matrix_a[i][z]*matrix_a2[z][x];
         }
      }
   }
   for(i=0; i<length_l; i++){
      for(x=0; x<length_m2; x++){
         printf("%d \n",matrix[i][x]);
      }
   }
   fclose(matrix_a_fp);       
   for(i=0; i<length_l; i++){
      free(matrix_a[i]);
   }
   free(matrix_a);
   fclose(matrix_a_fp2); 
   for( i=0; i<length_l2; i++){
      free(matrix_a2[i]);
   }
   free(matrix_a2);
   for( i=0; i<length_l; i++){
      free(matrix[i]);    
   }
   free(matrix);
   return 0;
}
//Matrix A has size L rows x M columns, matrix B has size M x N, then the matrix 
//multiplication of the two matrices A x B = C, where matrix C has size L x N.
//./matMul tests/matrix_a_0.txt tests/matrix_b_0.txt
