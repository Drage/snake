
ALLFILES = $(wildcard *)
IGNORE = Common makefile
SUBDIRS = $(filter-out $(IGNORE), $(ALLFILES))

all:
	for F in $(SUBDIRS); do cd $$F; make; done
	rm Common/*.o
