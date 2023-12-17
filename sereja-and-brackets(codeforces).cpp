#include<bits/stdc++.h>
using namespace std;

class info
{
    public:
    int open=0,close=0,full=0;
    info(int o,int c,int f)
    {
        open=o;
        close=c;
        full=f;
    }
    info()
    {
        open=0;
        close=0;
        full=0;
    }
};

info merge(info left,info right)
{
    info ans = info(0,0,0);
    ans.full = left.full + right.full + min(left.open, right.close);
    ans.open = left.open + right.open - min(left.open, right.close);
    ans.close = left.close + right.close - min(left.open, right.close);
    return ans;
}

void build(string& s,vector<info>& seg,int idx,int low,int high)
{
    if(low==high)
    {
        if(s[low]=='(') seg[idx].open = 1;
        else if(s[low]==')') seg[idx].close = 1;
        seg[idx].full = 0;
        return ;
    }
    int mid=(low+high)/2;
    build(s,seg,2*idx+1,low,mid);
    build(s,seg,2*idx+2,mid+1,high);
    seg[idx] = merge(seg[2*idx+1],seg[2*idx+2]);
}

info query(string& s,vector<info>& seg,int idx,int low,int high,int l,int r)
{
    if(r<low || l>high) return info();
    else if(low>=l && high<=r) return seg[idx];
    else
    {
        int mid=(low+high)/2;
        info left = query(s,seg,2*idx+1,low,mid,l,r);
        info right = query(s,seg,2*idx+2,mid+1,high,l,r);
        return merge(left,right);
    }
}

void solve()
{
    string s;
    cin>>s;
    vector<info> seg(4*s.size());
    build(s,seg,0,0,s.size()-1);
    // for(int i=0;i<seg.size();i++)
    // {
    //     cout<<seg[i].open<<" "<<seg[i].close<<" "<<seg[i].full<<endl;
    // }
    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int l,r;
        cin>>l>>r;
        l--,r--;
        cout<<query(s,seg,0,0,s.size()-1,l,r).full*2<<endl;
    }
}

int main()
{
    solve();
    return 0;
}