#include <bits/extc++.h>
using namespace std;

struct chash{
	const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
	static unsigned long long hash_f(unsigned long long x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
	int operator()(int x) const { return hash_f(x)^RANDOM; }
};

// __gnu_pbds::gp_hash_table<int, __gnu_pbds::null_type, chash> mp;
// <key, value, optional custom hash>