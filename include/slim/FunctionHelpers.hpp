#pragma once
#include "Function.hpp"
#include "Error.hpp"
#include "types/String.hpp"
#include "types/Number.hpp"
#include <cassert>

namespace slim
{
    inline bool try_unpack_arg(const ObjectPtr &arg, std::string *out)
    {
        auto str = dynamic_cast<String*>(arg.get());
        if (str)
        {
            *out = str->get_value();
            return true;
        }
        else return false;
    }
    inline bool try_unpack_arg(const ObjectPtr &arg, double *out)
    {
        auto n = dynamic_cast<Number*>(arg.get());
        if (n)
        {
            *out = n->get_value();
            return true;
        }
        else return false;
    }
    inline bool try_unpack_arg(const ObjectPtr &arg, int *out)
    {
        auto n = dynamic_cast<Number*>(arg.get());
        if (n)
        {
            *out = (int)n->get_value();
            return true;
        }
        else return false;
    }
    
    template<class T>
    bool try_unpack_arg(const ObjectPtr &arg, T **ptr)
    {
        *ptr = dynamic_cast<T*>(arg.get());
        return *ptr ? true : false;
    }

    inline bool try_unpack_inner(FunctionArgs::const_iterator begin, FunctionArgs::const_iterator end)
    {
        assert(begin == end);
        return true;
    }

    template<class NEXT, class... ARGS>
    bool try_unpack_inner(
        FunctionArgs::const_iterator begin, FunctionArgs::const_iterator end,
        NEXT *out, ARGS && ...args)
    {
        if (begin == end) return true;
        NEXT tmp; //dont overwrite *out until sure of success
        if (!try_unpack_arg(*begin, &tmp)) return false;
        if (!try_unpack_inner(begin + 1, end, std::forward<ARGS...>(args)...)) return false;
        *out = std::move(tmp);
        return true;
    }

    inline void check_arg_count(const FunctionArgs &args, size_t min, size_t max)
    {
        if (args.size() < min || args.size() > max)
            throw InvalidArgumentCount(args.size(), min, max);
    }

    template<size_t required, class... ARGS>
    bool try_unpack(const FunctionArgs &args, ARGS && ...out)
    {
        if (required > args.size() || args.size() > sizeof...(ARGS)) return false;
        return try_unpack_inner(args.begin(), args.end(), std::forward<ARGS>(out)...);
    }

    template<class... ARGS>
    bool try_unpack(const FunctionArgs &args, ARGS && ...out)
    {
        return try_unpack<sizeof...(ARGS)>(args, std::forward<ARGS>(out)...);
    }

    /**Unpack an argument list into provided objects.
     * Optional parameters will be left with their initial values if there is no
     * corresponding argument.
     * @param required The minimun number of arguments that are required.
     * @param args The argument array.
     * @param out Pointers to objects to unpack the array elements into.
     */
    template<size_t required, class... ARGS>
    void unpack(const FunctionArgs &args, ARGS && ...out)
    {
        if (required > args.size() || args.size() > sizeof...(ARGS))
            throw InvalidArgumentCount(args.size(), required, sizeof...(ARGS));
        if (!try_unpack_inner(args.begin(), args.end(), std::forward<ARGS>(out)...))
            throw InvalidArgument();
    }

    template<class... ARGS>
    void unpack(const FunctionArgs &args, ARGS && ...out)
    {
        return unpack<sizeof...(ARGS)>(args, std::forward<ARGS>(out)...);
    }
}