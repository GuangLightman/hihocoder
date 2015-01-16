#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
struct node
{
	int i, j, len;
};
const int M = 1000010;
const int N = 100010;
node e[M];
int p[N];
int son[N];
int m, n;
bool cmp(const node &e1, const node &e2)
{
	return e1.len < e2.len;
};
int unionsearch(int x)
{
	if(x != p[x])
		p[x] = unionsearch(p[x]);
	return p[x];
};
bool join(int x, int y)
{
	int root1 = unionsearch(x);
	int root2 = unionsearch(y);
	if(root1 == root2)
		return false;
	else if(son[root1] < son[root2])
	{
		p[root1] = root2;
		son[root2] += son[root1];
	}
	else
	{
		p[root2] = root1;
		son[root1] += son[root2];
	}
	return true;
};
int prime()
{
	sort(e + 1, e + m + 1, cmp);
	int count = 1;
	long result = 0;
	for(int i = 1; i <= m; i++)
	{
		if(join(e[i].i, e[i].j))
		{
			result += e[i].len;
			if((++count) == n)
			    return result;
		}
	}
	return result;
};

int main()
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		son[i] = 1;
		p[i] = i;
	}
	for(int i = 1; i <= m; i++)
		scanf("%d %d %d", &e[i].i, &e[i].j, &e[i].len);
	printf("%d\n", prime());
	return 0;
}
