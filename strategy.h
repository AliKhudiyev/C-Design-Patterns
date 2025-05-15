struct Person{
	char name[100];
	unsigned char age;
	double balance;
	long _hash;
};

void change_name(struct Person *person, const void *name);
void change_age(struct Person *person, const void *age);
void change_balance(struct Person *person, const void *balance);

void edit_person_info(struct Person *person, void *data, void (*meth)(struct Person*, const void*));
