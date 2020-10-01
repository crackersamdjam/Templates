vector<int> merge_sort(vector<int> &nums) {
    if(nums.size() <= 1) return nums;
    vector<int> first_half, second_half, res;
    int mid = (int)(nums.size()+1)/2, ptr = 0;
    for(int i=0; i<mid; i++){
        first_half.push_back(nums[i]);
        if(mid+i < nums.size())
            second_half.push_back(nums[mid+i]);
    }
    first_half = merge_sort(first_half);
    second_half = merge_sort(second_half);
    for(int i=0; i<first_half.size(); i++){
        while(ptr < second_half.size() && second_half[ptr] <= first_half[i])
            res.push_back(second_half[ptr++]);
        res.push_back(first_half[i]);
    }
    for(int i=ptr; i<second_half.size(); i++)
        res.push_back(second_half[i]);
    return res;
}