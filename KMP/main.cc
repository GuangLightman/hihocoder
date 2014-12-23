#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;


class Solution {

public:

    int KMP(string &target, string &mode) {
		int lm = mode.length();
		int lt = target.length();
		if(lm*lt == 0)	return 0;
		vector<int> part(lm, 0);

		// init for the part array.
		// this will be TLE.
		for(int i = 1; i < lm; i++){
			int pre = part[i-1];
			if(mode[i] == mode[pre]){
				part[i] = pre+1;
				continue;
			}
			int pos = i - pre;
			while(pos <= i){
				int k, p;
				int len = i - pos + 1;
				for(k = 0, p = pos; k < len; k++, p++){
					if(mode[k] != mode[p]){
						pos = pos + k + 1 - part[k-1];
						break;
					}
				}
				if(k == len){
					part[i] = k;
					break;
				}
			}
		}

		vector<int> next(lm, -1);
		for(int i = 1; i < lm; i++){
			#ifdef DEBUG
			cout<<part[i]<<endl;
			#endif
			next[i] = part[i-1];
		}

		// search the mode str by the next array.
		int count = 0;
		for(int pos = 0; pos < lt - lm + 1;){
			int i, j;
			for(j = 0, i = pos; j < lm; i++, j++){
				if(mode[j] != target[i]){
					if(next[j] != -1){
						j = next[j];
						continue;
					}else{
						break;
					}
				}	
			}
			if(j == lm){
				pos = pos + lm - part[j-1];
				count++;
			}else{
				pos++;
			}
		}
		return count;
    }

};

int main(int argc, char** argv)
{
	#ifdef DEBUG
	//freopen("input","r",stdin);
	#endif
	Solution sl;
	string target;		
	string mode;		
	int count;
	cin>>count;
	while(count){
		cin>>mode;
		cin>>target;
   		cout<<sl.KMP(target, mode)<<endl;
		count--;
	}

	return 0;

}
