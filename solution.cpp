#include <iostream>
#include <math.h>

#define MAX_SPEED 200
#define SPEED_CHANGE_AMOUNT 20
// When the hybrid motor switches from electric to gas engine
#define HYBRID_SWITCH 50

enum class EngineType {
    Gas, 
    Electric, 
    Hybrid 
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
        speed += 1;
    }
    void decrease() {
        speed -= 1;
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
        speed += 1;
    }
    void decrease() {
        speed -= 1;
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
        gasEngine = new GasEngine();
        elecEngine = new ElectricEngine();
    }

    void increase() {
        int speed = getSpeed();
        bool isElectric = gasEngine->getSpeed() == 0;

        switch(isElectric) {
            case true: {
                if (speed < HYBRID_SWITCH) {
                    elecEngine->increase();
                }
                else {
                    std::cout << "LOG: switching to gas\n";
                    while (elecEngine->getSpeed()){
                        elecEngine->decrease();
                    }
                    for (int i = 0; i < speed+1; i++) {
                        gasEngine->increase();
                    }
                }
                break;
            }
            case false:
                gasEngine->increase();
                break;
        }

    }
    
    void decrease() {
        int speed = getSpeed();
        bool isGas = elecEngine->getSpeed() == 0;
        if (speed == 0) {
            return;
        }

        switch(isGas) {
            case true: {
                if (speed >= HYBRID_SWITCH) {
                    gasEngine->decrease();
                }
                else {
                    std::cout << "LOG: switching to electric\n";
                    while (gasEngine->getSpeed()){
                        gasEngine->decrease();
                    }

                    for (int i = 0; i < speed-1; i++) {
                        elecEngine->increase();
                    }
                }
                break;
            }
            case false:
                elecEngine->decrease();
                break;
        }
    }

    int getSpeed() override {
        return std::max(elecEngine->getSpeed(), gasEngine->getSpeed());
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
        if (engine->getSpeed() == MAX_SPEED) {
            std::cout << "LOG: max engine speed reached, speed: " << engine->getSpeed() << "\n";
            return;
        }

        for (int i = 0; i < SPEED_CHANGE_AMOUNT && engine->getSpeed() < MAX_SPEED; i++) {
            engine->increase();
        }
        std::cout << "LOG: Car's speed: " << engine->getSpeed() << "\n";
    }
    void brake() {
        for (int i = 0; i < SPEED_CHANGE_AMOUNT && engine->getSpeed() >= 0; i++) {
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
        case EngineType::Gas: {
            auto gasEngine = new GasEngine();
            return Car(gasEngine);
        }
        case EngineType::Electric: {
            auto elecEngine = new ElectricEngine();
            return Car(elecEngine);
        }
        case EngineType::Hybrid: {
            auto hybird = new HybirdEngine();
            return Car(hybird);
        }
    }
    std::cout << "ERROR: not a valid engine type\n"; 
    exit(-1);
    return NULL;
}

int main() {
    auto car = createCar(EngineType::Hybrid);
    
    car.start();
    for (int i = 0; i < 11; i++) {
        car.accerlate();
    }

    for (int i = 0; i < 3; i++) {
        car.brake();
    }

    car.stop();
    return 0;
}
