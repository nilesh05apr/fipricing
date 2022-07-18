#include<iostream>
#include<math.h>
using namespace std;


double bond(double C, double pv, double y, double n){
    C = C*pv;
    double ans = 0;
    for(int i = 1; i <= n; i++){
        ans += double(C/ pow((1+y),n));
    }
    return ans + double(pv/pow((1+y),n));
}


int main(){
    double coupon, par_value, time_to_maturity, yield_rate;

    cout<<"--------------------Bond price calculator------------------"<<endl;
    cout<<"Enter Par/ Face Value of the bond: "<<endl;
    cin>>par_value;
    cout<<"Enter coupon as percentage of Par/Face value in decimals (i.e, 8% == 0.08):"<<endl;
    cin>>coupon;
    cout<<"Enter time to maturity in years:"<<endl;
    cin>>time_to_maturity;
    cout<<"Yield Rate of the Bond in decimals (i.e, 8% == 0.08):"<<endl;
    cin>>yield_rate;

    cout<<"------------------------------------------------------------"<<endl;

    double bondprice = bond(coupon,par_value,yield_rate,time_to_maturity);
    cout<<"\t\t\tBond Price is: "<<bondprice<<endl;





    return 0;
}