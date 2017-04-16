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
#include <unordered_map>
#include <unordered_set>
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

int main(int argc, char *argv[]) {
	// INFILE();
  ll h, w, n;
  cin >> h >> w >> n;
  vector<vector<int>> maze = {{-1, 0, 1}, {-1, 0, 1}};

  vector<ll> counter(10);
  map<ll_ll, ll> ms;
  vector<ll> v(2);
  REPC(i, n) {
    scan(v);
    ll minX = max((ll)2, v[1] - 1), maxX = min(w, v[1] + 2);
    ll minY = max((ll)2, v[0] - 1), maxY = min(h, v[0] + 2);
    REP(i, minX, maxX) {
      REP(j, minY, maxY) {
        ms[make_pair(j, i)]++;
      }
    }
  }

	for(const auto& val : ms) {
		counter[val.second]++;
	}

  ll z = (w - 2) * (h - 2);
  counter[0] = z - accumulate(begin(counter) + 1, end(counter), 0);
  for (const auto &val : counter) {
    cout << val << "\n";
  }
  return 0;
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
