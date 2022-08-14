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
    Paytype pt = Paytype::CALL;                      //'Payoff type call or put'

    MonteCarlo mcp = MonteCarlo(timeperiod,volatility,initPrice,rate,strike,pt,n_samples);
    std::cout<<mcp.getOptionPrice()<<std::endl;

    for(auto x: mcp.seeds){
        std::cout<<x<<" ";
    }

    return 0;
}