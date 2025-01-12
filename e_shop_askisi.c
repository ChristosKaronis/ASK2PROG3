#include "e_shop.h"

// Sunartisi arxikopoiisis twn antikimenon Shop
void initialize_shop(Shop *shop) {
    const char *base_names[5] = {"Laptop", "Mouse", "Keyboard", "Monitor", "Headphones"};
    int name_counter[5] = {0, 0, 0, 0, 0};  // Counter gia to kathe onoma
    
    
    for (int i = 0; i < 20; i++) {
        int name_index = i % 5;  // Dialegoume onoma apo to pinaka onomatwn
        name_counter[name_index]++;  // Auksanoume to counter gia to sygkekrimeno onoma

         // dinoume ta onomata analoga me to metriti pou exoume
        sprintf(shop->items[i].description, "%s_%d", base_names[name_index], name_counter[name_index]);

        // Dhmiourgia onomatos proiontos
        shop->items[i].quantity =  2;  
        shop->items[i].price = ((rand() % 100) + 1) * 0.5;
         printf("Initialized item: %s | Quantity: %d | Price: $%.2f\n", 
               shop->items[i].description, shop->items[i].quantity, shop->items[i].price);
         // Price na einai 2 kai i timi enas tuxaios arithmos apo 1-50
         }
    shop->total_earnings = 0.0;
    shop->successful_orders = 0;
    shop->declined_orders = 0;

}

// Paraggelia gia th thugatriki diergasiaa
int process_order(Shop *shop, Order *order) {
    for (int i = 0; i < 20; i++) {
        if (strcmp(shop->items[i].description, order->item_name) == 0) {
            shop->items[i].total_orders++; // Auksanoume tis sunolikes paraggelies
            if (shop->items[i].quantity >= order->quantity) {
                shop->items[i].quantity -= order->quantity;
                 shop->items[i].quantity_sold += order->quantity;  // Auksanoume tis paraggelies gia auto to antikeimeno
                 shop->total_earnings += shop->items[i].price * order->quantity;
                shop->successful_orders++;
                return shop->items[i].price * order->quantity;  // Epituxia
            } else {
                 shop->items[i].unsuccessful_orders++;  // Auksanoume tis apotuximenes paraggelies
                shop->declined_orders++;
                return -1;  // Apotuxia logo apothematos
            }
        }
    }
    shop->declined_orders++;
    return -1;  // Apotuxia 
}

int main (void){

    Shop eshop;

    srand(time(NULL)); // Gia tuxaious arithmous

    // Arxikopoiisi tou struct shop
    initialize_shop(&eshop);

    // file descriptors gia ta pipe mas
    int pipefd[2];

    pid_t pid ; // to pid tou process mas
    char buffer[BUFFER_SIZE]; // to buffer mas

    // Dimiourgia pipes
    if (pipe(pipefd) ==-1) {
        perror("Pipe apetixe");
        exit(EXIT_FAILURE);}

    for (int client_id = 1; client_id <= 5; client_id++) {
        pid = fork();
        if (pid < 0) {
            // Lathos tis fork
            perror("Fork() apetixe!!");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  // Thugatriki diergasia
            close(pipefd[0]);  // kleinoume pipes anagnwsis

            // Dhmiourgia eikonikou shop stis thugatrikes diergasies
            ShopItem local_shop[20];
            memcpy(local_shop, eshop.items, sizeof(eshop.items));

            for (int j = 0; j < 10; j++) {
                Order order;
                 int random_item_index = rand() % 20;  // Tuxaia epilogi antikeimenou
                strcpy(order.item_name, local_shop[random_item_index].description);  // Antigrafi onomatos local
                order.quantity = 1;  // Paraggelia 1 antikeimeno
                if (write(pipefd[1], &order, sizeof(Order)) == -1) {
                    perror("Error writing to pipe");
                    exit(EXIT_FAILURE);
                }

            }
            close(pipefd[1]);  // kleinoume pipes grapsimatos
            exit(EXIT_SUCCESS);
        }
    }
        

    for (int i = 0; i < 50; i++) {  // Prepei na exoume 50 paraggelies
        Order order;
        read(pipefd[0], &order, sizeof(Order));
        int price = process_order(&eshop, &order);
        if (price > 0) {
            printf("Client %d: Order Successful for %s. Total: $%.2f\n", i / 10 + 1, order.item_name, (float)price);
        } else {
            printf("Client %d: Order Declined for %s.\n", i / 10 + 1, order.item_name);
        }
    }

    close(pipefd[0]);  // Kleisimo pipes anagnwsis

    for (int i = 0; i < 5; i++) {
        wait(NULL);  // perimenoume na teleiwsoun oi thugatrikes diergasies
    }

    // Statistika ektelesis
    printf("\nTziros Shop :\n");
    printf("Total Earnings: $%.2f\n", eshop.total_earnings); // Sunolika esoda 
    printf("Successful Orders: %d\n", eshop.successful_orders); // epituximenes paraggelies
    printf("Declined Orders: %d\n", eshop.declined_orders); // apotuximenes paraggelies

    // Statistika antikeimenwn
    printf("\nStatistika Antikeimenwn:\n");
    for (int i = 0; i < 20; i++) {
        printf("%s: Sunolikes paraggelies = %d, Sold = %d, Unsuccessful Orders = %d\n", 
               eshop.items[i].description, eshop.items[i].total_orders, eshop.items[i].quantity_sold, eshop.items[i].unsuccessful_orders);
    }
    //Telos programmatos
    return 0;
}