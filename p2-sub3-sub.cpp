#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")

#define ll long long
#define int ll
#define ios ios_base::sync_with_stdio(0);cin.tie(0);

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__);
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int gen(int a, int b) {return (ll)rng() % (b - a + 1) + a;}

struct state {
	int n, b, p;
	state() {
		cin >> n >> b >> p;
	}
};

template<typename T>
void max_self(T& a, T b) {
	if(a < b) {
		a = b;
	}
}

const int max_paintings = 1e5 + 1, INF = 1e15L + 5;
signed main()
{
	ios
	int n; cin >> n;
	vector<state> painters(n);
	for(state& s : painters) {
		s.p *= -1;
	}
	int m; cin >> m;
	vector<state> costumers(m);
	vector<state> all = painters;
	for(state& s : costumers) {
		s.n *= -1;
		all.emplace_back(s);
	}
	sort(all.begin(), all.end(), [&](const state& a, const state& b) {
		return make_pair(a.b, a.n) > make_pair(b.b, b.n);
	});
	int sz = all.size();
	vector<int> dp(max_paintings, -INF);
	dp[0] = 0;
	for(state& s : all) { // each time you buy smth it is garanteed that you would have enough money for it
		vector<int> new_dp(max_paintings, -INF);
		for(int j = 0; j < max_paintings; ++j) {
			max_self(new_dp[j], dp[j]);
			if(j + s.n >= 0) {
				max_self(new_dp[j + s.n], dp[j] + s.p);
			}
		}
		swap(dp, new_dp);
	}
	cout << *max_element(dp.begin(), dp.end()) << '\n';
}
