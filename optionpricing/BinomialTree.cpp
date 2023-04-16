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


double binomial_tree_price(double s, double k, double r, double sigma, double t, int n, char type) {
    double delta_t = t / n;
    double u = exp(sigma * sqrt(delta_t));
    double d = 1 / u;
    double p = (exp(r * delta_t) - d) / (u - d);

    vector<double> prices(n + 1);
    
    iota(prices.begin(), prices.end(), 0.0);
    
    transform(prices.begin(), prices.end(), prices.begin(), [&](double i) { return s * pow(u, n - i) * pow(d, i); });
    
    vector<double> values(n + 1);
    
    if (type == 'C') {
        transform(prices.begin(), prices.end(), values.begin(), [&](double price) { return max(0.0, price - k); });
    } else if (type == 'P') {
        transform(prices.begin(), prices.end(), values.begin(), [&](double price) { return max(0.0, k - price); });
    }
    
    for (int j = n - 1; j >= 0; j--) {
        transform(values.begin(), values.begin() + j + 1, values.begin() + 1, values.begin(), [&](double a, double b) { return exp(-r * delta_t) * (p * a + (1 - p) * b); });
        if (type == 'C') {
            transform(prices.begin(), prices.begin() + j + 1, values.begin(), values.begin(), [&](double price, double value) { return max(value, price - k); });
        } else if (type == 'P') {
            transform(prices.begin(), prices.begin() + j + 1, values.begin(), values.begin(), [&](double price, double value) { return max(value, k - price); });
        }
    }

    return values[0];
}

int main(){
    double s = 100; // underlying asset price
    double k = 90; // option strike price
    double r = 0.05; // risk-free interest rate
    double sigma = 0.2; // underlying asset volatility
    double t = 1; // time to expiration
    int n = 10; // number of time steps
    char type = 'C'; // option type ('C' for call, 'P' for put)
    double price = binomial_tree_price(s, k, r, sigma, t, n, type);
    cout << "Option price: " << price << endl;
    return 0;
}