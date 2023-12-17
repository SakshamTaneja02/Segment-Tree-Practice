class NumArray {
public:
    
    vector<int> seg;
    int n;

    void build(vector<int>& nums,int idx,int low,int high)
    {
        if(low==high)
        {
            seg[idx]=nums[low];
            return ;
        }
        int mid=(low+high)/2;
        build(nums,2*idx+1,low,mid);
        build(nums,2*idx+2,mid+1,high);
        seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    }

    NumArray(vector<int>& nums) {
        n=nums.size();
        seg=vector<int>(4*nums.size());
        build(nums,0,0,n-1);
    }

    void Update(int idx,int low,int high,int i,int val)
    {
        if(low==high)
        {
            seg[idx]=val;
            return ;
        }
        int mid=(low+high)/2;
        if(i<=mid) Update(2*idx+1,low,mid,i,val);
        else Update(2*idx+2,mid+1,high,i,val);
        seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    }
    
    void update(int index, int val) {
        Update(0,0,n-1,index,val);
    }
    
    int query(int idx,int low,int high,int l,int r)
    {
        if(r<low || l>high) return 0;
        if(l<=low && high<=r) return seg[idx];
        int mid=(low+high)/2;
        return query(2*idx+1,low,mid,l,r)+query(2*idx+2,mid+1,high,l,r);
    }

    int sumRange(int left, int right) {
        return query(0,0,n-1,left,right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */