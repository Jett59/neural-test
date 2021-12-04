#include "neurons.h"
#include "trainer.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

using namespace neurons;

double testLossFunction(double* outputs) {
    double previous = 0;
    double total = 0;
    for (int i = 0; i < 5; i ++) {
      total += abs((previous+2) - outputs[i]);
      previous = outputs[i];
    }
    return total;
    }

int main() {
  cout << "Neurons" << endl;
  NeuralNetwork network;
  network.addLayer(5).addLayer(20).addLayer(5).connect();
  double inputs[5] = {1, 2, 3, 4, 5};
  double outputs[5];
  Trainer trainer;
  double highScore = trainer.train(network, testLossFunction, inputs, outputs, 2000);
  network(inputs, outputs);
  cout << "High score: " << highScore << endl;
  for (int i = 0; i < 5; i ++) {
    cout << outputs[i] << endl;
  }
  return 0;
}
