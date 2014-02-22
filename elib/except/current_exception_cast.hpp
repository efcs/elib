#ifndef ELIB_EXCEPT_CURRENT_EXCEPTION_CAST_HPP
#define ELIB_EXCEPT_CURRENT_EXCEPTION_CAST_HPP

# include <elib/except/fwd.hpp>
# include <elib/aux.hpp>

namespace elib { namespace except
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
}}                                                          // namespace elib
#endif /* ELIB_EXCEPT_CURRENT_EXCEPTION_CAST_HPP */