#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {

public:

    int KMP(string &target, string &mode) {
		int lm = mode.length();
		int lt = target.length();
		vector<int> part(lm, 0);

		// init for the part array.
		for(int i = 1; i < lm; i++){
			int pre = part[i-1];
			if(mode[i] == mode[pre]){
				part[i] = pre + 1;
			}else{
				int j, k;
				for(j = pre; j > 0; j--){
					for(k = 0; k < j; k++){
						if(mode[k] != mode[i-j+1+k])
							break;
					}
					if(k == j){
						part[i] = j;
						break;
					}
				}
			}
		}

		vector<int> next(lm, 0);
		for(int i = 0; i < lm; i++){
			next[i] = i + 1 - part[i];
		}

		int count = 0;
		for(int pos = 0; pos < lt;){
			int i, j;
			for(j = 0, i = pos; j < lm; i++, j++){
				if(mode[j] != target[i]){
					pos = pos + next[j];
					break;
				}	
			}
			if(j == lm){
				count++;
				pos = pos + next[j-1];
			}
		}
		return count;
    }

};

int main(int argc, char** argv)
{
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
