#include "neurons.h"
#include "trainer.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

using namespace neurons;

double testLossFunction(double* outputs, int set) {
    double total = 0;
    for (int i = 0; i < 5; i ++) {
      total += abs(((set + i) * 2) - outputs[i]);
    }
    return total;
    }

int main() {
  cout << "Neurons" << endl;
  NeuralNetwork network;
  network.addLayer(5).addLayer(20).addLayer(5).connect();
  double inputs1 [5] = {0, 1, 2, 3, 4};
  double inputs2[5] = {1, 2, 3, 4, 5};
  double inputs3 [5] = {2, 3, 4, 5, 6};
  double* inputSets[3] = {inputs1, inputs2, inputs3};
  double outputs[5];
  Trainer trainer;
  double highScore = trainer.train(network, testLossFunction, inputSets, 3, outputs, 2000);
  network(inputs1, outputs);
  cout << "High score: " << highScore << endl;
  for (int i = 0; i < 5; i ++) {
    cout << outputs[i] << endl;
  }
  double testInputs [5] = {3, 4, 5, 6, 7};
  network(testInputs, outputs);
  cout << "Test answers:" << endl;
  for (int i = 0; i < 5; i ++) {
    cout << outputs[i] << endl;
  }
  return 0;
}
