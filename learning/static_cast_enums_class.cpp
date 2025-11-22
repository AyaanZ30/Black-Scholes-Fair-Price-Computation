# include <iostream>
# include <vector>
# include <memory>

using namespace std;

enum class Tracks{
    Interlagos,
    Spa_Francorchamps,
    Circuit_de_Monaco,
    Marina_Bay
};
enum class Winners{
    Lewis,
    Max,
    Leclerc,
    Russell
};

string to_string(Winners w){
    switch(w){
        case Winners::Lewis: return "Lewis Hamilton";
        case Winners::Max: return "Max Verstappen";
        case Winners::Russell: return "George Russell";
        case Winners::Leclerc: return "Charles Leclerc";
        default: return "Unknown Winner";
    }
}
string to_string(Tracks t){
    switch (t) {
        case Tracks::Interlagos:         return "Interlagos";
        case Tracks::Spa_Francorchamps:  return "Spa-Francorchamps";
        case Tracks::Circuit_de_Monaco:  return "Circuit de Monaco";
        case Tracks::Marina_Bay:         return "Marina Bay";
        default:                         return "Unknown Track";
    }
}
void scoped_enum(Tracks t, Winners w){
    cout << to_string(w) << "was the winner at" << to_string(t) << "!\n";
}

int main(){
    scoped_enum(Tracks::Circuit_de_Monaco, Winners::Leclerc);
    scoped_enum(Tracks::Interlagos, Winners::Lewis);
    scoped_enum(Tracks::Spa_Francorchamps, Winners::Max);
    scoped_enum(Tracks::Marina_Bay, Winners::Russell);

    return 0;
}