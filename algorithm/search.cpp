#include "../utility.h"
   
    bool search(vector<int>& nums, int target) {
        if(nums.size()==0) return false;
        if(nums.size()==1) return nums[0]==target;
        int ll = 0, rr = nums.size()-1;
        int mid = (ll+rr)/2;
        vector<int> tmp,tmq;
        if(nums[ll]==target || nums[rr]==target ||nums[mid]==target) return true;
        if(target>nums[rr]&&target<nums[ll]) return false;
        if(nums[ll]==nums[rr]&&nums[ll]==nums[mid])
        {
                tmp = vector<int>(nums.begin(),nums.begin()+mid);
                tmq = vector<int>(nums.begin()+mid,nums.end());
                return search(tmp,target)||search(tmq,target);
        }
        if(target<nums[rr])
        {   
            if(nums[mid]<nums[rr])
            {
                if(nums[mid]<=target)
                    tmp = vector<int>(nums.begin()+mid,nums.end());
                else
                    tmp = vector<int>(nums.begin(),nums.begin()+mid);
            }
            else if(nums[mid]==nums[rr])
            {
                tmp = vector<int>(nums.begin(),nums.begin()+mid);
            }
            else
                tmp = vector<int>(nums.begin()+mid+1,nums.end());
        }
        else
        {  
            if(nums[mid]>nums[ll])
            {
                if(nums[mid]>target)
                    tmp = vector<int>(nums.begin(),nums.begin()+mid);
                else
                    tmp = vector<int>(nums.begin()+mid,nums.end());
            }
            else if(nums[mid]==nums[ll])
            {
                tmp = vector<int>(nums.begin()+mid+1,nums.end());
            }
            else
                tmp = vector<int>(nums.begin(),nums.begin()+mid);
        }
        return search(tmp,target);
    }


int main()
{
    vector<int> num{1,1,1,1,1,3,1,1,1,1};
    cout<<search(num,3);
    return 0;
}