#include "IRTU.hpp"
#include <sstream>

int main() {
	std::ostringstream* ostream = new std::ostringstream();
	IRTUObject object;
	object.name = "object_0";
	IRTUByte* irtuByte = new IRTUByte(255);
	irtuByte->name = "byte_0";
	object.add(irtuByte);
	IRTUObject* nestedObject = new IRTUObject();
	nestedObject->name = "object_1";
	IRTUFloat* irtuFloat = new IRTUFloat(-29.4f);
	irtuFloat->name = "float_0";
	nestedObject->add(irtuFloat);
	object.add(nestedObject);
	IRTUDouble* irtuDouble = new IRTUDouble(-3.141);
	object.add(irtuDouble);
	std::cout << object.toString(0) << std::endl;
	object.write(ostream);
	std::istringstream* istream = new std::istringstream(ostream->str());
	IRTUObject object2;
	object2.readNew(istream);
	std::cout << object2.toString(0) << std::endl;
	delete ostream;
	delete istream;
}

std::string bToString(char b) {
	std::ostringstream oss;
	oss << (int) (unsigned char) b;
	return oss.str();
}

std::string sToString(short s) {
	std::ostringstream oss;
	oss << s;
	return oss.str();
}

std::string iToString(int i) {
	std::ostringstream oss;
	oss << i;
	return oss.str();
}

std::string lToString(long l) {
	std::ostringstream oss;
	oss << l;
	return oss.str();
}

std::string fToString(float f) {
	std::ostringstream oss;
	oss << f;
	return oss.str();
}

std::string dToString(double d) {
	std::ostringstream oss;
	oss << d;
	return oss.str();
}

IRTUByte* readByte(istream* stream) {
	IRTUByte* ret = new IRTUByte(0);
	ret->read(stream);
	return ret;
}

IRTUShort* readShort(istream* stream) {
	IRTUShort* ret = new IRTUShort(0);
	ret->read(stream);
	return ret;
}

IRTUInt* readInt(istream* stream) {
	IRTUInt* ret = new IRTUInt(0);
	ret->read(stream);
	return ret;
}

IRTULong* readLong(istream* stream) {
	IRTULong* ret = new IRTULong(0);
	ret->read(stream);
	return ret;
}

IRTUFloat* readFloat(istream* stream) {
	IRTUFloat* ret = new IRTUFloat(0);
	ret->read(stream);
	return ret;
}

IRTUDouble* readDouble(istream* stream) {
	IRTUDouble* ret = new IRTUDouble(0);
	ret->read(stream);
	return ret;
}

IRTUObject* readIRTU(istream* stream) {
	IRTUObject* ret = new IRTUObject();
	ret->read(stream);
	return ret;
}

std::string createIndent(int indent) {
	std::string string;
	for (int i = 0; i < indent; i++) {
		string += "  ";
	}
	return string;
}
