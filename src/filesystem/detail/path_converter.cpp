#include <elib/filesystem.hpp>

namespace elib { namespace fs { inline namespace v1 { namespace detail
{
    template <>
    std::string dispatch(directory_entry const & from)
    {
        return from.path().string();
    }
}}}}                                                        // namespace elib