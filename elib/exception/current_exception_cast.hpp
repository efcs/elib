#ifndef ELIB_EXCEPTION_CURRENT_EXCEPTION_CAST_HPP
#define ELIB_EXCEPTION_CURRENT_EXCEPTION_CAST_HPP

# include <elib/exception/fwd.hpp>
# include <elib/aux.hpp>

namespace elib { namespace except { inline namespace v1
{
    template <class E>
    E * current_exception_cast()
    {
        try {
            throw;
        } catch (E & e) {
            return elib::addressof(e);
        } catch (...) {
            return nullptr;
        }
    }
}}}                                                          // namespace elib
#endif /* ELIB_EXCEPTION_CURRENT_EXCEPTION_CAST_HPP */