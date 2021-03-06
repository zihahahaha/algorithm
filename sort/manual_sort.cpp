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


vector<int> bubble_sort(vector<int> a) {
	for (int i = 0; i < a.size() - 1; ++i)
		for (int j = 0; j < a.size() - i - 1; ++j)
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
	return a;
}

vector<int> choose_sort(vector<int> a) {
	for (int i = a.size() - 1; i >= 1; --i) {
		int maxIndex = i;
		for (int j = 0; j < i; ++j)
			if (a[j] > a[maxIndex])
				maxIndex = j;
		swap(a[i], a[maxIndex]);
	}
	return a;
}

vector<int> insert_sort(vector<int> a) {
	for (int i = 1; i < a.size(); ++i) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && key < a[j]) {
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = key;
	}
	return a;
}

//not manual

int main() {
	
}
