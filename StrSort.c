//работа со строками, лексикографический порядок

#include <stdio.h>
#include <stdlib.h>

int *read_str() {
	char c, l = 0;
	char *s = malloc(sizeof(char));
	c = getchar();
	while (c != '\n') {
		s[l] = c;
		l++;
		s = realloc(s, (l + 1)*sizeof(char));
		c = getchar();
	}
	s[l] = 0;
	return s;
}

int my_strlen(char *s) {
	int l = 0;
	while (s[l++]);
	return l - 1;
}

int num_words(char *s) {
	int k = 1;
	while (*s)
		if (*(s++) == ' ')
			k++;
	return k;
}

int wcmp(char *s1, char *s2) {
	while (*s1 && (*s1 != ' ')) {
		if (*s1 > * s2)
			return 1;
		if (*(s1++) < *(s2++))
			return -1;
	}
	if (!(*s2) || (*s2 == ' '))
		return 0;
	return -1;
}

int cmp(char *s, int i) {
	int l = 0;
	while (l != i) {
		if (wcmp(s + l, s + i) == 1)
			return l;
		while (s[l] && (s[l++] != ' '));
	}
	return l;
}

void copy_word(char *a, char *b, int l) {
	while (((*(b++) = *a) != ' ') && *(a++));
	if (l)
		*(b - 1) = ' ';
	else
		*(b - 1) = 0;
}

void insert(char *s, int i, int k) {
	char *w = malloc(my_strlen(s)*sizeof(char));
	int l;
	copy_word(s + i, w, 0);
	l = my_strlen(w);
	for (int j = i - 2; j >= k; j--)
		s[j + l + 1] = s[j];
	copy_word(w, s + k, 1);
}

void string_sort(char *s) {
	int i = 0, k, n = num_words(s), m;
	if (n < 2)
		return;
	while (s[i++] != ' ');
	while(s[i]) {
		k = cmp(s, i);      //куда вставлять слово
		m = i;
		while (s[i] && (s[i++] != ' '));
		if (k == m)
			continue;
		insert(s, m, k);
	}
}

void main() {
	char *s = read_str();
	string_sort(s);
	printf("%s\n", s);
}
