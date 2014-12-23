#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

struct STNode{
	int start;
	int end;
	int val;
	STNode *left;
	STNode *right;
	STNode(int start = 0, int end = 0, int val = 0):start(start), end(end), val(val), left(NULL), right(NULL){}
};

class Solution {

public:
	Solution(int n, vector<int> &weight) : root(NULL){
		root = init(0, n - 1, weight);
	}

	STNode* init(int start, int end, vector<int> &weight){
		if(start > end)	return NULL;
		if(start == end) return (new STNode(start, end, weight[start]));
		STNode *node = new STNode(start, end);
		int mid = (start + end) / 2;
		node->left = init(start, mid, weight);
		node->right = init(mid+1, end, weight);
		node->val = min(node->left->val, node->right->val);
		return node;
	}

	void modify(int pos, int w){
		modify(pos - 1, w, root);
	}

	void modify(int pos, int w, STNode *node){
		if(!node)	return;
		if(node->start == node->end){
			node->val = w;
			return;
		}
		if(pos <= node->left->end)
			modify(pos, w, node->left);
		else
			modify(pos, w, node->right);
		node->val = min(node->left->val, node->right->val);
	}

	int query(int l, int r){
		return query(l - 1, r - 1, root);
	}

	int query(int l, int r, STNode *node){
		if(!node)	return 0;
		if(l == node->start && r == node->end)
			return node->val;
		if(l >= node->start && r <= node->left->end)
			return query(l, r, node->left);
		if(l >= node->right->start && r <= node->end)
			return query(l, r, node->right);
		return min(query(l, node->left->end, node->left), query(node->right->start, r, node->right));
	}
	
private:
	STNode *root;
	
};

int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input","r",stdin);
	#endif
	int n;
	cin>>n;
	vector<int> weight(n, 0);
	for(int i = 0; i < n; i++)
		cin>>weight[i];
	Solution sl(n, weight);
	int times;
	cin>>times;
	for(int i = 0; i < times; i++){
		int type;
		cin>>type;
		if(type){
			int pos, w;
			cin>>pos>>w;
			sl.modify(pos, w);
		}else{
			int l, r;
			cin>>l>>r;
			cout<<sl.query(l,r)<<endl;
		}
	}

	return 0;

}
