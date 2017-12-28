#include <iostream>
#include "string.hpp"
#include "timer.hpp"

std::string create_find_string()
{
    std::string str = "";

    for (int i = 0; i < 1000; i++)
    {
        str.append("TheEndOfDogsTheEnd!!! ");
    }
    return str;
}

int test_find_performance(const std::string &str, std::string_view fnd)
{

    size_t pos=0;
    size_t sizeFnd = fnd.size();
    int count = 0;

    for (;;)
    {
        pos = mdl::find_first(str, fnd, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos += sizeFnd;
    }
    return count;
}

int test_find_performance_stl(const std::string &str, std::string_view fnd)
{

    size_t pos=0;
    size_t sizeFnd = fnd.size();
    int count = 0;

    for (;;)
    {
        pos = str.find(fnd, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos += sizeFnd;
    }
    return count;
}

int test_find_performance_earlyexit(const std::string &str, std::string_view fnd)
{

    size_t pos=0;
    size_t sizeFnd = fnd.size();
    int count = 0;

    for (;;)
    {
        pos = mdl::find_first_earlyexit(str, fnd, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos += sizeFnd;
    }
    return count;
}

int test_find_performance_old(const std::string &str, std::string_view fnd)
{

    size_t pos=0;
    size_t sizeFnd = fnd.size();
    int count = 0;

    for (;;)
    {
        pos = mdl::find_first_old(str, fnd, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos += sizeFnd;
    }
    return count;
}

int test_find_performance_char(const std::string &str, char fnd)
{

    size_t pos=0;
    int count = 0;

    for (;;)
    {
        pos = mdl::find_first(str, fnd, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos++;
    }
    return count;
}

int main()
{
    mdl::Timer ti;


    std::string str = create_find_string();

    int r1,r2,r3,r4,r5;

    ti.tick();
    r1 = test_find_performance(str, "TheEndOfDogs");
    auto t = ti.tick();

    ti.tick();
    r2 = test_find_performance_stl(str, "TheEndOfDogs");
    auto t2 = ti.tick();

    ti.tick();
    r3 = test_find_performance_earlyexit(str, "TheEndOfDogs");
    auto t3 = ti.tick();

    ti.tick();
    r4 = test_find_performance_old(str, "TheEndOfDogs");
    auto t4 = ti.tick();

    std::cout << "Long needle find: " << r1 << " time custom: " << t << "\n";
    std::cout << "Long needle find: " << r2 << " time stl: " << t2 << "\n";
    std::cout << "Long needle find: " << r3 << " time earlyexit: " << t3 << "\n";
    std::cout << "Long needle find: " << r4 << " time old: " << t4 << "\n";
    std::cout << std::endl;

    ti.tick();
    r2 = test_find_performance(str, "!! ");
    t = ti.tick();

    ti.tick();
    r2 = test_find_performance_stl(str, "!! ");
    t2 = ti.tick();

    ti.tick();
    r3 = test_find_performance_earlyexit(str, "!! ");
    t3 = ti.tick();

    ti.tick();
    r4 = test_find_performance_old(str, "!! ");
    t4 = ti.tick();

    std::cout << "Short needle find: " << r1 << " time custom: " << t << "\n";
    std::cout << "Short needle find: " << r2 << " time stl: " << t2 << "\n";
    std::cout << "Short needle find: " << r3 << " time earlyexit: " << t3 << "\n";
    std::cout << "Short needle find: " << r4 << " time old: " << t4 << "\n";
    std::cout << std::endl;

    ti.tick();
    r2 = test_find_performance(str, " ");
    t = ti.tick();

    ti.tick();
    r2 = test_find_performance_stl(str, " ");
    t2 = ti.tick();

    ti.tick();
    r3 = test_find_performance_earlyexit(str, " ");
    t3 = ti.tick();

    ti.tick();
    r4 = test_find_performance_old(str, " ");
    t4 = ti.tick();

    ti.tick();
    r5 = test_find_performance_char(str, ' ');
    auto t5 = ti.tick();

    std::cout << "Single char find: " << r1 << " time custom: " << t << "\n";
    std::cout << "Single char find: " << r2 << " time stl: " << t2 << "\n";
    std::cout << "Single char find: " << r3 << " time earlyexit: " << t3 << "\n";
    std::cout << "Single char find: " << r4 << " time old: " << t4 << "\n";
    std::cout << "Single char find: " << r5 << " time char: " << t5 << "\n";
    std::cout << std::endl;

    return 0;
}