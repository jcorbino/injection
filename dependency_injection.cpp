// Dependency injection (a design pattern) in C++

#include <iostream>

class GasolineSource // Abstract class
{
public:
    virtual void FuelUp() = 0; // Pure virtual function
    virtual ~GasolineSource() = default;
};

class GasStation : public GasolineSource
{
public:
    virtual void FuelUp()
    {
        std::cout << "Pumping gas at gas station\n";
    }
};

class FuelCan : public GasolineSource
{
public:
    virtual void FuelUp()
    {
        std::cout << "Pumping gas from fuel can\n";
    }
};

class Car
{
    GasolineSource *gasolineService = nullptr;

public:
    // The dependency for a source of gasoline is passed in
    // through "constructor injection"
    // as opposed to hard-coded into the class definition
    Car(GasolineSource *service)
        : gasolineService(service)
    {
        // If the dependency was not defined, throw an exception
        if (gasolineService == nullptr)
            throw std::invalid_argument("Service must not be null");
    }
    void getGasoline()
    {
        std::cout << "Car needs more gasoline!\n";
        // Abstract away the dependency implementation with polymorphism
        gasolineService->FuelUp();
    }
};

int main()
{
    GasolineSource *stationService = new GasStation();
    GasolineSource *canService = new FuelCan();

    // racecar is independent from the implementation of the fuel service,
    // a gas station service is injected.
    Car racecar(stationService);
    racecar.getGasoline();

    // dune buggy is independent from the implementation of the fuel service,
    // a fuel can service is injected.
    Car duneBuggy(canService);
    duneBuggy.getGasoline();

    delete stationService;
    delete canService;
    return 0;
}
