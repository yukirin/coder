#include <algorithm>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <cfloat>
#include <cmath>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>
#include <numeric>

#define DEBUG(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define REPC(i, a) REP(i, 0, a)
#define ALL(s) begin(s), end(s)
#define RALL(s) rbegin(s), rend(s)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_i = pair<ll, int>;
using i_ll = pair<int, ll>;
using d_i = pair<double, int>;
using ll_ll = pair<ll, ll>;
using d_d = pair<double, double>;

static constexpr ll LL_MOD = 1000000009;
static constexpr int I_MOD = 1000000007;
static constexpr double EPS = numeric_limits<double>::epsilon();
static constexpr double PI = 3.14159265358979323846264338327950288;

template <class T> static void scan(vector<T> &v);
static void scan(vector<string> &v, bool isWord = true);
static boost::dynamic_bitset<> scan(char trueValue = 'o');

int roadG[200000];
int railG[200000];
int result[200000];

int main(int argc, char *argv[]) {
	// INFILE();
	int n, k, l;
	cin >> n >> k >> l;

	vector<vector<int>> roadList(n);
	vector<vector<int>> railList(n);

	vector<vector<int>> roads(k);
	vector<int> r(2);
	REPC(i, k) {
		scan(r);
		roadList[r[0] - 1].push_back(r[1] - 1);
		roadList[r[1] - 1].push_back(r[0] - 1);
	}

	REPC(i, l) {
		scan(r);
		railList[r[0] - 1].push_back(r[1] - 1);
		railList[r[1] - 1].push_back(r[0] - 1);
	}

	REPC(i, n) {
		if (roadG[i] != 0) {
			continue;
		}

		int group = i + 1;
		stack<int> st;
		st.push(i);
		roadG[i] = group;

		while(!st.empty()) {
			auto cur = st.top();
			st.pop();

			for(const auto& n : roadList[cur]) {
				if (roadG[n] != 0) {
					continue;
				}

				roadG[n] = group;
				st.push(n);
			}
		}
	}

	REPC(i, n) {
		if (railG[i] != 0) {
			continue;
		}

		int group = i + 1;
		stack<int> st;
		st.push(i);
		railG[i] = group;

		while(!st.empty()) {
			auto cur = st.top();
			st.pop();

			for(const auto& n : railList[cur]) {
				if (railG[n] != 0) {
					continue;
				}

				railG[n] = group;
				st.push(n);
			}
		}
	}

	multimap<i_i, int> mp;
	auto itr = begin(mp);
	REPC(i, n) {
		itr = mp.emplace_hint(itr, make_pair(roadG[i], railG[i]), i);
	}

	REPC(i, n) {
		if (result[i] != 0) {
			cout << result[i] << " ";
			continue;
		}

		auto ret = mp.equal_range(make_pair(roadG[i], railG[i]));
		int count = mp.count(make_pair(roadG[i], railG[i]));

		for(auto f = ret.first; f != ret.second; f++) {
			result[f->second] = count;
		}
		cout << count << " ";
	}

  return 0;
}

template <class T> static void scan(vector<T> &v) {
  map<type_index, const char *const> m = {{typeid(int), "%d"},
                                          {typeid(ll), "%lld"},
                                          {typeid(double), "%lf"},
                                          {typeid(char), "%c"}};

  auto tFormat = m[typeid(T)];

  for (T &n : v) {
    scanf(tFormat, &n);
  }
}

static void scan(vector<string> &v, bool isWord) {
  if (isWord) {
    for (auto &n : v) {
      cin >> n;
    }
    return;
  }

  int i = 0, size = v.size();
  string s;
  getline(cin, s);

  if (s.size() != 0) {
    i++;
    v[0] = s;
  }

  for (; i < size; ++i) {
    getline(cin, v[i]);
  }
}

static boost::dynamic_bitset<> scan(char trueValue) {
  string s;
  getline(cin, s);

  if (s.size() == 0) {
    getline(cin, s);
  }

  for_each(begin(s), end(s),
           [trueValue](char &c) { c = (c == trueValue) ? '1' : '0'; });
  return boost::dynamic_bitset<>(string(rbegin(s), rend(s)));
}
