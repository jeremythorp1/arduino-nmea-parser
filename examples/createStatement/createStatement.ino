/*
This program will create a random NMEA 0183 statement every second.
*/

#include <NmeaParser.h>

NmeaParser parser;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	parser.createStatement("AAAAA");
	parser.append(1);
	parser.append(2.0);
	parser.append('B');
	parser.append((int)millis());

	Serial.println(parser.getStatement());

	delay(1000);
}
