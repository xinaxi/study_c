//создание своего динамического массива

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int* arr;
	int len;
	int capacity;
} ext_array;

ext_array *ext_arr_create(int cap) {
	ext_array *this = malloc(sizeof(ext_array));
	int *c = malloc(cap*sizeof(int));
	this->arr = c;
	this->len = 0;
	this->capacity = cap;
	return this;
}

int ext_arr_get_len(ext_array* this) {
	return this->len;
}

void ext_arr_delete(ext_array* this) {
	free(this->arr);
	free(this);
}

void ext_arr_add_end(ext_array* this, int x) {
	if (this->capacity == this->len) {
		this->capacity *= 2;
		this->arr = realloc(this->arr, this->capacity*sizeof(int));
	}
	this->arr[this->len++] = x;
}

void ext_arr_add_begin(ext_array* this, int x) {
	if (this->capacity == this->len) {
		this->capacity *= 2;
		this->arr = realloc(this->arr, this->capacity*sizeof(int));
	}
	for (int i = this->len; i > 0; i--)
		this->arr[i] = this->arr[i - 1];
	this->arr[0] = x;
	this->len++;
}

int ext_arr_del_end(ext_array* this) {
	return this->arr[--this->len];
}

int ext_arr_del_begin(ext_array* this) {
	int x = this->arr[0];
	for (int i = 1; i < this->len; i++)
		this->arr[i - 1] = this->arr[i];
	this->len--;
	return x;
}

int ext_arr_get(ext_array* this, int index) {
	return this->arr[index];
}

void ext_arr_set(ext_array* this, int index, int value) {
	if (this->capacity == this->len) {
		this->capacity *= 2;
		this->arr = realloc(this->arr, this->capacity*sizeof(int));
	}
	for (int i = this->len; i > index; i--)
		this->arr[i] = this->arr[i - 1];
	this->arr[index] = value;
	this->len++;
}

void print_arr(int *a, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void main() {
	int c, l;
	ext_array* this = ext_arr_create(3);
	printf("n = ");
	scanf("%d", &l);
	printf("Array: ");
	for (int i = 0; i < l; i++) {
		scanf("%d", &c);
		ext_arr_add_end(this, c);
	}
	print_arr(this->arr, ext_arr_get_len(this));
	printf("add begin: ");
	scanf("%d", &c);
	ext_arr_add_begin(this, c);
	print_arr(this->arr, ext_arr_get_len(this));
	printf("del end\n");
	c = ext_arr_del_end(this);
	print_arr(this->arr, ext_arr_get_len(this));
	printf("%d\n", c);
	printf("del begin\n");
	c = ext_arr_del_begin(this);
	print_arr(this->arr, ext_arr_get_len(this));
	printf("%d\n", c);
	printf("index ");
	scanf("%d", &l);
	c = ext_arr_get(this, l);
	printf("%d\n", c);
	printf("index: ");
	scanf("%d", &l);
	printf("value: ");
	scanf("%d", &c);
	ext_arr_set(this, l, c);
	print_arr(this->arr, ext_arr_get_len(this));
	ext_arr_delete;
}
