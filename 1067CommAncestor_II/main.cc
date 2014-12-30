#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>

using namespace std;

map<string, int> family;

struct TNode{
	string str;
	int parent;
	int color;
	vector<int> sons;
	vector<vector<int> > querys;
	TNode(string s = "", int p = -1):str(s),parent(p),color(0){}
};

vector<TNode> tree;
vector<vector<int> > querys;

void dfs(int pos){
	for(int i = 0; i < tree[pos].querys.size(); i++){
		int id = tree[pos].querys[i][0];
		if(querys[id][2] != -1) continue;
		int other = tree[pos].querys[i][1];
		if(tree[other].color != 0){
			if(tree[other].color == 2){
				// 向上搜寻
				while(other != 0){
					if(tree[other].color == 1)
							break;
					other = tree[other].parent;	
				}
			}
			querys[id][2] = other;
		}
	}
	tree[pos].color = 1; // gray
	for(int i = 0; i < tree[pos].sons.size(); i++){
		dfs(tree[pos].sons[i]);
	}
	tree[pos].color = 2;  // black
}

void MakeQuery(){
	dfs(0);
}


int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int n;
	cin>>n;
	string f, s;
	char t1[100], t2[100];
	int count = 0;
	for(int i = 0; i < n; i++){
		t1[0] = t2[1] = '\0';
		scanf("%s %s", t1, t2);
		f = t1;
		s = t2;
		//cin>>f>>s;
		if(family.count(f) == 0){
			TNode tmp(f, -1);
			tree.push_back(tmp);
			family[f] = count++;
		}
		if(family.count(s) == 0){
			TNode tmp(s, -1);
			tree.push_back(tmp);
			family[s] = count++;
		}
		tree[family[f]].sons.push_back(family[s]);
		tree[family[s]].parent = family[f];
	}
	int m;
	cin>>m;
	string n1, n2;
	int c = 0;
	vector<int> qtmp(3, -1);
	vector<int> ttmp(2, 0);
	for(int i = 0; i < m; i++){
		t1[0] = t2[1] = '\0';
		scanf("%s %s", t1, t2);
		n1 = t1;
		n2 = t2;
		//cin>>n1>>n2;
		if(n1 == n2){
			if(family.count(n1) != 0){
				qtmp[0] = family[n1];
				qtmp[1] = family[n2];
				querys.push_back(qtmp);
				querys[c][2] = family[n1];
			}
			else{
				TNode Ttmp(n1, -1);
				tree.push_back(Ttmp);
				qtmp[0] = family[n1];
				qtmp[1] = family[n2];
				querys.push_back(qtmp);
				querys[c][2] = tree.size() - 1;
			}
			c++;
			continue;
		}
		if(family.count(n1) == 0 || family.count(n2) == 0){
			querys.push_back(qtmp);
			continue;
		}
		int fn1 = family[n1];
		int fn2 = family[n2];
		qtmp[0] = fn1;
		qtmp[1] = fn2;
		querys.push_back(qtmp);
		ttmp[0] = c;
		ttmp[1] = fn2;
		tree[fn1].querys.push_back(ttmp);
		ttmp[1] = fn1;
		tree[fn2].querys.push_back(ttmp);
		c++;
	}

	MakeQuery();

	for(int i = 0; i < c; i++){
		if(querys[i][2] == -1){
			printf("-1\n");
		}
		else{
			printf("%s\n", tree[querys[i][2]].str.c_str());
			//cout<<tree[querys[i][2]].str<<endl;
		}
	}

	/*
	cout<<"pos | string | parent | sons"<<endl;
	for(int i = 0; i < count; i++){
		cout<<i<<" | "<<tree[i].str<<" | "<<tree[i].parent<<" | ";
		for(int j = 0; j < tree[i].sons.size(); j++)
			cout<<tree[i].sons[j]<<" ";
		cout<<endl;
	}
	*/

	return 0;
}
