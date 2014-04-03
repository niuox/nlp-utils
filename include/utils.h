#ifndef _UTILS_H_
#define _UTILS_H_ 

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Remove white characters at the beginning and  end of string 
 * @param "string str" "the string"
 * @return "string" "the trimed string"
 */
string trim(string str){
	int left,right;
	int len = str.size();
	for(left = 0;left < len && (str[left] == ' ' || str[left] == '\t' || str[left] == '\r' || str[left] == '\n') ; left++);
	for(right = len - 1;right >= 0 && (str[right] == ' ' || str[right] == '\t' || str[right] == '\r' || str[right] == '\n') ; right--);
	int cnt = right - left + 1;
	if ( cnt <= 0){
		return "";
	}
	else{
		return str.substr(left,cnt);
	}
}

/*
 * Split the string with the separtor of "whitespace" "\t" "\r" "\n"
 * @param "string str" "the string"
 * @return "vector<string>" "the result"
 */
vector<string> split(string str){
	vector<string> res;
	int left = 0,right = 0;
	int len = str.size();
	while(right < len){
		for(left = right;left < len && (str[left] == ' ' || str[left] == '\t' || str[left] == '\r' || str[left] == '\n') ; left++);
		if (left == len) break;
		for(right = left;right < len && str[right] != ' ' && str[right] != '\t' && str[right] != '\r' && str[right] != '\n' ; right++);
		res.push_back(str.substr(left,right - left));
	}
	return res;
}

/*
 * Get character from utf8 format string
 * @param "string str" "the string"
 * @return "vector<string>" "the result" 
 */
vector<string> get_character(string str){
	vector<string> chs;
	int len = str.size();
	int idx = 0;
	while(idx < len){
		if ( (str[idx] & 0x80) == 0 ){
			chs.push_back(str.substr(idx,1));
			idx++;
		}
		else if ( (str[idx] & 0xE0) == 0xC0 ){
			chs.push_back(str.substr(idx,2));
			idx += 2;
		}
		else if ( (str[idx] & 0xF0) == 0xE0 ){
			chs.push_back(str.substr(idx,3));
			idx += 3;
		}
		else if ( (str[idx] & 0xF8) == 0xF0){
			chs.push_back(str.substr(idx,4));
			idx += 4;
		}
		else{
			cout<< "Error: "<<"the str "<<str<<"is not encoded in utf8."<<endl;
			idx++;
		}
	}
	if ( idx != len ){
		cout<< "Error: "<<"the str "<<str<<"is not encoded in utf8."<<endl;
	}
	return chs;
}

vector<string> wordtypetest(string str){
	vector<string> chs;
	int len = str.size();
	int idx = 0;
	while(idx < len){
		if ( (str[idx] & 0x80) == 0 ){
			chs.push_back(str.substr(idx,1));
			idx++;
			cout<<"1"<<endl;
		}
		else if ( (str[idx] & 0xE0) == 0xC0 ){
			chs.push_back(str.substr(idx,2));
			idx += 2;
			cout<<"2"<<endl;
		}
		else if ( (str[idx] & 0xF0) == 0xE0 ){
			chs.push_back(str.substr(idx,3));
			idx += 3;
			cout<<"3"<<endl;
		}
		else if ( (str[idx] & 0xF8) == 0xF0){
			chs.push_back(str.substr(idx,4));
			idx += 4;
			cout<<"4"<<endl;
		}
		else{
			cout<< "Error: "<<"the str "<<str<<"is not encoded in utf8."<<endl;
			idx++;
		}
	}
	if ( idx != len ){
		cout<< "Error: "<<"the str "<<str<<"is not encoded in utf8."<<endl;
	}
	return chs;
}

/*
 * Get utf8 format string size based on character
 * @param "string str" "the string"
 * @return "int" "the size of the utf8 string size" 
 */
int getut8size(string str){
	int size = 0;
	int len = str.size();
	int idx = 0;
	while(idx < len){
		if ( (str[idx] & 0x80) == 0 ){
			size++;
			idx++;
		}
		else if ( (str[idx] & 0xE0) == 0xC0 ){
			size++;
			idx += 2;
		}
		else if ( (str[idx] & 0xF0) == 0xE0 ){
			size++;
			idx += 3;
		}
		else if ( (str[idx] & 0xF8) == 0xF0){
			size++;
			idx += 4;
		}
		else{
			cout<< "Error: "<<"the str "<<str<<"is not encoded in utf8."<<endl;
			idx++;
		}
	}
	if ( idx != len ){
		cout<< "Error: "<<"the str "<<str<<"is not encoded in utf8."<<endl;
	}
	return size;
}


/*
 * Convert utf string to unicode string
 * @param "string str" "the source utf8 string"
 * @return "wstring" "the unicode wstring"
 */
wstring utf82unicode(string src){
	if (src.size() == 0){
		return L"";
	}
	int size_s = src.size();
	//the size of unicode wstring is less than utf8 string
	int size_d = size_s + 10;
	wchar_t *des = new wchar_t[size_d];
	memset(des, 0, size_d * sizeof(wchar_t));
	int s = 0, d = 0;
	while (s < size_s && d < size_d){
		unsigned char c = src[s];
		if ((c & 0x80) == 0){
			des[d++] += src[s++];
		}
		else if((c & 0xE0) == 0xC0){
			wchar_t &wc = des[d++];
			wc = (src[s + 0] & 0x3F) << 6;
			wc |= (src[s + 1] & 0x3F);
			s += 2;
		}
		else if((c & 0xF0) == 0xE0){
			wchar_t &wc = des[d++];
			wc = (src[s + 0] & 0x1F) << 12;
			wc |= (src[s + 1] & 0x3F) << 6;
			wc |= (src[s + 2] & 0x3F);
			s += 3;
		}
		else if((c & 0xF8) == 0xF0){
			wchar_t &wc = des[d++];
			wc= (src[s + 0] & 0x0F) << 18;
			wc = (src[s + 1] & 0x3F) << 12;
			wc |= (src[s + 2] & 0x3F) << 6;
			wc |= (src[s + 3] & 0x3F);
			s += 4;
		}
		else{
			wchar_t &wc = des[d++];
			wc = (src[s + 0] & 0x07) << 24;
			wc = (src[s + 1] & 0x3F) << 18;
			wc = (src[s + 2] & 0x3F) << 12;
			wc |= (src[s + 3] & 0x3F) << 6;
			wc |= (src[s + 4] & 0x3F);
			s += 5;
		}
	}
	des[d++] = '\0';
	wstring t = des;
	delete[] des;
	des = NULL;
	return t;
}

/*
 * Convert utf string to unicode string and count the size of utf8
 * @param "string str" "the source utf8 string"
 * @param "int& utf8_size" "the utf8 size"
 * @return "wstring" "the unicode wstring"
 */
wstring utf82unicode(string src,int &utf8_size){
	if (src.size() == 0){
		return L"";
	}
	int size_s = src.size();
	//the size of unicode wstring is less than utf8 string
	int size_d = size_s + 10;
	wchar_t *des = new wchar_t[size_d];
	memset(des, 0, size_d * sizeof(wchar_t));
	int s = 0, d = 0;
	utf8_size = 0;
	while (s < size_s && d < size_d){
		unsigned char c = src[s];
		if ((c & 0x80) == 0){
			des[d++] += src[s++];
			utf8_size++;
		}
		else if((c & 0xE0) == 0xC0){
			wchar_t &wc = des[d++];
			wc = (src[s + 0] & 0x3F) << 6;
			wc |= (src[s + 1] & 0x3F);
			s += 2;
			utf8_size++;
		}
		else if((c & 0xF0) == 0xE0){
			wchar_t &wc = des[d++];
			wc = (src[s + 0] & 0x1F) << 12;
			wc |= (src[s + 1] & 0x3F) << 6;
			wc |= (src[s + 2] & 0x3F);
			s += 3;
			utf8_size++;
		}
		else if((c & 0xF8) == 0xF0){
			wchar_t &wc = des[d++];
			wc= (src[s + 0] & 0x0F) << 18;
			wc = (src[s + 1] & 0x3F) << 12;
			wc |= (src[s + 2] & 0x3F) << 6;
			wc |= (src[s + 3] & 0x3F);
			s += 4;
			utf8_size++;
		}
		else{
			wchar_t &wc = des[d++];
			wc = (src[s + 0] & 0x07) << 24;
			wc = (src[s + 1] & 0x3F) << 18;
			wc = (src[s + 2] & 0x3F) << 12;
			wc |= (src[s + 3] & 0x3F) << 6;
			wc |= (src[s + 4] & 0x3F);
			s += 5;
			utf8_size++;
		}
	}
	des[d++] = '\0';
	wstring t = des;
	delete[] des;
	des = NULL;
	return t;
}
/*
 * Convert unicode string to utf8 string
 * @param "wstring  str" "the source unicode wstring"
  * @return "string" "the utf8 string"
 */
string unicode2utf8( wstring src){
	int size_s = src.length();
	//the size of utf8 string is less than the size of utf8 string multiply 4
	int size_d = size_s * 4 + 10;
	char * des = new char[size_d];
	int len = 0;
	for (wstring::const_iterator it = src.begin(); it != src.end(); ++it){
		wchar_t wc = *it;
		if (wc < 0x80){
			des[len++] = (char)wc;
		}
		else if(wc < 0x800){
			des[len++] = 0xc0 | ( wc >> 6 );
			des[len++] = 0x80 | ( wc & 0x3f );
		}
		else if(wc < 0x10000 ){
			des[len++] = 0xe0 | ( wc >> 12 );
			des[len++] = 0x80 | ( (wc >> 6) & 0x3f );
			des[len++] = 0x80 | ( wc & 0x3f );
		}
		else if( wc < 0x200000 ){
			des[len++] = 0xf0 | ( (int)wc >> 18 );
			des[len++] = 0x80 | ( (wc >> 12) & 0x3f );
			des[len++] = 0x80 | ( (wc >> 6) & 0x3f );
			des[len++] = 0x80 | ( wc & 0x3f );
		}
	}
	des[len++] = '\0';
	string t = string(des);
	return t;
}

/*
 * Convert half string to full string
 * @param "string str" "the half string"
 * @return "string" "the full string"
 */
string utf8_half2full(string str){
	wstring wstr;
	wstr = utf82unicode(str);
	int len = wstr.length();
	for(int i = 0; i < len ; i++){
		if( wstr[i] == 32 ) {
			wstr[i] = wstr[i] +12256;
		}
		if( wstr[i] >= 33 && wstr[i] <= 126 ) {
			wstr[i] = wstr[i] + 65248;
		}
	}
	return unicode2utf8(wstr);
}

/*
 * Convert half string to full string and count the size of utf8
 * @param "string str" "the half string"
 * @param "int& utf8_size" "the utf8 size"
 * @return "string" "the full string"
 */
string utf8_half2full(string str,int& utf8_size){
	wstring wstr;
	wstr = utf82unicode(str,utf8_size);
	int len = wstr.length();
	for(int i = 0; i < len ; i++){
		if( wstr[i] == 32 ) {
			wstr[i] = wstr[i] +12256;
		}
		if( wstr[i] >= 33 && wstr[i] <= 126 ) {
			wstr[i] = wstr[i] + 65248;
		}
	}
	return unicode2utf8(wstr);
}

/*
 * Convert full string to half string
 * @param "string str" "the full string"
 * @return "string" "the half string"
 */
string utf8_full2half(string str){
	wstring wstr;
	wstr = utf82unicode(str);
	int len = wstr.length();
	for(int i = 0; i < len ; i++){
		if( wstr[i] == 12288 ) {
			wstr[i] = wstr[i] -12256;
		}
		if(  wstr[i] >= 65281 && wstr[i] <= 65374 ) {
			wstr[i] = wstr[i] - 65248;
		}
	}
	return unicode2utf8(wstr);
}

/*
 * Convert int to string
 * @param "int i" "the integer"
 * @return "string str" "the string" 
*/
string int2string(int i){
	string str = "";
	if(i > 0){
		while(i > 0){
			str.push_back('0' + i%10);
			i = i/10;
		}
		reverse(str.begin(), str.end());
	}
	else if(i == 0){
		str.push_back('0');
	}
	else if(i < 0){
		i = -i;
		while(i > 0){
			str.push_back('0' + i%10);
			i = i/10;
		}
		str.push_back('-');
		reverse(str.begin(), str.end());	
	}
	return str;
}

/*
 * Convert string to positive int
 * @param "string str" "the string"
 * @return "int integer" "the integer" if the string is negative or other,
 * just return -1 then. 
*/
int string2int(string str){
	int len = str.size();
	int i = 0;
	for(int j = 0 ; j < len ; j++){
		if(str[j]>='0' && str[j]<='9'){
			i = i * 10 + (str[j] - '0');
		}
		else{
			cout<<"string can not convert into int"<<endl;
			return -1;
		}
	}
	return i;
}


/*
 * Change raw sentence to seged words based on the labels of the sentence
 * @param "string rawsen" "the raw sentence"
 * @param "vector<string> label" "the labels of the sentence"
 * @return "vector<string>" "the seged words"
 *
*/
vector<string> rawsen2segsen(string rawsen,vector<string> label){
	vector<string> characters = get_character(rawsen);
	vector<string> words;
	int len = characters.size();
	string preword= "";
	for(int i = 0 ; i < len ; i++){
		if( (label[i] == "B" || label[i] == "S") && preword != ""){
			words.push_back(preword);
			preword = "";
		}
		preword.append(characters[i]);
	}
	if(preword != ""){
		words.push_back(preword);
	}
	return words;
}

/*
 * Convert char into unsinged int
 * @param "char c" "the char"
 * @return "unsigned int" "the unsigned int value"
*/
unsigned int char2uint(char c){
	return (unsigned int)((unsigned char)(c));
}

// double periods int value
static int __double_periods_utf8_buff_x__[12] = {
	14909570 , 14844061 , 15711361 , 14844061 ,
	15711391 , 14844061 , 15711387 , 14844061 ,
	14844070 , 14844070 , 15711391 , 15711361 ,
};

//single peroids int value
static int __single_periods_utf8_buff_x__[4] = {
	14909570 , 15711361 , 15711391 , 15711387 ,
};

/*
 * Split text into sentences
 * @param "string text" "the text"
 * @param "vector<string> &sentence" "the sentence result vector"
 * @return "int" "the sentence num"
*/
int splitsentence(string text,vector<string> &sentence){
	int len = text.size();
	int idx = 0;
	int cnt = 0;
	string senttmp;
	const int * buff = __double_periods_utf8_buff_x__;
	const int * buff2 = __single_periods_utf8_buff_x__;
	sentence.clear();    
	while(idx < len){
		if ( (text[idx] & 0x80) == 0 ){
			senttmp.append(text.substr(idx,1));
			if(text[idx] == '\r' || text[idx] == '\n' || text[idx] == '!' || text[idx] == '?' || text[idx] == ';'){
				sentence.push_back(senttmp);
				senttmp = "";
				cnt++;
			}
			idx++;
		}
		else if ( (text[idx] & 0xE0) == 0xC0 ){
			senttmp.append(text.substr(idx,2));
			idx += 2;
		}
		else if ( (text[idx] & 0xF0) == 0xE0 ){
			unsigned block = ( (char2uint(text[idx])<<16) | (char2uint(text[idx+1])<<8) | char2uint(text[idx+2]) );
			if ( idx+6<len && ((text[idx+3] & 0xF0) == 0xE0) ) {
				int block2 = ( (char2uint(text[idx+3])<<16) | (char2uint(text[idx+4])<<8) | char2uint(text[idx+5]) );
				if( (block == buff[0] && block2 == buff[1]) || 
					(block == buff[2] && block2 == buff[3]) || 
					(block == buff[4] && block2 == buff[5]) || 
					(block == buff[6] && block2 == buff[7]) || 
					(block == buff[8] && block2 == buff[9]) ||
					(block == buff[10] && block2 == buff[11]) ) {
					senttmp.append(text.substr(idx,6));
					sentence.push_back(senttmp);
					senttmp = "";
					cnt++;
					idx += 6;
				}
				else if((block == buff2[0]) || (block == buff2[1]) ||
						(block == buff2[2]) || (block == buff2[3])) {
						senttmp.append(text.substr(idx,3));
						sentence.push_back(senttmp);
						senttmp = "";
						cnt++;
						idx += 3;
				}
				else{
					senttmp.append(text.substr(idx,3));
					idx += 3;
				}
			}
			else{
				senttmp.append(text.substr(idx,3));
				if ((block == buff2[0]) || (block == buff2[1]) ||
					(block == buff2[2]) || (block == buff2[3])) {
					sentence.push_back(senttmp);
					senttmp = "";
					cnt++;
				}
				idx += 3;
			}
		}
		else if ( (text[idx] & 0xF8) == 0xF0){
			senttmp.append(text.substr(idx,4));
			idx += 4;
		}
		else{
			cout<< "Error: "<<"the text "<<text<<"is not encoded in utf8."<<endl;
			idx++;
		}
	}
	if( senttmp.size() != 0 ){
		sentence.push_back( senttmp );
	}
	if ( idx != len ){
		cout<< "Error: "<<"the text "<<text<<"is not encoded in utf8."<<endl;
	}
	return cnt;
}

void replacechar(string &str,char c1,char c2){
	for(int i = 0;i<str.size();i++){
		if(str[i] == c1){
			str[i] = c2;
		}
	}
}

#endif