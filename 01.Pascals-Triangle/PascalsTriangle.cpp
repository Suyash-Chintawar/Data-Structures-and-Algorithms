#include<bits/stdc++.h>
using namespace std;
int pascEle(int r,int c)
{
    if(r>=0 && (c==0||c==r))
    {
        return 1;
    }
    else{
    return pascEle(r-1,c)+pascEle(r-1,c-1);
    }
}
int main()
{
    int i,j,n;
    cin>>n;
    for(i=0;i<n;i++)
    {
        for(j=0;j<=(n-i-1);j++)
        {
            printf("   ");
        }
        for(j=0;j<=i;j++)
        {
            printf("%6d ",pascEle(i,j));
        }
        printf("\n");
    }
}
