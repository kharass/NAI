#include <iostream>
#include <functional>
#include <vector>
#include <random>
#include <string>

using namespace std;

double beale(vector <double> xy) {
//    zakres -4.5, 4.5
    double x = xy[0];
    double y = xy[1];
    double first_square = (1.5 - x - x*y)*(1.5 - x - x*y);
    double second_square = (2.25 - x - x*y*y)*(2.25 - x - x*y*y);
    double third_square = (2.625 - x - x*y*y*y)*(2.625 - x - x*y*y*y);
    return first_square + second_square + third_square;
}

double matyas(vector <double> xy){
//    zakres -10 , 10
    double x = xy[0];
    double y = xy[1];
    return 0.26*(x*x + y*y) - 0.48*x*y;
}

double himmel(vector <double> xy){
//    zakres -5 ,5
    double x = xy[0];
    double y = xy[1];
    return (x*x + y - 11.0)*(x*x + y - 11.0) + (x + y*y - 7.0)*(x + y*y - 7.0);
}

double rastrigin(vector <double> xy){
//    zakres -5.12, 5.12
    double x = xy[0];
    double y = xy[1];
    double A = 10.0;
    return A*2.0 + x*x - A*cos(2*M_PI*x) + y*y - A*cos(2*M_PI*y);
}

vector<double> metoda_pelnego_przegladu(function<double(vector<double>)> f, double border_1, double border_2, int iterations){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_real_distribution<double> distr(border_1, border_2);
    vector<double> closest_numbers = {distr(gen), distr(gen)};

    double result = f(closest_numbers);
    for(int u = 0; u < iterations; u++){
        vector<double> args = {distr(gen), distr(gen)};
        double new_result = f(args);
        if (new_result < result){
            result = new_result;
            closest_numbers = args;
        }
    }
    return closest_numbers;
}

vector<double> get_neighbor_hill(vector<double> ar) {
    double a = ar[0];
    double b = ar[1];
    random_device rd;
    mt19937 gen(rd()); // seed the generator
    uniform_real_distribution<double> distance(-0.005, 0.005);
    a = a + distance(gen);
    b = b + distance(gen);
    return {a, b};
}

vector<double> metoda_hill_climbing(function<double(vector<double>)> f, double border_1, double border_2, int iterations){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_real_distribution<double> distr(border_1, border_2);
    vector<double> closest_numbers = {distr(gen), distr(gen)};

    double result = f(closest_numbers);
    for(int u = 0; u < iterations; u++){
        vector<double> args = get_neighbor_hill(closest_numbers);
        if (args[0] > border_2 or args[0] < border_1 or args[1] > border_2 or args[1] < border_1){
            continue;
        }
        double new_result = f(args);
        if (new_result < result){
            result = new_result;
            closest_numbers = args;
        }
    }
    return closest_numbers;
}


vector<double> get_neighbour_wyzarzanie(vector<double> current_point){
    double a = current_point[0];
    double b = current_point[1];
    random_device rd;
    mt19937 gen(rd()); // seed the generator
    normal_distribution<double> distance;
    a = a + 0.01*distance(gen);
    b = b + 0.01*distance(gen);
    return {a, b};
}

vector<double> metoda_wyzarzania(function<double(vector<double>)> f, double border_1, double border_2, int iterations){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_real_distribution<double> distr(border_1, border_2);
    vector<double> closest_numbers = {distr(gen), distr(gen)};
    vector<double> args = {distr(gen), distr(gen)};
    double result = f(closest_numbers);
    vector<vector<double>> visited_points = {};

    for (int k = 0; k < iterations; k++){
        vector<double> neighbour = get_neighbour_wyzarzanie(closest_numbers);
        double new_result = f(neighbour);
        if (new_result < result){
            result = new_result;
            closest_numbers = neighbour;
        }
        else {
            uniform_real_distribution<double> rand(0, 1);
            double temp = new_result-result;
            if (temp < 0){
                temp = temp * -1;
            }
            double Tk = 10000.0/k;
            if (rand(gen) < exp(-1*temp)/Tk) {
                closest_numbers = neighbour;
            }
        }
    }


    for(int u = 0; u < iterations; u++){
        vector<double> args = {distr(gen), distr(gen)};
        double new_result = f(args);
        if (new_result < result){
            result = new_result;
            closest_numbers = args;
        }
    }
    return closest_numbers;
}


int main(int argc, char **argv) {
    vector<double> my_result = metoda_pelnego_przegladu(rastrigin, -5.12, 5.12, 1000000);
    cout << "Metoda pelnego przegladu: " << endl;
    cout << my_result[0] << endl;
    cout << my_result[1] << "\n" << endl;

    vector<double> annealing_result = metoda_wyzarzania(rastrigin, -5.12, 5.12, 1000000);
    cout << "Wyzarzanie: " << endl;
    cout << annealing_result[0] << endl;
    cout << annealing_result[1] << "\n" << endl;

    vector<double> hill_climb_result = metoda_hill_climbing(rastrigin, -5.12, 5.12, 1000000);
    cout << "Hill climbing: " << endl;
    cout << hill_climb_result[0] << endl;
    cout << hill_climb_result[1] << "\n" << endl;

    return 0;
}