#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;


class Solution {
private:
	bool dfs(vector<vector<int> > &map, vector<int> &mark, vector<bool> &sign, int start, int end, bool &ok){
		if(mark[start] <= -1){
			ok = false;
			return false;
		}
		sign[start] = true;
		mark[start]--;
		if(start == end)	return true;
		for(int i = 0; i < map[start].size(); i++){
			if(!sign[map[start][i]] && mark[map[start][i]] > 0){
				if(dfs(map, mark, sign, map[start][i], end, ok)){
					return true;
				}
			}
		}
		mark[start]++;
		return false;
	}
public:
	bool isExistPath(vector<vector<int> > &map, vector<int> &trace){
		int n = map.size();
		vector<int> mark(n, 2);
		int m = trace.size();
		vector<bool> sign(n, false);
		bool ok = true;
		dfs(map, mark, sign,  0, trace[0], ok);
		for(int i = 0; i < m - 1; i++){
			if(mark[trace[i+1]] != 2 || !ok)	return false;
			vector<bool> sign(n, false);
			if(!dfs(map, mark, sign, trace[i], trace[i+1], ok))	return false;
		}
		return true;
	}
};

int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	Solution sl;
	int T;
	cin>>T;
	for(int i = 0; i < T; i++){
		int n;
		cin>>n;
		vector<vector<int> > map(n, vector<int>()); // 邻接表
		for(int j = 0; j < n - 1; j++){
			int p, q;
			cin>>p>>q;
			map[p-1].push_back(q-1);
			map[q-1].push_back(p-1);
		}
		int m;
		cin>>m;
		vector<int> trace(m, 0);
		for(int j = 0; j < m; j++){
			int pos;
			cin>>pos;
			trace[j] = pos - 1;
		}
		bool ret = sl.isExistPath(map, trace);
		if(ret)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}

	return 0;

}
