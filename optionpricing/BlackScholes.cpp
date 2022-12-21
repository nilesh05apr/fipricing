#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<future>
#include<ctime>
#include<limits>
#include<random>


using namespace std;
using std::normal_distribution;
using std::mt19937_64;

enum Paytype {
    CALL,
    PUT
};

double stdNormalGeneration(double seed){
    mt19937_64 mtre(seed);
    normal_distribution<> stnd;
    return stnd(mtre);
}

double payoffPrice(double Nd1, double Nd2, double S, double K, double r, double T, Paytype pt){
    switch(pt){
        case CALL: return S*Nd1 - K*exp(-r*T)*Nd2; break;
        case PUT: return K*exp(-r*T)*(1 - Nd2) - S*(1 - Nd1); break;
        default: return 0.0; break;
    }
    
}

double BlackScholes(double S, double K, double r, double sigma, double T, Paytype paytype){
    double d1 = (log(S/K) + (r + sigma*sigma/2)*T)/(sigma*sqrt(T));
    double d2 = d1 - sigma*sqrt(T);
    double Nd1 = 0.5*(1 + erf(d1/sqrt(2)));
    double Nd2 = 0.5*(1 + erf(d2/sqrt(2)));
    return payoffPrice(Nd1, Nd2, S, K, r, T, paytype);
}

int main(){
    double S = 100; //current price of the underlying
    double K = 100; //strike price of the option
    double r = 0.05; //risk-free interest rate
    double sigma = 0.2; //volatility of the underlying
    double T = 1; //time to maturity of the option
    Paytype paytype = CALL;
    double price = BlackScholes(S, K, r, sigma, T, paytype);
    cout << "The price of the option is " << price << endl;

    return 0;
}
