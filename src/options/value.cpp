#include <elib/options/value.hpp>
#include <elib/options/error.hpp>

namespace elib { namespace options
{
    void untyped_value::parse(
        elib::any & store
      , std::vector<std::string> const & new_tokens
    ) const
    {
        if (!store.empty()) throw multiple_occurrences_error("multiple occurrences");
        if (new_tokens.size() > 1) throw multiple_values_error("multiple values");
        store = new_tokens.empty() ? std::string("") : new_tokens.front();
    }
}}                                                          // namespace elib