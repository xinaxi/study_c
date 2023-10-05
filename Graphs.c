//обходы в глубину и ширину, компоненты связности

#include <stdio.h>
#include <stdlib.h>

int **make_matrix(int n, FILE *f) {
	int **A = malloc(n*sizeof(int *));
	for (int i = 0; i < n; i++) {
		A[i] = malloc(n*sizeof(int));
		for (int j = 0; j < n; j++) {
			int x;
			fscanf(f, "%d", &x);
			A[i][j] = x;
		}
	}
	return A;
}

void delete_matrix(int **A, int n) {
	for (int i = 0; i < n; i++)
		free(A[i]);
	free(A);
}

void DFS_2(int **A, int n, int *m, int *B, int *C, int x) {
	B[(*m)++] = x;
	C[x] = 1;
	for (int i = 0; i < n; i++) {
		if (A[x][i] && !C[i])
			DFS_2(A, n, m, B, C, i);
	}
}

int *DFS(int **A, int n, int start, int *m, int **marks) {
	int *B = malloc(n * sizeof(int)), *C;
	if (marks)
		C = *marks;
	else
		C = calloc(n, sizeof(int));
	*m = 0;
	DFS_2(A, n, m, B, C, start);
	if (marks)
		*marks = C;
	else
		free(C);
	return B;
}

int *BFS(int **A, int n, int start, int *m, int **b_steps) {
	int *B = malloc(n * sizeof(int));
	int *D = malloc(n * sizeof(int));
	int *C = calloc(n, sizeof(int));
	int i = 0, j = 0;
	B[i++] = start;
	C[start] = 1;
	D[start] = -1;
	while (i != j) {
		int a = B[j++];
		for (int ii = 0; ii < n; ii++)
			if (A[a][ii] && !C[ii]) {
				B[i++] = ii;
				C[ii] = 1;
				D[ii] = a;
			}
	}
	free(C);
	*m = i;
	if (b_steps)
		*b_steps = D;
	else
		free(D);
	return B;
}

void fprint_arr(FILE *f, int *a, int n) {
	for (int i = 0; i < n; i++)
		fprintf(f, "%d ", a[i]);
	fprintf(f, "\n");
}

void component(FILE *f, int **A, int n) {
	int *C = calloc(n, sizeof(int)), *B;
	int m, i;
	fprintf(f, "Components:\n");
	for (i = 0; i < n; i++) {
		if (!C[i]) {
			B = DFS(A, n, i, &m, &C);
			fprintf(f, "\t");
			fprint_arr(f, B, m);
			free(B);
		}
	}
	free(C);
}

int *path(int **A, int n, int *m, int from, int to) {
	int *D, *B, i = 0;
	B = BFS(A, n, to, m, &D);
	B[i++] = from;
	if (from == to) {
		*m = i;
		free(D);
		return B;
	}
	while ((B[i] = D[B[i - 1]]) != to)
		i++;
	*m = i + 1;
	return B;
}

int connected(int **A, int n, int a, int b) {
	int m, *C = calloc(n, sizeof(int));
	DFS(A, n, a, &m, &C);
	if (C[b])
			return 1;
	free(C);
	return 0;
}

int cycle_2(int **A, int n, int *C, int p, int x) {
	C[x] = 1;
	for (int i = 0; i < n; i++) {
		if (A[x][i])
			if (!C[i])
				if (cycle_2(A, n, C, x, i))
					return 1;
				else;
			else
				if (i != p)
					return 1;
	}
	return 0;
}

int cycle(int **A, int n) {
	int *C = calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		if (!C[i])
			if (cycle_2(A, n, C, -1, i))
				return 1;
	}
	return 0;
}

void main() {
	int **A, n, *B, m;
	FILE *f = fopen("text.txt", "r");
	fscanf(f, "%d", &n);
	A = make_matrix(n, f);
	fclose(f);

	f = fopen("text2.txt", "w");
	B = BFS(A, n, 7, &m, NULL);
	fprintf(f, "BFS: ");
	fprint_arr(f, B, m);
	free(B);
	B = DFS(A, n, 3, &m, NULL);
	fprintf(f, "DFS: ");
	fprint_arr(f, B, m);
	free(B);
	component(f, A, n);
	fprintf(f, "paths:\n");
	for (int i = 0; i < n; i++) {
		fprintf(f, "\t%d: ", i);
		if (connected(A, n, 1, i)) {
			B = path(A, n, &m, 1, i);
			fprint_arr(f, B, m);
		}
		else
			fprintf(f, "no\n");
	}
	free(B);
	if (cycle(A, n))
		fprintf(f, "there is a cycle\n");
	else
		fprintf(f, "there is no cycle\n");
	fclose(f);

	delete_matrix(A, n);
}
