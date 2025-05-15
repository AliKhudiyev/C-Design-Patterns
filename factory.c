#include "factory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Salad{
	char veggies[10][100];
};

struct Salad *make_salad(){
	struct Salad *salad = malloc(sizeof(struct Salad));
	strcpy(salad->veggies[0], "cucumber");
	strcpy(salad->veggies[1], "cabbage");
	strcpy(salad->veggies[2], "tomato");
	fprintf(stdout, "making salad...\n");
	return salad;
}

struct Soup{
	char has_chicken;
	float temp;
};

struct Soup *make_soup(){
	struct Soup *soup = malloc(sizeof(struct Soup));
	soup->has_chicken = 1;
	soup->temp = 60;
	fprintf(stdout, "making a chicken soup...\n");
	return soup;
}

struct Steak{
	char is_vegan;
	char how_cooked[32];
};

struct Steak *make_Steak(){
	struct Steak *Steak = malloc(sizeof(struct Steak));
	Steak->is_vegan = 0;
	strcpy(Steak->how_cooked, "well done");
	fprintf(stdout, "making a %s Steak...\n", Steak->how_cooked);
	return Steak;
}

void *factory_make_food(enum Food food){
	if(food == SALAD) return make_salad();
	if(food == SOUP) return make_soup();
	if(food == STEAK) return make_Steak();
	fprintf(stderr, "No such food item.\n");
	return 0;
}
