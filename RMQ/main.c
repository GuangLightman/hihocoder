#include <stdio.h>
#include <malloc.h>

typedef struct STNode{
	int start;
	int end;
	int val;
	struct STNode *left;
	struct STNode *right;
}STNode;

int min(int a, int b){
	return a < b? a : b;
}

STNode* init(int start, int end, int* weight){
	if(start > end)	return NULL;
	STNode *node =  (STNode*)malloc(1*sizeof(STNode));
	node->start = start;
	node->end = end;
	node->left = node->right = NULL;
	node->val = weight[start];
	if(start == end) return node;
	int mid = (start + end) / 2;
	node->left = init(start, mid, weight);
	node->right = init(mid+1, end, weight);
	node->val = min(node->left->val, node->right->val);
	return node;
}

void modify(int pos, int w, STNode *node){
	if(!node)	return;
	if(node->start == node->end){
		node->val = w;
		return;
	}
	if(pos <= node->left->end)
		modify(pos, w, node->left);
	else
		modify(pos, w, node->right);
	node->val = min(node->left->val, node->right->val);
}

int query(int l, int r, STNode *node){
	if(!node)	return 0;
	if(l == node->start && r == node->end)
		return node->val;
	if(l >= node->start && r <= node->left->end)
		return query(l, r, node->left);
	if(l >= node->right->start && r <= node->end)
		return query(l, r, node->right);
	return min(query(l, node->left->end, node->left), query(node->right->start, r, node->right));
}
	

int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input","r",stdin);
	#endif
	int n;
	int *weight;
	int i = 0;
	int times;
	STNode *root;
	scanf("%d",&n);
	weight = (int*)malloc(n*sizeof(int));
	for(i = 0; i < n; i++)
		scanf("%d",&weight[i]);
	root = init(0, n - 1, weight);
	scanf("%d",&times);
	for(i = 0; i < times; i++){
		int type;
		scanf("%d",&type);
		if(type){
			int pos, w;
			scanf("%d%d", &pos, &w);
			modify(pos - 1, w, root);
		}else{
			int l, r;
			scanf("%d%d",&l,&r);
			printf("%d\n", query(l - 1, r - 1, root));
		}
	}
	free(weight);
	return 0;

}
