#include "IRTU.hpp"

IRTUFloat::IRTUFloat(float value) :
		value(value) {

}

union rawFloatBits {
	float f;
	unsigned int i;
};

void IRTUFloat::read(istream* stream) {
	char* buffer = new char[1];
	int i;
	int state = STATE_READING_NAME_LENGTH;
	unsigned int size = 0;
	unsigned int cnt = 0;
	rawFloatBits bits;
	while ((stream->rdstate() & stream->eofbit) == 0) {
		stream->read(buffer, 1);
		if (stream->gcount() == 0) {
			continue;
		}
		i = (unsigned char) buffer[0];
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
			bits.i <<= 8;
			bits.i |= i;
			++cnt;
			if (cnt == 4) {
				break;
			}
			continue;
		}
	}
	value = bits.f;
	delete[] buffer;
}

void IRTUFloat::write(ostream* stream) {
	std::string s;
	s += TAG_TYPE_FLOAT;
	s += ((name.length() & 0xff00) >> 8);
	s += (name.length() & 0xff);
	s += name;
	rawFloatBits bits;
	bits.f = value;
	int i = bits.i;
	for (unsigned int j = 0; j < sizeof(i); j++) {
		s += (i & 0xff000000) >> 24;
		i <<= 8;
	}
	stream->write(s.c_str(), s.length());
}

std::string IRTUFloat::toString(int initIndent) {
	return createIndent(initIndent) + "[float name=\"" + name + "\", value=" + fToString(value) + "]";
}
