#include <stdio.h>
#include <malloc.h>

typedef struct STNode{
	int start;
	int end;
	int val;
	int lazy;
	int is_lazy;
	struct STNode *left;
	struct STNode *right;
}STNode;

STNode* init(int start, int end, int* price){
	if(start > end)	return NULL;
	STNode *node =  (STNode*)malloc(1*sizeof(STNode));
	node->start = start;
	node->end = end;
	node->left = node->right = NULL;
	node->val = price[start];
	node->is_lazy = 0;
	if(start == end) return node;
	int mid = (start + end) / 2;
	node->left = init(start, mid, price);
	node->right = init(mid+1, end, price);
	node->val = node->left->val + node->right->val;
	return node;
}

void modify(int s, int e, int p, STNode *node){
	if(!node)	return;
	if(node->start == s && node->end == e){
		node->val = p * (e - s + 1);
		node->lazy = p;
		node->is_lazy = 1;
		return;
	}
	if(node->is_lazy){
		node->is_lazy = 0;
		node->left->is_lazy = 1;
		node->right->is_lazy = 1;
		node->left->lazy = node->lazy;
		node->right->lazy = node->lazy;
		node->left->val = node->lazy * (node->left->end - node->left->start + 1);
		node->right->val = node->lazy * (node->right->end - node->right->start + 1);
	}
	if(e <= node->left->end){
		modify(s, e, p, node->left);
		node->val = node->left->val + node->right->val;
		return;
	}
	if(s >= node->right->start){
		modify(s, e, p, node->right);
		node->val = node->left->val + node->right->val;
		return;
	}
	modify(s, node->left->end, p, node->left);
	modify(node->right->start, e, p, node->right);
	node->val = node->left->val + node->right->val;
}

int query(int l, int r, STNode *node){
	if(!node)	return 0;
	if(l == node->start && r == node->end)
		return node->val;
	if(node->is_lazy){
		node->is_lazy = 0;
		node->left->is_lazy = 1;
		node->right->is_lazy = 1;
		node->left->lazy = node->lazy;
		node->right->lazy = node->lazy;
		node->left->val = node->lazy * (node->left->end - node->left->start + 1);
		node->right->val = node->lazy * (node->right->end - node->right->start + 1);
	}
	if(l >= node->start && r <= node->left->end)
		return query(l, r, node->left);
	if(l >= node->right->start && r <= node->end)
		return query(l, r, node->right);
	return query(l, node->left->end, node->left) + query(node->right->start, r, node->right);
}
	

int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input","r",stdin);
	#endif
	int n = 1;
	int *price;
	int i = 0;
	int times;
	STNode *root;
	scanf("%d",&n);
	price = (int*)malloc(n*sizeof(int));
	for(i = 0; i < n; i++)
		scanf("%d",&price[i]);
	root = init(0, n - 1, price);
	scanf("%d",&times);
	for(i = 0; i < times; i++){
		int type;
		scanf("%d",&type);
		if(type){
			int s, e, p;
			scanf("%d%d%d", &s, &e, &p);
			modify(s - 1, e - 1, p, root);
		}else{
			int l, r;
			scanf("%d%d",&l,&r);
			printf("%d\n", query(l - 1, r - 1, root));
		}
	}
	free(price);
	return 0;

}
