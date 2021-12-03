#ifndef NEURONS_NEURONS_H
#define NEURONS_NEURONS_H

#include <vector>
#include <random>

namespace neurons {
class NeuralLayer;
class NeuralNetwork;
class Neuron {
    protected:
     double weight;
     double threshold;
     std::vector<double> inputs;
     std::vector<int> outputTargets;
     friend class neuralLayer;
     friend class NeuralNetwork;
};
class NeuralLayer {
    protected:
     std::vector<Neuron> neurons;
     std::uniform_int_distribution<int> distribution;
     friend class NeuralNetwork;
};
class NeuralNetwork {
    private:
     std::vector<NeuralLayer> layers;
     std::default_random_engine randomEngine;
     public:
      NeuralNetwork() {
          std::random_device seedGenerator;
          randomEngine = std::default_random_engine(seedGenerator());
       }
       NeuralNetwork& addLayer(int numNeurons);
       void operator()(double inputs[], double outputs[]);
};
}

#endif