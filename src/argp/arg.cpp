#include "elib/argp/arg.h"

namespace elib {
namespace argp {


////////////////////////////////////////////////////////////////////////////////
//                            functions                                       //
////////////////////////////////////////////////////////////////////////////////


bool
prefix_is_long_name(const std::string & name)
{
    if (name.size() < 3)
        return false;
    
    return (name[0] == '-' && name[1] == '-' && isalpha(name[2]));
}

bool
prefix_is_short_name(const std::string & name)
{
    if (name.size() < 2)
        return false;
    
    return (name[0] == '-' && isalpha(name[1]));
}

bool
is_valid_arg_name(const std::string & name)
{
    
    if (prefix_is_long_name(name)) {
        return is_valid_long_name(name);
    }
    else if (prefix_is_short_name(name)) {
        return is_valid_short_name(name);
    }
    
    return false;
}

bool
is_valid_short_name(const std::string & name)
{
    if (name.size() != 2)
        return false;
    
    return (name[0] == '-' && isalpha(name[1]));
}

bool
is_valid_long_name(const std::string & name)
{
    if (name.size() < 3)
        return false;
    
    if (name[0] != '-' || name[1] != '-' || ! isalpha(name[2]))
        return false;
    
    for (auto it=name.begin() + 3; it != name.end(); ++it) {
        if (! isalpha(*it) && ! isdigit(*it) && *it != '_' && *it != '-')
            return false;
    }
    return true;
}
    
    
} /* namespace argp */
} /* namespace elib */