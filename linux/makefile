SRC_PATH := ../src/irtu/
BUILD_PATH := ../lin_build/

all: prepare Infinite-Reality

Infinite-Reality: IRTUByte.o IRTUDouble.o IRTUElement.o IRTUFloat.o IRTUInt.o IRTUList.o IRTULong.o IRTUObject.o IRTUShort.o IRTU.o
	g++ -o $(BUILD_PATH)Infinite-Reality $(BUILD_PATH)IRTU.o $(BUILD_PATH)IRTUByte.o $(BUILD_PATH)IRTUDouble.o $(BUILD_PATH)IRTUElement.o $(BUILD_PATH)IRTUFloat.o $(BUILD_PATH)IRTUInt.o $(BUILD_PATH)IRTUList.o $(BUILD_PATH)IRTULong.o $(BUILD_PATH)IRTUObject.o $(BUILD_PATH)IRTUShort.o -std=c++0x
	
IRTU.o:
	g++ -o $(BUILD_PATH)IRTU.o $(SRC_PATH)IRTU.cpp -std=c++0x
	
IRTUByte.o:
	g++ -o $(BUILD_PATH)IRTUByte.o $(SRC_PATH)IRTUByte.cpp -std=c++0x
	
IRTUDouble.o:
	g++ -o $(BUILD_PATH)IRTUDouble.o $(SRC_PATH)IRTUDouble.cpp -std=c++0x
	
IRTUElement.o:
	g++ -o $(BUILD_PATH)IRTUElement.o $(SRC_PATH)IRTUElement.cpp -std=c++0x
	
IRTUFloat.o:
	g++ -o $(BUILD_PATH)IRTUFloat.o $(SRC_PATH)IRTUFloat.cpp -std=c++0x
	
IRTUInt.o:
	g++ -o $(BUILD_PATH)IRTUInt.o $(SRC_PATH)IRTUInt.cpp -std=c++0x
	
IRTUList.o:
	g++ -o $(BUILD_PATH)IRTUList.o $(SRC_PATH)IRTUList.cpp -std=c++0x
	
IRTULong.o:
	g++ -o $(BUILD_PATH)IRTULong.o $(SRC_PATH)IRTULong.cpp -std=c++0x
	
IRTUObject.o:
	g++ -o $(BUILD_PATH)IRTUObject.o $(SRC_PATH)IRTUObject.cpp -std=c++0x
	
IRTUShort.o:
	g++ -o $(BUILD_PATH)IRTUShort.o $(SRC_PATH)IRTUShort.cpp -std=c++0x
	
clear:
	rm -rv $(BUILD_PATH)
	
prepare:
	mkdir $(BUILD_PATH)