enum Size{
	SMALL = 0,
	MEDIUM,
	BIG,
};

enum Meat{
	NO_MEAT = 0,
	BEEF,
	CHICKEN,
};

enum Veggy{
	NO_VEGGY = 0,
	TOMATO,
	CABBAGE,
};

enum Sauce{
	NO_SAUCE = 0,
	KETCHUP,
	CHILI,
	BBQ,
};

struct Burger{
	enum Meat meat;
	enum Veggy veggies[5];
	enum Sauce sauces[3];
	unsigned weight;
	unsigned vi, si;
};

struct Burger *make_burger(enum Size size);
struct Burger *reset_burger(enum Size size, struct Burger *burger);
struct Burger *add_meat(enum Meat meat, struct Burger *burger);
struct Burger *add_veggy(enum Veggy veggy, struct Burger *burger);
struct Burger *add_sauce(enum Sauce sauce, struct Burger *burger);
