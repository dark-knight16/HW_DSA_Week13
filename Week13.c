#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100    //* The max number of Merchandise in ShoppingCart 
#define EMPTY -1        //* ShoppingCart is Empty

//! ShoppingCart is Stack, Checkout is Queue

//TODO 1. Inititalize Struct and Parameters are necessary

//* Struct Merchandise has Name and Price
typedef struct Merchandise {
    char name_merchandise[100];
    int price;
} Merchandise;

//* Struct ShoppingCart is Stack use Array
typedef struct ShoppingCart {
    int Top;
    Merchandise merchandise[MAX_SIZE];
} ShoppingCart;

//* Struct Customers has their's ShoppingCart
typedef struct Customers {
    ShoppingCart* sc;
    struct Customers* next;
} Customers;

//* Struct Checkout is Queue use Linked List
typedef struct Checkout {
    Customers* front;
    Customers* rear;
} Checkout;

//TODO Create Stack is ShoppingCart
ShoppingCart* create_shoppingcart() {
    ShoppingCart* sc = (ShoppingCart*)malloc(sizeof(ShoppingCart));
    sc->Top = EMPTY;
    return sc;
}

//TODO Dispose Stack is ShoppingCart
void dispose_shoppingcart(ShoppingCart* sc) {
    free(sc);
}

//? Check State of ShoppingCart is Empty or not
int sc_is_empty(ShoppingCart* sc) {
    return sc->Top == EMPTY;
}

//? Check State of ShoppingCart is Full or not
int sc_is_full(ShoppingCart* sc) {
    return sc->Top == MAX_SIZE - 1;
}

//TODO Add merchandise at the Top Position of ShoppingCart
void push_shoppingcart(ShoppingCart* sc, Merchandise m) {
    sc->Top++;
    sc->merchandise[sc->Top].price = m.price;
    strcpy(sc->merchandise[sc->Top].name_merchandise, m.name_merchandise);
}

//TODO Get merchandise at the Top Position of ShoppingCart
Merchandise pop_shoppingcart(ShoppingCart* sc) {
    Merchandise m = sc->merchandise[sc->Top];
    sc->Top--;
    return m;
}

//TODO Create Node People of Checkout
Customers* create_people_queue(ShoppingCart* sc) {
    Customers* customer = (Customers*)malloc(sizeof(Customers));
    customer->sc = sc;
    customer->next = NULL;
    return customer;
}

//TODO Create Checkout to People pay Merchandise on ShoppingCart
Checkout* create_checkout() {
    Checkout* co = (Checkout*)malloc(sizeof(Checkout));
    co->front = co->rear = NULL;
    return co;
}

//? Check that Checkout has people or not
int checkout_is_empty(Checkout* co) {
    return co->front == NULL && co->rear == NULL;
}

//TODO Add People to pay Merchandise on their ShoppingCart
void enqueue_checkout(Checkout* co, Customers* customer) {
    if(checkout_is_empty(co)) {
        co->front = co->rear = customer;
        return;
    }
    co->rear->next = customer;
    co->rear = customer;
} 

//TODO Get First People that paid Merchandise on their ShoppingCart
Customers* dequeue_checkout(Checkout* co) {
    if(checkout_is_empty(co)) return NULL;
    Customers* first_customer = co->front;
    co->front = co->front->next;
    if(co->front == NULL) co->rear = NULL;
    return first_customer;
}

//TODO Display ShoppingCart
void display_shoppingcart(ShoppingCart* sc) {
    if(sc_is_empty(sc)) {
        printf("ShoppingCart is Empty\n");
        return;
    }
    else if(sc_is_full(sc)) {
        printf("ShoppingCart is Full\n");
        return;
    }
    else {
        while(sc->Top != EMPTY) {
            Merchandise m = pop_shoppingcart(sc);
            printf("%s %d\n", m.name_merchandise, m.price);
        }
    }
    printf("\n");
}

//TODO Display ShoppingCart of Customer
void display_customer(Customers* customer) {
    ShoppingCart* sc = customer->sc;
    display_shoppingcart(sc);
}

//TODO Display Checkout
void display_checkout(Checkout* co) {
    if(checkout_is_empty(co)) {
        printf("No Customer!\n");
        return;
    }
    do {
        Customers* customer = dequeue_checkout(co);
        display_shoppingcart(customer->sc);
    } while(!checkout_is_empty(co));
    printf("\n");
}

//TODO Driver code
int main() {

    //TODO Inititalize parameters
    Checkout* co = create_checkout();    //? Counter to checkout
    char merchandiseA[100] = "Tao";      //? Merchandise A 
    int money = 0;                       //? Total number of money that crasher calculate
    int count_merchandise_A = 0;         //? The number of Merchandise A

    //TODO Test
    ShoppingCart* sc1 = create_shoppingcart();  //? ShoppingCart 1st of Customer 1st
    ShoppingCart* sc2 = create_shoppingcart();  //? ShoppingCart2, 3 same
    ShoppingCart* sc3 = create_shoppingcart();

    //? Merchandises that Customers bought
    Merchandise m1 = {"Tao", 7};     
    Merchandise m2 = {"Le", 6};
    Merchandise m3 = {"Nho", 12};
    Merchandise m4 = {"Hoa", 50};

    //* Customers i th buy Merchandise x
    push_shoppingcart(sc1, m1);
    push_shoppingcart(sc1, m2);
    push_shoppingcart(sc1, m3);
    push_shoppingcart(sc2, m1);
    push_shoppingcart(sc2, m3);
    push_shoppingcart(sc3, m3);
    push_shoppingcart(sc3, m4);
    Customers* customer1 = create_people_queue(sc1);
    Customers* customer2 = create_people_queue(sc2);
    Customers* customer3 = create_people_queue(sc3);

    //* Add Customers pay at Checkout
    enqueue_checkout(co, customer1);
    enqueue_checkout(co, customer2);
    enqueue_checkout(co, customer3);

    //TODO Payments to Customers 
    while(!checkout_is_empty(co)) {
        Customers* first_customer = dequeue_checkout(co);
        ShoppingCart* sc = first_customer->sc;
        while(!sc_is_empty(sc)) {
            Merchandise first_m = pop_shoppingcart(sc);
            money += first_m.price;
            if(!strcmp(first_m.name_merchandise, merchandiseA)) ++count_merchandise_A;
        }
        free(sc);

        //TODO 2. Remove each person from the queue after the person has made a payment
        free(first_customer);
    }
    free(co);

    //TODO 3. Total number of money
    printf("The total amount of money that the cashier collects at the counter is %d\n", money);

    //TODO 4. The number of Merchandise A
    printf("The number of merchandise %s sold at the cashier counter is %d\n", merchandiseA, count_merchandise_A);
}