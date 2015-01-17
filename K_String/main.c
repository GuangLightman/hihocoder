#include <stdio.h>
#include <malloc.h>

typedef struct STNode{
	int start;
	int end;
	int val;
	int *list;
	int count;
	struct STNode *left;
	struct STNode *right;
}STNode;

void merge(STNode *node, int *left, int *right, int l, int r){
	int i = 0, j = 0, count = 0;
	node->val = 0;
	while(i < l && j < r){
		if(left[i] == right[i]){
			i++;
			j++;
		}else{
			if(left[i] < right[j])	i++;
			else j++;
		}
		count++;
	}
	if(i < l){
		count = count + l - i;
	}
	if(j < r){
		count = count + r - j;
	}
	node->list = (int*)malloc(count*sizeof(int));
	node->count = count;
	i = j = count = 0;
	while(i < l && j < r){
		node->list[count] = left[i];
		if(left[i] == right[i]){
			i++;
			j++;
		}else{
			if(left[i] < right[j])	i++;
			else{
				node->list[count] = left[j];
				node->val = node->val + left[i];
			 	j++;
			}
		}
		node->val = node->val + node->list[count];
		count++;
	}
	if(i < l){
		int p = i;
		while(p < l){
			node->list[count] = left[p];
			node->val = node->val + node->list[count];
			count++;
			p++;
		}
	}
	if(j < r){
		int p = j;
		while(p < r){
			node->list[count] = right[p];
			node->val = node->val + node->list[count];
			count++;
			p++;
		}
	}
}

STNode* init(int start, int end, int* weight){
	if(start > end)	return NULL;
	STNode *node =  (STNode*)malloc(1*sizeof(STNode));
	node->start = start;
	node->end = end;
	node->left = node->right = NULL;
	node->val = weight[start];
	if(start == end){
		node->list = (int*)malloc(1*sizeof(int));
		node->list[0]= weight[start];
		node->count = 1;
		return node;
	}
	int mid = (start + end) / 2;
	node->left = init(start, mid, weight);
	node->right = init(mid+1, end, weight);
	merge(node, node->left->list, node->right->list, node->left->count, node->right->count);
	return node;
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
