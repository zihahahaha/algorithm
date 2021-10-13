#include<vector>
#include<iostream>
using namespace std;

vector<int> testData(int n) {
	srand(time(nullptr));
	vector<int> data;
	for (int i = 0; i < n; ++i) {
		data.push_back(rand());
	}
	return data;
}

bool checkout(vector<int> a) {
	for (int i = 0; i < a.size() - 1; ++i) {
		if (a[i] > a[i + 1])
			return false;
	}
	return true;
}

int paration(vector<int>* a, int l, int r) {
	int i = l - 1;
	int key = (*a)[r - 1];
	for (int j = l; j < r; ++j) {
		if ((*a)[j] <= key) {
			i++;
			swap((*a)[i], (*a)[j]);
		}
	}
	return i;
}

void m_qsort(vector<int>* a, int l, int r) {
	if (l < r - 1) {
		int m = paration(a, l, r);
		m_qsort(a, l, m);
		m_qsort(a, m + 1, r);
	}
}

vector<int> q_sort(vector<int> a) {
	m_qsort(&a, 0, a.size());
	return a;
}

int main() {
	for (int i = 0; i < 100; ++i) {
		cout << checkout(q_sort(testData(1000))) << endl;
	}

}
