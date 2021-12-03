#include "neurons.h"

using std::default_random_engine;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::vector;

namespace neurons {
    void Neuron::randomize(default_random_engine& engine, uniform_real_distribution<double>& distribution) {
      this->weight = distribution(engine);
      this->threshold = distribution(engine);
    }
    void Neuron::createConnections(int numConnections, std::default_random_engine& engine, std::uniform_int_distribution<int>& distribution) {
      outputTargets.clear();
      for (int i = 0; i < numConnections; i ++) {
        outputTargets.push_back(distribution(engine));
      }
      }
    void NeuralLayer::randomize(default_random_engine& engine) {
      neurons.clear();
      for (int i = 0; i < numNeurons; i ++) {
        Neuron neuron;
        neuron.randomize(engine, realDistribution);
        neurons.push_back(neuron);
      }
    }
    void NeuralLayer::connect(default_random_engine& engine, NeuralLayer& other) {
      for (int i = 0; i < numNeurons; i ++) {
        int numConnections = static_cast<int>(realDistribution(engine)*(other.numNeurons/3));
        neurons[i].createConnections(numConnections, engine, other.intDistribution);
      }
    }
    NeuralNetwork& NeuralNetwork::addLayer(int numNeurons) {
      NeuralLayer layer(numNeurons);
      layer.randomize(randomEngine);
      layers.push_back(layer);
      return *this;
}
NeuralNetwork& NeuralNetwork::connect() {
  for (int i = 0; i < layers.size() - 1; i ++) {
    layers[i].connect(randomEngine, layers[i + 1]);
  }
  return *this;
}
}
