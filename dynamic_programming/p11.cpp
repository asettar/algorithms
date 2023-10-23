#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// prbLink: https://leetcode.com/problems/longest-increasing-subsequence/


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
		int ans = 0;
		vector<int> arr;
		for(int i : nums){
			if (arr.empty() || arr.back() < i)
				arr.push_back(i);
			else{
				int idx = lower_bound(arr.begin(), arr.end(), i) - arr.begin();
				arr[idx] = i;
			}
			
		}
		return arr.size();
    }
};

int main(){

}