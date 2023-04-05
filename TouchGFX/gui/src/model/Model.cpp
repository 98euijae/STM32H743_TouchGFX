#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "main.h"
#include <cmsis_os2.h>

extern "C"
{
    extern osMessageQueueId_t SDQueueHandle;
}

typedef struct {
    int dataX[DATA_SIZE];
    int dataY[DATA_SIZE];
    int readSuccess;
    int readSize;
} SDData_t;

Model::Model() : modelListener(0), readSuccess(false)
{

}

void Model::tick()
{
    SDData_t data;
    if(osMessageQueueGet(SDQueueHandle, &data, 0, 0) == osOK)
    {
        readSize = data.readSize;
        for(int i = 0; i < data.readSize; i++)
        {
            dataX[i] = data.dataX[i];
            dataY[i] = data.dataY[i];
        }
        modelListener->graphChanged();
    }
}

int* Model::getDataX()
{
    
    return dataX;
}

int* Model::getDataY()
{
    
    return dataY;
}

int Model::getReadSize()
{
    
    return readSize;
}