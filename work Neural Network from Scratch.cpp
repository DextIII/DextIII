#include <vector>
#include <cmath>
#include <random>
#include <iostream>

class NeuralNetwork {
private:
    std::vector<std::vector<double>> weights1, weights2;
    std::vector<double> bias1, bias2;
    std::mt19937 rng;
    
    double sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }
    double sigmoid_derivative(double x) { return x * (1.0 - x); }
    
public:
    NeuralNetwork(int inputs, int hidden, int outputs) : rng(std::random_device{}()) {
        weights1.resize(inputs, std::vector<double>(hidden));
        weights2.resize(hidden, std::vector<double>(outputs));
        bias1.resize(hidden);
        bias2.resize(outputs);
        
        std::normal_distribution<double> dist(0.0, 1.0);
        for (auto& row : weights1) for (auto& w : row) w = dist(rng);
        for (auto& row : weights2) for (auto& w : row) w = dist(rng);
        for (auto& b : bias1) b = dist(rng);
        for (auto& b : bias2) b = dist(rng);
    }
    
    std::vector<double> predict(const std::vector<double>& input) {
        std::vector<double> hidden;
        for (int i = 0; i < weights1[0].size(); i++) {
            double sum = bias1[i];
            for (int j = 0; j < input.size(); j++) {
                sum += input[j] * weights1[j][i];
            }
            hidden.push_back(sigmoid(sum));
        }
        
        std::vector<double> output;
        for (int i = 0; i < weights2[0].size(); i++) {
            double sum = bias2[i];
            for (int j = 0; j < hidden.size(); j++) {
                sum += hidden[j] * weights2[j][i];
            }
            output.push_back(sigmoid(sum));
        }
        return output;
    }
    
    void train(const std::vector<std::vector<double>>& X, 
               const std::vector<std::vector<double>>& y, int epochs) {
        double learning_rate = 0.1;
        for (int epoch = 0; epoch < epochs; epoch++) {
            for (size_t i = 0; i < X.size(); i++) {
                auto output = predict(X[i]);
                
            }
        }
    }
};

int main() {
    NeuralNetwork nn(2, 4, 1);
    std::vector<std::vector<double>> X = {{0,0}, {0,1}, {1,0}, {1,1}};
    std::vector<std::vector<double>> y = {{0}, {1}, {1}, {0}};
    nn.train(X, y, 1000);
    
    std::cout << "?? XOR Results:\n";
    for (auto& input : X) {
        auto result = nn.predict(input);
        std::cout << input[0] << "," << input[1] << " -> " << result[0] << "\n";
    }
    return 0;
}
