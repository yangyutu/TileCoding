
#include "TileCoding.h"

using namespace ReinforcementLearning;

TileCoding::TileCoding(int numTilings0, std::vector<double> generalization0, int dim) {
    numTilings = numTilings0;
    generalizations = generalization0;
    stateDim = dim;
    for (int i = 0; i < stateDim; i++) {
        offset.push_back(2 * i + 1);
        quantizer.push_back(generalizations[i] / numTilings);
    }
}
double TileCoding::predict(std::vector<double> input) {
    std::vector<std::vector<int>> coord = this->quantize(input);
    double prediction = 0.0;

    for(auto& it: coord){
        if (weights.find(it) != weights.end()) {
            prediction += this->weights[it];
        } else {
            this->weights[it] = 0.0;
        }
    }
    return prediction;
}

double TileCoding::learn(double learningRate, const std::vector<double>& input, const double& target) {
    std::vector<std::vector<int>> coord = this->quantize(input);
    learningRate /= this->numTilings;
    double error = target - this->predict(input);
    for(auto& it: coord){
        this->weights[it] += learningRate * error;
    }
    return error*error;
}

std::vector<std::vector<int>> TileCoding::quantize(const std::vector<double>& input) const {
    std::vector<std::vector<int>> coord;
    for (int tileIdx = 0; tileIdx < numTilings; tileIdx++) {
        coord.push_back(std::vector<int>());
        for (int i = 0; i < input.size(); i++) {
            int idx = (int) std::floor((input[i] / this->quantizer[i]));
            int coordinate;
            if (idx >= offset[i]){
                coordinate = idx - ((idx - offset[i])%numTilings);
            } else {
                coordinate = idx + 1 + ((offset[i] - idx - 1)%numTilings) - numTilings;
            }
            
            coord[tileIdx].push_back(coordinate);
        }
        coord[tileIdx].push_back(tileIdx);
    }
    return coord;
}

void TileCoding::outputWeight() const{
    int count = 0;
    for (auto const &ent: this->weights){
        for (auto const &vecElem: ent.first){
            std::cout << vecElem << "\t";
        }
        std::cout << ":" << ent.second << std::endl;
        count++;
    }

    std::cout << "total number of key-values: " << count << std::endl;

}

