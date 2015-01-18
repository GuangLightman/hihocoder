#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int getLongestRep(vector<int> &data){
	int n = data.size();
	int len , i, j, p;
	int s, e;
	for(len = n; len > 0; len--){
		for(i = 0; i < n + 1 - len; i++){
			s = i, e = i + len - 1;
			for(int j = i+len; j < n + 1 - len; j++){
				for(p = 0; p < len; p++){
					if(data[i+p] != data[j+p])	break;
				}
				if(p == len){
					return len;
				}
			}
		}
	}
}


int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int n;
	cin>>n;
	vector<int> data(n, 0);
	int count = 0;
	while(count < n){
		cin>>data[count];
		count++;
	}
	int ret = getLongestRep(data);
	cout<<ret<<endl;

	return 0;
}
