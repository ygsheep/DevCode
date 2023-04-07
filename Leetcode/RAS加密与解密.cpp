#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// 计算最大公约数
int gcd(int a, int b) {
  if (a == 0)
    return b;
  return gcd(b % a, a);
}

// 计算模逆元
int modInverse(int a, int m) {
  for (int x = 1; x < m; x++)
    if (((a % m) * (x % m)) % m == 1)
      return x;
  return -1;
}

// 快速幂取模运算
int power(int x, unsigned int y, int p) {
  int res = 1;
  x = x % p;
  while (y > 0) {
    if (y & 1)
      res = (res * x) % p;
    y = y >> 1;
    x = (x * x) % p;
  }
  return res;
}

void RSAEncryptDecrypt(string text, int key[], int n) {
  string result = "";
  for (char c : text) {
    int asciiVal = c;
    result += char(power(asciiVal, key[0], n));
  }

  cout << "Result: " << result << endl;
}

int main() {
  // 假设p=61和q=53是两个大质数
  double p = 61;
  double q = 53;

  // 计算n=p*q
  double n = p * q;

  // 计算φ(n)=(p-1)*(q-1)
  double phi_n = (p - 1) * (q - 1);

  // 找到e，使得e与φ(n)互质且e小于φ(n)
  double e = 2;

  while (e < phi_n) {
    if (gcd(e, phi_n) == 1) {
      break;
    } else {
      e++;
    }
  }

  cout << "The value of e is: " << e << endl;

  // 计算d，使得d*e≡1(mod φ(n))
  double d = modInverse(e, n);
  cout << "The value of d is: " << d << endl;

  // 公钥为{e,n}
  int publicKey[] = {(int)e, (int)n};

  // 私钥为{d,n}
  int privateKey[] = {(int)d, (int)n};

  string message = "Hello World!";

  cout << "Original Message: " << message << endl;

  cout << "Encrypted Message: ";
  RSAEncryptDecrypt(message, privateKey, n);

  cout << "Decrypted Message: ";
  RSAEncryptDecrypt(message, privateKey, n);

  return 0;
}
