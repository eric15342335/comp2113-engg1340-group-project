#include "stock.h"
#include "names.h"
#include "random_price.h"
using namespace std;

double Stock::purchase(double & balance, unsigned int amount, double trading_fees_percent) {
    double total_cost = price * amount * (1 + trading_fees_percent);
    if (total_cost > balance) {
        return -1;
    }
    balance -= total_cost;
    quantity += amount;
    money_spent += total_cost;
    return total_cost;
}

double Stock::sell(double & balance, unsigned int amount, double trading_fees_percent) {
    if (quantity < amount) {
        return -1;
    }
    double total_revenue = price * amount * (1 - trading_fees_percent);
    balance += total_revenue;
    quantity -= amount;
    money_spent -= total_revenue;
    return total_revenue;
}

string Stock::category_name(void) {
    return category_list[category];
}

unsigned int Stock::num_stocks_affordable(double balance, double trading_fees_percent) {
    return (unsigned int)balance / price * (1 + trading_fees_percent);
}

void Stock::update_history(void) {
    /** @note We use vector now! */
    history.push_back(price);
}

vector<double> Stock::return_most_recent_history(int rounds) {
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
    // Stock prices are stored in the history array
    if (history.size() < 2) {
        // If there are less than two prices in the history array, return 0
        return 0;
    }
    // Return the change of the last two prices
    return history[history.size() - 1] - history[history.size() - 2];
}

double Stock::delta_price_percentage(void) {
    if (history.size() < 2) {
        // If there are less than two prices in the history array, return 0
        return 0;
    }
    return delta_price() / history[history.size() - 2];
}

void Stock::add_event(Stock_event event) {
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
            /*
            Since we check the next Event_Modifier in the linked list,
            the current Event_Modifier is not obselete, so we don't need to delete it
            and we are safe to proceed to the next item
            */
        }
    }
}

double Stock::get_true_sd(void) {
    double true_sd = sd;
    Event_Modifier * current = event_modifier_head;
    // Add the standard deviation offset from each event modifier in the linked list
    while (current != nullptr) {
        true_sd += current->sd_change;
        current = current->next;
    }
    return true_sd;
}

double Stock::get_true_skewness(void) {
    double true_skew = skew;
    Event_Modifier * current = event_modifier_head;
    // Add the skewness offset from each event modifier in the linked list
    while (current != nullptr) {
        true_skew += current->skew_change;
        current = current->next;
    }
    return true_skew;
}

void Stock::init(void) {
    category = random_integer(category_list_size);
    name = generate_name(category);
}

void Stock::testing_set_attributes(string name, double price, unsigned int quantity, double sd, double skew, unsigned int category) {
    this->name = name;
    this->price = price;
    this->quantity = quantity;
    this->sd = sd;
    this->skew = skew;
    this->category = category;
    return;
}
