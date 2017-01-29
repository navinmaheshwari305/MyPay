CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

FLGS = -std=c++11
FLAGS += -std=c++11

SRC  = main/myPay.cpp utils/MyPayUtils.cpp ./services/TransactionService.cpp
SRC += data_layer/PaymentOption.cpp data_layer/Transaction.cpp 
SRC += db/DbConnection.cpp
OBJS = $(SRC:.cpp=.o)

LIBS  =		-L /home/navin/navin/restbed/restbed/distribution/library -lrestbed 
LIBS +=     -L /home/navin/navin/restbed/restbed/dependency/openssl   -lssl -lcrypto
LIBS +=   -lpthread
LIBS +=  -L /usr/lib -lmysqlcppconn

TARGET =	myPay

INCS  = -I/home/navin/navin/restbed/restbed/distribution/include -I /usr/include/cppconn/ -I ./json/
INCS += -I db/ -I data_layer/ -I services/ -I utils/ -I services/

#DATA_LAYER_SRC = data_layer/Transaction.cpp
#DATA_LAYER_OBJ = $(DATA_LAYER_SRC:.cpp=.o)
#OBJS += $(DATA_LAYER_OBJ)


$(TARGET): $(OBJS)
	echo "--> $(TARGET) $(OBJS)"
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(INCS) $(FLGS)

all:	$(TARGET)


clean:
	echo "--> $(TARGET) $(OBJS)"
	rm -f  $(TARGET) $(OBJS)

	
.cpp.o :
	$(CXX) -c $< -o $@  $(LIBS) $(INCS) $(FLGS)
	
	
cppcheck : 
	cppcheck --enable=all --inconclusive --xml-version=2 --force . 2> result.xml && cppcheck-htmlreport --title="my project name" --source-dir= . --report-dir=./reports/ --file=result.xml && rm result.xml