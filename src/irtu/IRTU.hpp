#ifndef IRTU_H_
#define IRTU_H_

#include <list>
#include <iostream>
#include <string>
#include "nvwa/debug_new.h"

using std::list;
using std::istream;
using std::ostream;

const unsigned char TAG_TYPE_BYTE = 10;
const unsigned char TAG_TYPE_SHORT = 11;
const unsigned char TAG_TYPE_INT = 12;
const unsigned char TAG_TYPE_LONG = 13;
const unsigned char TAG_TYPE_FLOAT = 20;
const unsigned char TAG_TYPE_DOUBLE = 21;
const unsigned char TAG_TYPE_STRING = 30;
const unsigned char TAG_TYPE_LIST = 31;
const unsigned char TAG_TYPE_IRTU = 32;
const unsigned char TAG_END_IRTU = 255;

const unsigned char STATE_BEGINNING = 0;
const unsigned char STATE_READING_TYPE = 1;
const unsigned char STATE_READING_NAME_LENGTH = 2;
const unsigned char STATE_READING_NAME = 3;
const unsigned char STATE_READING_LENGTH = 4;
const unsigned char STATE_READING_CONTENT = 5;

class IRTUElement {
public:
	std::string name;

	virtual void read(istream* stream) = 0;
	virtual void write(ostream* stream) = 0;
	virtual std::string toString(int initIndent) = 0;
	virtual ~IRTUElement() = 0;
};

class IRTUObject: public IRTUElement {
public:
	list<IRTUElement*> children;
	IRTUObject();

	void readNew(istream* stream);
	void read(istream* stream);
	void write(ostream* stream);
	void add(IRTUElement* child);
	std::string toString(int initIndent);
	~IRTUObject();
};

class IRTUByte: public IRTUElement {
public:
	char value;
	IRTUByte(char);
	void read(istream* stream);
	void write(ostream* stream);
	std::string toString(int initIndent);
};

class IRTUShort: public IRTUElement {
public:
	short value;
	IRTUShort(short);
	void read(istream* stream);
	void write(ostream* stream);
	std::string toString(int initIndent);
};

class IRTUInt: public IRTUElement {
public:
	int value;
	IRTUInt(int);
	void read(istream* stream);
	void write(ostream* stream);
	std::string toString(int initIndent);
};

class IRTULong: public IRTUElement {
public:
	long value;
	IRTULong(long);
	void read(istream* stream);
	void write(ostream* stream);
	std::string toString(int initIndent);
};

class IRTUFloat: public IRTUElement {
public:
	float value;
	IRTUFloat(float);
	void read(istream* stream);
	void write(ostream* stream);
	std::string toString(int initIndent);
};

class IRTUDouble: public IRTUElement {
public:
	double value;
	IRTUDouble(double);
	void read(istream* stream);
	void write(ostream* stream);
	std::string toString(int initIndent);
};

class IRTUList: public IRTUElement {
public:
	IRTUList();
	void read(istream* stream);
	void write(ostream* stream) = 0;
	std::string toString(int initIndent);
};

std::string createIndent(int indent);

std::string bToString(char b);
std::string sToString(short s);
std::string iToString(int i);
std::string lToString(long l);
std::string fToString(float f);
std::string dToString(double d);

IRTUByte* readByte(istream* stream);
IRTUShort* readShort(istream* stream);
IRTUInt* readInt(istream* stream);
IRTULong* readLong(istream* stream);
IRTUFloat* readFloat(istream* stream);
IRTUDouble* readDouble(istream* stream);
IRTUObject* readIRTU(istream* stream);

#endif
