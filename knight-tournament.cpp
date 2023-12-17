#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 10;
vector<int>t(4*MAXN,-1);
 
void query(int index,int tl,int tr,int l,int r,int val)
{
    if(tr<l || tl>r)
    {
        return;
    }
    if(tl>=l && tr<=r)
    {
        if(t[index]==-1)
        {
            t[index] = val;
        }
    }
    else
    {
        int tm = (tl+tr)/2;
        if(t[2*index]==-1) query(2*index,tl,tm,l,r,val);
        if(t[2*index+1]==-1) query(2*index+1,tm+1,tr,l,r,val);
    }
}
void build(vector<int>&a,int index,int tl,int tr)
{
    if(tl==tr && a[tl]==0)
    {
        a[tl] = t[index];
        if(a[tl]==-1)
        {
            a[tl]=0;
        }
    }
    else{
        int tm = (tl+tr)/2;
        if(t[index]!=-1)
        {
            if(t[2*index]==-1)
            {
                t[2*index]=t[index];
            }
            if(t[2*index+1]==-1)
            {
                t[2*index+1]=t[index];
            }
        }
        build(a,2*index,tl,tm);
        build(a,2*index+1,tm+1,tr);
    }
}
 
void solve()
{
    int n,m,l,r,x;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        cin>>l>>r>>x;
        l--;r--;x--;
        if(x-1>=l) query(1,0,n-1,l,x-1,x+1);
        if(x+1<=r) query(1,0,n-1,x+1,r,x+1);
    }
    vector<int> a(n,0);
    build(a,1,0,n-1);
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
}
int main()
{
    solve();
}