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

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

// warshall floyd (route restoration)
// ! init process -> adj[i][i] = 0, adj[i][j] = inf -> (add edge)
// ! init process -> next[i][j] = j
template <class T> void warshall_floyd(Matrix<T>& adj, Matrix<int>& next) {
  int s = sz(adj);
  for (int k = 0; k < s; k++) {
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (adj[i][k] + adj[k][j] >= adj[i][j]) continue;
        adj[i][j] = adj[i][k] + adj[k][j];
        next[i][j] = next[i][k];
      }
    }
  }
}

vector<int> route(int s, int g, Matrix<int>& next) {
  vector<int> path;
  for (int cur = s; cur != g; cur = next[cur][g]) path.pb(cur);
  path.pb(g);
  return path;
}

int main(int argc, char* argv[]) {
  ll n, m;
  cin >> n >> m;
  Matrix<int> adj(n, vec<int>(n, I_INF)), next(n, vec<int>(n, 0));
  vec<int> a(m), b(m), c(m);
  rep(i, 0, n) adj[i][i] = 0;
  rep(i, 0, n) rep(j, 0, n) next[i][j] = j;
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &a[i], &b[i], &c[i]);
    a[i]--, b[i]--;
    adj[a[i]][b[i]] = adj[b[i]][a[i]] = c[i];
  }
  warshall_floyd(adj, next);

  Matrix<bool> used(n, vec<bool>(n, false));
  rep(i, 0, n) rep(j, 0, n) {
    vec<int> path = route(i, j, next);
    rep(k, 1, sz(path)) { used[path[k]][path[k - 1]] = used[path[k - 1]][path[k]] = true; }
  }

  ll ans = 0;
  rep(i, 0, m) {
    if (used[a[i]][b[i]]) continue;
    ans++;
  }

  put(ans);
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
