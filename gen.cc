#include <iostream>
#include <cstdlib>

#define random(x) (rand()%x)

using namespace std;

int main(){
	int v = 10000, e = 100000;
	cout<<v<<" "<<e<<endl;
	int a, b, w;
	for(int i = 0; i < e; i++){
		a = random(v);
		b = random(v);
		if(b == a)	b = (a + 1) % v;
		w = random(1000);
		cout<<a<<" "<<b<<" "<<w<<endl;
	}
}
