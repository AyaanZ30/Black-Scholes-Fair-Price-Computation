# include "BlackScholes.hpp"
# include <stdexcept>


BlackScholes::BlackScholes(double strike, double spot, double time_to_exp, 
double rate, Payoff payoff_type, double div) : strike_{strike}, spot_{spot}, time_to_exp_{time_to_exp}, rate_{rate}, payoff_type_{payoff_type}, div_{div} {}


double BlackScholes::operator()(double vol){      // core overloaded function
const int phi = static_cast<int>(payoff_type_);

if(time_to_exp_ > (double)(0.0)){
    auto norm_args = compute_norm_args_(vol);

    double d1 = norm_args[0];
    double d2 = norm_args[1];

    function<double(double)> norm_cdf = [&norm_cdf](double x){
        if(x < 0){
            return (1.0 - norm_cdf(-x));
        }
        double k = 1.0 / (1.0 + 0.2316419 * x);
        double poly = k * (0.319381530 + k * (-0.356563782 + 
                    k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));
        return 1.0 - (1.0 / sqrt(2.0 * PI)) * exp(-0.5 * x * x) * poly;
    };
    auto n_d1 = norm_cdf(phi * d1);
    auto n_d2 = norm_cdf(phi * d2);
    double disc_fctr = exp(-rate_ * time_to_exp_);

    return (phi * (spot_ * exp(-div_ * time_to_exp_) * n_d1 - strike_ * disc_fctr * n_d2));     
    }else return max(phi * (spot_ - strike_), 0.0);
}     


double implied_volatility_with_lambda(BlackScholes &bScholes, double opt_market_price, double x0, double x1, double tol, unsigned int max_iter){
    function<double(double)> diff = [&bScholes, opt_market_price](double volatility){
        return (bScholes(volatility) - opt_market_price);
    };
    // 2 initial guesses for volatility
    auto y0 = diff(x0);
    auto y1 = diff(x1); 

    double impl_vol = 0.0;
    unsigned int count_iter = 0;
    for(count_iter = 0 ; count_iter <= max_iter ; ++count_iter){
        // x0, x1 : store prev & updated volatility values 
        // y0, y1 : store prev & updated diff b/w volatility and option market values
        if(abs(x0 - x1) > tol){     // tolerance limit
            impl_vol = x1 -  (y1) * ((x1 - x0) / (y1 - y0));

            x0 = x1;
            x1 = impl_vol;
            y0 = y1;

            y1 = diff(x1);
        }else{
            return x1;
        }
    }
    return std::nan("");      // fails to converge
}

