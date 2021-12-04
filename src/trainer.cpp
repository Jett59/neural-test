#include "trainer.h"

#include <iostream>

#include <cmath>

namespace neurons {
    double Trainer::train(NeuralNetwork& network, double(*loss)(double* outputs), double* inputs, double* outputs, int iterations) {
      network(inputs, outputs);
      double bestScore = loss(outputs);
      for (int i = 0; i < iterations; i ++) {
        NeuralNetwork mutatedNetwork = network;
        mutatedNetwork(inputs, outputs);
        double mutatedScore =
         mutatedNetwork.optimize(inputs, outputs, loss);
        if (mutatedScore < bestScore) {
          network = mutatedNetwork;
          bestScore = mutatedScore;
          std::cout << "New high score: " << bestScore << std::endl;
        }
      }
      return bestScore;
      }
}
