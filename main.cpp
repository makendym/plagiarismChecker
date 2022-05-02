#include <bits/stdc++.h> // basic file header that includes every standard library

using namespace std;

const int LengthOfKeyWord = 50; // An array that has all the keywords we're searching for.
				                // Will be utilized in a function to check for keywords.

char ActualKeyWords[LengthOfKeyWord][15] { // 38 total completely alpabetical
"Auto","bool","Break","Case","Catch",
"Char","cin>>","Class","Const","cout<<",
"Default","Double","else","enum","float",
"for","if","int","long","new","operator",
"private","protected","public","short",
"signed","sizeof""static","struct","switch",
"This","Throw","try","unsigned","return",
"virtual","void","while"
};

const int LengthOfDataType = 15; // An array that has all the data types we're searching for.
                                 // Will Will be utilized in a function to check for data types.

char dataType[LengthOfDataType][15]={ // 15 total
                                      //All the data types being searched
"bool","bool*"
"char","char*"
"double","double*"
"float","float*"
"int","int*"
"long","long*"
"string","string*"
"void"
};


const int LengthOfDelimiter = 16; // Characters that separate text strings declaration


char delimiter[LengthOfDelimiter][2]=
                    {" ","+","-","*",
                      "/",",",";",">",
                      "<","=","(",")",
                      "[","]","{","}"}; // The actual characters that separate text strings



const int LengthOfOperator = 14;; // Operators that separate text strings declaration


char OperatorLength[LengthOfOperator][2]= // The actual operators that separate text strings
                    {"+","-","*",
                     "/",">","<",
                     "=","!","&",
                     "|",".",":",
                     "?","~"};


const int LengthOfInteger = 10; // Declaration that counts integer Length


char integer[LengthOfInteger][2]={"0","1","2","3","4","5","6","7","8","9"}; // Counts integer length


bool isDelimiter(char ch) // If a character is a delimiter(separates strings) return true
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
    return (true);
    return (false);
}

bool isOperator(char ch) // If what separates the characters/strings is an operator return true
{
    if  (ch == '/' || ch == '>' || ch == '<' ||
        ch == '+' || ch == '-' || ch == '*' ||
        ch == '=')
    return (true);
    return (false);
}

bool isValidIdentifier(char* str) // If what separates the characters/strings is an valid identifier return true //confused...
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
    return (false);
    return (true);
}

bool isKeyword(char* str) // If what separates the characters/strings is a keyword (line 9-17) return true
{
int i;
  	for(i=0; i<LengthOfKeyWord; i++){
      if (!strcmp(str, ActualKeyWords[i]))
        		return (true);
    }
    return (false);
}

 bool isInteger(char* str) // If the string is an a integer return true
{

int i, len = strlen(str);

        if (len == 0)
            return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

bool isRealNumber(char* str) // If the string is a real number return true.
{
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

char* subString(char* str, int left, int right) //  Specifies the start position of a substring and counts how many characters are in the string.
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

const int keylen=50;

string removeComments(string prgm){
    int len = prgm.length();
    string result;
    bool comment = false;
    string commentType = "";

    //for loop will check for / sign, which may idicate upcoming comment
    for(int i = 0; i < len; i++){
        if(prgm[i] == '/'){
            if(prgm[i+1] == '/'){ //line is indeed a comment
                comment = true;
                commentType = "Slash";
            }

            else if(prgm[i+1] == '*'){ //line is indeed a comment
                comment = true;
                commentType = "Multi Line";
            }
        }

        else if(prgm[i] == '#') //sharp automatically means a comment
        {
            comment = true;
            commentType = "Sharp";
        }


        else{
            result += prgm[i]; //skip on to next char
        }

//determine when to stop removing characters
        while (comment == true){
            if(commentType == "Slash"){
                if(prgm[i] == '\n'){
                    comment == false;
                    commentType = "";
                }
                else{
                    i++;
                }
            }

            else if(commentType == "Multi Line"){
                if(prgm[i] == '*' && prgm[i+1] == '/'){
                    comment == false;
                    commentType = "";
                }
                else{
                    i++;
                }
            }

            else if(commentType == "Sharp"){
                if(prgm[i] == '/n'){
                    comment == false;
                    commentType = "";
                }
                else{
                    i++;
                }
            }
        }
    }
    return result;
}

string removeSpacesAndNewlines(string str){
    int len = str.length();
    string result;

    //checks for any empty spaces of \n
    for(int i = 0; i < len; i++){
        if(str[i] == ' '){
            if(str[i + 1] == ' '){
                str.erase(i, 1);
            }
        }

        else if((str[i] == '.' || str[i] == ',' ||
                 str[i] == '?' ||str[i] == '!' ||
                 str[i] == ';') && i - 1 >= 0){
                    if(str[i - 1] == ' '){
                        str.erase(i - 1, 1);
                    }
        }

         else{
            result += str[i];
         }
    }
    return result;
}


string getToken(string s)
{
    //Create new string one index larger than s
    char str[s.length()+1];
    //Create a copy of the string
    strcpy(str,s.c_str());

    int left = 0, right = 0;
    int len = strlen(str);
    string token;

    //loop until right passes len or left passes right
    while (right <= len && left <= right) {
        //checks if the current right index is a delimeter
        if (isDelimiter(str[right]) == false){
            //checks if the content is a string (enclosed in single or double quotations)
            if(str[right]=='\'')
            {
                right++;
                while(str[right]!='\'')
                {
                    right++;
                }
                token+="\'S\'";
            }
            else if(str[right]=='\"')
            {
                right++;
                while(str[right]!='\"')
                {
                    right++;
                }
                token+="\'S\'";
            }
            right++;
    }
        //Checks if the current index is a delimeter, and the indices are aligned
        if (isDelimiter(str[right]) == true && left == right) {
            //If the current index is a parenthesis or bracket, simply add the character to the tokens
            if(str[right]=='(' || str[right]==')' || str[right]=='{' || str[right]=='}')
            {
                token+=str[right];
            }
            //If the current index is an operator, add the character to the tokens
            if (isOperator(str[right]) == true)
            {
                token+=str[right];
            }
            right++;
            //reset the indices alignment
            left = right;
        }
        //If the current index is a delimeter, but the indices are not aligned
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
              char* subStr = subString(str, left, right - 1);

        //If the current index is a keyword, add the first character of the keyword to the tokens
        if (isKeyword(subStr) == true)
            token+=subStr[0];
        //If the current index is an Integer, add the character "L"
        else if (isInteger(subStr) == true)
            token+="L";
        //If the current index is a Real Number, add the character "L"
        else if (isRealNumber(subStr) == true)
            token+="L";
        //If the current index is an Identifier, add the character "I"
        else if (validIdentifier(subStr) == true
                && isDelimiter(str[right - 1]) == false)
            token+="I";
        //If the current index is none of the above, then an error has occurred
        else if (validIdentifier(subStr) == false
                && isDelimiter(str[right - 1]) == false)
            return "invalid";
        //reset indices
        left = right;
        }
    }
    return token;
}

//takes file input to covert file data into string for parsing further.
string inputFileName(string fileName) //initializing our method that takes in strings
{
 	ifstream file; // initializing an Input stream class to operate on files.
    int length;
    file.open(fileName); //opening the file that is given
    file.seekg(0, std::ios::end); //Sets the position of the next character to be extracted from the input stream.
    length = file1.tellg(); //returns the current “get” position of the pointer in the stream and then is set as length1
    file.seekg(0, std::ios::beg);
    char buf1[length]; //initializing our chararcter array
    file.read(buf1, length); //Extracts n characters from the stream and stores them in the  character array pointed to by s
    file.close(); //Closes the file currently associated with the object,
  	return buf1; //return our character array
}

string program1=inputFileName("file1.cpp"); //taking file into a string

#include <map>

    int N1=0, n1=0, n2=0, N2=0;
    for ( map<string, int>::iterator it=operator_counts.begin(); it != operator_counts.end(); it++ )
    {
        if ( (*it).second )
          n1++;
        N1 += (*it).second;
    }

    for ( map<string, int>::iterator it=operand_counts.begin(); it != operand_counts.end(); it++ )
    {
        if( (*it).second )
          n2++;
        N2 += (*it).second;
    }

set<string> operators;
map<string, int> operator_counts, operand_counts;

printf("n1:%d, n2:%d, N1:%d, N2:%d\n", n1, n2 , N1, N2);

// computations for halstead metrics

//program size is the sum of
//all operands and operators
int pro_size = N1 + N2;

// the program volume is defined as follows:
// Volume = size x log ( voc_size )
double pro_volume = size*log2(voc_size);

// Size of the vocabulary can be
// defined as sum of distinct operands and operators


// Difficulty = ( n1/2 ) x ( N2/n2 ) and level = 1/difficulty
double difficulty = (double(n1)/2) * (double(N2)/double(n2));
double level = (1/difficulty);

// effort = volume x difficulty
double effort = pro_volume*difficulty;

cout << "Size : " << pro_size << endl;
cout << "volume : " << pro_volume << endl;
cout << "Vocabulary Size : " << voc_size << endl;
cout << "difficulty : " << difficulty << endl;
cout << "level : " << level << endl;
cout << "effort : " << effort << endl;

int main {

}
