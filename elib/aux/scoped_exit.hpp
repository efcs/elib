#ifndef ELIB_AUX_SCOPED_EXIT_HPP
#define ELIB_AUX_SCOPED_EXIT_HPP

# include <functional>

namespace elib 
{
    namespace aux
    {
        
        ////////////////////////////////////////////////////////////////////////
        // scoped_exit
        class scoped_exit
        {
        public:
            scoped_exit( std::function<void()> fn )
                : m_fn{fn}
            {}

            scoped_exit() = delete;
            scoped_exit(const scoped_exit&) = delete;
            scoped_exit(scoped_exit&&) = delete;

            scoped_exit& operator=(const scoped_exit&) = delete;
            scoped_exit& operator=(scoped_exit&&) = delete;

            ~scoped_exit()
            { if (m_fn) m_fn(); }

            void release()
            { m_fn = std::function<void()>{}; }

            operator bool() const
            { return static_cast<bool>(m_fn); }

        private:
            std::function<void()> m_fn;
        };
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_SCOPED_EXIT_HPP */