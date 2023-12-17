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
    if(l>high || r<low) return 0;
    if(l<=low && high<=r) return seg[idx];
    int mid=(low+high)/2;
    return query(seg,arr,2*idx+1,low,mid,l,r)+query(seg,arr,2*idx+2,mid+1,high,l,r);
}

void update(int seg[],int arr[],int idx,int low,int high,int i,int val)
{
    if(low==high)
    {
        seg[idx]=val;
        return ;
    }
    int mid=(low+high)/2;
    if(i<=mid) update(seg,arr,2*idx+1,low,mid,i,val);
    else update(seg,arr,2*idx+2,mid+1,high,i,val);
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];
}

void solve()
{
    int n;
    cin>>n;
    int arr[n];
    int mx=-1;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
        mx=max(mx,arr[i]);
    }
    int freq[mx+1];
    for(int i=0;i<mx+1;i++) freq[i]=0;
    for(int i=0;i<n;i++)
    {
        freq[arr[i]]++;
    }
    int seg[4*(mx+1)];
    build(seg,freq,0,0,mx);
    int ans=0;
    for(int i=0;i<n;i++)
    {
        freq[arr[i]]--;
        update(seg,freq,0,0,mx,arr[i],freq[arr[i]]);
        ans+=query(seg,freq,0,0,mx,1,arr[i]);
    }
    cout<<ans<<endl;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}