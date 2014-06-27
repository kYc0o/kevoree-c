#ifndef H_TOOLS
#define H_TOOLS

short StartsWith (char* base, char* str);
short EndsWith (char* base, char* str);
int IndexOf (char* base, char* str);
int IndexOf_shift (char* base, char* str, int startIndex);
int LastIndexOf (char* base, char* str);
char* Substring(char *string, int position, int length);



#endif
