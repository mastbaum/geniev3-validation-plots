CPPFLAGS=-I $(BOOST_INC) \
         -I $(CANVAS_INC) \
         -I $(CANVAS_ROOT_IO_INC) \
         -I $(CETLIB_INC) \
         -I $(CETLIB_EXCEPT_INC) \
         -I $(FHICLCPP_INC) \
         -I $(GALLERY_INC) \
         -I $(LARCOREOBJ_INC) \
         -I $(LARDATAOBJ_INC) \
         -I $(NUSIMDATA_INC) \
         -I $(ROOT_INC) \
	 -I $(LARSIM_INC) \
	 -I $(GENIE_INC) \
         -I $(HEP_CONCURRENCY_INC)

CXX=g++
CXXFLAGS=-std=c++17 -Wall -Werror -pedantic -g -I.

LDFLAGS=$(shell root-config --libs) \
        -L $(CANVAS_LIB) -l canvas \
        -L $(CETLIB_LIB) -l cetlib \
        -L $(GALLERY_LIB) -l gallery \
        -L $(NUSIMDATA_LIB) -l nusimdata_SimulationBase \
        -L $(LARCOREOBJ_LIB) -l larcoreobj_SummaryData \
        -L $(LARDATAOBJ_LIB) -l lardataobj_RecoBase \
	-L $(LARSIM_LIB) -l larsim_EventWeight_Base_dict -l larsim_EventWeight_Base

CXXROOTONLY=$(shell root-config --cxx)

CXXFLAGSROOTONLY=$(shell root-config --cflags) -D__NO_LARSOFT__

LDFLAGSROOTONLY=$(shell root-config --libs)


all: plot_kinematics plot_kinematics_nuistr

plot_kinematics: plot_kinematics.cpp filter.cpp distributions.cpp
	@echo Building $@
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

plot_kinematics_nuistr: plot_kinematics_nuistr.cpp NuisTree.cpp filter.cpp distributions.cpp
	@echo Building $@
	$(CXXROOTONLY) $(CXXFLAGSROOTONLY) $(LDFLAGSROOTONLY) -o $@ $^
