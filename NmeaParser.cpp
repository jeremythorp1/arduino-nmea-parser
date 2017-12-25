/*
Author: Ahmad Shahril Bin Mohd Ghani
Date: 25 December 2017
Description: This library allows the user to parse or create NMEA 0183 standard statement.
*/

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "NmeaParser.h"

NmeaParser::NmeaParser()
{
	currentTerm[0] = '\0';
	currentTermLength = 0;
	termCount = 0;
	parity = 0;
	isChecksumTerm = false;
	validStatement = false;
	wasCompleteStatement = true;

	messageConstruct = "";

	incompleteStatements = 0;
}

//For decipher ==================================================================================================================
bool NmeaParser::encode(char c)
{
	switch (c)
	{
	case ',': // term terminators
		parity ^= (byte)c;
		processCurrentTerm();
		break;

	case '*':
		isChecksumTerm = true;
		processCurrentTerm();
		break;

	case '\r':
	case '\n':
		processCurrentTerm();
		break;

	case '$': // sentence begin
		currentTerm[0] = '\0';
		currentTermLength = 0;
		termCount = 0;
		parity = 0;
		isChecksumTerm = false;
		validStatement = false;

		if (!wasCompleteStatement)
		{
			incompleteStatements++;
		}

		wasCompleteStatement = false;

		break;

	default: // ordinary characters
		if (currentTermLength < MAX_TERM_SIZE)
		{
			currentTerm[currentTermLength++] = c;
		}

		if (!isChecksumTerm)
		{
			parity ^= c;
		}
	}

	return validStatement;
}

void NmeaParser::processCurrentTerm()
{
	if (!wasCompleteStatement)
	{
		currentTerm[currentTermLength] = '\0';

		if (termCount < MAX_TERM_COUNT)
		{
			terms[termCount++] = String(currentTerm);
		}

		if (isChecksumTerm)
		{
			validStatement = hexStringToInt(currentTerm) == parity;
			wasCompleteStatement = validStatement;
		}

		currentTermLength = 0;
	}
	else {
		validStatement = false;
	}
}

int NmeaParser::hexStringToInt(String str)
{
	int value = 0;
	byte strLength = str.length();

	for (byte i = 0; i < strLength; i++)
	{
		value += ceil(fromHex(str.charAt(i)) * pow(16, (strLength - i - 1)));
	}

	return value;
}

int NmeaParser::fromHex(char a)
{
	if (a >= 'A' && a <= 'F')
	{
		return a - 'A' + 10;
	}
	else if (a >= 'a' && a <= 'f')
	{
		return a - 'a' + 10;
	}
	else
	{
		return a - '0';
	}
}

byte NmeaParser::getTermsCount()
{
	return termCount;
}

String NmeaParser::getTerm(byte index)
{
	if (index < termCount)
	{
		return terms[index];
	}

	return "N/A";
}

//For encoding ==================================================================================================================
void NmeaParser::createStatement(String statementId)
{
	messageConstruct = statementId;
}

void NmeaParser::append(String str)
{
	messageConstruct += String(",");
	messageConstruct += str;
}

void NmeaParser::append(char c)
{
	append(String(c));
}

void NmeaParser::append(int num)
{
	append(String(num));
}

void NmeaParser::append(float num)
{
	append(String(num));
}

void NmeaParser::append(double num)
{
	append(String(num));
}

void NmeaParser::clearStatement()
{
	messageConstruct = "";
}

String NmeaParser::getStatement()
{
	return String("$") + messageConstruct + String("*") + byteToHexString(calculateChecksum(messageConstruct)) + String("\r\n");
}

byte NmeaParser::calculateChecksum(String statement)
{
	byte checksum = 0;
	char c;

	for (byte i = 0; i < statement.length(); i++)
	{
		c = statement.charAt(i);

		if (c != '$' && c != '*')
		{
			checksum ^= c;
		}
	}

	return checksum;
}

String NmeaParser::byteToHexString(byte num)
{
	String str = String(num, 16);

	if (str.length() % 2 != 0)
	{
		str = String("0") + str;
	}

	str.toUpperCase();

	return str;
}

//For debugging =================================================================================================================
unsigned long NmeaParser::getIncompleteStatementsCount()
{
	return incompleteStatements;
}