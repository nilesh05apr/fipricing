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



int main(){
    return 0;
}