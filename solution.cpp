#include <iostream>

class Engine {
public:
    virtual void increase() = 0;
    virtual void decrease() = 0;
};

class GasEngine : Engine {
    int speed;
public: 
    GasEngine() {
        speed = 0; 
    }
    void increase() {
    }
    void decrease() {
    }
    ~GasEngine() {
    }
};

class ElectricEngine : Engine {
    int speed;
public: 
    ElectricEngine() {
        speed = 0; 
    }
    void increase() {
    }
    void decrease() {
    }
    ~ElectricEngine() {
    }
};

class HybirdEngine : Engine {
    int speed = 0; 
    GasEngine gasEngine; 
    ElectricEngine elecEngine; 
public: 
    HybirdEngine() {
        gasEngine = new GasEngine()
        elecEngine = new ElectricEngine()
    }
    void increase() {
    }
    void decrease() {
    }

    ~HybirdEngine() {
        delete gasEngine
        delete elecEngine
    }
};

class Car {
private: 
    // engine 
public: 
    void start() {
    }
    void stop() {
    }
    void accerlate() {
    }
    void brake() {
    }
};

int main() {

    return 0;
}
