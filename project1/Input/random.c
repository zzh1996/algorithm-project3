#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    FILE *f=fopen("input1.txt","w");
    int i;
    srand(time(NULL));
    for(i=0;i<30;i++){
        fprintf(f,"%d\n",rand()%50+1);
    }
    fclose(f);
    return 0;
}
