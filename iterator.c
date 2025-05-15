#include "iterator.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct Text{
	struct Iterator iter;
	char *str;
};

struct Text *make_text(const char *str){
	struct Text *text = malloc(sizeof(struct Text));
	text->str = malloc(strlen(str)+1);
	strncpy(text->str, str, strlen(str)+1);
	text->iter = (struct Iterator){.type=TEXT, .container=text, .iter=text->str};
	return text;
}

struct Tree{
	struct Iterator iter;
	char chr;
	struct Tree *parent, *left, *right;
};

static size_t _get_index(size_t depth, size_t col){
	size_t index = 0;
	for(size_t i=1; i<depth; ++i) index = 2*index + 1;
	return index + col;
}

static struct Tree *_make_tree(const char *str, struct Tree *root, struct Tree *node, size_t depth, size_t col){
	size_t index = _get_index(depth, col);
	if(strlen(str) <= index) return 0;
	node = malloc(sizeof(struct Tree));
	node->chr = str[index];
	node->parent = root;
	node->left = _make_tree(str, node, node->left, depth+1, col*2);
	node->right = _make_tree(str, node, node->right, depth+1, col*2+1);
	return node;
}

struct Tree *make_tree(const char *str){
	struct Tree *tree = _make_tree(str, 0, 0, 1, 0);
	tree->iter = (struct Iterator){.type=TREE, .container=tree, .iter=tree};
	return tree;
}

struct Iterator get_iterator(void *container){
	return *(struct Iterator*)container;
}

char get_next(struct Iterator *iter){
	char c = 0;
	if(iter->type == TEXT){
		const char *begin = ((struct Text*)(iter->container))->str;
		size_t size = strlen(begin);
		if(begin + size > (char*)iter->iter){
			c = *((char*)iter->iter++);
		}
	} else if(iter->type == TREE){
		struct Tree *node = (struct Tree*)(iter->iter);
		if(node){
			c = node->chr;
			if(node->left){ iter->iter = node->left; }
			else if(node->right){ iter->iter = node->right; }
			else{
				struct Tree *parn = node->parent;
				for(; parn; parn=parn->parent){
					if(!parn->right || parn->right == node) node = parn;
					else break;
				}
				iter->iter = parn ? parn->right : 0;
			}
		}
	}
	return c;
}
