#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "singleton.h"
#include "strategy.h"
#include "iterator.h"
#include "factory.h"
#include "builder.h"
#include "state.h"
#include "facade.h"
#include "proxy.h"
#include "observer.h"

void test_singleton(){
	// assert(g_dbsesh == 0);
	struct DBSesh *dbsesh = 0;
	// dbsesh = malloc(sizeof(struct DBSesh));
	dbsesh = make_dbsesh();
	assert(dbsesh);
	assert(dbsesh == make_dbsesh());
	assert(make_dbsesh() == make_dbsesh());
}

void test_strategy(){
	struct Person p = {.name="Adam", .age=28, .balance=128.32};
	edit_person_info(&p, "Adam Smith", change_name);
	edit_person_info(&p, (unsigned char[]){30}, change_age);
	edit_person_info(&p, (double[]){-5.8}, change_balance);
	assert(!strcmp(p.name, "Adam Smith"));
	assert(p.age == 30);
	assert(p.balance == -5.8);
}

void test_iterator(){
	struct Text *text = make_text("Hello World!");
	struct Tree *tree = make_tree("Hello World!");
	struct Iterator iter;

	char chr = 0;
	iter = get_iterator((void*)text);
	while((chr=get_next(&iter))){ printf("%c", chr); }
	printf("\n");
	iter = get_iterator((void*)text);
	unsigned i = 0;
	while((chr=get_next(&iter))){ assert(chr == "Hello World!"[i++]); }
	// printf("\n");

	iter = get_iterator((void*)tree);
	while((chr=get_next(&iter))){ printf("[%c]", chr); }
	printf("\n");
	iter = get_iterator((void*)tree);
	i = 0;
	while((chr=get_next(&iter))){ assert(chr == "Heloroldl !W"[i++]); }
	// printf("\n");
}

void test_factory(){
	struct Salad *salad = factory_make_food(SALAD);
	struct Soup *soup = factory_make_food(SOUP);
	struct Steak *steak = factory_make_food(STEAK);
}

void test_builder(){
	struct Burger *burger = make_burger(SMALL);
	add_sauce(BBQ,
	add_sauce(CHILI,
	add_veggy(TOMATO,
	add_meat(BEEF,
	reset_burger(BIG,
	add_meat(CHICKEN, burger))))));
	assert(burger->weight == 500);
	assert(burger->meat == BEEF);
	assert(burger->veggies[0] == TOMATO);
	assert(burger->sauces[0] == CHILI);
	assert(burger->sauces[1] == BBQ);
}

void test_state(){
	struct VendingMachine *mac = make_vmachine();
	assert(insert_dime(mac) == -1);
	assert(select_item(mac, JELLY) == 1);
	assert(buy_selected(mac) == -1);
	assert(insert_dime(mac) == 1);
	assert(insert_dime(mac) == 1);
	assert(insert_dime(mac) == 1);
	assert(select_item(mac, MARS) == 1);
	assert(insert_dime(mac) == -1);
	assert(select_item(mac, KITKAT) == 1);
	assert(insert_dime(mac) == 1);
	assert(select_item(mac, JELLY) == 1);
	assert(buy_selected(mac) == 1);
}

void test_observer(){
	struct Podcast *podcast = make_podcast("Design Patterns");
	struct User *users[3] = {
		make_user("Adam"),
		make_user("i'm just a guy"),
		make_user(" ")
	};
	subscribe(podcast, users[0]);
	notify(podcast, "New episode is up!");

	subscribe(podcast, users[1]);
	subscribe(podcast, users[2]);
	unsubscribe(podcast, users[0]);
	notify(podcast, "Yet another episode.");
}

void test_facade(){
	struct GameSetting *setting = make_default_setting();
	high_settings(setting);
	low_settings(setting);
	ultra_settings(setting);
}

void test_adapter(){
}

void test_proxy(){
	struct Log *log = make_log("log.dat");
	log_syscheck(log);
	log_info(log, "hello world!");
	log_alert(log, "this is an alert...");
	log_warn(log, "the system has a warning");
	log_abort(log, "aborting due to critical error!");
}

int main(){
	// creational
	test_factory();
	test_builder();
	test_singleton();

	// structural
	test_facade();
	test_adapter();
	test_proxy();

	// behavioral
	test_strategy();
	test_iterator();
	test_state();
	test_observer();
	return 0;
}
