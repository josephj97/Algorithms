// GROUP:       05
// ID:          20150311
// Assign:      04
// Assign:      CountInv
// UVA:         10810
// Name:        Joseph Atef Saad Ayad
// UVA Username:joseph_j97

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInv(long long* a, int n)
{
    //merge
    long long* b = new long long[n];
    long long i=0;
    long long x=0;
    long long m=(i+n)/2;
    long long y=m+1;
    long long cnt=0;
    while(x<n)
    {
        if(i<=m && a[x]<=a[y])
            b[x++] = a[i++];
        else
        {
            b[x++] = a[y++];
            cnt++;
        }
    }
    for(x=0;x<n;x++)
        a[x] = b[x];
    delete[](b);
    return cnt;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long* a, int n)
{
    //merge sort
    long long mid = n/2;
    long long cnt=0;
    if(n<=1)
        return 1;
    CountInvMerge(a,mid);
    CountInvMerge(a+mid,n-mid);
    cnt+= CountInv(a,n);
    return cnt;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a,int& b)
{
    return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    long long* arr;
    while(cin>>n)
    {
        if(n==0)
            return 0;
        arr = new long long [n];
        for(int i=0;i<n;i++)
            cin>>arr[i];
        cout<<CountInvMerge(arr,n)<<endl;

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
