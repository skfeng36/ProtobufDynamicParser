#debug 模式添加宏 -DDEBUG
CXX=g++
CXXFLAGS += -g -Wall  
LDFLAGS  += -lpthread  -lprotobuf  -L/usr/local/lib 

SOURCES=$(notdir $(shell echo  *.cpp ))
OBJECTS=$(addprefix ./, $(SOURCES:.CPP=.O))
STATIC_LIB=libpb_parser.a
build: $(STATIC_LIB)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.cc.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(STATIC_LIB) : $(OBJ)
	ar crus $@ $?

