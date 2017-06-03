#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>

int main(int argc, char const *argv[])
{
	std::ifstream fin(argv[1], std::ios_base::in);
	if (argc < 2)
	{
		std::cout << "Use ./brainfuck with the filelocation of the brainfuck behind it.";
		exit(1);
	}
	if (!fin)
	{
		std::cout << "Make sure the source directory of the brainfuck program is correct!";
		exit(1);
	}
	std::ofstream fout("a.out.c", std::ios_base::out);
	char ch;
	fout << "#include <stdio.h>\n#include <stdlib.h>\nint main(int argc, char** argv[]) {" << \
			"\n\tchar* ptr=(char*)malloc(sizeof(char)*1000000);\n" << \
			"\tlong long int i;\n" << \
			"\tfor (i = 0; i < 1000000; ++i) { \n" << \
			"\t\t*(ptr+i)=0;\n\t}" << std::endl ;
	std::stack<bool> tabs;
	while(fin.get(ch))
	{
		switch(ch)
		{
			case '>':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "++ptr;\n";
				break;
			case '<':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "--ptr;\n";
				break;
			case '+':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "++*ptr;\n";
				break;
			case '-':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "--*ptr;\n";
				break;
			case '[':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "while (*ptr) {\n";
				tabs.push(true);
				break;
			case ']':
				tabs.pop();
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "}\n";
				break;
			case '.':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "putchar(*ptr);\n";
				break;
			case ',':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "*ptr=getchar();\n";
				break;

			default:
				break;
		}
	}
	fout << "return 0;\n}";
	fout.close();
	#ifdef __linux__
		system("gcc a.out.c -o a.out");
	#elif _WIN32
		getch();// i really hate this
	#endif
	return 0;
}
