#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;


class Solution {
private:
	void genMark(vector<vector<int> > &map, vector<vector<int> > &mark, int id, int &count){
		mark[id].push_back(count++);
		for(int i = 0; i < map[id].size(); i++){
			if(mark[map[id][i]].size() == 0){
				genMark(map, mark, map[id][i], count);
				mark[id].push_back(count++);
			}
		}
	}

	bool isSub(vector<int> &root, vector<int> &node, int &index){
		int cur = node[0];
		int size = root.size();
		if(cur < root[0] || cur > root[size - 1])	return false;
		for(int i = 1; i < root.size(); i++){
			if(cur < root[i])	return i - 1;
		}
	}

public:
	bool isExistPath(vector<vector<int> > &map, vector<int> &trace){
		int n = map.size();
		vector<vector<int> > mark(n, vector<int>());
		int c = 0;
		genMark(map, mark, 0, c);
		int m = trace.size();
		bool in = true;
		int index = 0;
		for(int i = 0; i < m - 1; i++){
			int count = 1;
			bool is_sub;
			int last_index;
			int num = mark[trace[i]].size();
			vector<bool> lr(num, false);



			for(int j = i + 1; j < m; j++){
				is_sub = isSub( mark[trace[i]], mark[trace[j]], index);
				if(is_sub){
					if(lr[index] && last_index != index){
						return false;
					}else{
						lr[index] = true;
						last_index = index;
					}
				}
				if(is_sub != in){
					count++;
					in = is_sub;
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
