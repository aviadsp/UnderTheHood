#include <vector>
#include <iostream>
#include <chrono>

//Here we see that every insert to vector we allocated new memory buffer
void Example1()
{
    std::cout << "Example 1:\n";
    {
        std::cout << "******************* Vector without reserve ***********************\n";
        std::vector<int> vec;
        for (int i = 0; i < 10; ++i)
        {
            vec.push_back(i);
            std::cout << "vec capacity: " << vec.capacity() << "\n";
        }
    }
    {
        std::cout << "*************** Vector with reserve ******************\n";
        std::vector<int> vec;
        vec.reserve(10);
        for (int i = 0; i < 10; ++i)
        {
            vec.push_back(i);
            std::cout << "vec capacity: " << vec.capacity() << "\n";
        }
    }

    //results not only we allocated one time big buffer, our vector with reserve is use less memory
}

struct A
{
    A(int n) : number(n) { std::cout << "constructor of A" << '\n'; }
    A(const A&) { std::cout << "Copy constructor of A" << '\n'; }
    A(A&&) { std::cout << "Move constructor of A" << '\n'; }
    A& operator=(const A&) { std::cout << "Copy operator of A" << '\n'; }
    A& operator=(A&&) { std::cout << "Move operator of A" << '\n'; }
    ~A() { std::cout << "Destructor of A" << '\n'; }
    int number;
};

struct B
{
    B(int n) : number(n) { std::cout << "constructor of B" << '\n'; }
    B(const B&) { std::cout << "Copy constructor of B" << '\n'; }
    B(B&&) noexcept { std::cout << "Move constructor of B" << '\n'; }
    B& operator=(const B&) { std::cout << "Copy operator of B" << '\n'; }
    B& operator=(B&&) { std::cout << "Move operator of B" << '\n'; }
    ~B() { std::cout << "Destructor of B" << '\n'; }
    int number;
};

void Example2()
{
    //In this example push_back create the Example and copy it to the vector, while the emplace_back creates the 
    //Example inside the vector, eliminate the copy/move constructor
    std::cout << "\nExample 2:\n";
    {
        std::cout << "************* Vector with push_back ******************\n";
        std::vector<A> vec;
        vec.push_back(A(5));
    }
    {
        std::cout << "************ Vector with emplace_back *****************\n";
        std::vector<A> vec;
        vec.emplace_back(5);
    }
    //We allocated Example only one time
}

void Example3()
{
    //In this example we can see that the internal implementation of vector copy or move
    //the element by noexcept deceleration of our struct, then move constructor is called and not copy
    std::cout << "\nExample 3:\n";
    {
        std::cout << "************* Vector Example *******************\n";
        std::vector<A> vec;
        for (int i = 0; i < 3; ++i)
        {
            vec.emplace_back(5);
        }
    }
    {
        std::cout << "************ Vector Example NoExcept *******************\n";
        std::vector<B> vec;
        for (int i = 0; i < 3; ++i)
        {
            vec.emplace_back(5);
        }
    }
}

int main()
{
    Example1();
    Example2();
    Example3();
    return 0;
}