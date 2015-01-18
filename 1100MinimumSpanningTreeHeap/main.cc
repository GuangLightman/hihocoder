#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Node{
	int index;
	int weight;
	Node(int index = 0, int weight = 0) : index(index), weight(weight){}
};

bool Cmp(const Node &a, const Node &b){
	return a.weight > b.weight;
}

int getMinSpanningTree(vector<vector<Node> > &data){
	int n = data.size();
	vector<Node> closeEdge;
	vector<bool> visited(n, false);
	visited[0] = true;
	// 初始化closeEdge函数
	for(int i = 0; i < data[0].size(); i++){
		closeEdge.push_back(data[0][i]);
	}
	make_heap(closeEdge.begin(), closeEdge.end(), Cmp);
	int sum = 0, count = 1, min = 0, index = 0;
	while(count < n){
		pop_heap(closeEdge.begin(), closeEdge.end(), Cmp);
		Node node = closeEdge.back();
		closeEdge.pop_back();
		min = node.weight;
		index = node.index;
		if(visited[index])	continue;
		visited[index] = true;
		sum = sum + min;
		count++;
		for(int i = 0; i < data[index].size(); i++){
			if(!visited[data[index][i].index]){
				closeEdge.push_back(data[index][i]);
				push_heap(closeEdge.begin(), closeEdge.end(), Cmp);
			}
		}
	}
	return sum;
}


int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int vecnum, arcnum;
	scanf("%d%d", &vecnum, &arcnum);
	if(vecnum <= 0 || arcnum <= 0 || vecnum > arcnum + 1)	return 0;
	int s, e, w, i = 0;
	vector<vector<Node> > data(vecnum, vector<Node>());
	for(i = 0; i < arcnum; i++){
		//cin>>s>>e>>w;
		scanf("%d%d%d", &s, &e, &w);
		s--;
		e--;
		data[s].push_back(Node(e, w));
		data[e].push_back(Node(s, w));
	}
	int ret = getMinSpanningTree(data);
	cout<<ret<<endl;
	return 0;
}
