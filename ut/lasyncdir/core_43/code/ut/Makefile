.PHONY: all
.PHONY: clean
.PHONY: libs

bins = $(shell files=""; for file in `ls *.cpp *.c 2>/dev/null`; do obj=`echo $$file |sed -r 's/(.*)\.(c|cpp)/\1/g'`; files="$$files $$obj"; done ; echo $$files)

DISTRO = $(shell lsb_release -is)

ifeq (${DISTRO}, CentOS)
    DISTRO = RHEL
else
    DISTRO = UBUNTU
endif


CXXFLAGS = -g -fpermissive -D$(DISTRO) -I ../lib ../lib/*.o

all: libs $(bins)

libs:
	cd ../lib; $(MAKE)

clean:
	rm -fr $(bins)
