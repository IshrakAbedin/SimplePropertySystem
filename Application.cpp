#include <iostream>

#include "Property.hpp"

class TestClass
{
private:
    int age;
    float height;

public:
    Property<int> Age{
        age,
        [&](){ return age; },
        [&](int value){ age = value < 0 ? 0 : (value > 120 ? 120 : value); }
    };

    ObservableProperty<float> Height{ height };

    TestClass(int age, float height)
    {
        Age = age;
        Height = height;
        Height.OnValueChange << [](float eArg){
            std::cout << "Height value changed to: " << eArg << std::endl;
        };
    }
};

int main()
{
    std::cout << "Entry" << std::endl;
    TestClass tc{10, 1.5f};
    std::cout << "Enter an age [0, 120]: ";
    std::cin >> tc.Age;
    tc.Height = 51.15f;
    tc.Height = 12.34f;
    std::cout << "Done, Age: " << tc.Age << ", Height: " << tc.Height << std::endl;
    return 0;
}