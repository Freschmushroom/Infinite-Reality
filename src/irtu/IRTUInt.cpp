#include "IRTU.hpp"

IRTUInt::IRTUInt(int value) :
		value(value) {

}

void IRTUInt::read(istream* stream) {
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
			if (cnt == 4) {
				return;
			}
			continue;
		}
	}
}
