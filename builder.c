#include "builder.h"
#include <stdlib.h>
#include <memory.h>

struct Burger *make_burger(enum Size size){
	struct Burger *burger = malloc(sizeof(struct Burger));
	memset(burger, 0, sizeof(struct Burger));
	burger->weight = (size == SMALL ? 150 : (size == MEDIUM ? 250 : 500));
	return burger;
}

struct Burger *reset_burger(enum Size size, struct Burger *burger){
	memset(burger, 0, sizeof(struct Burger));
	burger->weight = (size == SMALL ? 150 : (size == MEDIUM ? 250 : 500));
	return burger;
}

struct Burger *add_meat(enum Meat meat, struct Burger *burger){
	burger->meat = meat;
	return burger;
}

struct Burger *add_veggy(enum Veggy veggy, struct Burger *burger){
	burger->veggies[burger->vi] = veggy;
	burger->vi = (burger->vi + 1)%5;
	return burger;
}

struct Burger *add_sauce(enum Sauce sauce, struct Burger *burger){
	burger->sauces[burger->si] = sauce;
	burger->si = (burger->si + 1)%3;
	return burger;
}
