#include "neurons.h"

using std::default_random_engine;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::vector;

namespace neurons {
    void Neuron::randomizeConnections(int numConnections, default_random_engine& engine, uniform_real_distribution<double>& distribution) {
      outputWeights.clear();
      for (int i = 0; i < numConnections; i ++) {
        outputWeights.push_back(distribution(engine));
      }
      }
    void NeuralLayer::randomizeConnections(default_random_engine& engine, NeuralLayer& other) {
      for (int i = 0; i < numNeurons; i ++) {
        neurons[i].randomizeConnections(other.numNeurons, engine, realDistribution);
      }
    }
    NeuralNetwork& NeuralNetwork::addLayer(int numNeurons) {
      NeuralLayer layer(numNeurons);
      layers.push_back(layer);
      return *this;
}
NeuralNetwork& NeuralNetwork::connect() {
  for (int i = 0; i < layers.size() - 1; i ++) {
    layers[i].randomizeConnections(randomEngine, layers[i + 1]);
  }
  return *this;
}

double Neuron::operator()() {
    double result = 0;
  for (int i = 0; i < inputs.size(); i ++) {
    result += inputs[i];
  }
  inputs.clear();
  return result;
  }
void NeuralNetwork::operator() (double* inputs, double* outputs) {
  for (int i = 0; i < layers[0].neurons.size(); i ++) {
    layers[0].neurons[i].inputs.push_back(inputs[i]);
  }
    for (int i = 0; i < layers.size() - 1; i++) {
      NeuralLayer& layer = layers[i];
      for (int j = 0; j < layer.neurons.size(); j++) {
        Neuron& neuron = layer.neurons[j];
        double neuronValue = neuron();
          for (int k = 0; k < layers[i + 1].neurons.size(); k++) {
            Neuron& targetNeuron =
                layers[i + 1].neurons[k];
            targetNeuron.inputs.push_back(neuronValue * neuron.outputWeights[k]);
          }
    }
    }
    NeuralLayer& outputLayer = layers[layers.size() - 1];
    for (int i = 0; i < outputLayer.neurons.size(); i ++) {
      outputs[i] = outputLayer.neurons[i]();
    }
    }

double Neuron::optimize(NeuralNetwork& parent, double** inputSets, int numInputSets, double* outputs, double (*subLoss) (double* outputs, int set), double (*loss)(NeuralNetwork& network, double** inputSets, int numInputSets, double* outputs, double (*loss) (double* outputs, int set)), double learningRate) {
  double currentScore = loss(parent, inputSets, numInputSets, outputs, subLoss);
  for (int i = 0; i < outputWeights.size(); i ++) {
    double& weight = outputWeights[i];
    double originalWeight = weight;
    weight = originalWeight - learningRate;
    double newScore = loss(parent, inputSets, numInputSets, outputs, subLoss);
    if (newScore > currentScore) {
      weight = originalWeight + learningRate;
      newScore = loss(parent, inputSets, numInputSets, outputs, subLoss);
      if (newScore > currentScore) {
        weight = originalWeight;
        newScore = currentScore;
      }
    }
    currentScore = newScore;
  }
  return currentScore;
  }
double NeuralNetwork::optimize(double** inputSets, int numInputSets, double* outputs, double (*subLoss) (double* outputs, int set), double (*loss) (NeuralNetwork& network, double** inputs, int numInputSets, double* outputs, double(*loss) (double* outputs, int set)), double learningRate) {
  double newScore = 0;
  for (int i = 0; i < layers.size(); i ++) {
    NeuralLayer& layer = layers[i];
    for (int j = 0; j < layer.neurons.size(); j ++) {
      newScore = layer.neurons[j].optimize(*this, inputSets, numInputSets, outputs, subLoss, loss, learningRate);
    }
    }
    return newScore;
}
}
