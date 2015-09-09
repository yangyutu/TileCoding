
#include "TileCoding.h"

using namespace ReinforcementLearning;

TileCoding::TileCoding(int numTilings0, std::vector<double> quantizer0, int dim){
	numTilings = numTilings0;
	quantizer = quantizer0;
        stateDim = dim;
        for (int i = 0; i < numTilings; i++){
            std::unordered_map<std::vector<int>, double> map;
            this->weights.push_back(map);
        }
        
        for (int i = 0; i < stateDim; i++) {
            offset.push_back(2*i+1);
        }
        
}
double TileCoding::predict(std::vector<double> input){
	std::vector<std::vector<int>> coord = this->quantize(input);	
	double prediction = 0.0;
	for (int tileIdx = 0; tileIdx < numTilings; tileIdx++){
            if (weights[tileIdx].find(coord[tileIdx]) != weights[tileIdx].end()){	
       		prediction += this->weights[tileIdx].at(coord[tileIdx]);
            } else {
                this->weights[tileIdx][coord[tileIdx]] = 0.0;
            }
	}
//        prediction /= numTilings;
	return prediction;
}

double TileCoding::learn(double learningRate, const std::vector<double>& input, const double& target) {
    std::vector<std::vector<int>> coord = this->quantize(input);
    std::vector<double> inputTemp(2);
//    inputTemp[0] = 0.0;
//    inputTemp[1] = 0.0;
//    std::vector<std::vector<int>> coordTemp = this->quantize(inputTemp);
    
    learningRate /= this->numTilings;
    double error = target - this->predict(input);
    for (int tileIdx = 0; tileIdx < numTilings; tileIdx++) {
        this->weights[tileIdx].at(coord[tileIdx]) += learningRate * error;
    }
    return error*error;
}

std::vector<std::vector<int>> TileCoding::quantize(const std::vector<double>& input) const {
    std::vector<std::vector<int>> coord;
    for (int tileIdx = 0; tileIdx < numTilings; tileIdx++) {
        coord.push_back(std::vector<int>(input.size()));
        for (int i = 0; i < input.size(); i++) {
            int idx = std::round((input[i] / this->quantizer[i]));
            idx -= (idx - tileIdx) % numTilings;
            coord[tileIdx].push_back(idx);
        }
        coord[tileIdx].push_back(tileIdx);
    }
    return coord;
}

