/** @file events.cpp
 * stores the event texts and modifiers
 */
#include "events.h"
#include <iostream>
#include <algorithm>

/*  stock cats:
    "Adv&Market", "Aero&Def", "Airlines", "RenewEnergy", "Auto", "Banks", "Biotech",
    "Broadcast", "Casinos&Gaming", "E-Commerce", "FinServices",
    "Food&Beverage", "Healthcare", "Tech", "RealEstate", "Retail", "Telecom"
*/

/** The list of all events that can be applied to the stocks */
//event_id 0 to 7 affect all stocks
//event_id 8 to 11 affect category "Adv&Market"
//event_id 12 to 16 affect category "Aero&Def"
//event_id 17 to 22 affect category "Airlines"
//event_id 23 to 27 affect category "RenewEnergy"
//event_id 28 to 31 affect category "Auto"
//event_id 32 to 34 affect category "Banks"
//event_id 35 to 37 affect category "Biotech"                                

std::vector<Stock_event> all_stock_events = {
//event_id 0 to 7 affect all stocks
    {/** event_id */ 0,
     /** mutually_exclusive_events */ {1},
     /** text */ "The FED has decreased the interest rate!", 
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.1}, {mean, 2}, {lower_limit, 0}, {upper_limit, 20}}},
    {/** event_id */ 1,
     /** mutually_exclusive_events */ {0, 3},
     /** text */ "The FED has increased the interest rate!", 
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.1}, {mean, -2}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 2,
     /** mutually_exclusive_events */ {},
     /** text */ "Economic Recession: Market Downturn Signals Investor Concerns", 
     /** duration */ 7,
     /** percentage_permille */ 20,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.2}, {mean, -5}, {lower_limit, -50}, {upper_limit, 0}}},
    {/** event_id */ 3,
     /** mutually_exclusive_events */ {1},
     /** text */ "Central Bank Cuts Interest Rates: Market Stimulus Boosts Investor Sentiment", 
     /** duration */ 3,
     /** percentage_permille */ 5,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.05}, {mean, 1}, {lower_limit, 0}, {upper_limit, 10}}},
    {/** event_id */ 4,
     /** mutually_exclusive_events */ {},
     /** text */ "Trade War Escalates: Global Market Volatility Amidst Rising Tensions",
     /** duration */ 5,
     /** percentage_permille */ 15,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.15}, {mean, -3}, {lower_limit, -30}, {upper_limit, 0}}},
    {/** event_id */ 5,
     /** mutually_exclusive_events */ {},
     /** text */ "Natural Disaster Strikes: Stock Market Reacts to Catastrophic Event",
     /** duration */ 7,
     /** percentage_permille */ 10,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.1}, {mean, -2}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 6,
     /** mutually_exclusive_events */ {},
     /** text */ "Government Policy Change: Market Impacted by New Regulations",
     /** duration */ 4,
     /** percentage_permille */ 8,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.08}, {mean, -1}, {lower_limit, -15}, {upper_limit, 5}}},
    {/** event_id */ 7,
     /** mutually_exclusive_events */ {},
     /** text */ "Inflation Surges: Market Concerns Rise as Prices Soar", 
     /** duration */ 6,
     /** percentage_permille */ 12,
     /** type_of_event */ all_stocks,
     /** category */ 0,
     /** modifiers*/ {{standard_deviation, 0.12}, {mean, -3}, {lower_limit, -25}, {upper_limit, 0}}},
//event_id 8 to 11 affect category "Adv&Market"
    {/** event_id */ 8,
     /** mutually_exclusive_events */ {},
     /** text */ "New Social Media Platform Disrupts Advertising Landscape",
     /** duration */ 4,
     /** percentage_permille */ 8,
     /** type_of_event */ category,
     /** category */ 0,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, -3}, {lower_limit, -10}, {upper_limit, 0}}},
    {/** event_id */ 9,
     /** mutually_exclusive_events */ {},
     /** text */ "Digital Advertising Spend Reaches All-Time High",
     /** duration */ 6,
     /** percentage_permille */ 15,
     /** type_of_event */ category,
     /** category */ 0,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}}},
    {/** event_id */ 10,
     /** mutually_exclusive_events */ {},
     /** text */ "Marketing Automation Tools Gain Popularity Among Businesses",
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 0,
     /** modifiers */ {{standard_deviation, 0.12}, {mean, 2}, {lower_limit, 0}, {upper_limit, 15}}},
    {/** event_id */ 11,
     /** mutually_exclusive_events */ {},
     /** text */ "Artificial Intelligence Revolutionizes Targeted Advertising",
     /** duration */ 5,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 0,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, 4}, {lower_limit, 0}, {upper_limit, 25}}},
//event_id 12 to 16 affect category "Aero&Def"
    {/** event_id */ 12,
     /** mutually_exclusive_events */ {16},
     /** text */ "Government Increases Defense Spending Amid Rising Geopolitical Tensions",
     /** duration */ 4,
     /** percentage_permille */ 5,
     /** type_of_event */ category,
     /** category */ 1,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}}},
    {/** event_id */ 13,
     /** mutually_exclusive_events */ {15},
     /** text */ "Emerging Technologies Transform Aerospace Industry",
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 1,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}}},
    {/** event_id */ 14,
     /** mutually_exclusive_events */ {},
     /** text */ "Space Exploration Companies Achieve Major Milestones",
     /** duration */ 5,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 1,
     /** modifiers */ {{standard_deviation, 0.12}, {mean, 2}, {lower_limit, 0}, {upper_limit, 15}}},
    {/** event_id */ 15,
     /** mutually_exclusive_events */ {13},
     /** text */ "Supply Chain Disruptions Hinder Aerospace Manufacturing",
     /** duration */ 6,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 1,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, -3}, {lower_limit, -10}, {upper_limit, 0}}},
    {/** event_id */ 16,
     /** mutually_exclusive_events */ {12},
     /** text */ "Budget Cuts Lead to Decreased Defense Contracts",
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 1,
     /** modifiers */ {{standard_deviation, 0.12}, {mean, -2}, {lower_limit, -15}, {upper_limit, 0}}},
/event_id 17 to 22 affect category "Airlines"
    {/** event_id */ 17,
     /** mutually_exclusive_events */ {},
     /** text */ "Airline Industry Experiences Surge in Travel Demand",
     /** duration */ 7,
     /** percentage_permille */ 15,
     /** type_of_event */ category,
     /** category */ 2,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}}},
    {/** event_id */ 18,
     /** mutually_exclusive_events */ {},
     /** text */ "Fuel Prices Skyrocket, Putting Pressure on Airlines' Profit Margins",
     /** duration */ 6,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 2,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, -3}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 19,
     /** mutually_exclusive_events */ {},
     /** text */ "Airline Strikes Disrupt Travel Plans for Thousands of Passengers",
     /** duration */ 5,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 2,
     /** modifiers */ {{standard_deviation, 0.12}, {mean, -2}, {lower_limit, -15}, {upper_limit, 0}}},
    {/** event_id */ 20,
     /** mutually_exclusive_events */ {},
     /** text */ "New Low-Cost Airline Enters the Market, Intensifying Competition",
     /** duration */ 6,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 2,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}}},
    {/** event_id */ 21,
     /** mutually_exclusive_events */ {},
     /** text */ "Natural Disasters Disrupt Airline Operations and Cause Flight Cancellations",
     /** duration */ 3,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 2,
     /** modifiers */ {{standard_deviation, 0.12}, {mean, -2}, {lower_limit, -15}, {upper_limit, 0}}},
    {/** event_id */ 22,
     /** mutually_exclusive_events */ {},
     /** text */ "New Security Regulations Increase Operational Costs for Airlines",
     /** duration */ 6,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 2,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, -1}, {lower_limit, -10}, {upper_limit, 0}}},
//event_id 23 to 27 affect category "RenewEnergy"
    {/** event_id */ 23,
     /** mutually_exclusive_events */ {26},
     /** text */ "Government Implements New Incentives to Promote Renewable Energy Adoption",
     /** duration */ 6,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 3,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}}},
    {/** event_id */ 24,
     /** mutually_exclusive_events */ {},
     /** text */ "Breakthrough in Solar Panel Technology Increases Efficiency by 20%",
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 3,
     /** modifiers */ {{standard_deviation, 0.12}, {mean, 2}, {lower_limit, 0}, {upper_limit, 15}}},
    {/** event_id */ 25,
     /** mutually_exclusive_events */ {},
     /** text */ "Investment in Wind Farms Surges as Costs of Wind Energy Decrease",
     /** duration */ 7,
     /** percentage_permille */ 16,
     /** type_of_event */ category,
     /** category */ 3,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}}},
    {/** event_id */ 26,
     /** mutually_exclusive_events */ {23},
     /** text */ "Government Cuts Subsidies for Renewable Energy Projects, Slowing Down Progress",
     /** duration */ 6,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 3,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, -3}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 27,
     /** mutually_exclusive_events */ {},
     /** text */ "Persistent Cloud Cover Reduces Solar Power Generation",
     /** duration */ 5,
     /** percentage_permille */ 8,
     /** type_of_event */ category,
     /** category */ 3,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, -2}, {lower_limit, -15}, {upper_limit, 0}}},
//event_id 28 to 31 affect category "Auto"
    {/** event_id */ 28,
     /** mutually_exclusive_events */ {},
     /** text */ "Breakthrough in Electric Vehicle Battery Technology Extends Range and Reduces Charging Time",
     /** duration */ 6,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 4,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}}},
    {/** event_id */ 29,
     /** mutually_exclusive_events */ {},
     /** text */ "Sudden Increase in Oil Prices Impacts Affordability and Demand for Conventional Vehicles",
     /** duration */ 5,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 4,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, -2}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 30,
     /** mutually_exclusive_events */ {31},
     /** text */ "Introduction of Advanced Driver Assistance Systems Enhances Vehicle Safety",
     /** duration */ 5,
     /** percentage_permille */ 8,
     /** type_of_event */ category,
     /** category */ 4,
     /** modifiers */ {{standard_deviation, 0.06}, {mean, 2}, {lower_limit, 0}, {upper_limit, 15}}},
    {/** event_id */ 31,
     /** mutually_exclusive_events */ {30},
     /** text */ "Frequent Accidents raise safety Concerns",
     /** duration */ 6,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 4,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, -5}, {lower_limit, -30}, {upper_limit, 0}}},
//event_id 32 to 34 affect category "Banks"
    {/** event_id */ 32,
     /** mutually_exclusive_events */ {},
     /** text */ "Economic Recession Triggers Increase in Non-Performing Loans, Putting Banks at Risk",
     /** duration */ 7,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 5,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, -4}, {lower_limit, -25}, {upper_limit, 0}}},
    {/** event_id */ 33,
     /** mutually_exclusive_events */ {},
     /** text */ "Government Introduces Stimulus Package to Boost Lending and Economic Growth",
     /** duration */ 6,
     /** percentage_permille */ 15,
     /** type_of_event */ category,
     /** category */ 5,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, 5}, {lower_limit, 0}, {upper_limit, 25}}},
    {/** event_id */ 34,
     /** mutually_exclusive_events */ {},
     /** text */ "Government Implements Excessive Money Printing, Leading to Inflation and Currency Devaluation",
     /** duration */ 8,
     /** percentage_permille */ 16,
     /** type_of_event */ category,
     /** category */ 5,
     /** modifiers */ {{standard_deviation, 0.12}, {mean, -8}, {lower_limit, -40}, {upper_limit, 0}}},
//event_id 35 to 37 affect category "Biotech"
    {/** event_id */ 35,
     /** mutually_exclusive_events */ {},
     /** text */ "Breakthrough in Gene Therapy Offers Potential Cure for Genetic Diseases",
     /** duration */ 7,
     /** percentage_permille */ 14,
     /** type_of_event */ category,
     /** category */ 6,
     /** modifiers */ {{standard_deviation, 0.10}, {mean, 4}, {lower_limit, 0}, {upper_limit, 25}}},
    {/** event_id */ 36,
     /** mutually_exclusive_events */ {},
     /** text */ "Clinical Trial Failure Delays Development of Promising Drug Candidate",
     /** duration */ 5,
     /** percentage_permille */ 10,
     /** type_of_event */ category,
     /** category */ 6,
     /** modifiers */ {{standard_deviation, 0.08}, {mean, -3}, {lower_limit, -20}, {upper_limit, 0}}},
    {/** event_id */ 37,
     /** mutually_exclusive_events */ {},
     /** text */ "Successful FDA Approval Expedites Commercialization of Innovative Biotech Products",
     /** duration */ 6,
     /** percentage_permille */ 12,
     /** type_of_event */ category,
     /** category */ 6,
     /** modifiers */ {{standard_deviation, 0.09}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}}},

// print a map
void print_map(std::map<unsigned int, std::vector<unsigned int>> map) {
    for (auto i : map) {
        std::cout << i.first << ": ";
        for (unsigned int j : i.second) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

/**
int main() {
    // This outputs 0.1
    std::cout << all_stock_events[0].modifiers[standard_deviation] << std::endl;
    // Checks the events for mutual exclusivity
    print_map(check_mutual_exclusivity(all_stock_events));
    // Outputs:
    // 0: 2
    // 1: 2
    // 2:
    //@todo Consider remove this example in the future.
    return 0;
}
*/

std::map<unsigned int, std::vector<unsigned int>> check_mutual_exclusivity(std::vector<Stock_event> all_events) {
    std::map<unsigned int, std::vector<unsigned int>> mut_excl_map;
    // Build the map
    for (unsigned int i = 0; i < all_events.size(); i++) {
        for (unsigned int j = 0; j < all_events[i].mutually_exclusive_events.size(); j++) {
            mut_excl_map[all_events[i].event_id].push_back(all_events[i].mutually_exclusive_events[j]);
        }
    }
    // If two events are mutually exclusive, they should be in each other's list.
    // Remove such two events from the map.
    // E.g. {0: [1,2], 1: [0], 2:[]} -> {0: [2]}
    // In this case, 2 does not state that it is mutually exclusive with 0.
    for (auto i : mut_excl_map) {
        for (unsigned int j : i.second) {
            if (std::find(mut_excl_map[j].begin(), mut_excl_map[j].end(), i.first) != mut_excl_map[j].end()) {
                mut_excl_map[i.first].erase(std::remove(mut_excl_map[i.first].begin(), mut_excl_map[i.first].end(), j), mut_excl_map[i.first].end());
                mut_excl_map[j].erase(std::remove(mut_excl_map[j].begin(), mut_excl_map[j].end(), i.first), mut_excl_map[j].end());
            }
        }
    }
    return mut_excl_map; // Add the missing return statement
}
