#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;


class Solution {
private:
	void genMark(vector<vector<int> > &map, vector<vector<int> > &mark, int id, int &count){
		mark[id][0] = count++;
		for(int i = 0; i < map[id].size(); i++){
			if(mark[map[id][i]][0] == -1){
				genMark(map, mark, map[id][i], count);
			}
		}
		mark[id][1] = count++;
	}

public:
	bool isExistPath(vector<vector<int> > &map, vector<int> &trace){
		int n = map.size();
		vector<vector<int> > mark(n, vector<int>(2, -1));
		int c = 0;
		genMark(map, mark, 0, c);
		int m = trace.size();
		bool in = true;
		for(int i = 0; i < m - 1; i++){
			int count = 1;
			bool tmp;
			if(mark[trace[i]][0] < mark[trace[i+1]][0] && mark[trace[i]][1] > mark[trace[i+1]][1])
				tmp = true;
			else
				tmp = false;
			if(tmp != in){
				count++;
				in = tmp;
			}
			for(int j = i + 2; j < m; j++){
				if(mark[trace[i]][0] < mark[trace[j]][0] && mark[trace[i]][1] > mark[trace[j]][1])
					tmp = true;
				else
					tmp = false;
				if(tmp != in){
					count++;
					in = tmp;
				}
				if(count == 3)
					return false;
			}
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
