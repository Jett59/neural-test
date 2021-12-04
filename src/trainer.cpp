#include "trainer.h"

#include <iostream>

#include <cmath>

namespace neurons {
    static double getScore(NeuralNetwork& network, double** inputSets, int numInputSets, double* outputs, double (*loss)(double* outputs, int set)) {
      double totalScore = 0;
      for (int i = 0; i < numInputSets; i ++) {
        network(inputSets[i], outputs);
        totalScore += loss(outputs, i);
      }
      return totalScore / (double)numInputSets;
      }
    double Trainer::train(NeuralNetwork& network, double(*loss)(double* outputs, int set), double** inputSets, int numInputSets, double* outputs, int maxIterations) {
      double bestScore = getScore(network, inputSets, numInputSets, outputs, loss);
      for (int i = 0; i < maxIterations; i ++) {
        NeuralNetwork optimizedNetwork = network;
        double optimizedScore = optimizedNetwork.optimize(inputSets, numInputSets, outputs, loss, getScore, bestScore * 0.05);
        if (optimizedScore < bestScore) {
          network = optimizedNetwork;
          bestScore = optimizedScore;
          std::cout << "New high score: " << bestScore << std::endl;
        }else {
          break;
        }
      }
      return bestScore;
      }
}
