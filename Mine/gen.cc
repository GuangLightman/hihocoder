#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

const int len = 100000;

int main(){
	srand (time(NULL));
	vector<bool> mine(len ,false);
	for(int i = 0; i < len; i++){
		mine[i] = (1 == (rand() % 2));
	}
	vector<int> sign(len, 0);
	sign[0] = mine[0]? 1 : 0;
	sign[0] = mine[1]? sign[0] + 1: sign[0];
	sign[len - 1] = mine[len - 1]? 1 : 0;
	sign[len - 1] = mine[len - 2]? sign[len - 1] + 1: sign[len - 1];
	for(int i = 1; i < len - 1; i++){
		if(mine[i-1])	sign[i]++;
		if(mine[i])	sign[i]++;
		if(mine[i+1])	sign[i]++;
	}
	freopen("input", "w", stdout);
	cout<<1<<endl;
	cout<<len<<endl;
	for(int i = 0; i < len - 1; i++)
		cout<<sign[i]<<" ";
	cout<<sign[len-1]<<endl;
	fclose(stdout);


	freopen("check", "w", stdout);
	int nums = 0;
	for(int i = 0; i < mine.size(); i++){
		if(mine[i]) nums++;
	}
	cout<<nums;
	for(int i = 0; i < mine.size(); i++){
		if(mine[i]) cout<<" "<<i+1;
	}
	cout<<endl<<(mine.size() - nums);
	for(int i = 0; i < mine.size(); i++){
		if(!mine[i]) cout<<" "<<i+1;
	}
	cout<<endl;
	fclose(stdout);
}
