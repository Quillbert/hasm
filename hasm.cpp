#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::string removeFrontWhitespace(std::string str) {
	int start = str.find_first_not_of(" \f\n\r\t\v");
	if(start < 0) {
		return "";
	}
	return str.substr(start, str.size());
}

std::vector<std::string> split(std::string strToSplit, char delimeter) {
	strToSplit = removeFrontWhitespace(strToSplit);
    std::stringstream ss(strToSplit); 
	std::string item;                 
	std::vector<std::string> splittedStrings;  
			    
	while (std::getline(ss, item, delimeter)) {
		splittedStrings.push_back(item);
	}
					    
	return splittedStrings;
}

std::vector<std::string> setLabels(std::vector<std::string> lines) {
	std::vector<std::string> labels;
	for(int i = 0; i < lines.size(); i++) {
		std::vector<std::string> parts = split(lines[i], ' ');
		if(parts.size() > 0) {
			if(parts[0].compare("lbl") == 0) {
				labels.push_back(parts[1]);
				labels.push_back(std::to_string(i));
			}
		}
	}
	return labels;
}

int regNumber(std::string str, int pointers[]) {
	if(str[0] == 'c') {
		return std::stoi(str.substr(1, str.size()));
	} else if(str[0] == 'p') {
		return pointers[std::stoi(str.substr(1, str.size()))];
	}
	return -1;
}

int execute(int regs[], std::string str, std::vector<std::string> labels, int p[], int i) {
	std::vector<std::string> parts = split(str, ' ');
	if(parts.size() < 1) {
		return i+1;
	}
	if(parts[0].compare("lbl") == 0) {
		return i+1;
	} else if(parts[0].compare("gto") == 0) {
		for(int j = 0; j < labels.size(); j += 2) {
			if(labels[j].compare(parts[1]) == 0) {
				return std::stoi(labels[j+1]);
			}
		}
		return i+1;
	}
	int reg = regNumber(parts[1], p);
	if(parts[0].compare("set") == 0) {
		if(parts[2][0] == 'c' || parts[2][0] == 'p') {
			int reg2 = regNumber(parts[2], p);
			regs[reg] = regs[reg2];
		} else {
			regs[reg] = std::stoi(parts[2]);
		}
	} else if(parts[0].compare("stc") == 0) {
		regs[reg] = parts[2][0];
	} else if(parts[0].compare("dis") == 0) {
		std::cout << regs[reg];
	} else if(parts[0].compare("dsc") == 0) {
		std::cout << (char)(regs[reg]%128);
	} else if(parts[0].compare("add") == 0) {
		int reg2 = regNumber(parts[2], p);
		regs[reg] += regs[reg2];
	} else if(parts[0].compare("sub") == 0) {
		int reg2 = regNumber(parts[2], p);
		regs[reg] -= regs[reg2];
	} else if(parts[0].compare("mul") == 0) {
		int reg2 = regNumber(parts[2], p);
		regs[reg] *= regs[reg2];
	} else if(parts[0].compare("div") == 0) {
		int reg2 = regNumber(parts[2], p);
		regs[reg] /= regs[reg2];
	} else if(parts[0].compare("mod") == 0) {
		int reg2 = regNumber(parts[2], p);
		regs[reg] %= regs[reg2];
	} else if(parts[0].compare("cpr") == 0) {	
		int reg2 = regNumber(parts[2], p);
		int reg3 = regNumber(parts[3], p);
		if(regs[reg2] == regs[reg3]) {
			regs[reg] = 0;
		} else if(regs[reg2] > regs[reg3]) {
			regs[reg] = 1;
		} else {
			regs[reg] = -1;
		}
	} else if(parts[0].compare("cgt") == 0) {
		if(regs[reg] != 0) {
			for(int j = 0; j < labels.size(); j += 2) {
				if(labels[j].compare(parts[2]) == 0) {
					return std::stoi(labels[j+1]);
				}
			}
		}
	} else if(parts[0].compare("gtc") == 0) {
		regs[reg] = std::getchar();
	} else if(parts[0].compare("ptr") == 0) {
		int ptr = std::stoi(parts[1].substr(1, parts[1].size()));
		int reg2 = regNumber(parts[2], p);
		if(parts.size() > 3) {
			int reg3 = regNumber(parts[3], p);
			p[ptr] = reg2 + regs[reg3];
		} else {
			p[ptr] = reg2;
		}
	}
	return i+1;
}

int main(int argc, char *argv[]) {
	int registers[1024] = {};
	int pointers[4] = {};
	std::string filename;
	filename = argv[1];
	std::ifstream infile;
	infile.open(filename);
	std::string str;
	std::vector<std::string> lines;
	while(std::getline(infile, str)) {
		lines.push_back(str);
	}
	std::vector<std::string> labels = setLabels(lines);
	for(int i = 0; i < lines.size();) {
		i = execute(registers, lines[i], labels, pointers, i);
	}
	std::cout << "\n";
	return 0;
}
