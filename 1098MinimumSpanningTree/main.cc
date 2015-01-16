#include <iostream>
#include <climits>
#include <cstdio>
#include <map>
#include <set>
#include <vector>

using namespace std;

int root(int x, vector<int> &father){
	return x == father[x]? x : root(father[x], father);
}

bool join(int x, int y, vector<int> &father){
	if(root(x, father) == root(y, father))	return false;
	else{
		father[root(x, father)] = root(y, father);
		return true;
	}
}

int getMinSpanningTree(multimap<int, pair<int, int> > &data, vector<int> &father, int vecnum){
	int count = 0;
	int s, e;
	int sum = 0;
	for(multimap<int, pair<int, int> >::iterator iter = data.begin(); 
		iter != data.end() && count < vecnum; iter++){
		s = iter->second.first;
		e = iter->second.second;
		if(join(s, e, father))
			sum = sum + iter->first;
	}
	return sum;
}


int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int vecnum, arcnum;
	cin>>vecnum>>arcnum;
	if(vecnum <= 0 || arcnum <= 0 || vecnum > arcnum + 1)	return 0;
	multimap<int, pair<int, int> > table;
	vector<int> father(vecnum, -1);
	for(int i = 0; i < vecnum; i++){
		father[i] = i;
	}
	int s, e, w;
	for(int i = 0; i < arcnum; i++){
		cin>>s>>e>>w;
		s--;
		e--;
		table.insert(make_pair(w, make_pair(s, e)));
	}
	int ret = getMinSpanningTree(table, father, vecnum);
	cout<<ret<<endl;
	return 0;
}
