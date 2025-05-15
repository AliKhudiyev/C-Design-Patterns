#include <string.h>
#include "strategy.h"

void change_name(struct Person *person, const void *name){
	strncpy(person->name, (const char*)name, 100);
}
void change_age(struct Person *person, const void *age){
	person->age = *(const unsigned char*)age;
}
void change_balance(struct Person *person, const void *balance){
	person->balance = *(const double*)balance;
}

void edit_person_info(struct Person *person, void *data, void (*meth)(struct Person*, const void*)){
	meth(person, data);
	for(int i=0; i<100; i+=4)
		person->_hash ^= *(int*)(person->name + i);
	person->_hash ^= person->age;
	person->_hash ^= *(long*)&person->balance;
}
