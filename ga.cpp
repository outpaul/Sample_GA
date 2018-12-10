#include <bits/stdc++.h>

using namespace std;

//Set the population size here
#define N 100

//Set the target string here. The more the characters in the string, the greater the total number of generations
string target = "Ahem! Who are you?";

string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890. !?,;-'\"\\/\n[]{}()*@#$^&_+=~";

class Individual {

public:
    string chromosome = "";
    int fitness;
    Individual(string chromosome) {
        this->chromosome = chromosome;
        fitness = calc_fitness();
    }
    Individual mate(Individual parent) {
        string child = "";
        for(int i = 0;i < target.size();i++) {
            int p = rand()%100;
            if(p < 45)
                child += chromosome[i];
            else if(p < 90)
                child += parent.chromosome[i];
            else
                child += mutate();
        }
        return Individual(child);
    }
    char mutate() {
        char temp = characters[rand()%characters.size()];
        return temp;
    }

private:
    int calc_fitness() {
        int fitness = 0;
        for(int i = 0;i < chromosome.length();i++)
            if(chromosome[i] != target[i])
                fitness++;
        return fitness;
    }
};

string gen_individual() {
    string temp = "";
    for(int i = 0;i < target.length();i++)
        temp += characters[rand()%characters.size()];

    return temp;
}

bool compare(Individual one, Individual two) {
    return one.fitness<two.fitness;
}

int main() {
    vector<Individual> population;

    for(int i = 0;i < N;i++)
        population.push_back(Individual(gen_individual()));
    int g = 0;
    while(true) {
        sort(population.begin(), population.end(), compare);
        g++;
        if(population[0].fitness == 0)
            break;
        cout << "GENERATION " << g << ": " << population[0].chromosome <<" Fitness = " << population[0].fitness << endl;
        vector<Individual> new_population;
        for(int i = 0;i < (N/10);i++)
            new_population.push_back(population[i]);
        for(int i = N/10;i < N;i++)
            new_population.push_back(population[rand()%50].mate(population[rand()%50]));

        population = new_population;
    }
    cout << "\n----------------------------------------------------------" << endl;
    cout <<  "GENERATION " << g << ": " << "String -> " << population[0].chromosome << endl;
    cout << "----------------------------------------------------------\n" << endl;
    return 0;
}
