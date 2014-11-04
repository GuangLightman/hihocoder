#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode{
	int num;
	char val;
	bool black;
	vector<TreeNode*> son;
	TreeNode(char val):val(val), num(0), black(false), son(vector<TreeNode*>(26, NULL)){}
};

class Tree {

public:
	Tree():root(new TreeNode(' ')){}
	~Tree(){}
	void insert(string &str){
		int len = str.length();
		if(len == 0)	return;
		insert_rec(str, root, 0, len);
	}

	int getNum(string &str){
		TreeNode *pos = root;
		for(int i = 0; i < str.length(); i++){
			if(pos->son[str[i] - 'a']){
				pos = pos->son[str[i] - 'a'];
			}else{
				return 0;
			}
		}
		return pos->num;
	}

private:

	void insert_rec(string &str, TreeNode *root, int pos, int size){
		if(pos == size){
			root->black = true;
			root->num++;
			return;
		}
		int index = str[pos] - 'a';
		root->num++;
		if(root->son[index]){
			insert_rec(str, root->son[index], pos + 1, size);	
		}else{
			root->son[index] = new TreeNode(str[pos]);
			insert_rec(str, root->son[index], pos + 1, size);	
		}
	}

private:
	TreeNode *root;	
};

int main(int argc, char** argv)
{
	Tree t;

	int count;
	string str;
	cin>>count;
	while(count){
		cin>>str;
		t.insert(str);
		count--;
	}	
	cin>>count;
	while(count){
		cin>>str;
		cout<<t.getNum(str)<<endl;
		count--;
	}	

	return 0;

}
