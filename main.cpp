#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/types.h>
using namespace std;


const int LengthOfKeyWord = 50; // An array that has all the keywords we're searching for.
				                // Will be utilized in a function to check for keywords.
int n1 = 0, N1 = 0;
int str1n2 = 0, str1N2 = 0;
int str2n2 = 0, str2N2 = 0;
int pro_size = 0;
int pro_vocab = 0;
double pro_volume = 0.0;
double difficulty = 0.0;
double level = 0.0;
double effort = 0.0;
bool contains = false;
bool firstToken = true;
bool firstHal = true;

vector<double> str1Points;
vector<double> str2Points;

void separator()
{
    cout << endl << "========================================================================================================================";
    cout << "========================================================================================================================" << endl;
}


char ActualKeyWords[LengthOfKeyWord][15] { // 41 total completely alpabetical
"Auto","bool","Break","Case","Catch",
"Char","cin>>","Class","const","cout<<",
"Default","Double","else", "endl", "enum","float",
"for","if","int","long", "namespace", "new","operator",
"private","protected","public","short",
"signed","sizeof", "static","struct","switch",
"This","Throw","try","unsigned","return",
"using", "virtual","void","while"
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

bool isValidIdentifier(char* str) // If what separates the characters/strings is an valid identifier return true
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

//remove all the comments from the string of cpp code
string removeComments(string prgm)
{
    int n = prgm.length();
    string res;

    //single-line comment
    bool s_cmt = false;

    //multi-line comment
    bool m_cmt = false;


    for (int i=0; i<n; i++)
    {
        if (s_cmt == true && prgm[i] == '\n')
            s_cmt = false;

        else if  (m_cmt == true && prgm[i] == '*' && prgm[i+1] == '/')
            m_cmt = false,  i++;

        else if (s_cmt || m_cmt)
            continue;

        else if (prgm[i] == '/' && prgm[i+1] == '/')
            s_cmt = true, i++;
        else if (prgm[i] == '/' && prgm[i+1] == '*')
            m_cmt = true,  i++;

        else  res += prgm[i];
    }
    return res;
}

string removeSpacesAndNewlines(string str){
    int len = str.length();
    string result;

    //checks for any empty spaces of \n
    for(int i = 0; i < len; i++){
        if(str[i] == ' '){
            int j = i;
            while(str[j + 1] == ' ')
            {
                str.erase(j, 1);
                j++;
            }
        }

        else if((str[i] == '.' || str[i] == ',' ||
                 str[i] == '?' ||str[i] == '!' ||
                 str[i] == ';') && i - 1 >= 0){
                    if(str[i - 1] == ' '){
                        str.erase(i - 1, 1);
                    }
        }

        else if(str[i] == '\n')
        {
            str.erase(i, 1);
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
    string result = "";

    //loop until right passes len or left passes right
    while (right <= len && left <= right)
    {
        //checks if the current right index is a delimeter
        if (isDelimiter(str[right]) == false)
        {
            //checks if the content is a string (enclosed in single or double quotations)
            if(str[right] == '\'')
            {
                right++;
                while(str[right] != '\'')
                {
                    right++;
                }
                token += "\'S\'";
            }
            else if(str[right] == '\"')
            {
                right++;
                while(str[right] != '\"')
                {
                    right++;
                }
                token += "\'S\'";
            }
            right++;
        }
        //Checks if the current index is a delimeter, and the indices are aligned
        if (isDelimiter(str[right]) == true && left == right) {
            //If the current index is a parenthesis or bracket, simply add the character to the tokens
            if(str[right] == '(' || str[right] == ')' || str[right] == '{' || str[right] == '}')
            {
                token += str[right];
            }
            if(str[right+1] == '/')
            {
                token += "C";
                right += 2;
                while(str[right] != '\n')
                {
                    right++;
                }
            }

            else if(str[right+1] == '*')
            {
                right += 2;
                while(str[right] != '*' && str[right+1] != '/')
                {
                    token += str[right];
                    right++;
                }
            }
            //If the current index is an operator, add the character to the tokens
            if (isOperator(str[right]) == true)
            {
                token += str[right];
            }
            right++;
            //reset the indices alignment
            left = right;
        }
        //If the current index is a delimeter, but the indices are not aligned, OR if the right index has reached len and the indices are not aligned
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
              char* subStr = subString(str, left, right - 1);

            //If the current index is a keyword, add the first character of the keyword to the tokens
            if (isKeyword(subStr) == true)
                token += subStr[0];
            //If the current index is an Integer, add the character "L"
            else if (isInteger(subStr) == true)
                token += "N";
            //If the current index is a Real Number, add the character "L"
            else if (isRealNumber(subStr) == true)
                token += "N";
            //If the current index is an Identifier, add the character "I"
            else if (isValidIdentifier(subStr) == true
                    && isDelimiter(str[right - 1]) == false)
                token += "I";
            //If the current index is none of the above, then an error has occurred
            else if (isValidIdentifier(subStr) == false
                    && isDelimiter(str[right - 1]) == false)
                return "invalid";

            if(firstToken)
            {
                if(isValidIdentifier(subStr) || isInteger(subStr) || isRealNumber(subStr))
                {
                    str1N2++;
                    if(result.find(subStr) == -1)
                    {
                        result += subStr;
                        str1n2++;
                    }
                }
            }
            else if (!firstToken)
            {
                if(isValidIdentifier(subStr) || isInteger(subStr) || isRealNumber(subStr))
                {
                    str2N2++;
                    if(result.find(subStr) == -1)
                    {
                        result += subStr;
                        str2n2++;
                    }
                }
            }
            //reset indices
            left = right;
        }
    }
    if(firstToken)
        firstToken = false;
    else
        firstToken = true;

    token.erase(token.end() - 1, token.end());
    token = removeSpacesAndNewlines(token);
    return token;
}

double simpleComparison(string str1, string str2)
{
    double points = 0;
    int i = 0;
    int longer, shorter;
    int len1 = str1.length();
    int len2 = str2.length();

    if(str1.compare(str2) == 0)
    {
        return 100.0;
    }

    if(len1 < len2)
    {
        longer = len2;
        shorter = len1;
    }
    else if(len2 < len1)
    {
        longer = len1;
        shorter = len2;
    }
    while (i <= shorter)
    {
        if(str1[i] == str2[i])
        {
            points += 2;
        }
        else if(str1[i] == str2[i-1] || str1[i] == str2[i+1])
        {
            points += 1;
        }
        i++;
    }

    if(((points / (longer * 1.0)) * 100.0) > 100)
        return 100.0;
    else
        return ((points / (longer * 1.0)) * 100.0);
}

void halsteadsMetric(string s)
{
    int i = 0, j = 0;
    int total = 0;
    char str[s.length()+1];
    strcpy(str,s.c_str());
    int len = strlen(str);
    string result = "";

    while(i < len)
    {
        if(isOperator(str[i]))
        {
            total++;
            if(result.length() == 0)
            {
                result += str[i];
            }
            while(j < result.length() && contains == false)
            {
                if(result[j] == str[i])
                {
                    contains = true;
                }
                j++;
            }
            if(!contains)
                result += str[i];

            j = 0;
        }
        contains = false;
        i++;
    }

    n1 = result.length();
    N1 = total;

    if(firstHal)
    {
        str1Points.push_back(n1);
        str1Points.push_back(N1);
        str1Points.push_back(str1n2);
        str1Points.push_back(str1N2);

        //program size is the sum of
        //all operands and operators
        pro_size = N1 + str1N2;
        str1Points.push_back(pro_size);

        // Size of the vocabulary can be
        // defined as sum of distinct operators and operands
        pro_vocab = n1 + str1n2;
        str1Points.push_back(pro_vocab);

        // the program volume is defined as follows:
        // Volume = size * log (pro_vocab)
        pro_volume = pro_size * log2(pro_vocab);
        str1Points.push_back(pro_volume);

        // Difficulty = ( n1/2 ) * ( N2/n2 ) and level = 1/difficulty
        difficulty = (n1 / 2.0) * (double(str1N2)/double(str1n2));
        str1Points.push_back(difficulty);
    }
    else
    {
        str2Points.push_back(n1);
        str2Points.push_back(N1);
        str2Points.push_back(str2n2);
        str2Points.push_back(str2N2);

        //program size is the sum of
        //all operands and operators
        pro_size = N1 + str2N2;
        str2Points.push_back(pro_size);

        // Size of the vocabulary can be
        // defined as sum of distinct operators and operands
        pro_vocab = n1 + str2n2;
        str2Points.push_back(pro_vocab);


        // the program volume is defined as follows:
        // Volume = size * log (pro_vocab)
        pro_volume = pro_size * log2(pro_vocab);
        str2Points.push_back(pro_volume);


        // Difficulty = ( n1/2 ) * ( N2/n2 ) and level = 1/difficulty
        difficulty = (n1 / 2.0) * (double(str2N2)/double(str2n2));
        str2Points.push_back(difficulty);
    }

    if(firstHal)
        firstHal = false;
    else
        firstHal = true;

}

double halsteadsComparison(string str1, string str2)
{
    double operatorTotal, operandTotal, sizeTotal;
    double vocabTotal, volumeTotal, difficultyTotal;
    double operatorDiff, operandDiff, sizeDiff;
    double vocabDiff, volumeDiff, difficultyDiff;
    double results;
    halsteadsMetric(str1);
    halsteadsMetric(str2);

    if(str1Points.at(0) == 0 && str2Points.at(0) == 0)
        operatorTotal = 0;
    else if(str1Points.at(0) == 0 && str2Points.at(0) != 0)
        operatorTotal = str2Points.at(1) / str2Points.at(0);
    else if(str2Points.at(0) == 0 && str1Points.at(0) != 0)
        operatorTotal = str1Points.at(1) / str1Points.at(0);
    else
        operatorTotal = (str1Points.at(1) / str1Points.at(0)) + (str2Points.at(1) / str2Points.at(0));

    if(str1Points.at(2) == 0 && str2Points.at(2) == 0)
        operandTotal = 0;
    else if(str1Points.at(2) == 0 && str2Points.at(2) != 0)
        operandTotal = str2Points.at(3) / str2Points.at(2);
    else if(str2Points.at(2) == 0 && str1Points.at(2) != 0)
        operandTotal = str1Points.at(3) / str1Points.at(2);
    else
        operandTotal = (str1Points.at(3) / str1Points.at(2)) + (str2Points.at(3) / str2Points.at(2));

    sizeTotal = str1Points.at(4) + str2Points.at(4);
    vocabTotal = str1Points.at(5) + str2Points.at(5);
    volumeTotal = str1Points.at(6) + str2Points.at(6);
    difficultyTotal = str1Points.at(7) + str2Points.at(7);

    if(str1Points.at(0) == 0 && str2Points.at(0) == 0)
        operatorDiff = 0;
    else if(str1Points.at(0) == 0 && str2Points.at(0) != 0)
        operatorDiff = str2Points.at(1) / str2Points.at(0);
    else if(str2Points.at(0) == 0 && str1Points.at(0) != 0)
        operatorDiff = str1Points.at(1) / str1Points.at(0);
    else
        operatorDiff = abs((str1Points.at(1) / str1Points.at(0)) - (str2Points.at(1) / str2Points.at(0)));

    if(str1Points.at(2) == 0 && str2Points.at(2) == 0)
        operandDiff = 0;
    else if(str1Points.at(2) == 0 && str2Points.at(2) != 0)
        operandDiff = str2Points.at(3) / str2Points.at(2);
    else if(str2Points.at(2) == 0 && str1Points.at(2) != 0)
        operandDiff = str1Points.at(3) / str1Points.at(2);
    else
        operandDiff = abs((str1Points.at(3) / str1Points.at(2)) - (str2Points.at(3) / str2Points.at(2)));

    sizeDiff = abs(str1Points.at(4) - str2Points.at(4));
    vocabDiff = abs(str1Points.at(5) - str2Points.at(5));
    volumeDiff = abs(str1Points.at(6) - str2Points.at(6));
    difficultyDiff = abs(str1Points.at(7) - str2Points.at(7));

    str1Points.clear();
    str2Points.clear();

    if(abs(100 - ((25*(operatorDiff/operatorTotal))+(25*(operandDiff/operandTotal))+(20*(sizeDiff/sizeTotal))
       +(30*(vocabDiff/vocabTotal))+(20*(volumeDiff/volumeTotal))+(20*(difficultyDiff/difficultyTotal)))) < 0)
    {
       return 0.0;
    }
    else
        return
        {
            abs(100 - ((25*(operatorDiff/operatorTotal))+(25*(operandDiff/operandTotal))+(20*(sizeDiff/sizeTotal))
            +(30*(vocabDiff/vocabTotal))+(20*(volumeDiff/volumeTotal))+(20*(difficultyDiff/difficultyTotal))))
        };
}

string inputFileName(string fileName, string pathName) //initializing our method that takes in strings
{
    ifstream file; // initializing an Input stream class to operate on files.
    int length;
    file.open(pathName + "/" + fileName); //opening the file that is given
    file.seekg(0, ios::end); //Sets the position of the next character to be extracted from the input stream.
    length = file.tellg(); //returns the current “get” position of the pointer in the stream and then is set as length1
    file.seekg(0, ios::beg);
    char buf1[length]; //initializing our character array
    file.read(buf1, length); //Extracts n characters from the stream and stores them in the  character array pointed to by s
    file.close(); //Closes the file currently associated with the object,
  	return buf1; //return our character array
}

vector<int> combinations(int n, int k)
{
    string bitmask(k, 1); // K leading 1's
    bitmask.resize(n, 0); // N-K trailing 0's
    vector<int> combos;

    // print integers and permute bitmask
    do
    {
        for (int i = 0; i < n; i++) // [0..N-1] integers
        {
            if (bitmask[i])
                combos.push_back(i);
        }
    } while (prev_permutation(bitmask.begin(), bitmask.end()));

    return combos;
}

int main()
{
    vector<string> files;
    vector<string> cppfiles;
    DIR *dr;
    struct dirent *en;
    string p;
    char* path;
    bool validPath = false;
    int i, s;
    while(!validPath)
    {
        cout << "Enter the file path for the desired directory: ";
        cin >> p;
        cout << endl;
        path = &p[0];

        dr = opendir(path);
        if (dr)
        {
            validPath = true;
            while ((en = readdir(dr)) != NULL)
            {
                files.push_back(en->d_name);
            }

        }
        else
        {
            cout << "Invalid file path. Try again." << endl;
            separator();
        }

        i = 0;
        s = files.size();

        separator();

        while(i < s && validPath)
        {
            if(files.at(i).find(".cpp") != string::npos)
            {
                cout << files.at(i) << "    ";
                cppfiles.push_back(files.at(i));
            }
            i++;
        }
        cout << endl;
        if(cppfiles.size() == 0 && validPath)
        {
            validPath = false;
            cout << endl << "Empty Directory. Please choose another." << endl;
        }
     }
    closedir(dr); //close all directory
    int totalFiles = cppfiles.size();
    vector<int> combos = combinations(totalFiles, 2);
    char choice;
    string str1;
    string str2;
    int a, b;
    double sim;

    while(true)
    {
        separator();

        bool invalid = true;

        while(invalid)
        {
            cout << "Choose which type of comparison to perform:" << endl
                 << "Simple Text Comparison (with Comments) - 1" << endl
                 << "Simple Text Comparison (without Comments) - 2" << endl
                 << "Halstead's Metric Comparison - 3" << endl
                 << "Or enter 'q' to quit." << endl
                 << "Enter your selection: ";
            cin >> choice;
            cout << endl;

            if(choice == 'Q' || choice == 'q')
                return 0;
            if(choice == '1' || choice == '2' || choice == '3')
                invalid = false;
            else
            {
                cout << "Invalid choice, please try again." << endl;
                separator();
            }
        }
        a = 0;
        b = 1;
        while(b < combos.size())
        {
            str1 = inputFileName(cppfiles.at(combos.at(a)), path);
            str2 = inputFileName(cppfiles.at(combos.at(b)), path);

            if(choice == '1')
            {
                sim = simpleComparison(getToken(str1), getToken(str2));
                cout << "(" << cppfiles.at(combos.at(a)) << ", " << cppfiles.at(combos.at(b)) << "): " << setprecision(4)
                     << sim << "% Similarity w/ Comments.";
                if(sim > 80.0)
                    cout << "  --INVESTIGATION RECOMMENDED--";
                cout << endl;
            }
            else if(choice == '2')
            {
                string noCommentsStr1 = getToken(removeComments(str1));
                string noCommentsStr2 = getToken(removeComments(str2));
                sim = simpleComparison(noCommentsStr1, noCommentsStr2);
                cout << "(" << cppfiles.at(combos.at(a)) << ", " << cppfiles.at(combos.at(b)) << "): " << setprecision(4)
                     << sim << "% Similarity w/o Comments.";
                if(sim > 80.0)
                    cout << "  --INVESTIGATION RECOMMENDED--";
                cout << endl;
            }
            else if(choice == '3')
            {
                str1n2 = 0;
                str1N2 = 0;
                str2n2 = 0;
                str2N2 = 0;
                sim = halsteadsComparison(getToken(str1), getToken(str2));
                cout << "(" << cppfiles.at(combos.at(a)) << ", " << cppfiles.at(combos.at(b)) << "): " << setprecision(4)
                     << sim << "% Similarity using Halstead's Metric.";
                if(sim > 85.0)
                    cout << "  --INVESTIGATION RECOMMENDED--";
                cout << endl;
            }
            a += 2;
            b += 2;
        }
    }
}
