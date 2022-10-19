#include <iostream>
#include <functional>
#include <vector>
#include <random>

using namespace std;

//void transform(char **pString, char **pString1, back_insert_iterator<vector<double>> iterator,
//               double (*pFunction)(const char *));

double beale(vector <double> xy) {
//   zakres -4.5, 4.5
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

vector<double> get_result(function<double(vector<double>)> f, double border_1, double border_2, int iterations){
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

int main(int argc, char **argv) {

    vector<double> my_result = get_result(himmel, -5.0, 5.0, 10000000);
    cout << my_result[0] << endl;
    cout << my_result[1] << endl;

    return 0;
}



