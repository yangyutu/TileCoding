#include <iostream>
#include <cmath>
#include "TileCoding.h"

using namespace ReinforcementLearning;
void trainTileCoderSimpleFunc();
void trainTileCoderWaveFunc();
void testQuantization();
int main() {
    std::vector<int> m1(2),m2(2), m3(2), m4(2);
    m1[0] = 3;
    m1[1] = 2;
    m2[0] = 3;
    m2[1] = 2;
    m3[0] = 3;
    m3[1] = 4;
    m4[0] = 2;
    m4[1] = 3;
    
    
    std::unordered_map<std::vector<int>, double> map;
    map[m1] = 3;
    std::cout << map[m1] << std::endl;
    std::cout << map[m2] << std::endl;
    std::cout << map[m3] << std::endl;
    map[m2] = 1;
    map[m3] = 2;
    std::cout << map[m1] << std::endl;
    std::cout << map[m2] << std::endl;
    std::cout << map[m3] << std::endl;
 //   testQuantization();
//    trainTileCoderSimpleFunc();
    trainTileCoderWaveFunc();
    return 0;
}

void testQuantization(){
    std::vector<double> q(2);
    q[0] = 1;
    q[1] = 1;
    TileCoding tile(16, q, 2);
    int count = 0;
    double errorTotal;
    std::unordered_map<std::vector<int>, double> map;
         for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                std::vector<double> input(2);
                input[0] = 0.1 * i * 2.0 * M_PI;
                input[1] = 0.1 * j * 2.0 * M_PI;
                double val = sin(input[0]) + cos(input[1]);
                std::vector<std::vector<int>> coord = tile.quantize(input);
                for (auto const& it: coord){
                    for (auto const& it2: it){
                        std::cout << it2 << "\t";
                    }
                    map[it] = 0.0;
                    count++;
                    std::cout << std::endl;
                }
            }
        }
    std::cout << "there are totally:" << count << std::endl;
    
    count = 0;
    for (auto const &ent: map){
        for (auto const &vecElem: ent.first){
            std::cout << vecElem << "\t";
        }
        std::cout << ":" << ent.second << std::endl;
        count++;
    }

    std::cout << "total number of key-values: " << count << std::endl;
/*
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::vector<double> input(2);
            input[0] = 0.1 * i * 2.0 * M_PI;
            input[1] = 0.1 * j * 2.0 * M_PI;
            double val = sin(input[0]) + cos(input[1]);
            std::cout << input[0] << "\t" << input[1] << "\t" << val << "\t" << tile.predict(input) << std::endl;
        }
    }
    
    tile.outputWeight();
*/




}

void trainTileCoderSimpleFunc() {
    std::vector<double> q(2);
    q[0] = 0.2;
    q[1] = 0.2;
    TileCoding tile(8, q, 2);
    double errorTotal;
    for (int iter = 0; iter < 100; iter++) {
        errorTotal = 0.0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                double val = (i * i)*0.1 + (j * j)*0.1;
                std::vector<double> input(2);
                input[0] = 0.1 * i;
                input[1] = 0.1 * j;
                errorTotal += tile.learn(0.1, input, val);
            }
        }
        std::cout << errorTotal << std::endl;
    }


    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            double val = (i * i)*0.1 + (j * j)*0.1;
            std::vector<double> input(2);
            input[0] = 0.1 * i;
            input[1] = 0.1 * j;
            std::cout << input[0] << "\t" << input[1] << "\t" << val << "\t" << tile.predict(input) << std::endl;
        }
    }
}

void trainTileCoderWaveFunc() {
    std::vector<double> q(2);
    q[0] = 0.1;
    q[1] = 0.1;
    TileCoding tile(8, q, 2);
    double errorTotal;
    for (int iter = 0; iter < 100; iter++) {
        errorTotal = 0.0;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                std::vector<double> input(2);
                input[0] = 0.01 * i * 2.0 * M_PI;
                input[1] = 0.01 * j * 2.0 * M_PI;
                double val = sin(input[0]) + cos(input[1]);
                
                errorTotal += tile.learn(0.1, input, val);
            }
        }
        std::cout << errorTotal << std::endl;
    }


    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            std::vector<double> input(2);
            input[0] = 0.01 * i * 2.0 * M_PI;
            input[1] = 0.01 * j * 2.0 * M_PI;
            double val = sin(input[0]) + cos(input[1]);
            std::cout << input[0] << "\t" << input[1] << "\t" << val << "\t" << tile.predict(input) << std::endl;
        }
    }
    
    tile.outputWeight();
}
