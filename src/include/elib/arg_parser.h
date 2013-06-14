#ifndef ELIB_ARG_PARSER_H
#define ELIB_ARG_PARSER_H

#include <string>
#include <memory>

namespace elib {


struct added_order_t { };
struct argv_order_t { };
constexpr added_order_t in_order_added = added_order_t();
constexpr argv_order_t in_order_argv = argv_order_t;



class argp {
private:
	
	struct __arg {
		std::string cmd_line_flag;
		bool optional, seen;
		std::string description;
		std::function<void()> set_func;
		bool operator==(const char* arg) const {
			return cmd_line_flag == arg;
		}
		
		bool operator==(const std::string &str) const {
			return cmd_line_flag == str;
		}
	private:
		DISALLOW_COPY_AND_ASSIGN(__arg);
	};
	
	
public:
	argp();
	~argp();
	
	
	template <typename T, typename Func, typename... Args>
	void add_arg(const std::string &cmd_line_flag, const std::string description, 
				bool optional, T &val, Func&& f, Args&&... args) {
		
			std::function<T()> func = std::bind(std::forward<Func>(f),
												std::forward<Args>(args)...);
			
			
			auto arg = std::make_shared(new __arg);
			arg->cmd_line_flag = cmd_line_flag;
			arg->description = description;
			arg->optional = optional;
			arg->set_func = [&] () { (void)val = func(); }
			m_arg_list.push_back(arg);
	}
	
	
	
	
	void process_args(int argc, const char *argv[], 
					  std::vector<std::string>& unused,
					  const argv_order_t &t) {
		UNUSED(t);
		for (int i=0; i < argc; ++i) {
			auto it = std::find(m_arg_list.begin(), m_arg_list.end(), argv[i]);
			if (it == m_arg_list.end()) {
				unused.push_back(std::string(argv[i]));
			} else {
				(*it)->set_func();
				(*it)->seen = true;
			}
		}
		for (auto &arg : m_arg_list) {
			if (! arg->seen ) {
				if (arg->optional) {
					arg->seen_func();
					arg->seen = true;
				} else {
					//ERROR
					//TODO
				}
			}
		}
	}
	
	void process_args(int argc, const char *argv[], 
					  std::vector<std::string>& unused,
					  const added_order_t &t) {
		UNUSED(t);
		for (int i=0; i < argc; ++i)
			unused.push_back(std::string(argv[i]));
		for (auto &arg : m_arg_list) {
			std::remove(unused.begin(), unused.end(), arg->cmd_line_flag);
			arg->set_func();
			arg->seen = true;
		}
	}
	
private:
	bool _process_arg(const char *arg) {

		auto it = std::find_if(m_arg_list.begin(), m_arg_list.end(),
								[&](std::shared_ptr<__arg> m_arg) 
											{ (*m_arg) == arg; } );
		
		if (it != m_arg_list.end()) {
			it->set_func();
			it->seen = true;
			return true;
		}
		
		return false;
	}
	
private:
	std::vector<std::shared_ptr<__arg>> m_arg_list;
	_elib::arg_parser 
};










} /* namespace elib */
#endif /* ELIB_ARG_PARSER_H */