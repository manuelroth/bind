BINDTEST = bindtest/Debug
LINELIB = lineiteratortest/Debug
LINETEST = lineiteratortest/Debug

SUBPROJECTS = $(LINELIB) $(LINETEST) $(BINDTEST)

all: $(SUBPROJECTS)

$(LINELIB):
	@$(MAKE) -C $@;

$(BINDTEST):
	@$(MAKE) -C $@;

$(LINETEST): $(LINELIB)
	@$(MAKE) -C $@;

clean:
	@$(MAKE) clean -C $(BINDTEST);
	@$(MAKE) clean -C $(LINELIB);
	@$(MAKE) clean -C $(LINETEST);

test: $(SUBPROJECTS)
	cd $(BINDTEST) && ./bindtest;
	cd $(LINETEST) && ./lineiteratortest;

.PHONY: $(SUBPROJECTS)
