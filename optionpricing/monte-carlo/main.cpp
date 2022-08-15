#include<iostream>

#include "MonteCarlo.h"
#include "Paytype.h"

int main() {
    int timeperiod = 30;                    //30 days
    double volatility = 0.02;               //2% volatility
    double initPrice = 600.0;               // initial price of derivative (spot price)
    double rate = 0.06;                     //6% expected return rate
    int n_samples = 5000;
    double seed = time(nullptr);
    double strike = 650.0;                  // strike price of derivative
    Paytype pt = Paytype::CALL;             //'Payoff type call or put'
    int x;                      

    std::cout<<"---------------------------------------------------------------------"<<std::endl;
    std::cout<<"Enter Spot price of the asset: ";
    std::cin>>initPrice;
    std::cout<<"Enter Time to expiry in days: ";
    std::cin>>timeperiod;
    std::cout<<"Enter Volatility in decimals: ";
    std::cin>>volatility;
    std::cout<<"Enter Expected return rate in decimals: ";
    std::cin>>rate;
    std::cout<<"Enter Strike price of the option: ";
    std::cin>>strike;
    std::cout<<"Press 1 for CALL                          Press 0 for PUT";
    std::cin>>x;
    x == 1 ? pt = Paytype::CALL : pt = Paytype::PUT;

    MonteCarlo mcp = MonteCarlo(timeperiod,volatility,initPrice,rate,strike,pt,n_samples);
    std::cout<<mcp.getOptionPrice()<<std::endl;


    return 0;
}