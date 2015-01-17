#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;



int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int N;
	scanf("%d\n", &N);

	vector<int> data;
	make_heap(data.begin(), data.end());
	char type;
	int w;
	while(N-- > 0){
		scanf("%c ", &type);
		if(type == 'A'){
			scanf("%d\n", &w);
			data.push_back(w);
			push_heap(data.begin(), data.end());
		}else{
			pop_heap(data.begin(), data.end());
			w = data.back();
			printf("%d\n", w);
			data.pop_back();
		}
	}
	
	return 0;

}
