// GROUP:   5
// ID:      20150311
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Joseph Atef Saad

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

template<class Elem>
struct Heap
{
    Array<Elem> a;
    bool (*IsBefore)(int&, int&);
    
    void Initialize(bool (*_IsBefore)(int&, int&))
    {
        IsBefore = (*_IsBefore);
        a.Initialize();
    }
    void Destroy()
    {
        a.Destroy();
    }
    int Child(int i)
    {
        return 2*i+1;
    }
    int Parent(int i)
    {
        return (i-1)/2;
    }
    void MoveUp(int ind)
    {
        int parent=Parent(ind);
        if(parent>=0 && IsBefore(a[ind],a[parent]))
        {
            swap(a[ind],a[parent]);
            MoveUp(parent);
        }
    }
    void MoveDown(int ind)
    {
        int child1=Child(ind);
        int child2=Child(ind)+1;
        if(child1<= a.n && IsBefore(a[child1],a[child2]))
        {
            if(IsBefore(a[child1],a[ind]))
            {
                swap(a[child1],a[ind]);
                MoveDown(child1);
            }
        }
        else if(child2<= a.n && IsBefore(a[child2],a[child1]))
        {
            if(IsBefore(a[child2],a[ind]))
            {
                swap(a[child2],a[ind]);
                MoveDown(child2);
            }
        }
    }
    void Add(Elem e)
    {
        a.AddLast(e);
        MoveUp(a.n-1);
    }
    Elem GetFirst()
    {
        return a.arr[0];
    }
    Elem RetrieveFirst()
    {
        Elem temp = a.arr[0];
        a.arr[0]=a.arr[a.n-1];
        a.RemoveLast();
        MoveDown(0);
        return temp;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(int& a, int& b)
{
    return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    /*
    Array<int> a;
    a.Initialize();
    a[2]=3;
    cout<<a[2]<<endl;
    a.Destroy();
    */
    Heap <int> heap;
    int x;
    cin>>x;
    while(x!=0)
    {
        heap.Initialize(IsBefore);
        int m;
        int summation=0,cost;
        for(int i=0;i<x;i++)
        {
            cin>>m;
            heap.Add(m);
        }
        while(heap.a.n>1)
        {
            cost=0;
            cost+=heap.RetrieveFirst();
            cost+=heap.RetrieveFirst();
            heap.Add(cost);
            summation+=cost;
        }
        cout<<summation<<endl;
        heap.Destroy();
        cin>>x;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
