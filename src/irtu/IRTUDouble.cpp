#include "IRTU.hpp"

IRTUDouble::IRTUDouble(double value) :
		value(value) {
}

union rawDoubleBits {
	double d;
	unsigned int ia[2];
};

void IRTUDouble::read(istream* stream) {
	char* buffer = new char[1];
	unsigned char i;
	int state = STATE_READING_NAME_LENGTH;
	unsigned int size = 0;
	unsigned int cnt = 0;
	rawDoubleBits bits;
	bits.d = 0;
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
				std::cout << "name: " << name << std::endl;
			}
			continue;
		}
		if (state == STATE_READING_CONTENT) {
			bits.ia[cnt / 4] <<= 8;
			bits.ia[cnt / 4] |= i;
			++cnt;
			if (cnt == 8) {
				break;
			}
			continue;
		}
	}
	value = bits.d;
	delete[] buffer;
}

void IRTUDouble::write(ostream* stream) {
	std::string s;
	s += TAG_TYPE_DOUBLE;
	s += ((name.length() & 0xff00) >> 8);
	s += (name.length() & 0xff);
	s += name;
	rawDoubleBits v;
	v.d = value;
	for (int i = 0; i < 2; i++) {
		int j = v.ia[i];
		for (unsigned int k = 0; k < sizeof(j); k++) {
			s += (j & 0xff000000) >> 24;
			j <<= 8;
		}
	}
	stream->write(s.c_str(), s.length());
}

std::string IRTUDouble::toString(int initIndent) {
	return createIndent(initIndent) + "[double name=\"" + name + "\", value=" + dToString(value) + "]";
}
