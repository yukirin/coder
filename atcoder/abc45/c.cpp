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
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>

#define DEBUG(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define REPC(i, a) REP(i, 0, a)
#define RREP(i, a, b) for (int i = (a); i >= (b); i--)
#define RREPC(i, a) RREP(i, a, 0)
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

static map<type_index, const char *const> scanType = {{typeid(int), "%d"},
                                                      {typeid(ll), "%lld"},
                                                      {typeid(double), "%lf"},
                                                      {typeid(char), "%c"}};

template <class T> static void scan(vector<T> &v);
static void scan(vector<string> &v, bool isWord = true);
static boost::dynamic_bitset<> scan(char trueValue = 'o');
ll solve(string s, vector<int> &comb, bool ret);
void comb(vector<int> &nv, int r, string s);
void innerC(vector<int> &nv, vector<int> &ret, int count, int last, string s);

int main(int argc, char *argv[]) {
  // INFILE();
  string s;
  cin >> s;

	if (s.size() == 1) {
		cout << s << endl;
		return 0;
	}

  vector<int> v;
	REPC(i, (int)s.size() - 1) {
		v.push_back(i + 1);
	}

	REP(i, 1, (int)s.size()) {
		comb(v, i, s);
	}

	vector<int> tv;
	cout << solve("", tv, true) << endl;
  return 0;
}

void comb(vector<int> &nv, int r, string s) {
  int n = nv.size();

  vector<int> v;
  REPC(i, n - r + 1) { 
		v.push_back(nv[i]);
		innerC(nv, v, r - 1, i + 1, s);
		v.pop_back();
	}
}

void innerC(vector<int> &nv, vector<int> &ret, int count, int first, string s) {
  if (count == 0) {
		solve(s, ret, false);
    return;
  }

  int n = nv.size();
  count--;
  REP(i, first, n - count) {
    ret.push_back(nv[i]);
    innerC(nv, ret, count, i + 1, s);
		ret.pop_back();
  }
}

ll solve(string s, vector<int> &comb, bool ret) {
  static ll total = stoll(s);
	if (ret) {
		return total;
	}

  auto b = begin(s);
  int pos = 0;

	vector<int> v(comb);
	v.push_back(s.size());
  for (const auto &val : v) {
		total += stoll(string(b + pos, b + val));
    pos = val;
  }

  return total;
}

template <class T> static void scan(vector<T> &v) {
  auto tFormat = scanType[typeid(T)];
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
