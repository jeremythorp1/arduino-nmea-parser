This is a library for Arduino to encode or decode NMEA 0183 Statement.

Available functions:
- encode(char)  - To encode/process a character. Will return TRUE if found a valid NMEA Statement.
- getTermsCount() - To get the number of terms found.
- getTerm(byte) - To get the term at index that you want.
- createStatement(String) - To initialize a statement.
- append(char/int/float/double) - To append/add new term to the statement.
- clearStatement()  - To clear current statement.
- getStatement()  - To get the formatted NMEA statement.
- getIncompleteStatementsCount()  - To see the stat of the library. Mainly used for debugging only.
