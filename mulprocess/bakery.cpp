#include<thread>
#include<mutex>
#include<Windows.h>
#include<iostream>
#include<vector>
using namespace std;

const int maxn = 1000;
bool choosing[maxn];
int number[maxn];



bool cmp(int a1, int a2, int b1, int b2) {
	if (a1 == b1)
		return a2 < b2;
	else
		return a1 < b1;
}

int getNumber() {
	int maxx = 0;
	for (int i = 0; i < maxn; ++i) {
		if (number[i] > maxx)
			maxx = number[i];
	}
	return maxx + 1;
}


void lock(int pid) {
	choosing[pid] = true;//进程号为pid的进程正在取号
	number[pid] = getNumber();//取号
	choosing[pid] = false;//取号完了

	//忙等待代码
	for (int i = 0; i < maxn; ++i) {
		while (choosing[i]);//等i取完号,因为i可能优先级和pid相同

		//等待优先级小于当前进程的进程先执行完
		while (number[i] != 0 && cmp(number[i], i, number[pid], pid));
	}
}

void unlock(int pid) {
	number[pid] = 0;
}


void testa() {
	while (true) {
		lock(0);
		std::cout << "a";
		std::cout << "\n";
		unlock(0);
	}
}

void testb() {
	while (true) {
		lock(1);
		std::cout << "b";
		std::cout << "\n";
		unlock(1);
	}
}

int main() {
	std::thread p(testa);
	std::thread q(testb);
	p.join();
	q.join();
}
