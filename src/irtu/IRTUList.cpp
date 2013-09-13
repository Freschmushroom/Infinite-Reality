#include <sstream>
#include "IRTU.hpp"

IRTUList::IRTUList() {
	std::cerr << "This version of IRTU does not provide list compatibility. "
			<< "Any attempt to read or write using IRTULists will result in severe errors."
			<< std::endl;
	throw;
}

void IRTUList::read(istream* stream) {
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
				size = 0;
				state = STATE_READING_LENGTH;
			}
			continue;
		}
		if (state == STATE_READING_LENGTH) {
			++cnt;
			size <<= 8;
			size |= i;
			if (cnt == 8) {
				cnt = 0;
				state = STATE_READING_CONTENT;
			}
			continue;
		}
		if (state == STATE_READING_CONTENT) {

		}
	}
	delete[] buffer;
}

