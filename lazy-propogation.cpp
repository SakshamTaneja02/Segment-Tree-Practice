#include<bits/stdc++.h>
using namespace std;

void build(int seg[],int arr[],int idx,int low,int high)
{
    if(low==high)
    {
        seg[idx]=arr[low];
        return ;
    }
    int mid=(low+high)/2;
    build(seg,arr,2*idx+1,low,mid);
    build(seg,arr,2*idx+2,mid+1,high);
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];
}

int query(int seg[],int arr[],int idx,int low,int high,int l,int r)
{
    if(r<low || l>high) return INT_MAX;
    else if(low>=l && high<=r) return seg[idx];
    else
    {
        int mid=(low+high)/2;
        int left=query(seg,arr,2*idx+1,low,mid,l,r);
        int right=query(seg,arr,2*idx+2,mid+1,high,l,r);
        return left+right;
    }
}

void update(int seg[],int arr[],int idx,int low,int high,int i,int val)
{
    if(low==high)
    {
        seg[idx]=val;
        return ;
    }
    int mid=(low+high)/2;
    if(i<=mid)
    {
        update(seg,arr,2*idx+1,low,mid,i,val);
    }
    else
    {
        update(seg,arr,2*idx+2,mid+1,high,i,val);
    }
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];
}

void rangeUpdate(int seg[],int lazy[],int idx,int low,int high,int l,int r,int val)
{
    if(lazy[idx]!=0)
    {
        seg[idx]+=(high-low+1)*lazy[idx];
        if(low!=high)
        {
            lazy[2*idx+1]+=lazy[idx];
            lazy[2*idx+2]+=lazy[idx];
        }
        lazy[idx]=0;
    }
    if(r<low || l>high || low>high) return ;
    if(low>=l && high<=r)
    {
        seg[idx]+=(high-low+1)*val;
        if(low!=high)
        {
            lazy[2*idx+1]+=val;
            lazy[2*idx+2]+=val;
        }
        return ;
    }
    int mid = (low+high)>>1;
    rangeUpdate(seg,lazy,2*idx+1,low,mid,l,r,val);
    rangeUpdate(seg,lazy,2*idx+2,mid+1,high,l,r,val);
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];
}

int querySumLazy(int seg[],int lazy[],int idx,int low,int high,int l,int r,int val)
{
    if(lazy[idx]!=0)
    {
        seg[idx]+=(low-high+1)*lazy[idx];
        if(low!=high)
        {
            lazy[2*idx+1]+=lazy[idx];
            lazy[2*idx+2]+=lazy[idx];
        }
        lazy[idx]=0;
    }
    if(r<low || l>high || low>high) return 0;
    if(low>=l && high<=r) return seg[idx];
    int mid=(low+high)>>1;
    return querySumLazy(seg,lazy,2*idx+1,low,mid,l,r,val)+querySumLazy(seg,lazy,2*idx+2,mid+1,high,l,r,val);
}

void solve()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++) cin>>arr[i];
    int seg[4*n];
    build(seg,arr,0,0,n-1);
    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int type;
        cin>>type;
        if(type==0)
        {
            int l,r;
            cin>>l>>r;
            cout<<query(seg,arr,0,0,n-1,l,r)<<endl;
        }
        else
        {
            int idx,val;
            cin>>idx>>val;
            update(seg,arr,0,0,n-1,idx,val);
            arr[idx]=val;
        }
    }
}

int main()
{
    solve();
    return 0;
}