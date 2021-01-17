#include <bits/stdc++.h>

using namespace std;

const int N = 100001;
int sieve[N];
vector<int> primes;

int main() {
	memset(sieve, 0, N); 

	for (int i=2; i<N; i++) {
		if (sieve[i] == 0) {
			sieve[i] = i;
			primes.push_back(i);
		}
		for (int j=0; j<(int)primes.size() && i*primes.at(j)<N; j++) {
			sieve[i*primes.at(j)] = primes.at(j);
			if (i%primes.at(j) == 0) break;
		}
	}
	
	return 0;
}
