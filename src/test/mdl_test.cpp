#include <iostream>
#include "string.hpp"
#include "timer.hpp"

std::string create_find_string()
{
    std::string str = "";

    for (int i = 0; i < 10000; i++)
    {
        str.append("TheEndOfDogsTheEnd!!!   ");
    }
    return str;
}

std::string create_lined_string()
{
    std::string str = "";

    for (int i = 0; i < 10000; i++)
    {
        str.append("TheEndOfDogsTheEnd!!!   asdasda asgjdjdfkj\n");
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

int test_find_last_performance(const std::string &str, std::string_view fnd)
{

    size_t pos=str.size();
    size_t sizeFnd = fnd.size();
    int count = 0;

    for (;;)
    {
        pos = mdl::find_last(str, fnd, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos -= 1;
    }
    return count;
}

int test_find_last_performance_full(const std::string &str, std::string_view fnd)
{

    size_t pos=str.size();
    size_t sizeFnd = fnd.size();
    int count = 0;

    for (;;)
    {
        pos = mdl::find_last(str, fnd, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos -= sizeFnd;
    }
    return count;
}

int test_find_last_performance_stl(const std::string &str, std::string_view fnd)
{

    size_t pos=str.size();
    size_t sizeFnd = fnd.size();
    int count = 0;

    for (;;)
    {
        pos = str.rfind(fnd, pos);
        if (pos == std::string::npos)
        {
            pos = str.size();
            break;
        }
        else
        {
            count++;
        }
        pos -= sizeFnd;
    }
    return count;
}

int test_find_first_not_performance(const std::string &str, std::string_view collection)
{

    size_t pos=0;
    int count = 0;

    for (;;)
    {
        pos = mdl::find_first_not_in(str, collection, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos += 1;
    }
    return count;
}

int test_find_first_not_performance_stl(const std::string &str, std::string_view collection)
{

    size_t pos=0;
    int count = 0;

    for (;;)
    {
        pos = str.find_first_not_of(collection, pos);
        if (pos == std::string::npos)
        {
            pos = 0;
            break;
        }
        else
        {
            count++;
        }
        pos += 1;
    }
    return count;
}


int test_split_performance(const std::string &str, std::string_view chs)
{
    std::vector<std::string_view> spl = mdl::split(str, chs);

    return spl.size();
}

int test_split_performance_2(const std::string &str, std::string_view chs)
{
    std::vector<std::string_view> spl = mdl::split2(str, chs);

    return spl.size();
}

int test_split_performance_3(const std::string &str, std::string_view chs)
{
    std::vector<std::string_view> spl = mdl::split3(str, chs);

    return spl.size();
}

int main()
{
    mdl::Timer ti;


    std::string str = create_find_string();

    int r1,r2,r3,r4,r5,r6;

    ti.tick();
    r1 = test_find_performance(str, "TheEndOfDogs");
    auto t = ti.tick();

    ti.tick();
    r2 = test_find_performance_stl(str, "TheEndOfDogs");
    auto t2 = ti.tick();

    ti.tick();
    r3 = test_find_performance_earlyexit(str, "TheEndOfDogs");
    auto t3 = ti.tick();

    std::cout << "Long needle find: " << r1 << " time custom: " << t << "\n";
    std::cout << "Long needle find: " << r2 << " time stl: " << t2 << "\n";
    std::cout << "Long needle find: " << r3 << " time earlyexit: " << t3 << "\n";
    std::cout << std::endl;

    ti.tick();
    r1 = test_find_performance(str, "!! ");
    t = ti.tick();

    ti.tick();
    r2 = test_find_performance_stl(str, "!! ");
    t2 = ti.tick();

    ti.tick();
    r3 = test_find_performance_earlyexit(str, "!! ");
    t3 = ti.tick();

    std::cout << "Short needle find: " << r1 << " time custom: " << t << "\n";
    std::cout << "Short needle find: " << r2 << " time stl: " << t2 << "\n";
    std::cout << "Short needle find: " << r3 << " time earlyexit: " << t3 << "\n";
    std::cout << std::endl;

    ti.tick();
    r1 = test_find_performance(str, "   ");
    t = ti.tick();

    ti.tick();
    r2 = test_find_performance_stl(str, "   ");
    t2 = ti.tick();

    ti.tick();
    r3 = test_find_performance_earlyexit(str, "   ");
    t3 = ti.tick();

    std::cout << "Short needle find: " << r1 << " time custom: " << t << "\n";
    std::cout << "Short needle find: " << r2 << " time stl: " << t2 << "\n";
    std::cout << "Short needle find: " << r3 << " time earlyexit: " << t3 << "\n";
    std::cout << std::endl;

    ti.tick();
    r1 = test_find_performance(str, " ");
    t = ti.tick();

    ti.tick();
    r2 = test_find_performance_stl(str, " ");
    t2 = ti.tick();

    ti.tick();
    r3 = test_find_performance_earlyexit(str, " ");
    t3 = ti.tick();

    std::cout << "Single char find: " << r1 << " time custom: " << t << "\n";
    std::cout << "Single char find: " << r2 << " time stl: " << t2 << "\n";
    std::cout << "Single char find: " << r3 << " time earlyexit: " << t3 << "\n";
    std::cout << std::endl;


    ti.tick();
    r1 = test_find_last_performance(str, "!! ");
    t = ti.tick();

    ti.tick();
    r2 = test_find_last_performance_stl(str, "!! ");
    t2 = ti.tick();

    ti.tick();
    r3 = test_find_last_performance_full(str, "!! ");
    t3 = ti.tick();

    std::cout << "Find last custom: " << r1 << " time: " << t << "\n";
    std::cout << "Find last stl: " << r2 << " time: " << t2 << "\n";
    std::cout << "Find last full: " << r3 << " time: " << t3 << "\n";
    std::cout << std::endl;


    std::string collection = "abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    ti.tick();
    r1 = test_find_first_not_performance(str, collection);
    t = ti.tick();

    ti.tick();
    r2 = test_find_first_not_performance_stl(str, collection);
    t2 = ti.tick();

    std::cout << "Find last custom: " << r1 << " time: " << t << "\n";
    std::cout << "Find last stl: " << r2 << " time: " << t2 << "\n";
    std::cout << std::endl;


    ti.tick();
    r1 = test_find_first_not_performance(str, " \t\n");
    t = ti.tick();

    ti.tick();
    r2 = test_find_first_not_performance_stl(str, " \t\n");
    t2 = ti.tick();

    std::cout << "Find last custom: " << r1 << " time: " << t << "\n";
    std::cout << "Find last stl: " << r2 << " time: " << t2 << "\n";
    std::cout << std::endl;


    std::string lineString = create_lined_string();

    ti.tick();
    auto lr1 = test_split_performance(lineString, "\n");
    t = ti.tick();

    ti.tick();
    auto lr2 = test_split_performance_2(lineString, "\n");
    t2 = ti.tick();

    ti.tick();
    auto lr3 = test_split_performance_3(lineString, "\n");
    t3 = ti.tick();

    std::cout << "Line split custom " << lr1 << " performance: " << t << "\n";
    std::cout << "Line split earlyexit " << lr2 << " performance: " << t2 << "\n";
    std::cout << "Line split stl " << lr3 << " performance: " << t3 << "\n";
    std::cout << std::endl;

    return 0;
}