#include <algorithm>
#include <bitset>
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
#include <vector>

using namespace std;

#define DEBUG(x) cout << #x << ": " << x << endl
#define INFILE() freopen("input.txt", "r", stdin)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> i_i;
typedef pair<ll, int> ll_i;
typedef pair<int, ll> i_ll;
typedef pair<double, int> d_i;
typedef pair<ll, ll> ll_ll;
typedef pair<double, double> d_d;

constexpr ll LL_MOD = 1000000009;
constexpr int I_MOD = 1000000007;
constexpr double EPS = numeric_limits<double>::epsilon();
constexpr double PI = 3.14159265358979323846264338327950288;

void sI(int *pa, int size);
void sLL(ll *pa, int size);
void sD(double *pa, int size);
void sC(char *pa, int size);
void wS(string *ps, int size);
void lS(string *ps, int size);

int main(int argc, char *argv[]) {
  INFILE();
  cout << "coder"
       << "\n";
  return 0;
}

void sI(int *pa, int size) {
  for (int i = 0; i < size; ++i) {
    scanf("%d", pa + i);
  }
}

void sLL(ll *pa, int size) {
  for (int i = 0; i < size; ++i) {
    scanf("%lld", pa + i);
  }
}

void sD(double *pa, int size) {
  for (int i = 0; i < size; ++i) {
    scanf("%lf", pa + i);
  }
}

void sC(char *pa, int size) {
  for (int i = 0; i < size; ++i) {
    scanf(" %c", pa + i);
  }
}

void wS(string *ps, int size) {
  for (int i = 0; i < size; ++i) {
    cin >> ps[i];
  }
}

void lS(string *ps, int size) {
  int i = 0;
  string s;
  getline(cin, s);

  if (s.size() != 0) {
    i++;
    ps[0] = s;
  }

  for (; i < size; ++i) {
    getline(cin, ps[i]);
  }
}
