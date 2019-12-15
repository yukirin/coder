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

// dijkstra (route restoration)
// ! init process -> prev[i] = -1
template <class T> vector<T> dijkstra(int s, WeightedGraph<T>& adj_list, vector<int>& prev, T inf) {
  int si = sz(adj_list);
  vector<T> dist(si, inf);

  using Pi = pair<T, int>;
  priority_queue<Pi, vector<Pi>, greater<Pi>> que;
  dist[s] = 0;
  que.emplace(dist[s], s);
  while (!que.empty()) {
    T cost;
    int idx;
    tie(cost, idx) = que.top();
    que.pop();
    if (dist[idx] < cost) continue;
    for (auto& e : adj_list[idx]) {
      auto next_cost = cost + e.cost;
      if (dist[e.to] <= next_cost) continue;
      dist[e.to] = next_cost;
      prev[e.to] = idx;
      que.emplace(dist[e.to], e.to);
    }
  }
  return dist;
}

vector<int> route(int s, int g, vector<int>& prev) {
  vector<int> path;
  for (int cur = g; cur != -1; cur = prev[cur]) path.pb(cur);
  reverse(all(path));
  return path;
}

bool visited[100005];

ll dfs(int s, WeightedGraph<ll>& adj_list) {
  ll ret = !visited[s];
  visited[s] = true;
  rep(i, 0, sz(adj_list[s])) {
    int to = adj_list[s][i].to;
    if (visited[to]) continue;
    ret += dfs(to, adj_list);
  }

  return ret;
}

int main(int argc, char* argv[]) {
  long long n;
  scanf("%lld", &n);
  vec<ll> a(n - 1), b(n - 1);
  vec<int> prev(n, -1LL);
  WeightedGraph<ll> adjlist(n);
  for (int i = 0; i < n - 1; i++) {
    scanf("%lld %lld", &a[i], &b[i]);
    a[i]--, b[i]--;
    adjlist[a[i]].emplace_back(b[i], 1);
    adjlist[b[i]].emplace_back(a[i], 1);
  }

  auto dists = dijkstra(0, adjlist, prev, LL_INF);
  vec<int> path = route(0, n - 1, prev);

  vec<int> fennec, snuke;
  int middle = (sz(path) + 1) / 2;
  rep(i, 0, sz(path)) {
    visited[path[i]] = true;
    ((i < middle) ? fennec : snuke).pb(path[i]);
  }

  int first_play = (sz(path) % 2);
  ll f_count = 0, s_count = 0;
  for (ll num : fennec) f_count += dfs(num, adjlist);
  for (ll num : snuke) s_count += dfs(num, adjlist);

  if (first_play) {
    put(f_count >= s_count ? "Fennec" : "Snuke");
    return 0;
  }

  put(s_count >= f_count ? "Snuke" : "Fennec");
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
