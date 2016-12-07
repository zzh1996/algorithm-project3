#include<stdio.h>
#include<time.h>

#define INF 1000000000

int m[30][30];
int s[30][30];

void matrix_chain_order(int p[],int n){
    int i,l,j,k,q;
    for(i=1;i<=n;i++)
        m[i][i]=0;
    for(l=2;l<=n;l++){
        for(i=1;i<=n-l+1;i++){
            j=i+l-1;
            m[i][j]=INF;
            for(k=i;k<=j-1;k++){
                q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<m[i][j]){
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
}

void print_optimal_parens(FILE *f,int i,int j){
    if(i==j)
        fprintf(f,"A%d",i);
    else{
        fprintf(f,"(");
        print_optimal_parens(f,i,s[i][j]);
        print_optimal_parens(f,s[i][j]+1,j);
        fprintf(f,")");
    }
}

int main(){
    FILE *f,*t;
    int data[30];
    int i;
    double diff;
    struct timespec start,stop;
    f=fopen("../Input/input1.txt","r");
    for(i=0;i<30;i++){
        fscanf(f,"%d",&data[i]);
    }
    fclose(f);
    f=fopen("../Output/output.txt","w");
    t=fopen("../Output/time.txt","w");
    for(i=4;i<=28;i+=4){
        clock_gettime(CLOCK_MONOTONIC,&start); //开始计时
        matrix_chain_order(data,i);
        clock_gettime(CLOCK_MONOTONIC,&stop); //结束计时
        diff=(stop.tv_sec-start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1000000000L;
        fprintf(t,"%d %.9fs\n",i,diff);
        print_optimal_parens(f,1,i);
        fprintf(f,"\n");
    }
    fclose(f);
    return 0;
}
