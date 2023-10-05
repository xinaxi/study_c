//бинарное дерево, балансировка

#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

typedef struct _node {
	int value;
	struct _node *left;
	struct _node *right;
} node;

void tree_add(node **tree, int val) {
	node *root = *tree;
	if (!root) {
		root = malloc(sizeof(node));
		root->value = val;
		root->left = root->right = NULL;
		*tree = root;
		return;
	}
	if (val > root->value)
		tree_add(&(root->right), val);
	else
		if (val < root->value)
			tree_add(&(root->left), val);
	*tree = root;
	return;
}

node *tree_search(node *root, int val) {
	if (!root || root->value == val)
		return root;
	if (val > root->value)
		return tree_search(root->right, val);
	else
		return tree_search(root->left, val);
}

int tree_contains(node *root, int val) {
	return tree_search(root, val) != 0;
}

void tree_add_all(node **tree, node *root2) {
	node *root = *tree;
	if (!root2)
		return;
	tree_add(&root, root2->value);
	tree_add_all(&root, root2->left);
	tree_add_all(&root, root2->right);
	*tree = root;
}

void tree_free(node* root) {
	if (!root)
		return;
	tree_free(root->left);
	tree_free(root->right);
	free(root);
}

void tree_del(node **tree, int val) {
	node *root = *tree;
	if (!tree_contains(root, val))
		return;
	if (root->value == val) {
		tree_add_all(&(root->left), root->right);
		*tree = root->left;
		root->left = NULL;
		tree_free(root);
		return;
	}
	if (val > root->value)
		tree_del(&(root->right), val);
	else
		tree_del(&(root->left), val);
}

int dim(node *root) {
	if (!root)
		return 0;
	return dim(root->left) + dim(root->right) + 1;
}

void tree_to_arr(node *root, int *arr, int k0) {
	if (!root)
		return;
	else {
		int n = dim(root->left);
		arr[k0++] = root->value;
		if (n)
			tree_to_arr(root->left, arr, k0);
		k0 += n;
		if (root->right)
			tree_to_arr(root->right, arr, k0);
	}
}

void s_arr_to_tree(node **tree, int *arr, int k) {
	node *root = *tree;
	if (k < 1)
		return;
	if (k == 1)
		tree_add(&root, *arr);
	else {
		tree_add(&root, *(arr + k / 2));
		s_arr_to_tree(&(root->left), arr, k / 2);
		s_arr_to_tree(&(root->right), arr + k / 2 + 1, k - k / 2 - 1);
	}
	*tree = root;
}

void sort(int *a, int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[i]) {
				a[j] = a[j] + a[i];
				a[i] = a[j] - a[i];
				a[j] = a[j] - a[i];
			}
}

void balance(node **root) {
	node *tree = *root;
	int n = dim(tree);
	int *arr = malloc(n*sizeof(int));
	tree_to_arr(tree, arr, 0);
	tree_free(tree);
	tree = NULL;
	sort(arr, n);
	s_arr_to_tree(&tree, arr, n);
	free(arr);
	*root = tree;
}

void printArr(int *a, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int *genArr(int n) {
	int *a, m, f;
	a = malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		do {
			f = 0;
			m = rand() % 100 - 20;
			for (int j = 0; j < i; j++) {
				if (m == a[j])
					f = 1;
			}
		} while (f);
		a[i] = m;
	}
	return a;
}

void main() {
	int k = 6;
	int *arr = malloc(k * sizeof(int));
	node *tree = NULL;

	srand(time(0));
	arr = genArr(k);
	sort(arr, k);
	printArr(arr, k);

	s_arr_to_tree(&tree, arr, k);	
	tree_to_arr(tree, arr, 0);
	printArr(arr, k);

	balance(&tree);
	tree_to_arr(tree, arr, 0);
	printArr(arr, k);

	printf("\n%d\n\n", tree_contains(tree, arr[0]));

	tree_del(&tree, arr[1]);
	tree_to_arr(tree, arr, 0);
	printArr(arr, --k);

	free(arr);
	tree_free(tree);
}
