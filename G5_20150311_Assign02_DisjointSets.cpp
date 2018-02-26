// GROUP:       G5
// ID:          20150311
// Assign:      02
// Assign:      DisjointSets
// UVA:         10608
// UVA handle:  joseph_j97
// Name:        Joseph Atef Saad Ayad

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize()
    {
        sz=1;
        n=0;
        arr=new Value[sz];
    }
    void Destroy()
    {
        delete[] arr;
    }
    void AddLast(Value v)
    {
        if(n==sz)
        {
            sz*=2;
            Value* new_arr = new Value[sz];
            for(int i=0;i<n;i++)
                new_arr[i]=arr[i];
            delete[]arr;
            arr=new_arr;
        }
        arr[n++]=v;
    }
    void RemoveLast()
    {
        n--;
    }
    Value& operator[](int i)
    {
        return arr[i];
    }
};
///////////////////////

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n)
    {
        n = _n;
        parent = new int[n];
        num_nodes = new int [n];
        for(int i=0;i<n;i++)
        {
            parent[i] = i+1;
            num_nodes[i] = 1;
        }
    }
    void Destroy()
    {
        delete[]parent;
        delete[]num_nodes;
        n=0;
    }
    int Find(int i)
    {
        int p=i;
        while (parent[p]!=-1)
            p=parent[p];
        return p;
    }
    bool Union(int i, int j)
    {
        int a=Find(i), b=Find(j);
        if(a==b) return false;
        if(num_nodes[a]>=num_nodes[b])
        {
            parent[b]=a;
            num_nodes[a]+=num_nodes[b];
        }
        else
        {
            parent[a]=b;
            num_nodes[b]+=num_nodes[a];
        }
        return true;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int t,n,m,max=-1;
    cin>>t;
    while (t--)
    {
        DisjointSets djs;
        cin>>n>>m;
        djs.Initialize(n);
        int a,b;
        for(int i=0;i<m;i++)
        {
            cin>>a>>b;
            djs.Union(a,b);
        }
        for(int i=0;i<djs->num_nodes.length();i++)
        {
            if(max<djs.num_nodes[i])
                max=djs.num_nodes[i];
        }
        cout<<max<<endl;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
