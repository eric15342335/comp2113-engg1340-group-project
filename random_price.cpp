// code related to randomness
#include <cstdlib>
#include "random_price.h"
#include <iostream>
#include <random>

using namespace std;

double init_stock_price(int a){
	//Stock prices cluster in 3 tiers in our world: about 5 hkd (a=1) variating about 2 hkd; , 50 hkd(a=2) variating about 20 hkd, 
	//and 150 hkd(a=3)variating about 50 hkd (based on a very little sample observation of real world). 
	//If an invalid input we default a=1.
    	std::random_device rd;
	//std mt19937 Merssane Twister
	std::mt19937 gen(rd());
	//normal_distribution<double> distribution(5.0, 2.0);
	if(a==2){
		normal_distribution<double> distribution(50.0, 20.0);
		return distribution(gen);
		}
	else {
		if(a==3){
		normal_distribution<double> distribution(150.0, 50.0);
		return distribution(gen);
		}
	else{
		normal_distribution<double> distribution(5.0, 2.0);
		return distribution(gen);
		}
		}
    return 0.0;
}
double random_sd(float price){
	//s.d. usually 1%-5% of initial stock price; modelling with normal(0.03*init_price, 0.02*init_price)
	std::random_device rd;
	std::mt19937 gen(rd());
	normal_distribution<double> d(0.03*price, 0.02*price);
	return d(gen);

}	
double random_stock(float &mean, float &sd,float &upper_limit, float &lower_limit){
	//upper_limit and lower_limit are FRACTIONS of the mean so that it remains usable even for a rise 
	// or fall of large margin; unless changed manually. e.g. a 3% of the mean lower limit 
	//until mean price fall then lower_limit=0.03
	std::random_device rd;
    std::mt19937 gen(rd());
	normal_distribution<double> distribution(mean, sd);
	float price = distribution(gen);
	// for mean > temp i.e. falling prices
	if ((mean-price)>(lower_limit*mean)){
		mean=price;
	}
	//rising prices
	if ((price-mean)>(upper_limit*mean)){
		mean=price;
	}
	sd = random_sd(price);
	return price;
}
unsigned int random_integer(unsigned int max_integer) {
    // Return a random integer from 0 to max - 1
    return rand() % max_integer;
}
