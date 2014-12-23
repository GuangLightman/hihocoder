#include <iostream>
#include <string>

using namespace std;


class Solution {

public:

	int findSectionK(vector<int> A, int k, int n){
		
    }

};

int main(int argc, char** argv)
{
	Solution sl;
	int n, k;
	cin>>n>>k;
	vector<int> A(n, 0);
	for(int i = 0; i < n; i++)
		cin>>A[i];

	cout<<findSectionK(A, k, n)<<endl;

	return 0;

}
