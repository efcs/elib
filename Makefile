
ifneq ($(wildcard Makefile.user.config),)
	include Makefile.user.config
else
	include Makefile.config
endif

include Makefile.rules
-include Makefile.user.rules