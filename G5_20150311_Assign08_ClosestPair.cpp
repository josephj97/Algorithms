// GROUP:   5
// ID:      20150311
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name1:   Joseph Atef Saad
// Name2:   XX SECOND STUDENT FULL NAME
// UVA Username: joseph_j97

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
#include <vector>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = (n+1)/2;
    int i = 0, j = mid;
    int k = 0;
    Type* arr = new Type[n];
    while(i < mid || j < n)
    {
        if(i >= mid && j < n)
        {
            arr[k++] = a[j++];
        }
        else if ((j >= n && i < mid) || IsBefore)
        {
            arr[k++] = a[i++];
        }
        else if(!IsBefore)
        {
            arr[k++] = a[j++];
        }
    }
    for(int ind = 0 ; ind < n ; ind++)
    {
        a[ind] = arr[ind];
    }
    delete[] arr;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if(n<=1)
    {
        return;
    }
    int mid = (n+1)/2;
    MergeSort(a,mid,IsBefore);
    MergeSort(a+mid,n-mid,IsBefore);
    Merge(a,n,IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
    double x,y;
};

bool IsBeforeX(Point& a, Point& b)
{
    return a.x<b.x;
}
bool IsBeforeY(Point& a, Point& b)
{
    return a.y<b.y;
}

double dist(Point& a, Point& b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{

    if(n<=3)
    {
        double minimum=10000;
        for(int i=0;i<n-1;i++)
            for(int j=i+1;j<n;j++)
                minimum=min(minimum,dist(p[i],p[j]));
        MergeSort(p,n,IsBeforeY);
        return minimum;
    }
    Point* strip = new Point [n];
    int mid = n/2;
    double x_mid = (0.5 * (p[mid-1].x + p[mid].x));
    double res_left = ClosestPair(p,mid);
    double res_right = ClosestPair(p+mid,n-mid);
    double res = min(res_left,res_right);
    MergeSort(p,n,IsBeforeY);

    int ind=0;
    for(int i=0;i<n;i++)
    {
        if(p[i].x>x_mid-res && p[i].x<x_mid+res)
            strip[ind++]=p[i];
    }
    double minStrip=10000;
    for(int i=0; i <ind-1; i++)
        for(int j =i+1; j<ind;j++)
            minStrip=min(minStrip,dist(strip[i],strip[j]));
    double finalResult = min(minStrip,res);
    return finalResult;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int N,x,y;
    while(cin>>N)
    {
        if(N==0)
            return 0;
        Point* point = new Point[N];
        for(int i=0;i<N;i++)
        {
            cin>>x>>y;
            point[i].x=x;
            point[i].y=y;
        }
        MergeSort(point,N,IsBeforeX);
        double res = ClosestPair(point,N);
        if(res>=10000)
            cout<<"INFINITY"<<endl;
        else
            cout<<fixed<<setprecision(4)<<res<<endl;

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
