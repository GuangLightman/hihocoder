#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

bool dfs(vector<int> &sign, vector<int> &mine, int cur, bool isFirst = false){
	if(cur == sign.size() - 1){
		switch(sign[cur]){
			case 0:	if(mine[cur-1] == 1 || mine[cur] == 1) 
						return false; 
					break;
			case 1:	if((mine[cur-1] == 1 && mine[cur] == 1) 
						|| (mine[cur-1] == -1 && mine[cur] == -1)) 
						return false;
					break;
			case 2:	if(!((mine[cur-1] == 1) && (mine[cur] == 1))) 
						return false;
					break;
			case 3:	return false;
			default:;
		}
		return true;
	}
	if(isFirst){
		switch(sign[cur]){
			case 0:	mine[cur] = mine[cur+1] = -1; return dfs(sign, mine, cur+1);
			case 1:	{
						bool first = false, second = false;
						vector<int> tmp1 = mine, tmp2 = mine;
						tmp1[cur] = 1;
						tmp1[cur+1] = -1;
						first = dfs(sign, tmp1, cur+1);
						tmp2[cur] = -1;
						tmp2[cur+1] = 1;
						second = dfs(sign, tmp2, cur+1);
						//cout<<first<<" "<<second<<endl;
						if(first && second){
							for(int i = cur; i < mine.size(); i++){
								if(tmp1[i] == 1 && tmp2[i] == 1)	mine[i] = 1;
								if(tmp1[i] == -1 && tmp2[i] == -1)	mine[i] = -1;
							}
						}else{
							mine = first? tmp1 : tmp2;
						}
						return first || second;
					}
					break;
			case 2:	mine[cur] = mine[cur+1] = 1;
					return dfs(sign, mine, cur+1);
			case 3:	return false;
			default:;
		}
	}else{
		switch(sign[cur]){
			case 0:	{ 
						if(mine[cur-1] == 1 || mine[cur] == 1) 
							return false;
						mine[cur+1] = -1;
						return dfs(sign, mine, cur+1);
					}
					break;
			case 1:	{
						if(mine[cur-1] == 1 && mine[cur] == 1)
							return false;
						if(mine[cur-1] == -1 && mine[cur] == -1){
							mine[cur+1] = 1;
						}else{
							mine[cur+1] = -1;
						}
						return dfs(sign, mine, cur+1);
					}
					break;
			case 2:	{
						if(mine[cur-1] == -1 && mine[cur] == -1)  
							return false;
						if(!(mine[cur-1] == 1 && mine[cur] == 1)){
							mine[cur+1] = 1;
						}else{
							mine[cur+1] = -1;
						}
						return dfs(sign, mine, cur+1);
					}
					break;
			case 3:	{
						if(!(mine[cur-1] == 1 && mine[cur] == 1))
							return false;
						mine[cur+1] = 1;
						return dfs(sign, mine, cur+1);
					}
			default:;
		}
		return true;
	}
}

void findMine(vector<int> &sign){
	vector<int> mine(sign.size(), 0);
	if(sign.size() == 1){
		if(sign[0] == 1)	mine[0] = 1;  // 1 is must have , -1 is must not have
		else	mine[0] = -1;
	}else{
		dfs(sign, mine, 0, true);
	}
	int has = 0, no = 0;
	for(int i = 0; i < mine.size(); i++){
		if(mine[i] == 1) has++;
		if(mine[i] == -1) no++;
	}
	cout<<has;
	for(int i = 0; i < mine.size(); i++){
		if(mine[i] == 1) cout<<" "<<i+1;
	}
	cout<<endl<<no;
	for(int i = 0; i < mine.size(); i++){
		if(mine[i] == -1) cout<<" "<<i+1;
	}
	cout<<endl;
}


int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif

	int times;
	cin>>times;
	while(times-- > 0){
		int nums, count = 0;
		cin>>nums;
		vector<int> sign(nums, 0);
		while(count < nums){
			cin>>sign[count++];
		}
		findMine(sign);
	}

	return 0;
}
