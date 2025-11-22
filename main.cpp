# include "BlackScholes.hpp"
# include <iostream>
# include <cmath>


int main(){
    double strike = 95.0;
    double mkt_opt_price = 6.2; // Current option price quoted in the market
    auto payoff_type = Payoff::Call;
    double spot = 100.0;
    double rate = 0.05;
    double dividend = 0.07;
    double time_to_exp = 0.25;

    // Can also inclide IO for dynamic input
    BlackScholes bsc{strike, spot, time_to_exp, rate, payoff_type, dividend};
    double init_volatility_guess_1 = 0.1;
    double init_volatility_guess_2 = 0.15;

    double tol = 1e-6;
    unsigned int max_iter = 1000;

    // double value = bsc_itm_exp(vol);
    double impl_vol = implied_volatility_with_lambda(bsc, mkt_opt_price, init_volatility_guess_1, init_volatility_guess_2, tol, max_iter);
    
    if(!std::isnan(impl_vol)){
        cout << "[Call] ITM, time to expiration = " << time_to_exp << endl;
        cout << "Implied vol = " << impl_vol;
        double opt_val = bsc(impl_vol);
        cout << "Value of option at implied vol = " << opt_val;
        cout << "Market option price = " << mkt_opt_price;

    }else{
        cout << "No convergence to implied volatility\n";    // throw exception
    }
}