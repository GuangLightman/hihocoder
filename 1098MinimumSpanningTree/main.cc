#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int father[100001];
int son[100001];

struct Node{
	int w;
	int s;
	int e;
};

Node table[1000001];

int root(int x){
	if(x != father[x])
		father[x] = root(father[x]);
	return father[x];
}

bool join(int x, int y){
	int rx = root(x);
	int ry = root(y);
	if(rx == ry)	return false;
	else{
		if(son[rx] < son[ry]){
			father[rx] = ry;
			son[ry] +=son[rx];
		}else{
			father[ry] = rx;
			son[rx] +=son[ry];
		}
		return true;
	}
}

int getMinSpanningTree(int vecnum, int arcnum){
	int count = 0;
	int sum = 0;
	for(int i = 0; i < arcnum && count < vecnum; i++){
		if(join(table[i].s, table[i].e)){
			sum = sum + table[i].w;
			count++;
		}
	}
	return sum;
}

bool Cmp(const Node& a, const Node& b){
	return a.w < b.w;
}

int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int vecnum, arcnum;
	//cin>>vecnum>>arcnum;
	scanf("%d%d", &vecnum, &arcnum);
	if(vecnum <= 0 || arcnum <= 0 || vecnum > arcnum + 1)	return 0;
	for(int i = 0; i < vecnum; i++){
		father[i] = i;
		son[i] = 0;
	}
	int s, e, w, i = 0;
	for(i = 0; i < arcnum; i++){
		//cin>>s>>e>>w;
		scanf("%d%d%d", &s, &e, &(table[i].w));
		s--;
		e--;
		table[i].s = s; 
		table[i].e = e; 
	}
	sort(table, table + i, Cmp);
	int ret = getMinSpanningTree(vecnum, arcnum);
	cout<<ret<<endl;
	return 0;
}
