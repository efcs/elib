
-include Makefile.user.config
include Makefile.config

include Makefile.rules
-include build/rules/*.mk
-include Makefile.user.rules
