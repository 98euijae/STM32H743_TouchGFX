#ifndef MODEL_HPP
#define MODEL_HPP

#include "main.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    int* getDataX();
    int* getDataY();
    int getReadSize();
protected:
    ModelListener* modelListener;
    bool readSuccess;
    int dataX[DATA_SIZE];
    int dataY[DATA_SIZE];
    int readSize;
};

#endif // MODEL_HPP
