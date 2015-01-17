#include <iostream>
#include <string>

using namespace std;

class Solution {
private:
	int findPos(string &str, char c, int s, int e){
		for(int i = s; i <= e; i++){
			if(str[i] == c)	return i;
		}
		return -1;
	}

public:
	void construct(string &pre, string &in, string &post, int se, int sn, int st, int len){
		if(len <= 0)	return;
		post[st + len - 1] = pre[se];
		if(len == 1){
			return;
		}
		char root = pre[se];
		int split = findPos(in, root, sn, sn + len - 1);
		construct(pre, in, post, se + 1, sn, st, split - sn);
		construct(pre, in, post, se + 1 + split - sn, split + 1, st + split - sn, len - 1 - split + sn);
	}
};

int main(int argc, char** argv)
{
	Solution sl;
	string pre, in;
	cin>>pre;
	cin>>in;
	int n = pre.length();
	string post(n, ' ');
	sl.construct(pre, in , post, 0, 0, 0, n);
	cout<<post<<endl;
	return 0;
}
