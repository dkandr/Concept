#include <iostream>
#include <string>
#include <concepts>
#include <type_traits>

template<typename T>
concept ComplexConcept = requires (const T v)
{
      { v.hash() } -> std::convertible_to<long>;
      { v.toString() } -> std::same_as<std::string>;
      requires !std::has_virtual_destructor<T>::value;
};

struct Example
{
    Example() = default;
    Example(int num) : _num(num) {};
    //virtual ~Example() = default;

    int _num{0};
    int hash() const { return _num; };
    std::string toString() const { return std::to_string(_num); };
};

void PrintType(ComplexConcept auto& t)
{
    std::cout << t.toString() << std::endl;
}

int main()
{
    Example x{42};

    PrintType(x);

    return 0;
}

