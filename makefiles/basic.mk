# makefiles/basic.mk

ifndef PROJECT
$(error PROJECT not defined)
endif

ifndef VERSION
$(error VERSION not defined)
endif

ifndef DESCRIPTION
$(error DESCRIPTION not defined)
endif

all: $(VERSION_HEADER)

$(BUILD):
	@echo "\n===Generating $@===>"
	$(MKDIR) $@

$(VERSION_HEADER): $(BUILD)
	@echo "\n===Generating $@===>"
	@touch $@
	@echo "/* Automated generated file - `date -u` */" > $@
	@echo "#pragma once" >> $@
	@echo >> $@
	@echo "#define PROJECT \"$(PROJECT)\"" >> $@
	@echo "#define DESCRIPTION \"$(DESCRIPTION)\"" >> $@
	@echo "#define VERSION \"$(VERSION)\"" >> $@
	@echo "#define REVISION \"$(REVISION)\"" >> $@
	@echo "#define LAST_BUILD_TIME \"`date -u`\"" >> $@
	@echo >> $@
	@echo 



