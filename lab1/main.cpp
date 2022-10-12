#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using funkcja = std::function<double(std::vector<double>)>;
//funkcja ktora zwraca doubla, wektor przyjmuje doubla
//vector to dynamiczna tablica (pudełko na dane)

int main(int argc, char **argv) {
    using namespace std;
    map<string, funkcja> funkcje;
//mapa żeby stworzyc funkcje(formatery)
//** to wskaznik wskaznika

    funkcje["sin"] = [](vector<double> args){
        auto x = args.at(0);
        return sin(x);
    };

    funkcje["mod"] = [](vector<double> args) {
        double x = args.at(0);
        double y = args.at(1);
        return fmod(x, y);
    };

    funkcje["add"] = [](vector<double> args) {
        double x = args.at(0);
        double y = args.at(1);
        return x + y;
    };
    //ta sa nasze funkcje
    // n to są indeksy tych argumentów

    try {
        vector<string> argumenty(argv, argv + argc);
//przypisujemy argumenty temu wektorowi

        vector<double> values;
        transform(argv + 2, argv + argc,  std::back_inserter(values), [](const char* v){return std::stod(v);});
//ona przesuwa sie po wektorze o 2 argumenty ktore sa dalej niepozadane
//back_inserter wklada na koniec zamiast nadpisywac
//stod konwertuje stringa na double

        auto selected_f = argumenty.at(1);
//zwracam 1 argument i przypisuje do selected_f

        auto f = funkcje.at(selected_f);
//zwracam z listy funkcji wybrana przez uzytkownika funkcje i przypisuje do f

        auto c = f(values);
//przypisanie do c f(values)

        cout << "Rezultat dzialan: " << c << endl;
    }

    catch (std::out_of_range aor) {
        cout << "Podaj jakis argument. Dostepne to: ";
        for (auto [k, v] : funkcje) cout << " " << k;
        cout << endl;
    }
    return 0;
}