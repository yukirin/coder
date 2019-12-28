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

// @return -> not DAG if empty vector
int topological_sort(vec<vec<vec<i_i>>>& adj_list) {
  int v = sz(adj_list);
  int ans = 0;
  vec<vec<ll>> cnt(v, vec<ll>(v, 0));
  stack<i_i> st;
  rep(i, 0, v) rep(j, 0, v) {
    for (i_i& p : adj_list[i][j]) {
      cnt[p.fi][p.se]++;
    }
  }

  rep(i, 0, v) rep(j, 0, v) if (cnt[i][j] == 0) st.push({i, j});

  bool c = true;
  while (c) {
    vec<i_i> next_list;
    while (st.size()) {
      i_i cur = st.top();
      st.pop();

      for (auto to : adj_list[cur.fi][cur.se]) {
        cnt[to.fi][to.se]--;
        if (cnt[to.fi][to.se] == 0LL) next_list.pb(to);
      }
    }

    ans++;
    for (i_i p : next_list) st.push(p);
    if (sz(next_list) == 0) c = false;
  }

  rep(i, 0, v) rep(j, 0, v) if (cnt[i][j] > 0) return -1;
  return ans;
}

int main(int argc, char* argv[]) {
  int n;
  cin >> n;

  vec<vec<int>> match(n, vec<int>(n - 1));
  vec<vec<vec<i_i>>> adj_list(n, vec<vec<i_i>>(n, vec<i_i>()));
  rep(i, 0, n) scan(match[i]);

  rep(i, 0, n) {
    rep(j, 0, n - 2) {
      int l = min(i + 1, match[i][j]), l2 = min(i + 1, match[i][j + 1]);
      int r = max(i + 1, match[i][j]), r2 = max(i + 1, match[i][j + 1]);
      l--, l2--, r--, r2--;
      adj_list[l][r].emplace_back(l2, r2);
    }
  }

  ll ans = topological_sort(adj_list);
  cout << ans << endl;
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
