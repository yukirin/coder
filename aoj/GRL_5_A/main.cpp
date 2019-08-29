#include <bits/stdc++.h>

#ifdef _DEBUG
#define debug(x) cerr << "line: " << __LINE__ << ", func: " << __func__ << " ->  " << #x << " = " << x << endl
#else
#define debug(x)
#endif

#define all(s) begin(s), end(s)
#define rall(s) rbegin(s), rend(s)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define rrep(i, a, b) for (int i = ((a)-1); i >= (b); i--)
#define pb push_back
#define sz(a) int((a).size())

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;

static constexpr ll INF = 1LL << 60;
static constexpr double PI = static_cast<double>(3.14159265358979323846264338327950288);
static constexpr double EPS = numeric_limits<double>::epsilon();

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
[[maybe_unused]] static void scan(vector<string>& v, bool isWord = true);
template <class T> static inline bool chmax(T& a, T b);
template <class T> static inline bool chmin(T& a, T b);
template <class A, size_t N, class T> static void Fill(A (&arr)[N], const T& val);

struct Edge {
  int to;
  ll cost;
};

ll dists[100010];
vector<Edge> edges[100010];

void dfs1(int idx, int par) {
  for (const Edge& e : edges[idx]) {
    if (e.to == par) continue;
    dfs1(e.to, idx);
    chmax(dists[idx], dists[e.to] + e.cost);
  }
}

int dfs2(int idx, int d_par, int par) {
  vector<i_i> d_child;
  d_child.emplace_back(0, -1);

  for (Edge& e : edges[idx]) {
    if (e.to == par) {
      d_child.emplace_back(d_par + e.cost, e.to);
    } else {
      d_child.emplace_back(e.cost + dists[e.to], e.to);
    }
  }
  sort(rall(d_child));

  int ret = d_child[0].first + d_child[1].first;
  for (Edge& e : edges[idx]) {
    if (e.to == par) continue;

    ret = max(ret, dfs2(e.to, d_child[d_child[0].second == e.to].first, idx));
  }

  return (ret);
}

int main(int argc, char* argv[]) {
  int n;
  cin >> n;

  rep(i, 0, n - 1) {
    int a, b, w;
    cin >> a >> b >> w;
    edges[a].pb(Edge{b, w});
    edges[b].pb(Edge{a, w});
  }

  if (n == 1) {
    cout << 0 << endl;
    return 0;
  }

  if (n == 2) {
    cout << edges[0][0].cost << endl;
    return 0;
  }

  int root = 0;
  rep(i, 0, n) {
    if (sz(edges[i]) >= 2) root = i;
  }

  dfs1(root, -1);
  cout << dfs2(root, 99999, -1) << endl;
  return 0;
}

template <class T> static void scan(vector<T>& v) {
  auto tFormat = scanType[typeid(T)];
  for (T& n : v) {
    scanf(tFormat, &n);
  }
}

static void scan(vector<string>& v, bool isWord) {
  if (isWord) {
    for (auto& n : v) {
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

template <class T> inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

template <class T> inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}

template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val) {
  std::fill((T*)arr, (T*)(arr + N), val);
}
