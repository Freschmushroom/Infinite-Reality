#include "IRTU.hpp"
#include <sstream>

IRTUObject::IRTUObject() {

}

IRTUObject::~IRTUObject() {
	for (IRTUElement* irtu : children) {
		delete irtu;
	}
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

void IRTUObject::read(istream* stream) {
	char* buffer = new char[1];
	int len, i;
	int state = STATE_BEGINNING;
	unsigned int size = 0;
	unsigned int cnt = 0;
	name = "";
	while ((stream->rdstate() & stream->eofbit) == 0) {
		stream->read(buffer, 1);
		len = stream->gcount();
		if (len == 0) {
			continue;
		}
		i = buffer[0];
		if (state == STATE_BEGINNING) {
			state = STATE_READING_NAME_LENGTH;
			size = 0;
			continue;
		}
		if (state == STATE_READING_NAME_LENGTH) {
			size <<= 8;
			size |= i;
			++cnt;
			if (cnt == 2) {
				if (size != 0) {
					state = STATE_READING_NAME;
				} else {
					state = STATE_READING_CONTENT;
				}
				cnt = 0;
			}
			continue;
		}
		if (state == STATE_READING_NAME) {
			++cnt;
			name += (char) i;
			if (size == cnt) {
				state = STATE_READING_CONTENT;
				continue;
			}
		}
		if (state == STATE_READING_CONTENT) {
			IRTUByte* irtuByte;
			IRTUShort* irtuShort;
			IRTUInt* irtuInt;
			IRTULong* irtuLong;
			IRTUFloat* irtuFloat;
			IRTUDouble* irtuDouble;
			IRTUObject* IRTUObject;
			switch ((unsigned char) i) {
			case TAG_TYPE_BYTE:
				irtuByte = readByte(stream);
				std::cout << "Read byte " << irtuByte->name << ": "
						<< (int) irtuByte->value << std::endl;
				children.push_back(irtuByte);
				break;
			case TAG_TYPE_SHORT:
				irtuShort = readShort(stream);
				std::cout << "Read short " << irtuShort->name << ": "
						<< (int) irtuShort->value << std::endl;
				children.push_back(irtuShort);
				break;
			case TAG_TYPE_INT:
				irtuInt = readInt(stream);
				std::cout << "Read int " << irtuInt->name << ": "
						<< (int) irtuInt->value << std::endl;
				children.push_back(irtuInt);
				break;
			case TAG_TYPE_LONG:
				irtuLong = readLong(stream);
				std::cout << "Read long " << irtuLong->name << ": "
						<< irtuLong->value << std::endl;
				children.push_back(irtuLong);
				break;
			case TAG_TYPE_FLOAT:
				irtuFloat = readFloat(stream);
				std::cout << "Read float " << irtuFloat->name << ": "
						<< irtuFloat->value << std::endl;
				children.push_back(irtuFloat);
				break;
			case TAG_TYPE_DOUBLE:
				irtuDouble = readDouble(stream);
				std::cout << "Read double " << irtuDouble->name << ": "
						<< irtuDouble->value << std::endl;
				children.push_back(irtuDouble);
				break;
			case TAG_TYPE_IRTU:
				IRTUObject = readIRTU(stream);
				std::cout << "Read IRTU " << IRTUObject->name << std::endl;
				children.push_back(IRTUObject);
				break;
			case TAG_END_IRTU:
				std::cout << "Finished reading \"" << name << "\"."
						<< std::endl;
				break;
			default:
				std::cout << i << " has not been implemented yet." << std::endl;
			}
		}
	}
	delete[] buffer;
}

void IRTUObject::write(ostream* stream) {
	std::string s;
	s += TAG_TYPE_IRTU;
	s += (name.length() & 0xff00) >> 8;
	s += name.length() & 0xff;
	s += name;
	stream->write(s.c_str(), s.length());
	for (IRTUElement* irtu : children) {
		irtu->write(stream);
	}
	s = TAG_END_IRTU;
	stream->write(s.c_str(), s.length());
}

int main() {
	std::ostringstream* ostream = new std::ostringstream();
	IRTUObject* object = new IRTUObject();
	object->name = "test_object";
	IRTUInt* irtuI = new IRTUInt(160);
	irtuI->name = "test_int";
	object->children.push_back(irtuI);
	IRTUFloat* irtuF = new IRTUFloat(3.141f);
	irtuF->name = "test_float";
	object->children.push_back(irtuF);
	IRTUDouble* irtuD = new IRTUDouble(1.41421);
	irtuD->name = "test_double";
	object->children.push_back(irtuD);
	object->write(ostream);
	std::string data = ostream->str();
	std::istringstream* istream = new std::istringstream(data);
	IRTUObject object2;
	object2.read(istream);
	delete object;
	delete ostream;
	delete istream;
}
