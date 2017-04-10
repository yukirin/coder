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

#define DEBUG(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)
#define REP(i, a, b) for (int i = a; i < b; i++)
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

int adjList[100][100];
int nextP[100][100];
int used[100][100];

int main(int argc, char *argv[]) {
  // INFILE();
  int n, m;
  cin >> n >> m;

  fill((int *)adjList, (int *)adjList[100], 1000000000);
  REP(i, 0, 100) adjList[i][i] = 0;

  fill((int *)used, (int *)used[100], -1);

  REP(i, 0, 100) REP(j, 0, 100) nextP[i][j] = j;

  REP(i, 0, m) {
    int a, b, c;
    cin >> a >> b >> c;
    adjList[a - 1][b - 1] = adjList[b - 1][a - 1] = c;
    used[a - 1][b - 1] = used[b - 1][a - 1] = 1;
  }

  REP(k, 0, n) {
    REP(i, 0, n) {
      REP(j, 0, n) {
        if (adjList[i][j] > adjList[i][k] + adjList[k][j]) {
          adjList[i][j] = adjList[i][k] + adjList[k][j];

          nextP[i][j] = nextP[i][k];
        }
      }
    }
  }

  REP(i, 0, n) {
    REP(j, 0, n) {
      int cur = i, end = j;

      while (cur != j) {
        used[cur][nextP[cur][end]] = -1;
        used[nextP[cur][end]][cur] = -1;

        cur = nextP[cur][end];
      }
    }
  }

  int count = 0;
  REP(i, 0, n) {
    REP(j, 0, n) {
      if (used[i][j] == -1)
        continue;
      count++;
    }
  }

  cout << count / 2 << "\n";
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
