//外观模式
#include <iostream>
using namespace std;


//灯类
class Light {
public:
    void on() {
        cout << "Light on" << endl;
    }
    void off() {
        cout << "Light off" << endl;
    }
};

//音响
class Audio {
public:
    void on() {
        cout << "Audio on" << endl;
    }
    void off() {
        cout << "Audio off" << endl;
    }
};

//麦克风
class Microphone {
public:
    void on() {
        cout << "Microphone on" << endl;
    }
    void off() {
        cout << "Microphone off" << endl;
    }
};


//外观模式
class KTVMode {
public:
    KTVMode() {
        pLight = new Light;
        pAudio = new Audio;
        pMicrophone = new Microphone;
    }

    void onKTV() {
        pLight->off();
        pAudio->on();
        pMicrophone->on();
    }

    void offKTV() {
        pLight->off();
        pAudio->off();
        pMicrophone->off();
    }

    ~KTVMode() {
        delete pLight;
        delete pAudio;
        delete pMicrophone;
    }
private:
    Light* pLight;
    Audio* pAudio;
    Microphone* pMicrophone;
};

int main()
{
    KTVMode* ktv = new KTVMode;
    ktv->onKTV();

    // ktv->offKTV();
}
