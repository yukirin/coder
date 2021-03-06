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

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i_i = pair<int, int>;
using ll_ll = pair<ll, ll>;
using d_ll = pair<double, ll>;
using ll_d = pair<ll, double>;
using d_d = pair<double, double>;

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

int main(int argc, char* argv[]) {
  ll n, m;
  cin >> n >> m;
  vector<ll_ll> edges(m);
  for (auto& e : edges) {
    cin >> e.first >> e.second;
    e.first--, e.second--;
  }

  auto count = [](ll num) { return (num * (num - 1)) / 2; };
  vector<ll> ans(m);
  ans[m - 1] = count(n);
  ll useful = 0;
  UnionFind tree(n);

  rrep(i, m, 1) {
    ll_ll e = edges[i];
    if (tree.same(e.first, e.second)) {
      ans[i - 1] = ans[i];
      continue;
    }

    useful -= count(tree.size(e.first));
    useful -= count(tree.size(e.second));

    tree.unite(e.first, e.second);
    useful += count(tree.size(e.first));
    ans[i - 1] = ans[m - 1] - useful;
  }

  for (ll num : ans) put(num);
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

template <class T> inline T lcm(T a, T b) { return (a * b) / gcd(a, b); }

template <class A, size_t N, class T> void Fill(A (&arr)[N], const T& val) {
  std::fill((T*)arr, (T*)(arr + N), val);
}
