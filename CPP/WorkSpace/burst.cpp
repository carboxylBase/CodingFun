#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000000;  // 最大值为 10^7
int min_prime[MAXN + 1];    // 存储每个数的最小质因子
int sg[MAXN + 1];           // SG 值数组
vector<int> primes;         // 存储质数

// 线性筛法计算最小质因子和 SG 值
void calculate_min_prime_and_sg() {
  memset(min_prime, 0, sizeof(min_prime));  // 初始化最小质因子数组
  memset(sg, 0, sizeof(sg));                // 初始化 SG 值数组
  // 线性筛法
  for (int i = 2; i <= MAXN; ++i) {
    if (min_prime[i] == 0) {  // 如果 i 是质数
      min_prime[i] = i;       // 质数的最小质因子是它自己
      primes.push_back(i);    // 记录质数
      sg[i] = primes.size();
    }
    // 更新最小质因子
    for (int p : primes) {
      if (p > min_prime[i] || p * i > MAXN) break;  // 只需查找到 sqrt(i)
      min_prime[p * i] = p;                         // 设置最小质因子
    }
  }
  sg[1] = 1;  // SG(1) = 1
  sg[2] = 0;  // SG(2) = 0
  // 计算 SG 值
  for (int i = 3; i <= MAXN; ++i)
    if (min_prime[i] < i)
      sg[i] = sg[min_prime[i]];  // 合数的 SG 值等于其最小质因子的 SG 值
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 预处理最小质因子和 SG 值
  calculate_min_prime_and_sg();

  cout << sg[5880345];
  return 0;

  int t;
  cin >> t;  // 测试案例的数量
  vector<string> results;

  while (t--) {
    int n;
    cin >> n;  // 当前测试案例的石头堆数量
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];  // 当前测试案例的石头数量
    }

    // 计算 SG 的异或值
    int xor_sum = 0;
    for (int num : a) {
      xor_sum ^= sg[num];  // 使用预处理的 SG 值
    }

    // 判断赢家
    if (xor_sum == 0) {
      results.push_back("Bob");
    } else {
      results.push_back("Alice");
    }
  }

  // 输出结果
  for (const string& result : results) {
    cout << result << "\n";
  }

  return 0;
}