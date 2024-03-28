// the class Stock definition
#include <string>
#include "stock.h"
#include "names.h"
#include "random_price.h"
using namespace std;

double Stock::purchase(double &balance, unsigned int amount) {
    // Purchase a number of stocks
    // Return the total cost of the purchase
    // If the player does not have enough balance, return -1
    // Otherwise, update the balance and quantity of the stock
    double total_cost = price * amount;
    if (total_cost > balance) {
        return -1;
    }
    balance -= total_cost;
    quantity += amount;
    return total_cost;
}

double Stock::sell(double &balance, unsigned int amount) {
    // Sell a number of stocks
    // Return the total revenue of the sale
    // If the player does not have enough stocks, return -1
    // Otherwise, update the balance and quantity of the stock
    if (quantity < amount) {
        return -1;
    }
    double total_revenue = price * amount;
    balance += total_revenue;
    quantity -= amount;
    return total_revenue;
}

string Stock::category_name(void) {
    // Return the name of the category
    return category_list[category];
}

unsigned int Stock::num_stocks_affordable(double balance) {
    // Return the number of stocks that the player can afford
    return (unsigned int) balance / price;
}

void Stock::initialize_history(void) {
    // Initialize the history array
    history_array_size = 10;
    history_index = 0;
    double * history = new double[history_array_size];
    history[0] = price;
}

void Stock::update_history(void) {
    if (history == nullptr) {
        // If the history array is not initialized, throw an error
        initialize_history();
    }
    // Update the history array with the current price
    if (history_index == history_array_size) {
        // If the history array is full, double the size
        double * new_history = new double[history_array_size * 2];
        for (int i = 0; i < history_array_size; i++) {
            new_history[i] = history[i];
        }
        delete[] history;
        history = new_history;
        // A general practice is to double the array size
        history_array_size *= 2;
    }
    history[history_index] = price;
    history_index++;
}

void Stock::delete_memory(void) {
    // Delete the dynamically allocated memory
    delete[] history;
    history = nullptr; // Set the pointer to null
    // This is a good practice to avoid using a dangling pointer
    // In case someone forgot delete the stock object
    
    // TODO: delete the event modifier linked list
}

double Stock::delta_price(void) {
    // Return the change of stock price
    // which stock prices are stored in the history array
    if (history_index < 2) {
        // If there are less than two prices in the history array, return 0
        return 0;
    }
    // Return the change of the last two prices
    return history[history_index - 1] - history[history_index - 2];
}

double Stock::delta_price_percentage(void) {
    // Return the percentage of change of stock price using Stock::delta_price();
    if (history_index < 2) {
        // If there are less than two prices in the history array, return 0
        return 0;
        // since history[history_index - 2] will return strange value
    }
    return delta_price() / history[history_index - 2];
}

void Stock::add_event(Stock_event event) {
    // Add an event to the stock
    // Create a new event modifier and add it to the linked list
    if (event_modifier_head == nullptr) {
        // If the linked list is empty, create a new event modifier
        Event_Modifier * new_event = new Event_Modifier;
        new_event->sd_change = event.sd;
        new_event->skew_change = event.skew;
        new_event->duration = event.duration;
        new_event->next = nullptr;
        event_modifier_head = new_event;
        return;
    }
    else {
        // If the linked list is not empty, find the last element
        Event_Modifier * current = event_modifier_head;
        while (current->next != nullptr) {
            current = current->next;
        }
        // Create a new event modifier and add it to the end of the linked list
        Event_Modifier * new_event = new Event_Modifier;
        new_event->sd_change = event.sd;
        new_event->skew_change = event.skew;
        new_event->duration = event.duration;
        new_event->next = nullptr;
        current->next = new_event;
    }
}

void Stock::init(void) {
    // Assign a random price, standard deviation, skewness, and category to the stock
    category = random_integer(category_list_size);

    // Generate a name based on the category
    name = generate_name(category);
}
