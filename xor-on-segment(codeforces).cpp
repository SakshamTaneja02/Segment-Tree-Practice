#include <bits/stdc++.h>
#define pb push_back
#define dbg(x) cout << "reached here " << x << endl;
#define f first
#define s second
#define ll long long
 
using namespace std;
typedef pair<int, int> pii;
 
const int maxn = 1e5+5;
int a[maxn], mask[4*maxn][25], lzy[4*maxn];
 
void init(int id, int L, int R)
{
	if(L+1 == R)
	{
		int h = a[L], t = 0;
		while(h)
		{
			mask[id][t] = h&1;
			t++;
			h /= 2;
		}
		return;
	}	
 
	int mid = (L+R)/2, lc = 2*id, rc = 2*id+1;
 
	init(lc, L, mid);
	init(rc, mid, R);
 
	for (int i = 0; i <= 20; ++i)
		mask[id][i] = mask[lc][i] + mask[rc][i];
}
 
inline void XOR(int id, int L, int R, int h)
{
	int t = 0; 
	while(h)
	{
		if(h&1)
			mask[id][t] = R-L - mask[id][t];
		t++;
		h/= 2;
	}
}
 
inline void spread(int id, int L, int R)
{
	int mid = (L+R)/2, lc = 2*id, rc = 2*id+1;
 
	lzy[lc] ^= lzy[id];
	lzy[rc] ^= lzy[id];
 
	XOR(lc, L, mid, lzy[id]);
	XOR(rc, mid, R, lzy[id]);
 
	lzy[id] = 0; 
}
 
void update(int id, int L, int R, int l, int r, int x)
{
	if(L == l and R == r)
	{
		lzy[id] ^= x;
		XOR(id, L, R, x);
		return;
	}
 
	spread(id, L, R);
	int mid = (L+R)/2, lc = 2*id, rc = 2*id+1;
 
	if(l < mid)
		update(lc, L, mid, l, min(r, mid), x);
	if(mid < r)
		update(rc, mid, R, max(l, mid), r, x);
 
	for (int i = 0; i <= 20; ++i)
		mask[id][i] = mask[lc][i] + mask[rc][i];
}
 
ll get(int id, int L, int R, int l, int r)
{
	if(L == l and R == r)
	{
		ll sum = 0;
		for (int i = 0; i <= 20; ++i) 
			sum += 1ll * mask[id][i] * (1<<i);
		return sum;
	}
 
	spread(id, L, R);
	int mid = (L+R)/2, lc = 2*id, rc = 2*id+1;
	ll ret1 = 0, ret2 = 0;
 
	if(l < mid)
		ret1 = get(lc, L, mid, l, min(r, mid));
	if(mid < r)
		ret2 = get(rc, mid, R, max(l, mid), r);
 
	return ret1 + ret2;
}
 
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
 
	int n;
	cin >> n;
 
	for (int i = 1; i <= n; ++i)
	 	cin >> a[i];
 
	init(1, 1, n+1);
 
	int m;
	cin >> m;
 
	while(m--)
	{
		int t, l, r;
		cin >> t >> l >> r;
 
		if(t == 1)
			cout << get(1, 1, n+1, l, r+1) << endl;
		
		else
		{
			int x;
			cin >> x;
			update(1, 1, n+1, l, r+1, x);
		}
	}
 
	return 0;
} 
