
#include "token_parsing.h"

#include "endless_array_i.h"
#include "endless_array_p.h"

string read_token(istream& input)
{
	//input >> noskipws;

	endless_array_i::next_layer();

	int string_length = 0;
	// The state name refers to the most recently encountered character or known type, not the expected character or type.
	enum {PREFIX_WHITESPACE, 
		  ALPHANUM, // Generate an alpha-numeric token. 
		  SIGN, INTEGER, DECIMAL_POINT, FIXED, EXP, EXP_SIGN, EXP_INT, // Generating an integer or fixed-point or floating-point token.
		  LEFT_QUOTE, STRING, ESCAPE_CHAR, RIGHT_QUOTE, // Generating a string token.
		  SYMBOL, // Generating a single symbol token. 
		  COMPLETE} curr_state = PREFIX_WHITESPACE;
	//enum {USE_CHAR, IGNORE_CHAR, PUTBACK_CHAR} char_state = USE_CHAR;
	do
	{
		char char_buffer;
		char_buffer = input.peek(); // The character will always be popped from the stream unless the new state is "COMPLETE", which indicates that the character may belong to the next token.
		if (input.eof() || input.fail())
		{
			curr_state = COMPLETE;
			break;
		}

		// Skip any comments that may be present:
		if ((char_buffer == '{') && (curr_state != ESCAPE_CHAR))
		{
			input.get();
			while (char_buffer != '}')
			{
				char_buffer = input.get();
				if (input.eof() || input.fail())
				{
					curr_state = COMPLETE;
					break;
				}
			}
			char_buffer = input.peek();
		}

		// Process the current state.
		if (curr_state == PREFIX_WHITESPACE)
		{
			if (isalpha(char_buffer) || char_buffer == '_')
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = ALPHANUM;
			}
			else if ((char_buffer == '+') || (char_buffer == '-'))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = SIGN;
			}
			else if (isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = INTEGER;
			}
			else if (char_buffer == '.')
			{
				endless_array_i::write_data(0,string_length, 1, 2, "0."); // Pad a 0 before the decimal point.
				string_length += 2;
				curr_state = DECIMAL_POINT;
			}
			else if (char_buffer == '\"')
			{
				curr_state = LEFT_QUOTE;
			}
			else if (isspace(char_buffer))
			{
				curr_state = PREFIX_WHITESPACE;
			}
			else
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = SYMBOL;
			}
		}
		else if (curr_state == ALPHANUM) // Generate an alpha-numeric token.  
		{
			if (isalpha(char_buffer) || char_buffer == '_' || isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = ALPHANUM;
			}
			else 
			{
				curr_state = COMPLETE;
			}
		}
		else if (curr_state == SIGN) // Generating an integer or fixed-point or floating-point token.
		{
			if (isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = INTEGER;
			}
			else if (char_buffer == '.')
			{
				endless_array_i::write_data(0,string_length, 1, 2, "0."); // Pad a 0 before the decimal point.
				string_length += 2;
				curr_state = DECIMAL_POINT;
			}
			else
			{
				curr_state = COMPLETE;
			}
		}	
		else if (curr_state == INTEGER)
		{
			if (isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = INTEGER;
			}
			else if (char_buffer == '.')
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = DECIMAL_POINT;
			}
			else
			{
				curr_state = COMPLETE;
			}
		}
		else if (curr_state == DECIMAL_POINT)
		{
			if (isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = FIXED;
			}
			else if (char_buffer == 'e')
			{
				endless_array_i::write_data(0,string_length, 1, 2, "0e"); // Pad a 0 after the decimal point.
				string_length += 2;
				curr_state = EXP;
			}
			else
			{
				endless_array_i::write_data(0,string_length, 1, 1, "0"); // Pad a 0 after the decimal point.
				string_length += 1;
				curr_state = COMPLETE;
			}
		}
		else if	(curr_state == FIXED)
		{
			if (isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = FIXED;
			}
			else if (char_buffer == 'e')
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = EXP;
			}
			else
			{
				curr_state = COMPLETE;
			}
		}
		else if	(curr_state == EXP)
		{
			if ((char_buffer == '+') || (char_buffer == '-'))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = EXP_SIGN;
			}
			else if (isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = EXP_INT;
			}
			else
			{
				endless_array_i::write_data(0,string_length, 1, 1, "0"); // Pad a 0.
				string_length += 1;
				curr_state = COMPLETE;
			}
		}
		else if	(curr_state == EXP_SIGN)
		{
			if (isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = EXP_INT;
			}
			else
			{
				endless_array_i::write_data(0,string_length, 1, 1, "0"); // Pad a 0 after the sign.
				string_length += 1;
				curr_state = COMPLETE;
			}
		}
		else if (curr_state == EXP_INT)
		{
			if (isdigit(char_buffer))
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = EXP_INT;
			}
			else
			{
				curr_state = COMPLETE;
			}
		}
		else if (curr_state == LEFT_QUOTE || curr_state == STRING)
		{
			if (char_buffer == '\\')
			{
				curr_state = ESCAPE_CHAR;
			}
			else if (char_buffer == '\"')
			{
				curr_state = RIGHT_QUOTE;
			}
			else
			{
				endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
				string_length += 1;
				curr_state = STRING;
			}
		}
		else if (curr_state == ESCAPE_CHAR)
		{
			endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
			string_length += 1;
			curr_state = STRING;
		}
		else if (curr_state == RIGHT_QUOTE)
		{
			curr_state = COMPLETE;
		}
		else if (curr_state == SYMBOL)
		{
			curr_state = COMPLETE;
		}
		else
		{
			curr_state = COMPLETE;
		}

		if (curr_state != COMPLETE) // Always pop the character unless the current state is "COMPLETE", which indicates that the character may belong to the next token.
		{
			input.get();
		}
	} while (curr_state != COMPLETE);

	char* c_token_buffer = new char[string_length];
	endless_array_i::read_data(0,0,1,string_length,c_token_buffer);

	string the_token = string(c_token_buffer,string_length);
	delete[] c_token_buffer;

	endless_array_i::previous_layer();

	return the_token;
}


string encode_string(const string& the_string)
{
	endless_array_i::next_layer();

	int string_length = 0;
	endless_array_i::write_data(0,string_length, 1, 1, "\"");
	string_length += 1;
	for (int i = 0; i < (int) the_string.length(); i++)
	{
		if ((the_string[i] == '\"') || (the_string[i] == '\\') || (the_string[i] == '{') || (the_string[i] == '}'))
		{ // Write the escape character (\) if needed:
			endless_array_i::write_data(0,string_length, 1, 1, "\\");
			string_length += 1;
		}
		char char_buffer = the_string[i];
		endless_array_i::write_data(0,string_length, 1, 1, &char_buffer);
		string_length += 1;
	}
	endless_array_i::write_data(0,string_length, 1, 2, "\"\0");
	string_length += 2;

	char* c_str_buffer = new char[string_length];
	endless_array_i::read_data(0,0,1,string_length,c_str_buffer);

	string encoded_string = string(c_str_buffer);
	delete[] c_str_buffer;

	endless_array_i::previous_layer();

	return encoded_string;
}


char* get_c_str(const string& the_string)
{
	unsigned int max_c_str_length = 100;
	char* the_c_str = new char[max_c_str_length];
	for (unsigned int i = 0; (i <= the_string.length()) && (i <= max_c_str_length-1); i++)
	{
		if ((i < the_string.length()) && (i < max_c_str_length-1))
		{
			the_c_str[i] = the_string[i];
		}
		else
		{
			the_c_str[i] = '\0'; // End the C string with the null character.
		}
	}
	return the_c_str;
}
