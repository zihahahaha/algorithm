#include<thread>
#include<mutex>
#include<iostream>
#include<queue>
#include<Windows.h>

std::mutex flag;
std::condition_variable full;
std::condition_variable empty;
std::queue<std::string> cmdl;
const int N = 10;

void consumer() {
	while (true) {
		std::unique_lock<std::mutex> lk(flag);
		full.wait(lk, [] {
			return !cmdl.empty();
			});
		while (!cmdl.empty()) {
			std::cout << cmdl.front() << " ";
			cmdl.pop();
		}
		std::cout << std::endl;
		empty.notify_one();
		lk.unlock();
	}
}
int main() {
	std::thread p(consumer);
	p.detach();

	std::string s;
	while (true) {
		std::unique_lock<std::mutex> lk(flag);
		empty.wait(lk, [] {
			return cmdl.size() < N;
			});
		std::cin >> s;
		cmdl.push(s);
		full.notify_one();
		lk.unlock();
	}
}
