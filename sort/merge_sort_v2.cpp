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

void merge(vector<int>* a, int l, int r) {
	vector<int> container;
	int m = (l + r) >> 1;
	int i = l, j = m + 1;
	while (container.size() <= r - l) {
		if ((j > r || (*a)[i] <= (*a)[j]) && i <= m) {
			container.push_back((*a)[i]);
			++i;
		}
		else if ((i > m || (*a)[i] > (*a)[j]) && j <= r) {
			container.push_back((*a)[j]);
			++j;
		}
	}
	for (int i = l; i <= r; ++i) {
		(*a)[i] = container[i - l];
	}
}

void m_merge_sort(vector<int>* a, int l, int r) {
	if (l < r) {
		int m = (l + r) >> 1;
		m_merge_sort(a, l, m);
		m_merge_sort(a, m + 1, r);
		merge(a, l, r);
	}
}

vector<int> merge_sort(vector<int> a) {
	m_merge_sort(&a, 0, a.size() - 1);
	return a;
}



int main() {
	for (int i = 0; i < 100; ++i) {
		cout << checkout(merge_sort(testData(100))) << endl;
	}

}
