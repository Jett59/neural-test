#ifndef NEURONS_TRAINER_H
#define NEURONS_TRAINER_H

#include "neurons.h"

namespace neurons {
class Trainer {
    public:
     double train(NeuralNetwork& network, double(*loss)(double* outputs), double* inputs, double* outputs, int iterations);
};
}

#endif