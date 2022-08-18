#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void readfile(char input[], int &index){
	ifstream file;
	file.open("testcase.txt");
	if (!file){
		cout << "The Test case could not be opened" << endl;
		exit(1);
	}
	while (!file.eof()){
		file >> input[index];
		index++;
	}
	//cout << input[i];
	//cout << input[index - 1];
	//cout << input[index - 2];

	input[index - 1] = '\0';
	index--;
	file.close();
}
void errorfile(string lexeme, string attr){
	ofstream file;
	file.open("error.txt", ios::app);
	file << "[ " << lexeme << " , " << attr << " ]" << endl;
	file.close();
}

void tokenfile(string lexeme, string attr){
	ofstream file;
	file.open("token.txt", ios::app);
	//cout << 7 << endl;
	//cout << lexeme << endl;
	file << "[ " << lexeme << " , " << attr << " ]" << endl;
	file.close();
}
bool checkkeyword(string accepted){
	string keywords[11];  //sort of a symbol table of all the built-in keywords
	keywords[0] = "int";
	keywords[1] = "float";
	keywords[2] = "char";
	keywords[3] = "double";
	keywords[4] = "loop";
	keywords[5] = "do-loop";
	keywords[6] = "tour";
	keywords[7] = "iff";
	keywords[8] = "else";
	keywords[9] = "input->";
	keywords[10] = "output<-";
	for (int i = 0; i < 10; i++){
		if (accepted == keywords[i]){
			return 1;
		}
	}
	return 0;
}
void Analyser(char input[], int index){
	int i = 0, j = 0, e = 0;
	char ch = input[i];
	char *buffer = new char[index];
	char *errbuffer = new char[index];
	int state = 0;
	int check_keyword = 0;
	bool flag = 0;

	while (ch != '\0'){
		if (state == 0){
			//cout << "State S" << endl;
			if (ch == '_' || (ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')){
				//cout << "State S 1" << endl;
				//cout << ch << endl;
				if ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'))
					check_keyword++;
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 1;
			}
			else if (ch == '{'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 4;
			}
			else if (ch == '}'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 5;
			}
			else if (ch == '('){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 6;
			}
			else if (ch == ')'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 7;
			}
			else if (ch == '['){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 8;
			}
			else if (ch == ']'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 9;
			}
			else if (ch == '<'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 10;
			}
			else if (ch == '>'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 11;
			}
			else if (ch == '/' || ch == '*' || ch == '-' || ch == '%'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else if (ch == '+'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 12;
			}
			else if (ch == ':'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 13;
			}
			else if (ch == '!'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 14;
			}
			else if (ch == '&'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 15;
			}
			else if (ch == '|'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 16;
			}
			else if (ch == '='){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 17;
			}
			else if (ch >= '0'&&ch <= '9'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 18;
			}
			else {
				//cout << "State S 2" << endl;
				errbuffer[e] = ch;
				e++;
				errbuffer[e] = '\0';
				i++;
				ch = input[i];
				errorfile(errbuffer, "error");
			}
		}
		if (state == 1){
			//cout << "State 1" << endl;
			//cout << ch << endl;
			if (ch >= '0' && ch <= '9'){
				//cout << "1" << endl;
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 2;
			}
			else if (ch == '_'){
				//cout << "2" << endl;
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 3;
			}
			else if (ch == '@' || (ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')){
				//cout << "3" << endl;
				if ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')){
					check_keyword++;
					if (check_keyword >= 3){
						i++;
						buffer[j] = ch;
						j++;
						buffer[j] = '\0';
						ch = input[i];
						flag = checkkeyword(buffer);
						if (flag == 1){
							tokenfile(buffer, "Keyword");
							j = 0;
							state = 0;
						}
						else{
							state = 1;
						}
					}
					else{
						buffer[j] = ch;
						i++;
						j++;
						ch = input[i];
						state = 1;
					}
				}
				else{
					buffer[j] = ch;
					i++;
					j++;
					ch = input[i];
					state = 1;
				}
			}
		}
		if (state == 2){
			//cout << "State 2" << endl;
			//cout << ch << endl;
			if (ch == '@' || (ch >= 'A'&& ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch >= '0' && ch <= '9')){
				//cout << "4" << endl;
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 1;
			}
			else if (ch == '_'){
				//cout << "5" << endl;
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 3;
			}
			else{
				//cout << "6" << endl;
				buffer[j] = ch;
				j++;
				buffer[j - 1] = '\0';
				tokenfile(buffer, "ID");
				state = 0;
			}
		}
		if (state == 3){
			//cout << "State 3" << endl;
			//cout << ch << endl;
			if (ch == '@' || (ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || ch == '_'){
				//cout << "7" << endl;
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 1;
			}
			else if (ch == '0' && ch <= '9'){
				//cout << "8" << endl;
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 2;
			}
			else{
				//cout << "9" << endl;
				buffer[j] = '\0';
				j = 0;
				tokenfile(buffer, "ID");
				state = 0;
			}
		}
		if (state == 4 || state == 5 || state == 6 || state == 7 || state == 8 || state == 9){
			buffer[j] = '\0';
			j = 0;
			tokenfile(buffer, "Punctuation");
			state = 0;
		}
		if (state == 10){
			if (ch == '>' || ch == '<'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else
			{
				buffer[j] = '\0';
				j = 0;
				tokenfile(buffer, "Operator");
				state = 0;
			}
		}
		if (state == 11){
			if (ch == '=' || ch == '>'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else
			{
				buffer[j] = '\0';
				j = 0;
				tokenfile(buffer, "Operator");
				state = 0;
			}
		}
		if (state == 12){
			if (ch == '+' || ch == '='){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else
			{
				buffer[j] = '\0';
				j = 0;
				tokenfile(buffer, "Operator");
				state = 0;
			}
		}
		if (state == 13){
			if (ch == '='){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else
			{
				errbuffer[e] = ch;
				e++;
				errbuffer[e] = '\0';
				i++;
				ch = input[i];
				errorfile(errbuffer, "error");
			}
		}
		if (state == 14){
			if (ch == '='){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else
			{
				errbuffer[e] = ch;
				e++;
				errbuffer[e] = '\0';
				i++;
				ch = input[i];
				errorfile(errbuffer, "error");
			}
		}
		if (state == 15){
			if (ch == '&'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else
			{
				errbuffer[e] = ch;
				e++;
				errbuffer[e] = '\0';
				i++;
				ch = input[i];
				errorfile(errbuffer, "error");
			}
		}
		if (state == 16){
			if (ch == '|'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else
			{
				errbuffer[e] = ch;
				e++;
				errbuffer[e] = '\0';
				i++;
				ch = input[i];
				errorfile(errbuffer, "error");
			}
		}
		if (state == 17){
			if (ch == '=' || ch == '<'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 27;
			}
			else
			{
				errbuffer[e] = ch;
				e++;
				errbuffer[e] = '\0';
				i++;
				ch = input[i];
				errorfile(errbuffer, "error");
			}
		}
		if (state == 18){
			if (ch >= '0'&&ch <= '9'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 18;
			}
			else if (ch == '.'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 19;
			}
			else if (ch == 'E'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 20;
			}
			else{
				buffer[j] = ch;
				j++;
				buffer[j - 1] = '\0';
				tokenfile(buffer, "Number");
				state = 0;
			}
		}
		if (state == 19){
			if (ch >= '0'&&ch <= '9'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 21;
			}
			else{
				errbuffer[e] = ch;
				e++;
				errbuffer[e] = '\0';
				i++;
				ch = input[i];
				errorfile(errbuffer, "error");
			}
		}
		if (state == 21){
			if (ch >= '0'&&ch <= '9'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 21;
			}
			else if (ch == 'E'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 20;
			}
			else{
				buffer[j] = ch;
				j++;
				buffer[j - 1] = '\0';
				tokenfile(buffer, "Number");
				state = 0;
			}
		}
		if (state == 20){
			if (ch >= '0'&&ch <= '9'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 22;
			}
			else{
				buffer[j] = ch;
				j++;
				buffer[j - 1] = '\0';
				tokenfile(buffer, "Number");
				state = 0;
			}
		}
		if (state == 22){
			if (ch >= '0'&&ch <= '9'){
				buffer[j] = ch;
				i++;
				j++;
				ch = input[i];
				state = 22;
			}
			else{
				buffer[j] = ch;
				j++;
				buffer[j - 1] = '\0';
				tokenfile(buffer, "Number");
				state = 0;
			}
		}
		if (state == 27){ //sort of a common final state of different operator states
			buffer[j] = '\0';
			j = 0;
			tokenfile(buffer, "Operator");
			state = 0;
		}
	}


}
int main(){
	char *input = new char[10000]; //making a pointer array because the size is unknown
	int index = 0;
	readfile(input, index);
	cout << "-----------Lexical Analysis Phase-----------" << endl;
	cout << "-----------The Source code is : -----------" << endl << endl;;
	for (int i = 0; i < index; i++)
		cout << input[i];
	cout << endl << endl;
	Analyser(input, index);
	cout << "-----------The token.txt is updated accordingly-----------" << endl;
	cout << "-----------The error.txt is updated accordingly-----------" << endl << endl;;

}
