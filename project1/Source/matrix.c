#include<stdio.h>

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

void print_optimal_parens(int i,int j){
    if(i==j)
        printf("A%d",i);
    else{
        printf("(");
        print_optimal_parens(i,s[i][j]);
        print_optimal_parens(s[i][j]+1,j);
        printf(")");
    }
}

int main(){
    FILE *f=fopen("../Input/input1.txt","r");
    int data[30]={30,35,15,5,10,20,25};
    int i;
    for(i=0;i<30;i++){
        //fscanf(f,"%d",&data[i]);
    }
    fclose(f);
    matrix_chain_order(data,6);
    print_optimal_parens(1,6);
    return 0;
}
