enum Food{
	SALAD = 0,
	SOUP,
	STEAK,
};

struct Salad;
struct Soup;
struct Steak;
void *factory_make_food(enum Food food);
