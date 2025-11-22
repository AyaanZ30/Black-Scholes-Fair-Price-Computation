# include <iostream>
# include <vector>
# include <cmath>
# include <numbers>

using namespace std;

void hello_world(){
    auto f = []
    {
        cout << "Hello world" << "\n";
    };
    f();
}
auto g = [](double x, double y){
    return (double)(x + y);
};

int main(){
    hello_world();
    auto z = g(2.56, 7.86);
    cout << z;

    vector<double> u = {1.0, 1.5, 2.0, 2.5, 3.0, 3.5};
    double shift = 0.25;

    auto l = [&u, shift](double alpha) -> double
    {
        for(auto& x : u){
            x = ((x + shift) * alpha);
        }
        return 0;
    };
    
    l(-1.5);
    for(auto it = u.begin() ; it != u.end() ; ++it){
        cout << *it << " ";
    }

    
    return 0;
}