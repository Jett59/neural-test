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
    void NeuralLayer::randomize(default_random_engine& engine) {
      neurons.clear();
      for (int i = 0; i < numNeurons; i ++) {
        Neuron neuron;
        neuron.randomize(engine, realDistribution);
        neurons.push_back(neuron);
      }
    }
NeuralNetwork& NeuralNetwork::addLayer(int numNeurons) {
  NeuralLayer layer(numNeurons);
  layer.randomize(randomEngine);
  layers.push_back(layer);
  return *this;
}
}
