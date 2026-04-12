#include "RingBuff.h"
#include <iostream>
using namespace std;


int main()
{
    uint16_t RECEIVE_BUFFER_SIZE=6;
    RingBuffer<uint8_t> *rxBuffer = new RingBuffer<uint8_t>(RECEIVE_BUFFER_SIZE);
    rxBuffer->push(0xA3);



    int len = RECEIVE_BUFFER_SIZE;
    uint8_t rxFrameBuffer[len];

    rxBuffer->read(rxFrameBuffer, len);

    for(int i=0;i<6;i++)
    {
        cout<<rxFrameBuffer[i]<<endl;
    }


    return 0;
}