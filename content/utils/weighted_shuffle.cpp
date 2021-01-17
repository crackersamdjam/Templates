#include <bits/stdc++.h>
using namespace std;

/*
 *  Shuffles a weighted array (arr) in O(N log N) time.
 *  Larger weighted items will have a higher probability to be placed at the front
 *  As a result, shuffling an array like {0, 1, 2, 3} will always leave the last element as 0.
 */

vector<long long> weighted_shuffle(vector<long long> &arr){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    long long p, sum, TSUM = 0;
    for(auto i : arr) TSUM += i;
    vector<long long> bit(arr.size() + 1, 0), out;
    for(int i = 0; i < int(arr.size());){
        bit[i + 1] += arr[i]; ++i;
        if(i + (i & -i) < int(bit.size())) bit[i + (i & -i)] += bit[i];
    }
    for(int i = 0; i < int(bit.size()) - 1; ++i){
        p = uniform_int_distribution<long long>(0, TSUM)(rng);
        int pos = 0; sum = 0;
        for(int j = 1 << __lg(arr.size()); j > 0; j >>= 1){
            if(pos + j < arr.size() && sum + bit[pos + j] <= p){
                pos += j; sum += bit[pos];
            }
        }
        out.push_back(arr[pos]);
        TSUM -= arr[pos];
        if(pos != int(arr.size()) - 1){
            sum = arr.back() - arr[pos];
            for(int j = pos + 1; j < int(arr.size()); j += j & -j) bit[j] += sum;
            swap(arr.back(), arr[pos]);
        }
        arr.pop_back();
    }
    return out;
}


int main(){
    /*** Sample usage ***/
    vector<long long> arr = {0, 1, 2};
    vector<long long> shuffled = weighted_shuffle(arr);
    for(auto i : shuffled) cout << i << endl;
    return 0;
}
