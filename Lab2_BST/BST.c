#include <stdio.h>
#include <stdlib.h>

#include "BST.h"

// Insert val into BST
void BSTinsert(int val, BST** q) {
	if (*q == NULL) {
		*q = malloc(sizeof(BST));
		(*q)->left = (*q)->right = NULL;
		(*q)->value = val;
		return;
	}
	if ((*q)->value > val)
		BSTinsert(val, &(*q)->left);
	else
		BSTinsert(val, &(*q)->right);
}

// Print BST elements in increasing order
void BSTprintInc(BST* p) {
	if (p == NULL) return;
	BSTprintInc(p->left);
	printf("%d ", p->value);
	BSTprintInc(p->right);
}

// Delete value from BST. Return 1 on success, 0 on failure.
int BSTdelete(int val, BST** node) {
	BST* t, *up;
	if (*node == NULL) return 0; // нет такого значения

	if ((*node)->value == val) {

		// если значение в листе, удаляем лист
		if (((*node)->left == NULL)
			&& ((*node)->right == NULL)) {
			free(*node);
			*node = NULL;
			printf("Delete List\n");
			return 1;
		}

		// если у вершины только правый потомок
		if ((*node)->left == NULL) {
			t = *node; *node = (*node)->right;
			free(t);
			printf("Delete Left = 0\n");
			return 1;
		}

		// если у вершины только левый потомок
		if ((*node)->right == NULL) {
			t = *node; *node = (*node)->left;
			free(t);
			printf("Delete Right = 0\n");
			return 1;
		}

		// если у вершины два потомка, заменяем удаляемое значение
		// на значение самого правого элемента в левом поддереве
		up = *node; t = (*node)->left; // идем влево

		//спускаемся до крайнего правого узла
		while (t->right != NULL) { up = t; t = t->right; }

		//копируем значение из правого узла
		(*node)->value = t->value;

		// если ниже удаляемого больше, чем одна вершина
		if (up != (*node)) {
			if (t->left != NULL) up->right = t->left;
			else up->right = NULL; // удаляем лист
		}

		// если ниже удаляемого одна вершина, удаляем лист
		else (*node)->left = t->left;

		// освобождаем память – удаляем крайнюю
		// правую вершину
		free(t);
		printf("Delete Two\n");
		return 1;
	}

	// поиск ключа в левом или правом поддереве
	if ((*node)->value < val)
		return BSTdelete(val, &(*node)->right);
	return BSTdelete(val, &(*node)->left);
}