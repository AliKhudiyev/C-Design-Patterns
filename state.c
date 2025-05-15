#include "state.h"
#include <stdlib.h>
#include <stdio.h>

static struct MachineState{
	int (*insert_dime)(struct VendingMachine *mac);
	int (*select_item)(struct VendingMachine *mac, enum Item item);
	int (*buy_selected)(struct VendingMachine *mac);
	int (*reset_all)(struct VendingMachine *mac);
} g_selection_state, g_insertion_state, g_purchase_state;

struct VendingMachine{
	enum Item item;
	unsigned balance;
	struct MachineState *state;
};

static int selection_state_insert_dime(struct VendingMachine *mac){
	fprintf(stderr, "You need to select an item first.\n");
	return -1;
}

static int selection_state_select_item(struct VendingMachine *mac, enum Item item){
	mac->item = item;
	if(item != NONE){
		mac->state = &g_insertion_state;
		return 1;
	}
	fprintf(stderr, "Select a valid item.\n"); 
	return -1;
}

static int selection_state_buy_selected(struct VendingMachine *mac){
	fprintf(stderr, "You need to select an item first.\n");
	return -1;
}

static int insertion_state_select_item(struct VendingMachine *mac, enum Item item){
	fprintf(stdout, "A new item has been selected.\n");
	if(mac->balance >= (int)item){ mac->state = &g_purchase_state; }
	else{ fprintf(stdout, "You don't have sufficient balance for the item.\n"); }
	return 0;
}

static int insertion_state_insert_dime(struct VendingMachine *mac){
	fprintf(stdout, "A dime has been inserted.\n");
	if(++mac->balance >= (int)mac->item){
		fprintf(stdout, "You can buy the item now.\n");
		mac->state = &g_purchase_state;
	}
	return 1;
}

static int insertion_state_buy_selected(struct VendingMachine *mac){
	fprintf(stderr, "You need to insert a dime.\n");
	return -1;
}

static int purchase_state_select_item(struct VendingMachine *mac, enum Item item){
	fprintf(stdout, "A new item has been selected.\n");
	if(mac->balance < (int)item){
		fprintf(stdout, "Your balance is unsufficient.\n");
		mac->state = &g_insertion_state;
	}
	else{ fprintf(stdout, "You can buy the item now.\n"); }
	return 1;
}

static int purchase_state_insert_dime(struct VendingMachine *mac){
	fprintf(stderr, "Your balance is already sufficient.\n");
	return -1;
}

static int purchase_state_buy_selected(struct VendingMachine *mac){
	fprintf(stdout, "You bought the item for %d dimes.\n", (int)mac->item);
	fprintf(stdout, "%d dimes have been refunded.\n", mac->balance - (int)mac->item);
	mac->item = NONE;
	mac->balance = 0;
	mac->state = &g_selection_state;
	return 1;
}

static int any_state_reset_all(struct VendingMachine *mac){
	fprintf(stdout, "Take your %d dimes.\n", mac->balance);
	mac->item = NONE;
	mac->balance = 0;
	mac->state = &g_selection_state;
	return 1;
}

struct VendingMachine *make_vmachine(){
	struct VendingMachine *mac = malloc(sizeof(struct VendingMachine));
	mac->item = NONE;
	mac->balance = 0;
	mac->state = &g_selection_state;

	g_selection_state = (struct MachineState){
		.select_item=selection_state_select_item,
		.insert_dime=selection_state_insert_dime,
		.buy_selected=selection_state_buy_selected,
		.reset_all=any_state_reset_all
	};

	g_insertion_state = (struct MachineState){
		.select_item=insertion_state_select_item,
		.insert_dime=insertion_state_insert_dime,
		.buy_selected=insertion_state_buy_selected,
		.reset_all=any_state_reset_all
	};

	g_purchase_state = (struct MachineState){
		.select_item=purchase_state_select_item,
		.insert_dime=purchase_state_insert_dime,
		.buy_selected=purchase_state_buy_selected,
		.reset_all=any_state_reset_all
	};

	return mac;
}

int select_item(struct VendingMachine *mac, enum Item item){
	return mac->state->select_item(mac, item);
}

int insert_dime(struct VendingMachine *mac){
	return mac->state->insert_dime(mac);
}

int buy_selected(struct VendingMachine *mac){
	return mac->state->buy_selected(mac);
}

int reset_all(struct VendingMachine *mac){
	return mac->state->reset_all(mac);
}
