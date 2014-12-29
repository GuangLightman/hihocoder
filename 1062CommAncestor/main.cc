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
	vector<int> sons;
	TNode(string s = "", int p = -1):str(s),parent(p){}
};

vector<TNode> tree;

int getHeight(int pos){
	int height = 0;
	while(pos != 0){
		pos = tree[pos].parent;
		height++;
	}
	return height;
}

int getComm(string &n1, string &n2){
	if(family.count(n1) == 0 || family.count(n2) == 0)	return -1;
	int pos1 = family[n1];
	int pos2 = family[n2];
	int h1 = getHeight(pos1);
	int h2 = getHeight(pos2);
	if(h1 < h2){
		int tmp = h1;
		h1 = h2;
		h2 = tmp;
		tmp = pos1;
		pos1 = pos2;
		pos2 = tmp;
	}
	int gap = h1 - h2;
	while(gap-- > 0){
		pos1 = tree[pos1].parent;
	}
	while(h2-- > 0){
		if(pos1 == pos2)	return pos1;
		else{
			pos1 = tree[pos1].parent;
			pos2 = tree[pos2].parent;
		}
	}
	return -1;
}


int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int n;
	cin>>n;
	string f, s;
	TNode tmp;
	tree.push_back(tmp); // 虚拟根节点，防止森林
	family[""] = 0;
	int count = 1;
	for(int i = 0; i < n; i++){
		cin>>f>>s;
		if(family.count(f) == 0){
			TNode tmp(f, 0);
			tree.push_back(tmp);
			family[f] = count++;
		}
		if(family.count(s) == 0){
			TNode tmp(s,0);
			tree.push_back(tmp);
			family[s] = count++;
		}
		tree[family[f]].sons.push_back(family[s]);
		tree[family[s]].parent = family[f];
	}
	int m;
	cin>>m;
	string n1, n2;
	for(int i = 0; i < m; i++){
		cin>>n1>>n2;
		if(n1 == n2){
			cout<<n1<<endl;
			continue;
		}
		int ret = getComm(n1, n2);
		if(ret == -1) cout<<"-1"<<endl;
		else cout<<tree[ret].str<<endl;
	}

	cout<<"pos | string | parent | sons"<<endl;
	for(int i = 0; i < count; i++){
		cout<<i<<" | "<<tree[i].str<<" | "<<tree[i].parent<<" | ";
		for(int j = 0; j < tree[i].sons.size(); j++)
			cout<<tree[i].sons[j]<<" ";
		cout<<endl;
	}

	return 0;
}
