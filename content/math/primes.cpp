#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;

//mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
//mt19937_64 g((uint64_t) new char);
mt19937_64 g(0);
int randint(int l, int r){return uniform_int_distribution<int>(l, r)(g);}
long long randl(long long l, long long r){return uniform_int_distribution<long long>(l, r)(g);}

template<class T> T gcd(T _a, T _b){return _b == 0 ? _a : gcd(_b, _a%_b);}
template<class T, class U> T fpow(T _base, U _pow, T _mod){_base %= _mod; T _x = 1; for(; _pow > 0; _pow >>= 1){ if(_pow&1) _x = _x*_base%_mod; _base = _base*_base%_mod;} return _x;}
template<class T> T mulmod(T _a, T _b, T _mod){ return _a%_mod*(_b%_mod)%_mod;}
template<class T> T divmod(T _a, T _b, T _mod){return _a*fpow(_b, _mod-2, _mod)%_mod;}

// https://github.com/wesley-a-leung/Resources/blob/master/Content/C++/math/Primes.h#L94
// checks whether N is prime in O(iterations * complexity of fpow)
// if N is small, we can get away with trying fewer 'a's https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Testing_against_small_sets_of_bases
template<class T> bool miller_rabin(T N, int iterations = 7){
	if(N < 2 or N%6%4 != 1)
		return (N|1) == 3;
	vector<T> A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	while(int(A.size()) < iterations)
		A.emplace_back(uniform_int_distribution<long long>(1795265023, numeric_limits<long long>::max())(g));
	int s = 0;
	while(!(((N-1)>>s)&1))
		s++;
	T d = N>>s;
	for(T a: A){
		T p = fpow(a%N, d, N);
		int i = s;
		while(p != 1 and p != N-1 and a%N and i--)
			p = p*p%N;
		if(p != N-1 and i != s)
			return 0;
	}
	return 1;
}

// count number of divisors of N in O(N^(1/3))
template<class T> T count_divisors(T N){
	T ret = 1;
	T m = cbrtl(N);
	for(T i = 2; i <= m; i++){
		T cnt = 0;
		while(N%i == 0){
			N /= i;
			cnt++;
		}
		ret *= cnt+1;
	}
	// N is now either 1, p, pq, or p^2
	if(N > 1){
		if(miller_rabin(N))
			ret *= 2;
		else{
			T p = sqrtl(N);
			if(p*p == N) ret *= 3;
			else ret *= 4;
		}
	}
	return ret;
}

// https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Primality/Sieve.h
// returns a boolean array of whether prime and a list of primes
template<class T> pair<vector<bool>, vector<T>> fast_sieve(T N){
	vector<bool> p(N+1, 1);
	vector<T> primes = {2};
	p[0] = p[1] = 0;
	for(T i = 4; i <= N; i += 2)
		p[i] = 0;
	for(T i = 3; i*i <= N; i += 2)
		if(p[i]) for(T j = i*i; j <= N; j += i*2)
				p[j] = 0;
	for(T i = 3; i <= N; i += 2)
		if(p[i]) primes.emplace_back(i);
	return {move(p), move(primes)};
}

// https://cp-algorithms.com/algebra/prime-sieve-linear.html
// returns an array of the lowest prime factor (other than 1) of each integer and a list of primes
template<class T> pair<vector<T>, vector<T>> linear_sieve(T N){
	vector<T> low(N+1, 0);
	vector<T> primes;
	for(T i = 2; i <= N; i++){
		if(!low[i])
			low[i] = i, primes.emplace_back(i);
		for(T j = 0; j < (T)size(primes) and primes[j] <= low[i] and i*primes[j] <= N; j++)
			low[i*primes[j]] = primes[j];
	}
	return {move(low), move(primes)};
}

// https://github.com/wesley-a-leung/Resources/blob/master/Content/C++/math/Primes.h#L267
// Returns an arbitrary divisor of N in O(N^(1/4))
template<class T> T pollards_rho(T N, int iterations = 40){
	if(N == 1) return 1;
	auto f = [&](T x){
		return mulmod(x, x, N) + 1;
	};
	T x = 0, y = 0, p = 2, q;
	int t = 0, i = 1;
	while(t++ % iterations || gcd(p, N) == 1){
		if(x == y)
			y = f(x = ++i);
		if(q = mulmod(p, max(x, y) - min(x, y), N))
			p = q;
		x = f(x); y = f(f(y));
	}
	return gcd(p, N);
}

// https://github.com/wesley-a-leung/Resources/blob/master/Content/C++/math/Primes.h#L296
// prime factorizes x in O(x^(1/4) log(x))
template<class T> vector<T> pollards_rho_prime_factor(T x, int pollardsRhoIters = 40, int millerRabinIters = 7){
	if(x == 1) return {};
	vector<T> ret;
	queue<T> q; q.push(x);
	while(size(q)){
		T y = q.front(); q.pop();
		if(miller_rabin(y, millerRabinIters))
			ret.push_back(y);
		else{
			q.push(pollards_rho(y, pollardsRhoIters));
			q.push(y/q.back());
		}
	}
	return ret;
}

namespace factors2{
	//https://cboj.ca/problem/factor2
	using ll = long long;
	int main(){
		 ll n;
		 cin>>n;
		 cout<<count_divisors(n)<<'\n';
		 return 0;
	}
}

namespace phantom1{
	//https://dmoj.ca/problem/phantom1
	using ll = long long;
	int main(){
		 // auto v = linear_sieve((ll)1e6).first;
		 // auto v = fast_sieve((ll)1e6).first;
		 auto a = linear_sieve((ll)1e6).second;
		 int q;
		 cin>>q;
		 while(q--){
			int l, r, ans = 0;
			cin>>l>>r;
			// for(int i = l; i < r; i++)
				// ans += v[i] == i;
			// for(int i = l; i < r; i++)
				// ans += v[i];
			for(auto i: a)
				ans += i >= l and i < r;
			cout<<ans<<'\n';
		 }
		 return 0;
	}
}

namespace boring{
	// https://ccoj.ca/problem/boring
	using ll = long long;
	int main(){
		ll a, b;
		cin>>a>>b;
		auto v = pollards_rho_prime_factor(__gcd(a, b));
		
		ll ans = 1, sub = 0, last = 0, cnt = 0;
		sort(all(v));
		v.emplace_back(-1);
		for(ll p: v){
			if(p == last){
				cnt++;
			}
			else{
				sub += last;
				ll f = 1, add = ans;
				while(cnt--){
					f = f*last;
					ans += f*add;
				}
				
				last = p;
				cnt = 1;
			}
		}
		ans -= sub;
		cout<<ans<<'\n';
		return 0;
	}
}

int main(){
	// factors2::main();
	// phantom1::main();
	boring::main();
}
