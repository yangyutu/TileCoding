#include <iostream>
#include <vector>
#include <unordered_map>
#include <boost/functional/hash/hash.hpp>
#include <boost/functional/hash/extensions.hpp>

namespace std{
template<>
struct equal_to<std::vector<int>>{
    bool operator()(const std::vector<int> &s1, const std::vector<int> &s2) const{
	for (int i = 0; i < s1.size(); i++){
		if (s1[i] != s2[i]) return false;
	}
	return true;
    }
};

template<>
struct hash<std::vector<int>>{
    typedef std::vector<int> argument_type;
    typedef std::size_t result_type;
    result_type operator()(const argument_type& s) const{
    result_type h=boost::hash_value<argument_type>(s);
    return h;
    }
};
};


namespace ReinforcementLearning{

class TileCoding{
public:
	TileCoding(int numTilings0, std::vector<double> generation0, int);
	~TileCoding(){}
	double predict(std::vector<double> input);
	double learn(double learningRate, const std::vector<double>& input, const double& target);			
	std::vector<std::vector<int>> quantize(const std::vector<double>& input) const;
        void outputWeight() const;
private:
	int numTilings;
        int stateDim;
	std::vector<double> quantizer;
        std::vector<double> generalizations;
	std::vector<int> offset;        
        std::unordered_map<std::vector<int>, double> weights;

};
}
