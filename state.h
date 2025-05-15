enum Item{
	NONE = 0,
	COLA = 5,
	JELLY = 3,
	KITKAT = 4,
	MARS = 2,
};

struct VendingMachine;
struct VendingMachine *make_vmachine();
int select_item(struct VendingMachine *mac, enum Item item);
int insert_dime(struct VendingMachine *mac);
int buy_selected(struct VendingMachine *mac);
int reset_all(struct VendingMachine *mac);
