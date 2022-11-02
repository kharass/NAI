#include <iostream>
#include <utility>
#include <vector>
#include <random>

using namespace std;

random_device rd;
mt19937 mt_generator(rd());
int index = 22637;

pair<double, double> toPhenotype(vector<int> chromosomes) {
    double x, y = 0.0;

    for (int i = 0; i < chromosomes.size() / 2; i++) {
        x = x * 2 + chromosomes[i];
    }

    for (int i = (int) chromosomes.size() / 2; i < chromosomes.size(); i++) {
        y = y * 2 + chromosomes[i];
    }

    x = x / pow(2.0, (chromosomes.size() / 2 - 4)) - 8;
    y = y / pow(2.0, (chromosomes.size() / 2 - 4)) - 8;

    return {x, y};
}

auto three_hump_camel_function = [](pair<double, double> pair) {
    double x = pair.first;
    double y = pair.second;

    return 2 * pow(x, 2) - 1.05 * pow(x, 4) + pow(x, 6)/6 + x*y + pow(y, 2);
};


double fitness(vector<int> chromosomes) {
    return 1.0 / (1.0 + abs(three_hump_camel_function(toPhenotype(std::move(chromosomes)))));
}


vector<vector<int>> generate_genotype(int size) {
    vector<vector<int>> genotype;
    vector<int> chromosomes;

    for (int i = 0; i < size; ++i) {
        chromosomes.clear();

        for (int j = 0; j < size ; ++j) {
            uniform_int_distribution<int> uni(0, 1);
            chromosomes.push_back(uni(mt_generator));
        }

        genotype.push_back(chromosomes);
    }

    return genotype;
}

void showCTX(double x, double y, double maximized){
    cout << "X: " << x << "\nY: " << y << "\nMaksymalizacja: " << maximized <<"\n"<< endl;
}

int main() {
    int genotypeFromIndex = 100 + (index % 10) * 2;

    for (auto &element: generate_genotype(genotypeFromIndex)) {
        auto decoded = toPhenotype(element);
        showCTX(decoded.first, decoded.second, fitness(element));
    }

    return 0;
}