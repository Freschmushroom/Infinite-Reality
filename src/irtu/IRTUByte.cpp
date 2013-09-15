#include "IRTU.hpp"

IRTUByte::IRTUByte(char value) :
		value(value) {

}

void IRTUByte::read(istream* stream) {
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
			value = (char) i;
			break;
		}
	}
	delete[] buffer;
}

void IRTUByte::write(ostream* stream) {
	std::string s;
	s += TAG_TYPE_BYTE;
	s += ((name.length() & 0xff00) >> 8);
	s += (name.length() & 0xff);
	s += name;
	s += value;
	stream->write(s.c_str(), s.length());
}

std::string IRTUByte::toString(int initIndent) {
	return createIndent(initIndent) + "[byte name=\"" + name + "\", value=" + bToString(value) + "]";
}
