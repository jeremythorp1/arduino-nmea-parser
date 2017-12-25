/*
This program will parse the input from the SoftwareSerial and print each term in the NMEA Statement received.
*/

#include <SoftwareSerial.h>
#include <NmeaParser.h>

SoftwareSerial ss(2, 3);
NmeaParser parser;

void setup()
{
	Serial.begin(9600);
	ss.begin(9600);
}

void loop()
{
	if (ss.available())
	{
		char c = ss.read();

		if (parser.encode(c))
		{
			for (byte i = 0; i < parser.getTermsCount(); i++)
			{
				Serial.print(parser.getTerm(i));
				Serial.print('\t');
			}

			Serial.println(parser.getIncompleteStatementsCount()); //The lower this value, the better.
		}
	}
}
