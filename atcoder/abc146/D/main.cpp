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

map<ll_ll, int> m;
UnWeightedGraph g;
int max_color = 0;
vector<bool> checked;

void dfs(int prev_color, int vertex) {
  for (int next_vertex : g[vertex]) {
    i_i p;
    p.first = min(vertex, next_vertex);
    p.second = max(vertex, next_vertex);

    if (m[p] > 0) continue;
    prev_color = (prev_color + 1) % (max_color);
    m[p] = prev_color + 1;

    dfs(prev_color, next_vertex);
  }
}

int main(int argc, char* argv[]) {
  long long N;
  scanf("%lld", &N);
  g.assign(N, vector<int>());
  checked.assign(N, false);
  std::vector<long long> a(N - 1);
  std::vector<long long> b(N - 1);
  for (int i = 0; i < N - 1; i++) {
    scanf("%lld", &a[i]);
    scanf("%lld", &b[i]);
    a[i]--, b[i]--;
    g[a[i]].pb(b[i]);
    g[b[i]].pb(a[i]);
  }

  rep(i, 0, N) {
    int s = g[i].size();
    chmax(max_color, s);
  }
  dfs(-1, 0);
  put(max_color);
  rep(i, 0, N - 1) { put(m[make_pair(a[i], b[i])]); }
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

template <class T> T mod(T a, T m) { return (a % m + m) % m; }
