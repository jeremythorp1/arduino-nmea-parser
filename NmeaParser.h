/*
Author: Ahmad Shahril Bin Mohd Ghani
Date: 25 December 2017
Description: This library allows the user to parse or create NMEA 0183 standard statement.
*/

#ifndef NmeaParser_H_INCLUDED
#define NmeaParser_H_INCLUDED

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define MAX_TERM_SIZE 25  //Max size of each term
#define MAX_TERM_COUNT 50 //Max number of terms

class NmeaParser
{
  public:
	NmeaParser();

	//For decipher
	bool encode(char c);
	byte getTermsCount();
	String getTerm(byte index);

	//For encoding
	void createStatement(String statementId);
	void append(String str);
	void append(char c);
	void append(int num);
	void append(float num);
	void append(double num);
	void clearStatement();
	String getStatement();

	//For debugging
	unsigned long getIncompleteStatementsCount();

  private:
	//For decipher
	char currentTerm[MAX_TERM_SIZE];
	String terms[MAX_TERM_COUNT];
	byte parity, termCount, currentTermLength;
	bool isChecksumTerm, validStatement, wasCompleteStatement;

	//For encoding
	String messageConstruct;

	//For debugging
	unsigned long incompleteStatements;

	//Private functions
	void processCurrentTerm();
	byte calculateChecksum(String statement);
	int hexStringToInt(String str);
	int fromHex(char a);
	String byteToHexString(byte num);
};

#endif