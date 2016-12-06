#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int data[2][14]={
        {20,10,20,20,20,30,20,40,20,50,20,60,20,70},
        {15,25,30,25,45,25,60,25,75,25,90,25,105,25}
    };
    FILE *f;
    int i,j,k;
    srand(time(NULL));
    for(i=0;i<2;i++){
        f=fopen(i?"inputB.txt":"inputA.txt","w");
        for(j=0;j<14;j++){
            for(k=0;k<data[i][j];k++){
                fprintf(f,"%c",rand()%26+'A');
            }
            fprintf(f,"\n");
        }
        fclose(f);
    }
    return 0;
}
