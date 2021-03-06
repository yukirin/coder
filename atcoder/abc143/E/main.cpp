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

// ! init process -> adj[i][i] = 0, adj[i][j] = inf -> (add edge)
template <class T> void warshall_floyd(Matrix<T>& adj) {
  int s = sz(adj);
  for (int k = 0; k < s; k++) {
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (adj[i][k] + adj[k][j] >= adj[i][j]) continue;
        adj[i][j] = adj[i][k] + adj[k][j];
      }
    }
  }
}

int main(int argc, char* argv[]) {
  ll n, m, l;
  cin >> n >> m >> l;
  Matrix<ll> adj(n, vector<ll>(n, LL_INF)), adj2(n, vec<ll>(n, LL_INF));
  rep(i, 0, n) adj[i][i] = adj2[i][i] = 0;

  rep(i, 0, m) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    if (c > l) continue;
    adj[a][b] = adj[b][a] = c;
  }

  ll q;
  cin >> q;
  vec<int> s(q), t(q);
  rep(i, 0, q) {
    scanf("%d %d", &s[i], &t[i]);
    s[i]--, t[i]--;
  }

  warshall_floyd(adj);
  rep(i, 0, n) rep(j, 0, n) if (adj[i][j] <= l) adj2[i][j] = 1;
  warshall_floyd(adj2);

  rep(i, 0, q) { put(adj2[s[i]][t[i]] == LL_INF ? -1 : adj2[s[i]][t[i]] - 1); }
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
