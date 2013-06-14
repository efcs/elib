#ifndef ELIB_ARG_PARSER_H
#define ELIB_ARG_PARSER_H

#include <string>
#include <memory>
#include <vector>

namespace elib {


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
	argp() { }
	~argp() { }
	
	
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
					  std::vector<std::string>& unused) {
		for (int i=0; i < argc; ++i)
			unused.push_back(std::string(argv[i]));
		for (auto &arg : m_arg_list) {
			std::remove(unused.begin(), unused.end(), arg->cmd_line_flag);
			arg->set_func();
		}
	}
	
private:
	std::vector<std::shared_ptr<__arg>> m_arg_list;
};


} /* namespace elib */
#endif /* ELIB_ARG_PARSER_H */