/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;

void sieve (int n = N) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (int i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

void find_divs(map<int,int>::iterator it, int p, map<int,int> &facts, set<int> &nums) {
    if(it == facts.end()) {
        if(p != 1) {
            nums.insert(p);
        }
        return;
    }
    for(int j = 0; j < (*it).second + 1; j++) {
        find_divs(++it, p, facts, nums);
        --it;
        p *= (*it).first;
    }
}

void find_divisors(int num, set<int> &nums) {
    map<int,int> factors;
    // cout << "num: " << num << " ";
    for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
        while(num % prime[i] == 0) {
            factors[prime[i]]++;
            num /= prime[i];
        }
    }
    if(num != 1) {
        factors[num]++;
    }
    // cout << factors << "\n";
    find_divs(factors.begin(), 1, factors, nums);
}