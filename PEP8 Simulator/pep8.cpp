#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	string line;
	string fileName = "data.txt";
	ifstream file(fileName);
	unsigned int cellSize = 8;
	struct cell {
		unsigned int data : 8;
	};
	cell memory[65536];
	for (unsigned int i = 0; i < sizeof(memory)/cellSize; i++) {
		memory[i] = { 0 };
	}
	
	//0 is A
	//1 is X
	//2 is PC
	//3 is SP
	unsigned int registers[4];
	for (int i = 0; i < sizeof(registers) / sizeof(registers[0]); i++) {
		registers[i] = 0;
	}

	union instruction{
		struct four_one_three {
			unsigned int a : 3;
			unsigned int r : 1;
			unsigned int op_code : 4;
		};
		struct five_three {
			unsigned int a : 3;
			unsigned int op_code : 5;
		};
		struct seven_one {
			unsigned int r : 1;
			unsigned int op_code : 7;
		};
		unsigned int eight;

		//struct half {
			//unsigned int first : 4;
			//unsigned int second : 4;
		//};

		four_one_three four;
		five_three five;
		seven_one seven;
		//half h;
	};
	//load the memory with instructions
	//currentMemLoc represents the location where we will put the next piece of data into the memory array
	unsigned int currentMemLoc = 0;
	if (file.is_open()) {
		while (getline(file, line)) {
			//line represents the entire line in the text file (3 sets of instructions)
			while (!line.empty()) {
				//pos is the location of the next space (as a delimiter)
				size_t pos = line.find(" ");
				//word is the 2-digit hex instruction
				string word = "";
				if (pos == string::npos) {
					word = line;
					line = "";
				}
				else {
					word = line.substr(0, pos);
					line = line.substr(pos + 1);
				}
				if (word == "zz") {
					goto run;
				}
				//num is the instruction converted from hex to dec
				unsigned int num = stoul(word, nullptr, 16);
				memory[currentMemLoc] = { num };
				currentMemLoc++;

			}
		}
		file.close();
	}
	else {
		cout << "Could not open file";
	}

	run:
	//begin running instructions
	registers[3] = memory[65528].data;
	for (registers[2] = 0; registers[2] < sizeof(memory)/cellSize;) {
		//get the instruction first
		instruction i = { memory[registers[2]].data };
		registers[2]++;
		//cout << "First: " << i.h.second << endl;
		unsigned int loc = -1;
		char c;
		string in;
		unsigned int num;
		unsigned int MSB;
		unsigned int LSB;
		switch (i.four.op_code) {
			case 0:
				//stop execution
				cout << "A: " << registers[0] << endl;
				cout << "X: " << registers[1] << endl;
				cout << "PC: " << registers[2] << endl;
				cout << "SP: " << registers[3] << endl;
				return 0;
			case 1:
				//get the 7 code
				switch (i.seven.op_code) {
					case 12:
						//bitwise invert r
						registers[i.seven.r] = ~registers[i.seven.r];
						break;
					case 14:
						//ASL r
						registers[i.seven.r] = registers[i.seven.r] << 1;
						break;
					case 15:
						//ASR r
						registers[i.seven.r] = registers[i.seven.r] >> 1;
						break;
					}
				break;
			case 2:
				//get 7 code
				switch (i.seven.op_code) {
				case 16:
					//rotate left r
					MSB = registers[i.seven.r] >= 32768? 1 : 0;
					registers[i.seven.r] = (registers[i.seven.r] << 1) + MSB;
					break;
				case 17:
					//rotate right r
					 LSB = (registers[i.seven.r] % 2 == 1) ? 32768 : 0;
					registers[i.seven.r] = (registers[i.seven.r] << 1) + LSB;
					break;
				}
				break;
			case 3:
				if (i.four.r == 0) {
					//decimal input trap
					loc = memory[registers[2]].data;
					registers[2]++;
					loc = loc << 4;
					loc += memory[registers[2]].data;
					registers[2]++;

					cout << "\nEnter a decimal number" << endl;
					cin >> num;
					memory[loc].data = num;
				}
				else {
					//decimal output trap
					if (i.five.a == 0) {
						//immediate
						loc = memory[registers[2]].data;
						registers[2]++;
						loc = loc << 4;
						loc += memory[registers[2]].data;
						registers[2]++;

						cout << loc << endl;
					}
					else {
						//direct
						loc = memory[registers[2]].data;
						registers[2]++;
						loc = loc << 4;
						loc += memory[registers[2]].data;
						registers[2]++;

						cout << memory[loc].data << endl;
					}
				}
				break;
			case 4:
				//character input
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;
				cout << "\nEnter a char" << endl;
				cin >> in;
				c = in[0];
				memory[loc] = { (unsigned int)c };
				break;
			case 5:
				//character output
				//get a
				if (i.five.a == 0) {
					//immediate addressing
					loc = memory[registers[2]].data;
					registers[2]++;
					loc = loc << 4;
					loc += memory[registers[2]].data;
					registers[2]++;

					cout << (char)loc << endl;
				}
				else {
					//direct addressing
					loc = memory[registers[2]].data;
					registers[2]++;
					loc = loc << 4;
					loc += memory[registers[2]].data;
					registers[2]++;
					cout << (char)(memory[loc].data) << endl;
				}
				break;
			case 7:
				//add to r
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;

				if (i.four.a == 0) {
					//immediate
					registers[i.four.r] += loc;
				}
				else {
					//direct
					registers[i.four.r] += (memory[loc].data << 8);
				}
				
				
				break;
			case 8:
				//subtract from r
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;

				if (i.four.a == 0) {
					//immediate
					registers[i.four.r] -= loc;
				}
				else {
					//direct
					registers[i.four.r] -= (memory[loc].data << 8);
				}
				break;
			case 9:
				//bitwise AND to r
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;

				if (i.four.r == 0) {
					//immediate
					registers[i.four.r] = registers[i.four.r] & loc;
				}
				else {
					//direct
					registers[i.four.r] = registers[i.four.r] & (memory[loc].data << 8);
				}
				break;
			case 10:
				//bitwise OR to r
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;

				if (i.four.r == 0) {
					//immediate
					registers[i.four.r] = registers[i.four.r] | loc;
				}
				else {
					//direct
					registers[i.four.r] = registers[i.four.r] | (memory[loc].data << 8);
				}
				break;
			case 12:
				//load r from memory
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;
				if (i.four.r == 1) {
					//immediate
					registers[i.four.r] = loc;
				}
				else {
					//direct
					registers[i.four.r] = (memory[loc].data << 8) + memory[loc + 1].data;
				}
				break;
			case 13:
				//load byte from memory
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;

				if (i.four.r == 0) {
					//immediate
					registers[i.four.r] = registers[i.four.r] & 65280;
					registers[i.four.r] += loc;
				}
				else {
					//direct
					registers[i.four.r] = registers[i.four.r] & 65280;
					registers[i.four.r] += memory[loc].data;
				}
				break;
			case 14:
				//store r to memory
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;
				memory[loc].data = registers[i.four.r] >> 8;
				memory[loc + 1].data = (registers[i.four.r] << 8)>> 8;
				break;
			case 15:
				//store byte r to memory
				loc = memory[registers[2]].data;
				registers[2]++;
				loc = loc << 4;
				loc += memory[registers[2]].data;
				registers[2]++;

				memory[loc].data = registers[i.four.r] & 255;
				break;
		}
		cout << "A: " << registers[0] << endl;
		cout << "X: " << registers[1] << endl;
		cout << "PC: " << registers[2] << endl;
		cout << "SP: " << registers[3] << endl;
		cout << "-------" << endl;
	}
	return 0;
}