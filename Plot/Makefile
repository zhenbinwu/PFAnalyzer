ifeq ($(debug),1)
ROOTBUILD=debug
CPPFLAGS=-g
endif

CXX       = g++ -Wunused-parameter
#CXX      = ~/.vim/bundle/ClangComplete/bin/cc_args.py g++  -Wunused-parameter
LD        = g++ -Wunused-parameter
LDFLAGS   = -g -O
OutPutOpt = -o
CPPFLAGS  = -g -O2 -pipe -Wall -W -Woverloaded-virtual -fPIC \
        -D__REGEXP -DG__UNIX -DG__SHAREDLIB -DG__ROOT -DG__REDIRECTIO \
        -DG__OSFDLL -D__NO_CDFSOFT__ $(shell root-config --cflags)

LIBS      = $(shell root-config --glibs) -lASImage

HEADERS   = $(shell ls *.h *.hh) Makefile
HEADERS   = Makefile

ifneq ($(shell echo $(CMSSW_FWLITE_INCLUDE_PATH)), '')
  CPPFLAGS += -I$(shell echo $(CMSSW_FWLITE_INCLUDE_PATH) | cut -d : -f 3)
endif

all: Plot

%.o : %.C $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

%.o : %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<


Plot: Plot.o TPlot.o Perf2D.o
	$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt) $@
	@echo "$@ done"

clean :
	rm -f *.o cyclic tcbayes tccls tcclsobs tcclsexp tcclspx nk_bayes cdf.root

