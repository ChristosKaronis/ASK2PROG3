#ifndef E_SHOP_H
#define E_SHOP_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define BUFFER_SIZE 100


typedef struct {
    char description[50];
    int quantity;
    float price;
    int total_orders;
    int quantity_sold;
    int unsuccessful_orders;
} ShopItem;


typedef struct {
    ShopItem items[20];
    float total_earnings;
    int successful_orders;
    int declined_orders;
} Shop;


typedef struct {
    char item_name[50];
    int quantity;
} Order;


void initialize_shop(Shop *shop);
int process_order(Shop *shop, Order *order);

#endif 
