#include<stdio.h>
#include<string.h>
#include<time.h>

int b[110][110],c[110][110];

void lcs_length(char *x,char *y,int m,int n){
    int i,j;
    for(i=1;i<=m;i++)
        c[i][0]=0;
    for(j=0;j<=n;j++)
        c[0][j]=0;
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            if(x[i-1]==y[j-1]){
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=1;
            }else if(c[i-1][j]>=c[i][j-1]){
                c[i][j]=c[i-1][j];
                b[i][j]=2;
            }else{
                c[i][j]=c[i][j-1];
                b[i][j]=3;
            }
        }
    }
}

void print_lcs(FILE *f,char *x,int i,int j){
    if(i==0||j==0)
        return;
    if(b[i][j]==1){
        print_lcs(f,x,i-1,j-1);
        fprintf(f,"%c",x[i-1]);
    }else if(b[i][j]==2)
        print_lcs(f,x,i-1,j);
    else
        print_lcs(f,x,i,j-1);
}

int main(){
    FILE *f,*t;
    char data[14][110];
    int i,j;
    double diff;
    struct timespec start,stop;

    /*
    char x[]="ABCBDAB";
    char y[]="BDCABA";
    lcs_length(x,y,7,6);
    for(i=0;i<=7;i++){
        for(j=0;j<=6;j++)
            printf("%d %d%c%c\t",c[i][j],b[i][j],x[i-1],y[j-1]);
        printf("\n");
    }
    print_lcs(stdout,x,7,6);
    */

    for(i=0;i<2;i++){
        f=fopen(i?"../Input/inputB.txt":"../Input/inputA.txt","r");
        for(j=0;j<14;j++){
            fscanf(f,"%s",data[j]);
        }
        fclose(f);
        f=fopen(i?"../Output/ex2/output.txt":"../Output/ex1/output.txt","w");
        t=fopen(i?"../Output/ex2/time.txt":"../Output/ex1/time.txt","w");
        for(j=0;j<14;j+=2){
            int xlen=strlen(data[j]);
            int ylen=strlen(data[j+1]);
            memset(b,0,sizeof(b));
            memset(c,0,sizeof(c));
            clock_gettime(CLOCK_MONOTONIC,&start); //开始计时
            lcs_length(data[j],data[j+1],xlen,ylen);
            clock_gettime(CLOCK_MONOTONIC,&stop); //结束计时
            diff=(stop.tv_sec-start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1000000000L;
            fprintf(t,"(%d,%d) %.9fs\n",xlen,ylen,diff);
            print_lcs(f,data[j],xlen,ylen);
            fprintf(f,"\n");
        }
        fclose(f);
        fclose(t);
    }
    return 0;
}
