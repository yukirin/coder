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
#define put(a) ((cout) << (a) << (endl))
#define putf(a, n) ((cout) << (fixed) << (setprecision(n)) << (a) << (endl))
#define deg2rad(x) (((x)*PI) / (180.0))
#define rad2deg(x) (((x) * (180.0)) / PI)
#define fi first
#define se second

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;
template <class T> using vec = vector<T>;

static constexpr ll LL_INF = 1LL << 60;
static constexpr int I_INF = 1 << 28;
static constexpr double PI = static_cast<double>(3.14159265358979323846264338327950288);
static constexpr double EPS = numeric_limits<double>::epsilon();

static map<type_index, const char* const> scanType = {
    {typeid(int), "%d"}, {typeid(ll), "%lld"}, {typeid(double), "%lf"}, {typeid(char), "%c"}};

template <class T> static void scan(vector<T>& v);
[[maybe_unused]] static void scan(vector<string>& v, bool isWord = true);
template <class T> static inline bool chmax(T& a, T b);
template <class T> static inline bool chmin(T& a, T b);
template <class T> static inline T gcd(T a, T b);
template <class T> static inline T lcm(T a, T b);
template <class A, size_t N, class T> static void Fill(A (&arr)[N], const T& val);
template <class T> T mod(T a, T m);

class UnionFind {
 private:
  std::vector<ll> par;
  std::vector<ll> siz;

 public:
  UnionFind(ll sz_) : par(sz_), siz(sz_, 1LL) {
    for (ll i = 0; i < sz_; i++) par[i] = i;
  }

  void reset(ll sz_) {
    par.assign(sz_, 0LL);
    siz.assign(sz_, 1LL);
    for (ll i = 0; i < sz_; i++) par[i] = i;
  }

  ll find(ll x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
  }

  bool unite(ll x, ll y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;

    if (siz[x] < siz[y]) std::swap(x, y);
    siz[x] += siz[y];
    par[y] = x;
    return true;
  }

  bool same(ll x, ll y) { return find(x) == find(y); }
  ll size(ll x) { return siz[find(x)]; }
};

template <class T> struct Edge {
  int src, to;
  T cost;

  Edge(int to, T cost) : src(-1), to(to), cost(cost) {}
  Edge(int src, int to, T cost) : src(src), to(to), cost(cost) {}

  Edge& operator=(const int& x) {
    to = x;
    return *this;
  }

  operator int() const { return to; }
};

template <class T> using Edges = vector<Edge<T>>;
template <class T> using WeightedGraph = vector<Edges<T>>;
using UnWeightedGraph = vector<vector<int>>;
template <class T> using Matrix = vector<vector<T>>;

template <class T> T kruskal(Edges<T>& edges, int V) {
  sort(begin(edges), end(edges), [](const Edge<T>& a, const Edge<T>& b) { return (a.cost < b.cost); });
  UnionFind tree(V);
  T ret = 0;
  for (auto& e : edges) {
    if (tree.unite(e.src, e.to)) ret += e.cost;
  }
  return (ret);
}

int main(int argc, char* argv[]) {
  ll n;
  cin >> n;
  vec<ll_ll> x(n), y(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld %lld", &x[i].fi, &y[i].fi);
    x[i].se = y[i].se = i;
  }

  sort(all(x));
  sort(all(y));

  Edges<ll> edges;
  rep(i, 0, n - 1) {
    edges.emplace_back(x[i].se, x[i + 1].se, abs(x[i].fi - x[i + 1].fi));
    edges.emplace_back(y[i].se, y[i + 1].se, abs(y[i].fi - y[i + 1].fi));
  }

  cout << kruskal(edges, n) << endl;
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

template <class T> inline T gcd(T a, T b) { return __gcd(a, b); }

template <class T> inline T lcm(T a, T b) {
  T c = min(a, b), d = max(a, b);
  return c * (d / gcd(c, d));
}

template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val) {
  std::fill((T*)arr, (T*)(arr + N), val);
}

template <class T> T mod(T a, T m) { return (a % m + m) % m; }
