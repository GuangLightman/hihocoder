#include <iostream>
#include <string>

using namespace std;


class Solution {

public:

	int sumAB(int A, int B){
		return A + B;
    }

};

int main(int argc, char** argv)
{
	Solution sl;
	int A, B;
	while(cin>>A>>B){
		cout<<sl.sumAB(A, B)<<endl;
	}

	return 0;

}
