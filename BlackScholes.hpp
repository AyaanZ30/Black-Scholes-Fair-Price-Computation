# ifndef BLACKSCHOLES_HPP
# define BLACKSCHOLES_HPP

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <functional>
#include <algorithm>

using namespace std;

const double PI = 3.14159265358979323846;

class BlackScholes;

enum class Payoff{
    Call = 1,
    Put = -1
};

class BlackScholes
{
    public:
        BlackScholes(double strike, double spot, double time_to_exp, 
        double rate, Payoff payoff_type, double div = 0.0);

        double operator()(double vol); 
    
    private:
        array<double, 2> compute_norm_args_(double vol) {
            double d1 = (log(spot_ / strike_) + (rate_ - div_ + 0.5 * vol * vol) * time_to_exp_) / (vol * sqrt(time_to_exp_));
            double d2 = d1 - (vol * sqrt(time_to_exp_));
            return {d1, d2};
        }; 
        
        // Data members
        double strike_, spot_, time_to_exp_;
        Payoff payoff_type_;
        double rate_, div_;
};

double implied_volatility_with_lambda(BlackScholes &bScholes, double opt_market_price, 
                                      double x0, double x1, double tol, unsigned int max_iter);


#endif 