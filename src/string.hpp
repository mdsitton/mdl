#include <string>
#include <vector>
#include <string_view>
#include <type_traits>


namespace mdl
{
    size_t find_first(std::string_view str, std::string_view chr, size_t start = 0);
    size_t find_first_earlyexit(std::string_view str, std::string_view chr, size_t start = 0);

    size_t find_last(std::string_view str, std::string_view chr, size_t start = std::string::npos);

    size_t find_first_not_in(std::string_view str, std::string_view collection, size_t start = 0);

    size_t find_last_not_in(std::string_view str, std::string_view collection, size_t start = std::string::npos);

    int count(const std::string& str, const std::string& substr);

    std::string join(const std::vector<std::string>& strElements, const std::string& delimiter);

    std::vector<std::string_view> split(std::string_view str, std::string_view delimiter);
    std::vector<std::string_view> split2(std::string_view str, std::string_view delimiter);
    std::vector<std::string_view> split3(std::string_view str, std::string_view delimiter);

    std::string_view strip(std::string_view str);


    // TODO - Add some sanity checks in here to error out when non alphanumeric values are passed in.
    template<typename T>
    T string_to_uint(std::string_view str)
    {
        static_assert(std::is_unsigned<T>(), "Must be unsigned type");

        T output = 0;

        for(char chr: str)
        {
            uint8_t d;
            if ((d = chr - '0') <=9 )
            {
                output = output * 10 + d;
            }
        }
        return output;
    }

} // namespace mdl