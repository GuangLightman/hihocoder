#include <iostream>
#include <vector>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

struct Node{
	int index;
	int weight;
	Node(int index = 0, int weight = 0):index(index),weight(weight){}
};

int findMin(vector<int> &cost, vector<bool> &visited){
	int min = INT_MAX;
	int pos = -1;
	for(int i = 0; i < cost.size(); i++){
		if(!visited[i] && min > cost[i]){
			min = cost[i];
			pos = i;
		}
	}
	return pos;
}

int minPath(vector<vector<Node> > &data, int S, int  T){
	int vecnum = data.size();
	vector<int> cost(vecnum, INT_MAX);
	vector<bool> visited(vecnum, false);
	visited[S] = true;
	for(int i = 0; i < data[S].size(); i++){
		cost[data[S][i].index] = min(cost[data[S][i].index],data[S][i].weight);
	}
	int count = 0;

	while(count++ < vecnum - 1){
		int cur = findMin(cost, visited);
		if(cur == T)	return cost[cur];
		visited[cur] = true;
		for(int i = 0; i < data[cur].size(); i++){
			int index = data[cur][i].index;
			if(!visited[index] && cost[cur] + data[cur][i].weight < cost[index]){
				cost[index] = cost[cur] + data[cur][i].weight;
			}
		}	
	}
	
}


int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int N, M, S, T;
	cin>>N>>M>>S>>T;
	S--;
	T--;
	vector<vector<Node> > data(N, vector<Node>());
	
	int count = 0;
	int s,e,w;
	while(count++ < M){
		cin>>s>>e>>w;
		s--;
		e--;
		data[s].push_back(Node(e, w));
		data[e].push_back(Node(s, w));
	}
	
	int ret = minPath(data, S, T);

	cout<<ret<<endl;

	return 0;
}
