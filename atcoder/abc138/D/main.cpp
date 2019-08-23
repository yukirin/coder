#include <bits/stdc++.h>

#ifdef _DEBUG
#define debug(x) cerr << "line: " << __LINE__ << ", func: " << __func__ << " ->  " << #x << " = " << x << endl
#define INFILE freopen("input.txt", "r", stdin)
#else
#define debug(x)
#define INFILE
#endif

#define ALL(s) begin(s), end(s)
#define RALL(s) rbegin(s), rend(s)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RREP(i, a, b) for (int i = (a); i >= (b); i--)

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

struct Node {
  vector<int> children;
  ll cost;
  bool used;
};

Node nodes[200010];
ll results[200010];

int main(int argc, char* argv[]) {
  ll N, Q;
  cin >> N >> Q;

  REP(i, 0, N - 1) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    nodes[a].children.push_back(b);
    nodes[b].children.push_back(a);
  }

  REP(i, 0, Q) {
    int p, x;
    cin >> p >> x;
    p--;
    nodes[p].cost += x;
  }

  stack<int> s;
  s.push(0);

  ll cost = 0;
  while (!s.empty()) {
    int index = s.top();
    s.pop();

    if (nodes[index].used) {
      cost -= nodes[index].cost;
      continue;
    }

    cost += nodes[index].cost;
    results[index] = cost;
    nodes[index].used = true;

    s.push(index);
    for (int next : nodes[index].children) {
      if (nodes[next].used) continue;
      s.push(next);
    }
  }

  string result;
  REP(i, 0, N) { result += to_string(results[i]) + " "; }
  result.pop_back();
  cout << result << endl;
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
