#include <vector>
#include <iostream>
#include <fstream>
#include <Windows.h>

std::vector<int> m_cells;
std::vector<int> m_current_loop;
std::vector<char> m_brainfuck_code;
int m_cell;
int m_inp_pos;
std::string input;
bool m_false_loop;
void runCode();
int m_found_brackets;

int main(int argc, char const *argv[])
{
	std::ifstream fin(argv[1], std::ios_base::in);
	input = argv[2];
	if (!argv[2])
		std::cout << "If the output isn't what you expected, you need to give a second argument which is used as input";
	if (!fin) {
		std::cout << "Are you sure there is a file there? I couldn't find it";
		exit(1);
	}
	for (unsigned int i = 0; i < 30000; i++)
		m_cells.push_back(0);
	m_cell = 0;
	m_false_loop = false;
	char ch;
	while (fin.get(ch))
	{
		m_brainfuck_code.push_back(ch);
	}
	runCode();
	Sleep(5000);
	return 0;
}

void runCode()
{
	int i = 0;
	for (i = 0; i < m_brainfuck_code.size(); i++) {
	//std::cout << i << std::endl;
		if (!m_false_loop) {
			switch (m_brainfuck_code[i])
			{
			case '>':
				(m_cell < m_cells.size() ? m_cell++ : m_cell = 0);
				break;
			case '<':
				(m_cell > 0 ? m_cell-- : m_cell = m_cells.size());
				break;
			case '+':
				(m_cells[m_cell] < 255 ? m_cells[m_cell]++ : m_cells[m_cell] = 0);
				break;
			case '-':
				(m_cells[m_cell] > 0 ? m_cells[m_cell]-- : m_cells[m_cell] = 255);
				break;
			case '[':
				(m_cells[m_cell] != 0 ? m_current_loop.push_back(i) : m_false_loop = true, m_found_brackets = 0);
				break;
			case ']':
				((int)m_cells[m_cell] == 0 ? m_current_loop.pop_back() : i = m_current_loop[m_current_loop.size() - 1]);
				break;
			case '.':
				if (m_cells[m_cell] != 0)
					std::cout << static_cast<char>(m_cells[m_cell]) << std::flush;
				break;
			case ',':
				(m_inp_pos < input.size() ? m_cells[m_cell] = static_cast<int>(input[m_inp_pos]), m_inp_pos++ : m_cells[m_cell] = 0);
				break;
			default:
				break;
			}
		}
		else if (m_brainfuck_code[i] == ']') {
			m_found_brackets++;
			if (m_found_brackets > 0) 
				m_false_loop = false;
		}
		else if (m_brainfuck_code[i] == '[')
			m_found_brackets--;
	}
}
