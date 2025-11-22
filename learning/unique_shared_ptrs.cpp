# include <iostream>
# include <vector>
# include <memory>

using namespace std;

class CallPayOff{
    double price;

public:
    explicit CallPayOff(double x) : price(x){
        cout << "CallPayoff created with strike " << price << "\n";
    }
    double operator()(double spot) const{
        return max(spot - price, 0.0);
    }

    // destructor called
    ~CallPayOff(){
        cout << "CallPayoff destroyed\n";
    }
};

class LiveMktData{
    string instrument;

public:
    explicit LiveMktData(const string &name) : instrument(name){
        cout << "Live market data stream started for " << instrument << "\n";
    }
    double getPrice() const {
        return 82.5;
    }

    //destructor called
    ~LiveMktData(){
        cout << "LiveMktData destroyed\n";
    }
};

int main(){
    auto call_pay_off = make_unique<CallPayOff>(75.0);
    auto live_market_data = make_shared<LiveMktData>("Electricity bills");

    {
        shared_ptr<LiveMktData> shared = live_market_data;
        cout << "Price from shared market data : " << shared -> getPrice() <<  "\n";
        cout << "Shared pointer count inside scope: " << live_market_data.use_count() << "\n";
    }
    cout << "Shared pointer count after scope : " << live_market_data.use_count() <<  "\n";

    double payoff = (*call_pay_off)(80.0);
    cout << "Call payoff at spot 80 = " << payoff << "\n";

    return 0;
}
