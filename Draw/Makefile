ifeq ($(debug),1)
ROOTBUILD=debug
CPPFLAGS=-g
endif

#CXX           = ~/.vim/bundle/ClangComplete/bin/cc_args.py g++
LD            = g++
LDFLAGS       = -g -O
OutPutOpt = -o
CPPFLAGS= -g -O2 -pipe -Wall -W -Woverloaded-virtual -fPIC \
        -D__REGEXP -DG__UNIX -DG__SHAREDLIB -DG__ROOT -DG__REDIRECTIO \
        -DG__OSFDLL -D__NO_CDFSOFT__ $(shell root-config --cflags)


ifneq ($(shell echo $(CMSSW_FWLITE_INCLUDE_PATH)), '')
  CPPFLAGS += -I$(shell echo $(CMSSW_FWLITE_INCLUDE_PATH) | cut -d : -f 3)
endif

LIBS = $(shell root-config --glibs)

HEADERS = $(shell ls *.h *.hh) Makefile
HEADERS = Makefile


#all: test
all: HTCom
#all: HistStack

%.o : %.C $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

%.o : %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<


HTCom: HTCom.o StopStyle.o tdrstyle.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt) $@
	@echo "$@ done"

clean :
	rm -f *.o cyclic tcbayes tccls tcclsobs tcclsexp tcclspx nk_bayes cdf.root

