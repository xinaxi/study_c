//односвязный список

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int val;
	struct _node *next;
} node;

typedef struct list {
	node *head;
	node *tail;
	int len;
} list;

list *list_create() {
	return calloc(sizeof(list), 1);
}

node *node_create(int val) {
	node *node = malloc(sizeof(node));
	node->val = val;
	node->next = NULL;
	return node;
}

int list_get_size(list *list) {
	return list->len;
}

void list_add_head(list *list, int val) {
	node *node = node_create(val);
	node->next = list->head;
	list->head = node;
	if (!list_get_size)
		list->tail = node;
	list->len++;
}

void list_add_tail(list *list, int val) {
	int len = list_get_size(list);
	node *p = list->head;
	node *node = node_create(val);
	for (int i = 0; i < len - 1; i++)
		p = p->next;
	p->next = node;
	list->tail = node;
	list->len++;
}

void list_add_index(list *list, int val, int index) {
	if (!index)
		list_add_head(list, val);
	else {
		node *p = list->head;
		node *node = node_create(val);
		for (int i = 0; i < index - 1; i++)
			p = p->next;
		node->next = p->next;
		p->next = node;
		list->len++;
	}
}

int list_del_head(list *list) {
	node *node = list->head;
	int val = node->val;
	list->head = node->next;
	list->len--;
	free(node);
	return val;
}

int list_del_tail(list *list) {
	int len = list_get_size(list);
	int val = list->tail->val;
	node *p = list->head;
	for (int i = 1; i < len - 1; i++)
		p = p->next;
	p->next = NULL;
	free(list->tail);
	list->tail = p;
	list->len--;
	return val;
}

int list_del_index(list *list, int index) {
	if (!index)
		return list_del_head(list);
	if (index == list->len - 1)
		return list_del_tail;
	else {
		node *p = list->head;
		node *node;
		int val;
		for (int i = 1; i < index; i++)
			p = p->next;
		node = p->next;
		p->next = node->next;
		list->len--;
		val = node->val;
		free(node);
		return val;
	}
}

int list_get_head(list *list) {
	return list->head->val;
}

int list_get_tail(list *list) {
	return list->tail->val;
}

int list_get_index(list *list, int index) {
	node *p = list->head;
	for (int i = 0; i < index; i++)
		p = p->next;
	return p->val;
}

void list_set_head(list *list, int val) {
	list->head->val = val;
}

void list_set_tail(list *list, int val) {
	list->tail->val = val;
}

void list_set_index(list *list, int val, int index) {
	node *p = list->head;
	for (int i = 0; i < index; i++)
		p = p->next;
	p->val = val;
}

void list_free(list *list) {
	int len = list_get_size(list);
	node *p = list->head, *p2;
	for (int i = 0; i < len / 2; i++) {
		p2 = p->next;
		free(p);
		p = p2->next;
		free(p2);
	}
	if (p)
		free(p);
	free(list);
}

void print_list(list *list) {
	int len = list_get_size(list);
	node *p = list->head;
	for (int i = 0; i < len; i++) {
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
}

void main() {
	int a;
	list *list = list_create();
	list_add_head(list, 1);
	print_list(list);
	list_add_head(list, 2);
	print_list(list);
	list_add_head(list, 3);
	print_list(list);

	list_add_tail(list, 4);
	print_list(list);
	list_add_tail(list, 5);
	print_list(list);

	list_add_index(list, 6, 1);
	print_list(list);
	list_add_index(list, 7, 3);
	print_list(list);

	a = list_get_head(list);
	printf("%d\n", a);
	a = list_get_tail(list);
	printf("%d\n", a);
	a = list_get_index(list, 5);
	printf("%d\n", a);

	list_set_head(list, 8);
	print_list(list);
	list_set_tail(list, 9);
	print_list(list);
	list_set_index(list, 10, 4);
	print_list(list);

	a = list_del_head(list);
	print_list(list);
	printf("%d\n", a);
	a = list_del_tail(list);
	print_list(list);
	printf("%d\n", a);
	a = list_del_index(list, 2);
	print_list(list);
	printf("%d\n", a);

	list_free(list);
}
