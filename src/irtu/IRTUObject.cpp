#include "IRTU.hpp"
#include <sstream>

IRTUObject::IRTUObject() {

}

IRTUObject::~IRTUObject() {
	for (IRTUElement* irtu : children) {
		std::cout << "Deleting " << irtu->name << std::endl;
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

IRTUObject* readIRTU(istream* stream) {
	IRTUObject* ret = new IRTUObject();
	ret->read(stream);
	return ret;
}

void IRTUObject::read(istream* stream) {
	char* buffer = new char[1];
	int len, i;
	int state = STATE_BEGINNING;
	int type = -1;
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
			type = i;
			state = STATE_READING_NAME_LENGTH;
			size = 0;
			std::cout << "Type: " << type << std::endl;
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
				std::cout << "Name length: " << size << std::endl;
			}
			continue;
		}
		if (state == STATE_READING_NAME) {
			++cnt;
			name += (char) i;
			if (size == cnt) {
				std::cout << "Name: " << name << std::endl;
				state = STATE_READING_CONTENT;
				continue;
			}
		}
		if (state == STATE_READING_CONTENT) {
			IRTUByte* irtuByte;
			IRTUShort* irtuShort;
			IRTUInt* irtuInt;
			IRTULong* irtuLong;
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

int main() {
	std::string testString;

	std::string name = "Cya";
	testString += TAG_TYPE_IRTU;
	testString += ((name.length() & 0xff00) >> 8);
	testString += (name.length() & 0xff);
	testString += name;

	testString += TAG_TYPE_SHORT;
	name = "test_short";
	testString += ((name.length() & 0xff00) >> 8);
	testString += (name.length() & 0xff);
	testString += name;
	testString += (char) 0;
	testString += (short) -16;

	testString += TAG_TYPE_BYTE;
	name = "test_byte";
	testString += ((name.length() & 0xff00) >> 8);
	testString += (name.length() & 0xff);
	testString += name;
	testString += 0xf0;

	testString += TAG_TYPE_LONG;
	name = "test_long (:iykwim:)";
	testString += ((name.length() & 0xff00) >> 8);
	testString += (name.length() & 0xff);
	testString += name;
	testString += (char) 0;
	testString += (char) 0;
	testString += (char) 0;
	testString += (char) 0;
	testString += (char) 0;
	testString += (char) 0;
	testString += (char) 0;
	testString += (long) -16;

	name = "bye";
	testString += TAG_TYPE_IRTU;
	testString += TAG_TYPE_IRTU;
	testString += ((name.length() & 0xff00) >> 8);
	testString += (name.length() & 0xff);
	testString += name;
	testString += TAG_TYPE_INT;
	name = "nested_test_int";
	testString += ((name.length() & 0xff00) >> 8);
	testString += (name.length() & 0xff);
	testString += name;
	testString += (char) 0;
	testString += (char) 0;
	testString += (char) 0;
	testString += (int) -16;
	testString += TAG_END_IRTU;

	testString += TAG_TYPE_INT;
	name = "test_int";
	testString += ((name.length() & 0xff00) >> 8);
	testString += (name.length() & 0xff);
	testString += name;
	testString += (char) 0;
	testString += (char) 0;
	testString += (char) 0;
	testString += (int) -16;

	testString += TAG_END_IRTU;

	istream* stream = new std::istringstream(testString);
	IRTUObject irtu;
	irtu.read(stream);
	delete stream;
}
