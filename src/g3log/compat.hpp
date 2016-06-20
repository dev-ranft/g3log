#ifndef COMPAT_HPP
#define COMPAT_HPP

#include <sstream>
#include <cstdlib>
#include <limits>
#include <cerrno>
#include <stdexcept>

namespace std {

#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ <= 8)
    template <typename T>
    string to_string(const T& val)
    {
        ostringstream str;
        str << val;
        return str.str();
    }

    inline int stoi(const std::string& str, std::size_t* pos = 0, int base = 10)
    {
        auto const errno_save = errno;
        const char* src = str.c_str();
        const char* end = nullptr;
        errno = 0;
        auto result = strtoul(src, const_cast<char**>(&end), base);
        auto const my_errno = errno;
        errno = errno_save;
        if(my_errno) {
            if(result) {
                throw out_of_range("Value to large");
            } else {
                throw invalid_argument("Not a number");
            }
        }
        if((result > std::numeric_limits<int>::max())
           || (result > std::numeric_limits<int>::max())) {
            throw out_of_range("Value to large");
        }
        return result;
    }

#endif

}

#endif // COMPAT_HPP
