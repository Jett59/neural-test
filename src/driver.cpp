#include "neurons.h"
#include <iostream>

using std::cout;
using std::endl;

using namespace neurons;

int main() {
  cout << "Neurons" << endl;
  NeuralNetwork network;
  network.addLayer(10).addLayer(20).addLayer(5).connect();
  double inputs[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  double outputs[5];
  network(inputs, outputs);
  for (int i = 0; i < 5; i ++) {
    cout << outputs[i] << endl;
  }
  return 0;
}
