// GROUP:       G5
// ID:          20150311
// Assign:      03
// Assign:      Graphs
// UVA handle:  joseph_j97
// UVA:         924
// Name:        Joseph Atef Saad

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array {
    int n, sz;
    Value *arr;

    void Initialize() {
        sz = 1;
        n = 0;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
            Value *new_arr = new Value[sz];
            for (int i = 0; i < n; i++)
                new_arr[i] = arr[i];
            delete[]arr;
            arr = new_arr;
        }
        arr[n++] = v;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
    //Array that contains the adjacent nodes.
    Array<int> adj;

    void Initialize()
    {
        adj.Initialize();
    }
    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        n=_n;
        nodes = new Node();
        for(int i=0;i<n;i++)
            nodes[i].Initialize();
    }
    void Destroy()
    {
        for(int i;i<n;i++)
            nodes[i].Destroy();
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue {
    int f, n;
    Type *elems;

    void Initialize(int size) {
        f = 0;
        n = 0;
        elems = new Type[size];
    }

    void Destroy() {
        delete[] elems;
    }

    void Add(Type t)
    {
        elems[n++] = t;
    }
    Type Pop()
    {
        Type temp = elems[f];
        f++;
        return temp;
    }
    Type Peek()
    {
        return elems[f];
    }
    int Num()
    {
        return n-f;
    }
};
void BFS(Graph& g, int s)
{
    Queue q;
    q.Initialize(1000000);
    int* vis = new int [g.n];
    int* dst = new int [g.n];
    int* pre = new int [g.n];
    memset(vis, 0, (sizeof(int)*g.n));
    memset(pre, -1, (sizeof(int)*g.n));
    for(int i=0;i<g.n;i++)
        dst[i]=g.n;

    vis[s]=1;
    dst[s]=0;
    q.Add(s);
    while(q.Num())
    {
        int cur=q.Pop();
        for(int i=0;i<g.nodes[cur].adj.n;i++)
        {
            int x=g.nodes[cur].adj[i];
            if(!vis[x])
            {
                vis[x]=1;
                pre[x]=cur;
                dst[x]=dst[cur]+1;
                q.Add(x);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
