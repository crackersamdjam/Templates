#include <bits/stdc++.h>

using namespace std;

const int N = 5000;
bool sieve[N];

int main() {
    memset(sieve, true, N); 
    sieve[0] = false; sieve[1] = false;

    for (int i=2; i<N; i++)
        if (sieve[i])
            for (int j=i*i; j<N; j+=i)
                sieve[j] = false;
	
    return 0;
}
