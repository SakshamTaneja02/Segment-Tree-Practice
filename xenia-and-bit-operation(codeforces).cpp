#include<bits/stdc++.h>
using namespace std;

void build(int seg[],int arr[],int idx,int low,int high,int level)
{
    if(low==high)
    {
        seg[idx]=arr[low];
        return ;
    }
    int mid=(low+high)/2;
    build(seg,arr,2*idx+1,low,mid,level+1);
    build(seg,arr,2*idx+2,mid+1,high,level+1);
    if(level%2==0)
    {
        seg[idx]=seg[2*idx+1]^seg[2*idx+2];
    }
    else
    {
        seg[idx]=seg[2*idx+1]|seg[2*idx+2];
    }
}

void update(int seg[],int arr[],int idx,int low,int high,int level,int i,int val)
{
    if(low==high)
    {
        seg[idx]=val;
        return ;
    }
    int mid=(low+high)/2;
    if(i<=mid)
    {
        update(seg,arr,2*idx+1,low,mid,level+1,i,val);
    }
    else
    {
        update(seg,arr,2*idx+2,mid+1,high,level+1,i,val);
    }
    if(level%2==0)
    {
        seg[idx]=seg[2*idx+1]^seg[2*idx+2];
    }
    else
    {
        seg[idx]=seg[2*idx+1]|seg[2*idx+2];
    }
}

void solve()
{
    int n;
    cin>>n;
    int q;
    cin>>q;
    int size=pow(2,n);
    int arr[size];
    for(int i=0;i<pow(2,n);i++) cin>>arr[i];
    cout<<endl;
    int seg[4*size];
    if(n%2==0)
    {
        build(seg,arr,0,0,size-1,0);
        for(int i=0;i<q;i++)
        {
            int idx,val;
            cin>>idx>>val;
            update(seg,arr,0,0,size-1,0,idx-1,val);
            cout<<seg[0]<<endl;
        }
    }
    else
    {
        build(seg,arr,0,0,size-1,1);
        for(int i=0;i<q;i++)
        {
            int idx,val;
            cin>>idx>>val;
            update(seg,arr,0,0,size-1,1,idx-1,val);
            cout<<seg[0]<<endl;
        }
    }
}

int main()
{
    solve();
    return 0;
}