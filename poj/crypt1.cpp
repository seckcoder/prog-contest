/*
ID: seckcoder
PROG: crypt1
LANG: C++
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

#define M 10

class BigNum 
{
	public:
		int a[M];
		int len;
		BigNum() { clear(); }
		BigNum(const BigNum &num) {len = num.len; memcpy(a,num.a,len*sizeof(a[0]));}
		BigNum &operator=(int b) {
			assert(b >= 0);
			if (b == 0) len = 1;
			else {
				while(b) {
					a[len] = b / 10;
					b %= 10;
					len++;
				}
			}
			return (*this);
		}
		void clear() { len = 0; memset(a,0,M * sizeof(a[0]));} 
		const int &operator[](int i) const {
			assert(i < M);
			return a[i];
		}
		int &operator[](int i) {
			assert(i < M);
			return a[i];
		}

};
static inline ostream &operator<<(ostream &os, const BigNum &num)
{
	for (int i = 0 ; i < num.len; i++) {
		os << num[num.len-i-1];
	}
	os << endl;
	return os;
}
static inline istream &operator>>(istream &is, BigNum &num)
{
	is >> num.len;
	for (int i = 0; i < num.len; i++) {
		is >> num[num.len-i-1];
	}
	return is;
}
static inline BigNum operator+(const BigNum &num1, const BigNum &num2)
{
	BigNum res;
	const BigNum *pmax, *pmin;
	if(num1.len > num2.len) pmax = &num1, pmin = &num2;
	else pmax = &num2, pmin = &num1;
	res.len = pmax->len;
	for (int i = 0; i < pmax->len; i++) {
		res[i] += (*pmin)[i] + (*pmax)[i];
		if (res[i] >= 10) res[i+1] += res[i] / 10, res[i] = res[i] % 10;
	}
	if (res[res.len] != 0) res.len++;
	while(res[res.len] >= 10) { res[res.len+1] += res[res.len] / 10; res[res.len+1] = res[res.len] % 10; res.len++; }
	return res;
}

static inline BigNum operator*(const BigNum &num1, const BigNum &num2)
{
	BigNum res;
	res.len = num1.len + num2.len - 1;
	for (int j = 0; j < num2.len; j++) {
		for (int i = 0; i < num1.len; i++) {
			res[i + j] += num1[i] * num2[j];
			if (res[i+j] >= 10) res[i+j+1] = res[i+j]/10, res[i+j] = res[i+j]%10;
		}
	}
	if (res[res.len] != 0) res.len++;
	while(res[res.len] >= 10) {res[res.len+1] += res[res.len] / 10; res[res.len+1] = res[res.len] % 10; res.len++;}
	return res;
}

int n;
int *digit;
BigNum arr1[1000];
BigNum arr2[100];
void test()
{
	ifstream ifs("test.in");
	ofstream ofs("test.out");
	BigNum num1;
	BigNum num2;
	ifs >> num1;
	ifs >> num2;
	cout << num1 << endl;
	cout << num2 << endl;
	//cout << num1 * num2 << endl;
	ifs.close();

}
int main()
{
	/*ifstream ifsin("crypt1.in");
	ofstream ofsout("crypt1.out");
	ifsin >> n;
	digit = new int[n];
	for (int i = 0; i < n; i++) {
		ifsin >> digit[i];
	}
	delete [] digit;*/
  test();
	return 0;
}
