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
     void randomize(std::default_random_engine& engine,
                    std::uniform_real_distribution<double>& distribution);
     void createConnections(int numConnections,
                            std::default_random_engine& engine,
                            std::uniform_int_distribution<int>& distribution);
     double operator()();
     void mutateConnection(std::default_random_engine& engine,
                           std::uniform_int_distribution<int>& distribution);
     friend class NeuralLayer;
     friend class NeuralNetwork;
};
class NeuralLayer {
    protected:
     std::vector<Neuron> neurons;
     std::uniform_int_distribution<int> intDistribution;
     std::uniform_real_distribution<double> realDistribution;
     int numNeurons;
     void randomize(std::default_random_engine& engine);
     void connect(std::default_random_engine& engine, NeuralLayer& other);
     NeuralLayer(int numNeurons) : numNeurons(numNeurons) {
       intDistribution = std::uniform_int_distribution<int>(0, numNeurons - 1);
       realDistribution = std::uniform_real_distribution<double>(0, 1);
     }
     void mutate(std::default_random_engine& engine);
     void mutate(std::default_random_engine& engine, NeuralLayer& nextLayer);
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
       NeuralNetwork& connect();
       void operator()(double* inputs, double* outputs);
       void mutate();
};
}

#endif