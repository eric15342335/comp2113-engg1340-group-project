// the class Stock definition
#include "stock.h"
#include "names.h"
#include "random_price.h"
using namespace std;

double Stock::purchase(double & balance, unsigned int amount, double trading_fees_percent) {
    // Purchase a number of stocks
    // Return the total cost of the purchase
    // If the player does not have enough balance, return -1
    // Otherwise, update the balance and quantity of the stock
    double total_cost = price * amount * (1 + trading_fees_percent);
    if (total_cost > balance) {
        return -1;
    }
    balance -= total_cost;
    quantity += amount;
    return total_cost;
}

double Stock::sell(double & balance, unsigned int amount, double trading_fees_percent) {
    // Sell a number of stocks
    // Return the total revenue of the sale
    // If the player does not have enough stocks, return -1
    // Otherwise, update the balance and quantity of the stock
    if (quantity < amount) {
        return -1;
    }
    double total_revenue = price * amount * (1 - trading_fees_percent);
    balance += total_revenue;
    quantity -= amount;
    return total_revenue;
}

string Stock::category_name(void) {
    // Return the name of the category
    return category_list[category];
}

unsigned int Stock::num_stocks_affordable(double balance, double trading_fees_percent) {
    // Return the number of stocks that the player can afford
    return (unsigned int)balance / price * (1 + trading_fees_percent);
}

void Stock::update_history(void) {
    // Update the history array with the current price
    // changes: We use vector now!
    history.push_back(price);
}

vector<double> Stock::return_most_recent_history(int rounds) {
    // Return the most recent stock prices
    // The number of rounds is specified by the parameter
    // If the number of rounds is greater than the size of the history array, return the entire history
    // Otherwise, return the most recent prices
    vector<double> recent_history;
    if (rounds >= history.size()) {
        return history;
    }
    for (int i = history.size() - rounds; i < history.size(); i++) {
        recent_history.push_back(history[i]);
    }
    return recent_history;
}

void Stock::delete_memory(void) {
    // Delete the event modifiers linked list
    // Loop through the linked list and delete each element sequentially
    Event_Modifier * current = event_modifier_head;
    while (current != nullptr) {
        Event_Modifier * temp = current;
        current = current->next;
        delete temp;
    }
    event_modifier_head = nullptr; // Set the pointer to null
}

double Stock::delta_price(void) {
    // Return the change of stock price
    // which stock prices are stored in the history array
    if (history.size() < 2) {
        // If there are less than two prices in the history array, return 0
        return 0;
    }
    // Return the change of the last two prices
    return history[history.size() - 1] - history[history.size() - 2];
}

double Stock::delta_price_percentage(void) {
    // Return the percentage of change of stock price using Stock::delta_price();
    if (history.size() < 2) {
        // If there are less than two prices in the history array, return 0
        return 0;
    }
    return delta_price() / history[history.size() - 2];
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

void Stock::remove_obselete_event(void) {
    // Loop through the Event_Modifier linked list and remove the obselete event
    // obselete events are events that have duration <= 0
    // Internal use after the "next_round" function is called
    if (event_modifier_head == nullptr) {
        // no Event_Modifier in the linked list
        return;
    }
    else {
        // If the first event is obselete, remove it
        if (event_modifier_head->duration <= 0) {
            Event_Modifier * temp = event_modifier_head;
            event_modifier_head = event_modifier_head->next;
            delete temp;
        }
        // Loop through the linked list and remove the obselete event(s)
        // save the current Event_Modifier pointer
        // since its duration is > 0 as checked in the above 'if' statement
        Event_Modifier * current = event_modifier_head;
        // check the next Event_Modifier
        while (current->next != nullptr) {
            if (current->next->duration <= 0) {
                // save the pointer of the next Event_Modifier struct
                // that has duration <= 0
                Event_Modifier * temp = current->next;
                // remove the item from the linked list
                current->next = temp->next;
                // delete the memory of the removed Event_Modifier
                delete temp;
            }
            // proceed to next item
            current = current->next;
            // since we check the next Event_Modifier in the linked list,
            // the current Event_Modifier is not obselete, so we don't need to delete it
            // and we are safe to proceed to the next item
        }
    }
}

double Stock::get_true_sd(void) {
    // Return the standard deviation value of the stock
    // after applying the event modifiers
    double true_sd = sd;
    Event_Modifier * current = event_modifier_head;
    while (current != nullptr) {
        true_sd += current->sd_change;
        current = current->next;
    }
    return true_sd;
}

double Stock::get_true_skewness(void) {
    // Return the skewness value of the stock
    // after applying the event modifiers
    double true_skew = skew;
    Event_Modifier * current = event_modifier_head;
    while (current != nullptr) {
        true_skew += current->skew_change;
        current = current->next;
    }
    return true_skew;
}

void Stock::init(void) {
    // Assign a random price, standard deviation, skewness, and category to the stock
    category = random_integer(category_list_size);

    // Generate a name based on the category
    name = generate_name(category);
}

void Stock::testing_set_attributes(string name, double price, unsigned int quantity, double sd, double skew, unsigned int category) {
    // Set the attributes of the stock for testing purposes
    this->name = name;
    this->price = price;
    this->quantity = quantity;
    this->sd = sd;
    this->skew = skew;
    this->category = category;
    return;
}
