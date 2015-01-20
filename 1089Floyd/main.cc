#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

int add(int a, int b){
	if(a == INT_MAX || b == INT_MAX)	return INT_MAX;
	return a + b;
}

void floyd(vector<vector<int> > &data){
	vector<vector<int> > DO = data;
	int vecnum = data.size();
	int count = 0;
	while(count < vecnum){
		for(int i = 0; i < vecnum - 1; i++){
			for(int j = i + 1; j < vecnum; j++){
				data[i][j] = min(DO[i][j], add(DO[i][count], DO[count][j]));
				data[j][i] = data[i][j];
			}
		}
		DO = data;
		count++;
	}
}

int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int N, M;

	cin>>N>>M;
	vector<vector<int> > data(N, vector<int>(N, INT_MAX));
	for(int i = 0; i < N; i++)
		data[i][i] = 0;

	int count = 0, s, e, w;
	while(count++ < M){
		cin>>s>>e>>w;
		s--;
		e--;
		data[s][e] = min(data[s][e], w);
		data[e][s] = data[s][e];
	}

	floyd(data);

	for(int i = 0; i < N; i++){
		for(int j = 0; j < N - 1; j++){
			cout<<data[i][j]<<" ";
		}
		cout<<data[i][N-1]<<endl;
	}

	return 0;
}
