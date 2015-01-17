#include <iostream>
#include <string>

using namespace std;

int longestPalindromeSubstr(string &str){
	int n = str.length();
	
}

int main(int argc, char** argv)
{
	int n = 0;
	cin>>n;
	for(int i = 0; i < n; i++){
		string str;
		cin>>str;
		cout<<longestPalindromeSubstr(str)<<endl;
	}

	return 0;

}
