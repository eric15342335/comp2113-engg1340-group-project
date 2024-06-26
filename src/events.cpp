/// @file events.cpp
/// Stores the event texts and modifiers.
/*
This program is free software: you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this
program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "events.h"

#include "random_price.h"

#include <algorithm>
#include <cassert>
#include <iostream>

/** @brief The list of all events that can be applied to the stocks.
 * @ref category_list
 * @details
 * | Event ID Range | Affected Category |
 * | -------------- | ----------------- |
 * | 0 to 7         | All Stocks        |
 * | 8 to 11        | Adv&Market        |
 * | 12 to 16       | Aero&Def          |
 * | 17 to 22       | Airlines          |
 * | 23 to 27       | RenewEnergy       |
 * | 28 to 31       | Auto              |
 * | 32 to 34       | Banks             |
 * | 35 to 37       | Biotech           |
 * | 38 to 40       | Broadcast         |
 * | 41 to 46       | Casinos&Gaming    |
 * | 47 to 51       | E-Commerce        |
 * | 52 to 55       | FinServices       |
 * | 56 to 61       | Food&Beverage     |
 * | 62 to 66       | Healthcare        |
 * | 67 to 74       | Tech              |
 * | 75 to 79       | RealEstate        |
 * | 80 to 85       | Retail            |
 * | 86 to 91       | Telecom           |
 * | 92 to 98       | pick_random_stock |
 */
const std::vector<Stock_event> all_stock_events = {
    // event_id 0 to 7 affect all stocks
    {
        /** event_id */ 0,
        /** mutually_exclusive_events */ {1},
        /** text */ "The FED has decreased the interest rate!",
        /** duration */ 5,
        /** percentage_permille */ 4,
        /** type_of_event */ all_stocks,
        /** category */ 0,
        /** modifiers*/
        {{standard_deviation, 0.1}, {mean, 20}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 1,
        /** mutually_exclusive_events */ {0, 3},
        /** text */ "The FED has increased the interest rate!",
        /** duration */ 5,
        /** percentage_permille */ 4,
        /** type_of_event */ all_stocks,
        /** category */ 0,
        /** modifiers*/
        {{standard_deviation, 0.1}, {mean, -20}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 2,
        /** mutually_exclusive_events */ {},
        /** text */ "Economic Recession: Market Downturn Signals Investor Concerns",
        /** duration */ 7,
        /** percentage_permille */ 2,
        /** type_of_event */ all_stocks,
        /** category */ 0,
        /** modifiers*/
        {{standard_deviation, 0.2}, {mean, -30}, {lower_limit, -30}, {upper_limit, 0}},
    },
    {
        /** event_id */ 3,
        /** mutually_exclusive_events */ {1},
        /** text */
        "Central Bank Cuts Interest Rates: Market Stimulus Boosts Investor Sentiment",
        /** duration */ 3,
        /** percentage_permille */ 4,
        /** type_of_event */ all_stocks,
        /** category */ 0,
        /** modifiers*/
        {{standard_deviation, 0.05}, {mean, 10}, {lower_limit, 0}, {upper_limit, 10}},
    },
    {
        /** event_id */ 4,
        /** mutually_exclusive_events */ {},
        /** text */
        "Trade War Escalates: Global Market Volatility Amidst Rising Tensions",
        /** duration */ 5,
        /** percentage_permille */ 4,
        /** type_of_event */ all_stocks,
        /** category */ 0,
        /** modifiers*/
        {{standard_deviation, 0.15}, {mean, -30}, {lower_limit, -30}, {upper_limit, 0}},
    },
    {
        /** event_id */ 5,
        /** mutually_exclusive_events */ {},
        /** text */
        "Natural Disaster Strikes: Stock Market Reacts to Catastrophic Event",
        /** duration */ 7,
        /** percentage_permille */ 4,
        /** type_of_event */ all_stocks,
        /** category */ 0,
        /** modifiers*/
        {{standard_deviation, 0.1}, {mean, -20}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 6,
        /** mutually_exclusive_events */ {},
        /** text */ "Government Policy Change: Market Impacted by New Regulations",
        /** duration */ 4,
        /** percentage_permille */ 4,
        /** type_of_event */ all_stocks,
        /** category */ 0,
        /** modifiers*/
        {{standard_deviation, 0.08}, {mean, -10}, {lower_limit, -15}, {upper_limit, 5}},
    },
    {
        /** event_id */ 7,
        /** mutually_exclusive_events */ {},
        /** text */ "Inflation Surges: Market Concerns Rise as Prices Soar",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ all_stocks,
        /** category */ 0,
        /** modifiers*/
        {{standard_deviation, 0.12}, {mean, 0}, {lower_limit, -25}, {upper_limit, 0}},
    },
    // event_id 8 to 11 affect category "Adv&Market"
    {
        /** event_id */ 8,
        /** mutually_exclusive_events */ {},
        /** text */ "New Social Media Platform Disrupts Advertising Landscape",
        /** duration */ 4,
        /** percentage_permille */ 8,
        /** type_of_event */ category,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, -3}, {lower_limit, -10}, {upper_limit, 0}},
    },
    {
        /** event_id */ 9,
        /** mutually_exclusive_events */ {},
        /** text */ "Digital Advertising Spend Reaches All-Time High",
        /** duration */ 6,
        /** percentage_permille */ 15,
        /** type_of_event */ category,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}},
    },
    {
        /** event_id */ 10,
        /** mutually_exclusive_events */ {},
        /** text */ "Marketing Automation Tools Gain Popularity Among Businesses",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, 2}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 11,
        /** mutually_exclusive_events */ {},
        /** text */ "Artificial Intelligence Revolutionizes Targeted Advertising",
        /** duration */ 5,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, 4}, {lower_limit, 0}, {upper_limit, 25}},
    },
    // event_id 12 to 16 affect category "Aero&Def"
    {
        /** event_id */ 12,
        /** mutually_exclusive_events */ {16},
        /** text */
        "Government Increases Defense Spending Amid Rising Geopolitical Tensions",
        /** duration */ 4,
        /** percentage_permille */ 5,
        /** type_of_event */ category,
        /** category */ 1,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}},
    },
    {
        /** event_id */ 13,
        /** mutually_exclusive_events */ {15},
        /** text */ "Emerging Technologies Transform Aerospace Industry",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 1,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 14,
        /** mutually_exclusive_events */ {},
        /** text */ "Space Exploration Companies Achieve Major Milestones",
        /** duration */ 5,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 1,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, 2}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 15,
        /** mutually_exclusive_events */ {13},
        /** text */ "Supply Chain Disruptions Hinder Aerospace Manufacturing",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 1,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, -3}, {lower_limit, -10}, {upper_limit, 0}},
    },
    {
        /** event_id */ 16,
        /** mutually_exclusive_events */ {12},
        /** text */ "Budget Cuts Lead to Decreased Defense Contracts",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 1,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -2}, {lower_limit, -15}, {upper_limit, 0}},
    },
    // event_id 17 to 22 affect category "Airlines"
    {
        /** event_id */ 17,
        /** mutually_exclusive_events */ {},
        /** text */ "Airline Industry Experiences Surge in Travel Demand",
        /** duration */ 7,
        /** percentage_permille */ 15,
        /** type_of_event */ category,
        /** category */ 2,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}},
    },
    {
        /** event_id */ 18,
        /** mutually_exclusive_events */ {},
        /** text */
        "Fuel Prices Skyrocket, Putting Pressure on Airlines' Profit Margins",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 2,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, -3}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 19,
        /** mutually_exclusive_events */ {},
        /** text */ "Airline Strikes Disrupt Travel Plans for Thousands of Passengers",
        /** duration */ 5,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 2,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -2}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 20,
        /** mutually_exclusive_events */ {},
        /** text */ "New Low-Cost Airline Enters the Market, Intensifying Competition",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 2,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 21,
        /** mutually_exclusive_events */ {},
        /** text */
        "Natural Disasters Disrupt Airline Operations and Cause Flight Cancellations",
        /** duration */ 3,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 2,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -2}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 22,
        /** mutually_exclusive_events */ {},
        /** text */ "New Security Regulations Increase Operational Costs for Airlines",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 2,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, -1}, {lower_limit, -10}, {upper_limit, 0}},
    },
    // event_id 23 to 27 affect category "RenewEnergy"
    {
        /** event_id */ 23,
        /** mutually_exclusive_events */ {26},
        /** text */
        "Government Implements New Incentives to Promote Renewable Energy Adoption",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 3,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 24,
        /** mutually_exclusive_events */ {},
        /** text */
        "Breakthrough in Solar Panel Technology Increases Efficiency by 20%",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 3,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, 2}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 25,
        /** mutually_exclusive_events */ {},
        /** text */ "Investment in Wind Farms Surges as Costs of Wind Energy Decrease",
        /** duration */ 7,
        /** percentage_permille */ 16,
        /** type_of_event */ category,
        /** category */ 3,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}},
    },
    {
        /** event_id */ 26,
        /** mutually_exclusive_events */ {23},
        /** text */
        "Government Cuts Subsidies for Renewable Energy Projects, Slowing Down "
        "Progress",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 3,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, -3}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 27,
        /** mutually_exclusive_events */ {},
        /** text */ "Persistent Cloud Cover Reduces Solar Power Generation",
        /** duration */ 5,
        /** percentage_permille */ 8,
        /** type_of_event */ category,
        /** category */ 3,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, -2}, {lower_limit, -15}, {upper_limit, 0}},
    },
    // event_id 28 to 31 affect category "Auto"
    {
        /** event_id */ 28,
        /** mutually_exclusive_events */ {},
        /** text */
        "Breakthrough in Electric Vehicle Battery Technology Extends Range and Reduces "
        "Charging Time",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 4,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 29,
        /** mutually_exclusive_events */ {},
        /** text */
        "Sudden Increase in Oil Prices Impacts Affordability and Demand for "
        "Conventional Vehicles",
        /** duration */ 5,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 4,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, -5}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 30,
        /** mutually_exclusive_events */ {31},
        /** text */
        "Introduction of Advanced Driver Assistance Systems Enhances Vehicle Safety",
        /** duration */ 5,
        /** percentage_permille */ 8,
        /** type_of_event */ category,
        /** category */ 4,
        /** modifiers */
        {{standard_deviation, 0.06}, {mean, 5}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 31,
        /** mutually_exclusive_events */ {30},
        /** text */ "Frequent Accidents raise safety Concerns",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 4,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, -5}, {lower_limit, -30}, {upper_limit, 0}},
    },
    // event_id 32 to 34 affect category "Banks"
    {
        /** event_id */ 32,
        /** mutually_exclusive_events */ {},
        /** text */
        "Economic Recession Triggers Increase in Non-Performing Loans, Putting Banks "
        "at Risk",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 5,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, -4}, {lower_limit, -25}, {upper_limit, 0}},
    },
    {
        /** event_id */ 33,
        /** mutually_exclusive_events */ {},
        /** text */
        "Government Introduces Stimulus Package to Boost Lending and Economic Growth",
        /** duration */ 6,
        /** percentage_permille */ 15,
        /** type_of_event */ category,
        /** category */ 5,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, 5}, {lower_limit, 0}, {upper_limit, 25}},
    },
    {
        /** event_id */ 34,
        /** mutually_exclusive_events */ {},
        /** text */
        "Government Implements Excessive Money Printing, Leading to Inflation and "
        "Currency Devaluation",
        /** duration */ 8,
        /** percentage_permille */ 16,
        /** type_of_event */ category,
        /** category */ 5,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, 0}, {lower_limit, -40}, {upper_limit, 0}},
    },
    // event_id 35 to 37 affect category "Biotech"
    {
        /** event_id */ 35,
        /** mutually_exclusive_events */ {},
        /** text */
        "Breakthrough in Gene Therapy Offers Potential Cure for Genetic Diseases",
        /** duration */ 7,
        /** percentage_permille */ 14,
        /** type_of_event */ category,
        /** category */ 6,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, 4}, {lower_limit, 0}, {upper_limit, 25}},
    },
    {
        /** event_id */ 36,
        /** mutually_exclusive_events */ {},
        /** text */
        "Clinical Trial Failure Delays Development of Promising Drug Candidate",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 6,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, -3}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 37,
        /** mutually_exclusive_events */ {},
        /** text */
        "Successful FDA Approval Expedites Commercialization of Innovative Biotech "
        "Products",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 6,
        /** modifiers */
        {{standard_deviation, 0.09}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}},
    },
    // event_id 38 to 40 affect category "Broadcast"
    {
        /** event_id */ 38,
        /** mutually_exclusive_events */ {},
        /** text */
        "New Streaming Service Launches with Extensive Content Library and Innovative "
        "Features",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 7,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 39,
        /** mutually_exclusive_events */ {},
        /** text */
        "Broadcast Network Faces Significant Revenue Losses Due to Declining "
        "Viewership",
        /** duration */ 7,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 7,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, -4}, {lower_limit, -25}, {upper_limit, 0}},
    },
    {
        /** event_id */ 40,
        /** mutually_exclusive_events */ {},
        /** text */
        "Broadcast Network Strikes Exclusive Deal for Live Coverage of Major Sporting "
        "Event",
        /** duration */ 5,
        /** percentage_permille */ 8,
        /** type_of_event */ category,
        /** category */ 7,
        /** modifiers */
        {{standard_deviation, 0.07}, {mean, 2}, {lower_limit, 0}, {upper_limit, 15}},
    },
    // event_id 41 to 46 affect category "Casinos&Gaming"
    {
        /** event_id */ 41,
        /** mutually_exclusive_events */ {},
        /** text */ "Stringent Gambling Regulations Restrict Casino Operations",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 8,
        /** modifiers */
        {{standard_deviation, 0.10}, {mean, -4}, {lower_limit, -25}, {upper_limit, 0}},
    },
    {
        /** event_id */ 42,
        /** mutually_exclusive_events */ {},
        /** text */
        "Innovative Strategies Help Casinos Navigate Stringent Regulations and "
        "Minimize Revenue Losses",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 8,
        /** modifiers */
        {{standard_deviation, 0.08}, {mean, 3}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 43,
        /** mutually_exclusive_events */ {45},
        /** text */
        "Online Gaming Goes Viral, Attracting Millions of Players Worldwide",
        /** duration */ 5,
        /** percentage_permille */ 20,
        /** type_of_event */ category,
        /** category */ 8,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 30}},
    },
    {
        /** event_id */ 44,
        /** mutually_exclusive_events */ {},
        /** text */ "New Esports Tournament Breaks Viewership Records",
        /** duration */ 4,
        /** percentage_permille */ 15,
        /** type_of_event */ category,
        /** category */ 8,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 7}, {lower_limit, 0}, {upper_limit, 25}},
    },
    {
        /** event_id */ 45,
        /** mutually_exclusive_events */ {43},
        /** text */
        "Major Data Breach Affects Gaming Platforms, Raising Concerns About Player "
        "Privacy",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 8,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -4}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 46,
        /** mutually_exclusive_events */ {},
        /** text */
        "Introduction of Virtual Reality Gaming Enhances Player Immersion and "
        "Experience",
        /** duration */ 5,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 8,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    // event_id 47 to 51 affect category "E-Commerce"
    {
        /** event_id */ 47,
        /** mutually_exclusive_events */ {},
        /** text */
        "E-commerce Sales Reach All-Time High, Exceeding Market Expectations",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 9,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 48,
        /** mutually_exclusive_events */ {},
        /** text */
        "Supply Chain Disruptions Cause Delivery Delays and Inventory Shortages in "
        "E-commerce",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 9,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -4}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 49,
        /** mutually_exclusive_events */ {},
        /** text */
        "Introduction of Innovative Payment Solutions Boosts E-commerce Conversion "
        "Rates",
        /** duration */ 5,
        /** percentage_permille */ 8,
        /** type_of_event */ category,
        /** category */ 9,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 4}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 50,
        /** mutually_exclusive_events */ {},
        /** text */
        "Cybersecurity Breach Raises Concerns About Online Shopping Privacy and Data "
        "Protection",
        /** duration */ 6,
        /** percentage_permille */ 15,
        /** type_of_event */ category,
        /** category */ 9,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -7}, {lower_limit, -25}, {upper_limit, 0}},
    },
    {
        /** event_id */ 51,
        /** mutually_exclusive_events */ {},
        /** text */
        "Advancements in Artificial Intelligence Revolutionize Personalized Shopping "
        "Experiences",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 9,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    // event_id 52 to 55 affect category "FinServices"
    {
        /** event_id */ 52,
        /** mutually_exclusive_events */ {53},
        /** text */
        "Fintech Startups Disrupt Traditional Banking, Providing Innovative Financial "
        "Services",
        /** duration */ 6,
        /** percentage_permille */ 15,
        /** type_of_event */ category,
        /** category */ 10,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 7}, {lower_limit, 0}, {upper_limit, 25}},
    },
    {
        /** event_id */ 53,
        /** mutually_exclusive_events */ {52, 54, 55},
        /** text */ "Stock Market Crash Leads to Financial Turmoil and Investor Losses",
        /** duration */ 7,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 10,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -4}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 54,
        /** mutually_exclusive_events */ {53},
        /** text */
        "Introduction of Blockchain Technology Enhances Security and Efficiency in "
        "Financial Transactions",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 10,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 55,
        /** mutually_exclusive_events */ {53},
        /** text */
        "Digital Wallets Gain Popularity, Simplifying Payment Processes and Increasing "
        "Financial Inclusion",
        /** duration */ 5,
        /** percentage_permille */ 8,
        /** type_of_event */ category,
        /** category */ 10,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 4}, {lower_limit, 0}, {upper_limit, 15}},
    },
    // event_id 56 to 61 affect category "Food&Beverage"
    {
        /** event_id */ 56,
        /** mutually_exclusive_events */ {},
        /** text */
        "Plant-Based Food Trend Continues to Grow, Offering Healthier and Sustainable "
        "Options",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 11,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 57,
        /** mutually_exclusive_events */ {},
        /** text */
        "Food Safety Scandal Raises Concerns About Contaminated Products and Consumer "
        "Health",
        /** duration */ 7,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 11,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -4}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 58,
        /** mutually_exclusive_events */ {},
        /** text */
        "Introduction of Innovative Cooking Techniques Enhances Culinary Experiences",
        /** duration */ 5,
        /** percentage_permille */ 8,
        /** type_of_event */ category,
        /** category */ 11,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 4}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 59,
        /** mutually_exclusive_events */ {},
        /** text */
        "Global Food Shortage Crisis Impacts Prices and Availability of Essential "
        "Commodities",
        /** duration */ 6,
        /** percentage_permille */ 15,
        /** type_of_event */ category,
        /** category */ 11,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -7}, {lower_limit, -25}, {upper_limit, 0}},
    },
    {
        /** event_id */ 60,
        /** mutually_exclusive_events */ {},
        /** text */
        "Rise of Food Delivery Services Provides Convenient and Wide-ranging Dining "
        "Options",
        /** duration */ 5,
        /** percentage_permille */ 8,
        /** type_of_event */ category,
        /** category */ 11,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 4}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 61,
        /** mutually_exclusive_events */ {},
        /** text */
        "Growing Demand for Organic and Locally Sourced Food Drives Sustainable "
        "Farming Practices",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 11,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    // event_id 62 to 66 affect category "Healthcare"
    {
        /** event_id */ 62,
        /** mutually_exclusive_events */ {},
        /** text */
        "Advancements in Telemedicine Improve Access to Medical Care for Remote Areas",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 12,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 63,
        /** mutually_exclusive_events */ {},
        /** text */
        "Outbreak of Global Pandemic Leads to Overwhelmed Healthcare Systems and High "
        "Mortality Rates",
        /** duration */ 8,
        /** percentage_permille */ 15,
        /** type_of_event */ category,
        /** category */ 12,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, 7}, {lower_limit, 0}, {upper_limit, 25}},
    },
    {
        /** event_id */ 64,
        /** mutually_exclusive_events */ {},
        /** text */
        "Development of Personalized Medicine Leads to More Effective Treatment and "
        "Prevention Strategies",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 12,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 65,
        /** mutually_exclusive_events */ {},
        /** text */
        "Shortage of Healthcare Professionals Causes Strain on Medical Services and "
        "Longer Wait Times",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 12,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -4}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 66,
        /** mutually_exclusive_events */ {},
        /** text */
        "Advancements in Gene Editing Technology Open New Avenues for Precision "
        "Medicine",
        /** duration */ 7,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 12,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    // event_id 67 to 74 affect category "Tech"
    {
        /** event_id */ 67,
        /** mutually_exclusive_events */ {},
        /** text */
        "Breakthrough in Artificial Intelligence Leads to Significant Advancements in "
        "Automation and Machine Learning",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 13,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 68,
        /** mutually_exclusive_events */ {},
        /** text */
        "Cybersecurity Breach Exposes Sensitive Data and Raises Concerns Over Digital "
        "Privacy",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 13,
        /** modifiers */
        {{standard_deviation, 0.3}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 69,
        /** mutually_exclusive_events */ {},
        /** text */
        "Emergence of 5G Technology Revolutionizes Connectivity and Enables Faster "
        "Data Transfer",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 13,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 70,
        /** mutually_exclusive_events */ {},
        /** text */
        "Failure of Major Tech Infrastructure Disrupts Services and Causes Widespread "
        "Outages",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 13,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -4}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 71,
        /** mutually_exclusive_events */ {},
        /** text */
        "Advancements in Quantum Computing Unlock New Possibilities for Solving "
        "Complex Problems",
        /** duration */ 7,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 13,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 72,
        /** mutually_exclusive_events */ {},
        /** text */
        "Rapid Advancements in Augmented Reality (AR) and Virtual Reality (VR) Enhance "
        "User Experiences",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 13,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 73,
        /** mutually_exclusive_events */ {},
        /** text */
        "Advancements in Robotics and Automation Transform Manufacturing and Increase "
        "Efficiency",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 13,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 74,
        /** mutually_exclusive_events */ {},
        /** text */
        "Emergence of Artificial General Intelligence (AGI) Raises Ethical and "
        "Societal Concerns",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 13,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    // event_id 75 to 79 affect category "RealEstate"
    {
        /** event_id */ 75,
        /** mutually_exclusive_events */ {76},
        /** text */
        "Strong Demand and Low Mortgage Rates Drive Real Estate Market Growth",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 14,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 76,
        /** mutually_exclusive_events */ {75},
        /** text */
        "Economic Downturn Leads to Decline in Real Estate Prices and Sales",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 14,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 77,
        /** mutually_exclusive_events */ {},
        /** text */
        "Rapid Urbanization and Infrastructure Development Boost Real Estate "
        "Investments",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 14,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 78,
        /** mutually_exclusive_events */ {},
        /** text */
        "Natural Disasters Cause Property Damage and Impact Real Estate Market",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 14,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 79,
        /** mutually_exclusive_events */ {},
        /** text */
        "Investigation Reveals Widespread Cases of Substandard Construction Projects",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 14,
        /** modifiers */
        {{standard_deviation, 0.12}, {mean, -4}, {lower_limit, -20}, {upper_limit, 0}},
    },
    // event_id 80 to 85 affect category "RealEstate"
    {
        /** event_id */ 80,
        /** mutually_exclusive_events */ {},
        /** text */
        "Shift in Consumer Behavior Leads to Decline in Brick-and-Mortar Retail Stores",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 15,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 81,
        /** mutually_exclusive_events */ {},
        /** text */
        "Adoption of Technology Enhances Customer Experience in Physical Retail Stores",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 15,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 82,
        /** mutually_exclusive_events */ {},
        /** text */
        "Integration of Augmented Reality Enhances In-Store Shopping Experience",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 15,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 83,
        /** mutually_exclusive_events */ {},
        /** text */
        "Increase in Online Counterfeit Products Impacts Consumer Trust in E-commerce",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 15,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 84,
        /** mutually_exclusive_events */ {},
        /** text */
        "Retailers Embrace Sustainable Practices, Driving Eco-friendly Consumer "
        "Choices",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 15,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 85,
        /** mutually_exclusive_events */ {},
        /** text */ "Supply Chain Disruptions Impact Retail Inventory and Availability",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 15,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    // event_id 86 to __ affect category "Telecom"
    {
        /** event_id */ 86,
        /** mutually_exclusive_events */ {},
        /** text */
        "Deployment of 5G Networks Enables Faster and More Reliable Connectivity",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 16,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 5}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 87,
        /** mutually_exclusive_events */ {},
        /** text */
        "Cybersecurity Breach in Telecom Networks Raises Concerns over Data Privacy",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 16,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 88,
        /** mutually_exclusive_events */ {},
        /** text */
        "Advancements in Voice Recognition Technology Enhance Telecommunication "
        "Services",
        /** duration */ 6,
        /** percentage_permille */ 12,
        /** type_of_event */ category,
        /** category */ 16,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, 6}, {lower_limit, 0}, {upper_limit, 20}},
    },
    {
        /** event_id */ 89,
        /** mutually_exclusive_events */ {},
        /** text */
        "Network Outage Disrupts Telecommunication Services in Several Regions",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 16,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 90,
        /** mutually_exclusive_events */ {},
        /** text */
        "Telecom Service Outage Caused by Natural Disaster Disrupts Communication",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 16,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    {
        /** event_id */ 91,
        /** mutually_exclusive_events */ {},
        /** text */
        "Telecom Regulatory Changes Affect Pricing and Service Plans for Consumers",
        /** duration */ 7,
        /** percentage_permille */ 10,
        /** type_of_event */ category,
        /** category */ 16,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -5}, {lower_limit, -15}, {upper_limit, 0}},
    },
    // event_id 92 to 98 affect pick_random_stock
    {
        /** event_id */ 92,
        /** mutually_exclusive_events */ {},
        /** text */ "Leadership Change: CEO Resigns, New CEO Appointed",
        /** duration */ 3,
        /** percentage_permille */ 10,
        /** type_of_event */ pick_random_stock,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.2}, {mean, 0}, {lower_limit, -15}, {upper_limit, 15}},
    },
    {
        /** event_id */ 93,
        /** mutually_exclusive_events */ {},
        /** text */
        "Labor Strike: Employees Go on Strike Demanding Better Working Conditions",
        /** duration */ 3,
        /** percentage_permille */ 12,
        /** type_of_event */ pick_random_stock,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -6}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 94,
        /** mutually_exclusive_events */ {97},
        /** text */ "Acquires a Competitor, Expands Market Presence",
        /** duration */ 4,
        /** percentage_permille */ 10,
        /** type_of_event */ pick_random_stock,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.2}, {mean, 5}, {lower_limit, 0}, {upper_limit, 15}},
    },
    {
        /** event_id */ 95,
        /** mutually_exclusive_events */ {98},
        /** text */ "Market Slump Leads to Business Contraction",
        /** duration */ 4,
        /** percentage_permille */ 10,
        /** type_of_event */ pick_random_stock,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.3}, {mean, -7}, {lower_limit, -20}, {upper_limit, 0}},
    },
    {
        /** event_id */ 96,
        /** mutually_exclusive_events */ {},
        /** text */ "Regulatory Non-Compliance: Fails to Meet Environmental Standards",
        /** duration */ 5,
        /** percentage_permille */ 10,
        /** type_of_event */ pick_random_stock,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.1}, {mean, -2}, {lower_limit, -10}, {upper_limit, 0}},
    },
    {
        /** event_id */ 97,
        /** mutually_exclusive_events */ {94, 98},
        /** text */ "Faces Bankruptcy, Forced to Cease Operations",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ pick_random_stock,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.5}, {mean, -9}, {lower_limit, -30}, {upper_limit, 0}},
    },
    {
        /** event_id */ 98,
        /** mutually_exclusive_events */ {95, 97},
        /** text */ "Opens New Branches in Multiple Locations",
        /** duration */ 6,
        /** percentage_permille */ 10,
        /** type_of_event */ pick_random_stock,
        /** category */ 0,
        /** modifiers */
        {{standard_deviation, 0.5}, {mean, 7}, {lower_limit, 0}, {upper_limit, 20}},
    },
};

// print a map
void print_map(const std::map<unsigned int, std::vector<unsigned int>> & map) {
    for (const auto & i : map) {
        std::cout << i.first << ": ";
        for (unsigned int j : i.second) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

/*
int main() {
    // This outputs 0.1
    std::cout << all_stock_events[0].modifiers[standard_deviation] << std::endl;
    // Checks the events for mutual exclusivity
    print_map(check_mutual_exclusivity(all_stock_events));
    // Outputs:
    // 0: 2
    // 1: 2
    // 2:
    return 0;
}
*/

mutuallyExclusiveMap build_mutual_exclusivity_map(
    const std::vector<Stock_event> & all_events) {
    mutuallyExclusiveMap mut_excl_map;
    // Build the map
    for (unsigned int i = 0; i < all_events.size(); i++) {
        for (unsigned int j = 0; j < all_events[i].mutually_exclusive_events.size();
             j++) {
            mut_excl_map[all_events[i].event_id].emplace_back(
                all_events[i].mutually_exclusive_events[j]);
        }
    }
    return mut_excl_map;
}

mutuallyExclusiveMap check_mutual_exclusivity(
    const std::vector<Stock_event> & all_events) {
    mutuallyExclusiveMap mut_excl_map = build_mutual_exclusivity_map(all_events);

    // If two events are mutually exclusive, they should be in each other's list.
    // Remove such two events from the map.
    // E.g. {0: [1,2], 1: [0], 2:[]} -> {0: [2]}
    // In this case, 2 does not state that it is mutually exclusive with 0.
    for (const auto & i : mut_excl_map) {
        for (unsigned int j : i.second) {
            if (std::find(mut_excl_map[j].begin(), mut_excl_map[j].end(), i.first) !=
                mut_excl_map[j].end()) {
                mut_excl_map[i.first].erase(std::remove(mut_excl_map[i.first].begin(),
                                                mut_excl_map[i.first].end(), j),
                    mut_excl_map[i.first].end());
                mut_excl_map[j].erase(std::remove(mut_excl_map[j].begin(),
                                          mut_excl_map[j].end(), i.first),
                    mut_excl_map[j].end());
            }
        }
    }
    return mut_excl_map;
}

bool assertion_check_mutual_exclusivity(void) {
    /// @todo: put assertion_check_uniq_events into a separate file, e.g. tests.cpp
    // Assert that the every key has no value.
    auto checkEventResult = check_mutual_exclusivity(all_stock_events);
    for (const auto & [key, value] : checkEventResult) {
        // If the assertion is raised, print the checkEventResult and exit the
        // program.
        if (!value.empty()) {
            std::cout << "Error: detected mutual exclusivity violation! Details:"
                      << std::endl;
            print_map(checkEventResult);
            return true;
        }
    }
    return false;
}

std::vector<Stock_event> pick_events(
    const std::vector<Stock_event> & all_events, unsigned int num_events) {
    std::vector<Stock_event> picked_events;
    unsigned int total_permille = 0;
    /// @todo Optimize this loop so that we don't have to calculate the total_permille
    /// every time we pick an event.
    for (const Stock_event & event : all_events) {
        total_permille += event.probability_permille;
    }
    // Pick num_events random events
    for (unsigned int i = 0; i < num_events; i++) {
        unsigned int _total_permille = total_permille;
        /** When picking the event, consider event.probability_permille.
         * E.g. if there are 3 events with probability_permille 10, 20, 30.
         * total_permille = 60;
         * random_permille = 0 to 59;
         * If random_permille is 0 to 9, pick the first event;
         * If random_permille is 10 to 29, pick the second event;
         * If random_permille is 30 to 59, pick the third event.
         */
        unsigned int random_permille = random_integer(_total_permille);
        for (const Stock_event & event : all_events) {
            _total_permille -= event.probability_permille;
            if (_total_permille <= random_permille) {
                picked_events.emplace_back(event);
                break;
            }
        }
    }
    return uniq_events(picked_events, all_stock_events);
}

std::vector<Stock_event> uniq_events(std::vector<Stock_event> picked_events,
    const std::vector<Stock_event> & all_events) {
    mutuallyExclusiveMap mut_excl_map = build_mutual_exclusivity_map(all_events);

    unsigned int first = 0;
    while (first < picked_events.size()) {
        unsigned int second = first + 1;
        while (second < picked_events.size()) {
            const bool isRandomStockEvents =
                picked_events[first].type_of_event == pick_random_stock;
            const bool isIdenticalEvents =
                picked_events[first] == picked_events[second];

            if (!isRandomStockEvents && isIdenticalEvents) {
                picked_events.erase(picked_events.begin() + second);
                continue;
            }

            const bool areMutuallyExclusiveEvents =
                std::find(mut_excl_map[picked_events[first].event_id].begin(),
                    mut_excl_map[picked_events[first].event_id].end(),
                    picked_events[second].event_id) !=
                mut_excl_map[picked_events[first].event_id].end();

            if (areMutuallyExclusiveEvents) {
                picked_events.erase(picked_events.begin() + second);
                continue;
            }

            second++;
        }
        first++;
    }
    return picked_events;
}

void assertion_check_uniq_events(void) {
    /// @todo: put assertion_check_uniq_events into a separate file, e.g. tests.cpp
    Stock_event craftedEvent = Stock_event{
        /* event_id */ 0,
        /* mutually_exclusive_events */ {1},
        /* text */ "Crafted Event",
        /* duration */ 1,
        /* percentage_permille */ 0,
        /* type_of_event */ pick_random_stock,
        /* category. Assign this to zero first. */ 0,
        /* modifiers */
        {{standard_deviation, 0}, {mean, 0}, {lower_limit, 0}, {upper_limit, 0}},
    };
    Stock_event craftedEvent_2 = craftedEvent;
    Stock_event craftedEvent_3 = Stock_event{
        /* event_id */ 1,
        /* mutually_exclusive_events */ {0},
        /* text */ "Crafted Event",
        /* duration */ 1,
        /* percentage_permille */ 0,
        /* type_of_event */ all_stocks,
        /* category. Assign this to zero first. */ 0,
        /* modifiers */
        {{standard_deviation, 0}, {mean, 0}, {lower_limit, 0}, {upper_limit, 0}},
    };
    std::vector<Stock_event> picked_events = {
        craftedEvent, craftedEvent_2, craftedEvent_3};
    std::vector<Stock_event> uniqEvents = uniq_events(picked_events, picked_events);

    std::cout << uniqEvents.size() << std::endl;
    if (!(uniqEvents.size() == 2)) {
        std::cout << uniqEvents.size() << std::endl;
        assert(false &&
               "Detected duplicate/mutually-exclusive events after uniq_events()");
    }
}

Stock_event getStockSplitEvent(void) {
    return Stock_event{
        /* event_id */ 65535,
        /* mutually_exclusive_events */ {},
        /* text */
        " has rised too high and the company has decide a stock split on it.",
        /* duration */ 1,
        /* percentage_permille */ 0,
        /* type_of_event */ pick_random_stock,
        /* category. Assign this to zero first. */ 0,
        /* modifiers*/
        {{standard_deviation, 0}, {mean, 0}, {lower_limit, 0}, {upper_limit, 0}},
    };
}
