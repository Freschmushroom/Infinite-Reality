#include "IRTU.hpp"

IRTUShort::IRTUShort(short value) :
		value(value) {

}

void IRTUShort::read(istream* stream) {
	char* buffer = new char[1];
	int i;
	int state = STATE_READING_NAME_LENGTH;
	unsigned int size = 0;
	unsigned int cnt = 0;
	while ((stream->rdstate() & stream->eofbit) == 0) {
		stream->read(buffer, 1);
		if (stream->gcount() == 0) {
			continue;
		}
		i = buffer[0];
		if (state == STATE_READING_NAME_LENGTH) {
			++cnt;
			size <<= 8;
			size |= i;
			if (cnt == 2) {
				cnt = 0;
				if (size != 0) {
					state = STATE_READING_NAME;
				} else {
					name = "";
					state = STATE_READING_CONTENT;
				}
				continue;
			}
		}
		if (state == STATE_READING_NAME) {
			++cnt;
			name += (char) i;
			if (cnt == size) {
				cnt = 0;
				state = STATE_READING_CONTENT;
			}
			continue;
		}
		if (state == STATE_READING_CONTENT) {
			value <<= 8;
			value |= i;
			++cnt;
			if (cnt == 2) {
				break;
			}
			continue;
		}
	}
	delete[] buffer;
}

void IRTUShort::write(ostream* stream) {
	std::string s;
	s += TAG_TYPE_SHORT;
	s += ((name.length() & 0xff00) >> 8);
	s += (name.length() & 0xff);
	s += name;
	short v = value;
	for (unsigned int j = 0; j < sizeof(v); j++) {
		s += (v & 0xff000000) >> 24;
		v <<= 8;
	}
	stream->write(s.c_str(), s.length());
}

std::string IRTUShort::toString(int initIndent) {
	return createIndent(initIndent) + "[short name=\"" + name + "\", value=" + sToString(value) + "]";
}
