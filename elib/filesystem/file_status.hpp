#ifndef ELIB_FILESYSTEM_FILE_STATUS_HPP
#define ELIB_FILESYSTEM_FILE_STATUS_HPP

# include <elib/filesystem/config.hpp>

namespace elib { namespace fs
{
    ////////////////////////////////////////////////////////////////////////////
    enum class file_type
    {
        none = 0,
        not_found = -1,
        regular = 1,
        directory = 2,
        symlink = 3,
        block = 4,
        character = 5,
        fifo = 6,
        socket = 7,
        unknown = 8
    };
    
    ////////////////////////////////////////////////////////////////////////////
    enum class perms
    {
        none = 0,
        
        owner_read = 0400,
        owner_write = 0200,
        owner_exec = 0100,
        owner_all = 0700,
        
        group_read = 040,
        group_write = 020,
        group_exec = 010,
        group_all = 070,
        
        others_read = 04,
        others_write = 02,
        others_exec = 01,
        others_all = 07,
        
        all = 0777,
        
        set_uid = 04000,
        set_gid = 02000,
        sticky_bit = 01000,
        
        mask = 07777,
        unknown = 0xFFFF,
        symlink_perms = 0x4000
    };
    
    ////////////////////////////////////////////////////////////////////////////
    constexpr perms operator~(perms lhs) noexcept
    {
        return static_cast<perms>(
            ~ static_cast<int>(lhs) 
          );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    constexpr perms operator&(perms lhs, perms rhs) noexcept
    {
        return static_cast<perms>(
            static_cast<int>(lhs) & static_cast<int>(rhs)
          );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline perms & operator&=(perms & lhs, perms rhs) noexcept
    {
        return lhs = lhs & rhs;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    constexpr perms operator|(perms lhs, perms rhs) noexcept
    {
        return static_cast<perms>(
            static_cast<int>(lhs) | static_cast<int>(rhs)
          );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline perms & operator|=(perms & lhs, perms rhs) noexcept
    {
        return lhs = lhs | rhs;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    constexpr perms operator^(perms lhs, perms rhs) noexcept
    {
        return static_cast<perms>(
            static_cast<int>(lhs) ^ static_cast<int>(rhs)
          );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline perms & operator^=(perms & lhs, perms rhs) noexcept
    {
        return lhs = lhs ^ rhs;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    class file_status
    {
    public:
      // constructors
        explicit 
        file_status(file_type ft = file_type::none,
            perms prms = perms::unknown) noexcept
            : m_type{ft}, m_perms{prms}
        { }
        
        file_status(const file_status&) noexcept = default;
        file_status(file_status&&) noexcept = default;
        
        file_status& operator=(const file_status&) noexcept = default;
        file_status& operator=(file_status&&) noexcept = default;
        
        // observers
        file_type type() const noexcept { return m_type; }
        perms permissions() const noexcept { return m_perms; }
        
        // modifiers
        void type(file_type ft) noexcept { m_type = ft; }
        void permissions(perms prms) noexcept { m_perms = prms; }
    private:
        file_type m_type;
        perms m_perms;
    };
}}                                                        // namespace elib::fs
#endif /* ELIB_FILESYSTEM_FILE_STATUS_HPP */