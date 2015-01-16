#include <iostream>
#include <climits>
#include <cstdio>
#include <vector>
#include <sys/time.h>
#include <algorithm>

using namespace std;

int father[100001];

struct Node{
	int w;
	int s;
	int e;
};

Node table[1000001];

inline int root(int x){
	return x == father[x]? x : root(father[x]);
}

inline bool join(int x, int y){
	if(root(x) == root(y))	return false;
	else{
		father[root(x)] = root(y);
		return true;
	}
}

int getMinSpanningTree(int vecnum, int arcnum){
	int count = 0;
	int s, e;
	int sum = 0;
	for(int i = 0; i < arcnum && count < vecnum; i++){
		s = table[i].s;
		e = table[i].e;
		if(join(s, e))
			sum = sum + table[i].w;
	}
	return sum;
}

class Cmp{
public:
	bool operator()(Node a, Node b){
		return a.w < b.w;
	}
};

int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int vecnum, arcnum;
	cin>>vecnum>>arcnum;
	if(vecnum <= 0 || arcnum <= 0 || vecnum > arcnum + 1)	return 0;
	for(int i = 0; i < vecnum; i++){
		father[i] = i;
	}
	int s, e, w;
	int count = 0;
	for(int i = 0; i < arcnum; i++, count++){
		//cin>>s>>e>>w;
		scanf("%d%d%d", &s, &e, &w);
		s--;
		e--;
		table[count].w = w; 
		table[count].s = s; 
		table[count].e = e; 
	}
	sort(table, table + count, Cmp());
	#ifdef DEBUG
	struct timeval start, end;
	gettimeofday(&start, NULL );
	#endif
	int ret = getMinSpanningTree(vecnum, arcnum);
	cout<<ret<<endl;
	#ifdef DEBUG
	gettimeofday( &end, NULL );
	double timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec; 
	cout<<timeuse/1000000<<endl;
	#endif
	return 0;
}
