#include <iostream>

enum EngineType {
    GAS, 
    ELECTRIC, 
    HYBRID 
};

class Engine {
protected:
    int speed;
public:
    virtual void increase() = 0;
    virtual void decrease() = 0;
    virtual int getSpeed() {
        return speed;
    }
    virtual ~Engine() {};
};

class GasEngine : public Engine {
public: 
    GasEngine() {
        speed = 0; 
    }
    void increase() {
        if (speed < 200) {
            speed += 1;
        }
    }
    void decrease() {
        if (speed > 0) {
            speed -= 1;
        }
    }
    ~GasEngine() {
        std::cout << "LOG: Engine destructor called\n";
    }
};

class ElectricEngine : public Engine {
public: 
    ElectricEngine() {
        speed = 0; 
    }
    void increase() {
        if (speed < 200) {
            speed += 1;
        }
    }
    void decrease() {
        if (speed > 0) {
            speed -= 1;
        }
    }
    ~ElectricEngine() {
        std::cout << "LOG: Engine destructor called\n";
    }
};

class HybirdEngine : public Engine {
    GasEngine* gasEngine; 
    ElectricEngine* elecEngine; 
public: 
    HybirdEngine() {
        speed = 0; 
        gasEngine = new GasEngine();
        elecEngine = new ElectricEngine();
    }
    void increase() {
    }
    void decrease() {
    }
    int getSpeed() override {
        // something 
        return 0;
    }
    ~HybirdEngine() {
        std::cout << "LOG: Engine destructor called\n";
        delete gasEngine;
        delete elecEngine;
    }
};

class Car {
private: 
    Engine* engine; 
public: 
    Car(Engine* e) {
        engine = e;
    }
    void start() {
        std::cout << "LOG: car started\n";
    }
    void stop() {
        while (engine->getSpeed()) {
            engine->decrease();
        }
        std::cout << "LOG: Car's speed: " << engine->getSpeed() << "\n";
    }
    void accerlate() {
        for (int i = 0; i < 20; i++) {
            engine->increase();
        }
        std::cout << "LOG: Car's speed: " << engine->getSpeed() << "\n";
    }
    void brake() {
        for (int i = 0; i < 20; i++) {
            engine->decrease();
        }
        std::cout << "LOG: Car's speed: " << engine->getSpeed() << "\n";
    }
    ~Car() {
        std::cout << "LOG: Car destructor called\n";
        delete this->engine;
    }
};

Car createCar(EngineType type) {
    switch (type) {
        case GAS: {
            auto gasEngine = new GasEngine();
            return Car(gasEngine);
        }
        case ELECTRIC: {
            auto elecEngine = new ElectricEngine();
            return Car(elecEngine);
        }
        case HYBRID: {
            auto hybird = new HybirdEngine();
            return Car(hybird);
        }
    }
    std::cout << "ERROR: not a valid engine type\n"; 
    exit(-1);
    return NULL;
}

int main() {
    auto car = createCar(GAS);
    
    car.start();
    car.accerlate();
    car.accerlate();

    car.brake();

    car.stop();

    return 0;
}
