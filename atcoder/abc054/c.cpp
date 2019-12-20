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

using namespace std;

#define DEBUG(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_i = pair<ll, int>;
using i_ll = pair<int, ll>;
using d_i = pair<double, int>;
using ll_ll = pair<ll, ll>;
using d_d = pair<double, double>;

constexpr ll LL_MOD = 1000000009;
constexpr int I_MOD = 1000000007;
constexpr double EPS = numeric_limits<double>::epsilon();
constexpr double PI = 3.14159265358979323846264338327950288;

template <class T> void scan(vector<T> &v);
void scan(vector<string> &v, bool isWord = true);
boost::dynamic_bitset<> scan(char trueValue = 'o');

class Node {
public:
  int cur;
  set<int> s;

  Node(int p) noexcept : cur(p), s({p}) {}

  bool in(const int next) const { return s.find(next) != end(s); }
  void add(const int next) {
    cur = next;
    s.insert(next);
  }
};

int main(int argc, char *argv[]) {
	// INFILE();
  int n, m;
  cin >> n >> m;

  bool adjList[8][8] = {};
  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    adjList[from - 1][to - 1] = true;
    adjList[to - 1][from - 1] = true;
  }

  queue<Node> q;
  q.push(Node(1));

  int total = 0;
  while (!q.empty()) {
    Node next_p = q.front();
    q.pop();

    for (int i = 0; i < n; i++) {
      if (!adjList[next_p.cur - 1][i] || next_p.in(i + 1)) {
        continue;
      }

      Node new_node = next_p;
      new_node.add(i + 1);

      if (new_node.s.size() == n) {
        total++;
        continue;
      }
      q.push(new_node);
    }
  }

  cout << total << "\n";
  return 0;
}

template <class T> void scan(vector<T> &v) {
  map<type_index, const char *const> m = {{typeid(int), "%d"},
                                          {typeid(ll), "%lld"},
                                          {typeid(double), "%lf"},
                                          {typeid(char), "%c"}};

  auto tFormat = m[typeid(T)];

  for (T &n : v) {
    scanf(tFormat, &n);
  }
}

void scan(vector<string> &v, bool isWord) {
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

boost::dynamic_bitset<> scan(char trueValue) {
  string s;
  getline(cin, s);

  if (s.size() == 0) {
    getline(cin, s);
  }

  for_each(begin(s), end(s),
           [trueValue](char &c) { c = (c == trueValue) ? '1' : '0'; });
  return boost::dynamic_bitset<>(string(rbegin(s), rend(s)));
}
