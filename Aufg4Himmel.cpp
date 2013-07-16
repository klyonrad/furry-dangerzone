// Aufg4Himmel.cpp : Usage of SparseMatrix with the sample file himmel.txt
/* SparseMatrix class with templates

Licensed under: WTFPL lol
( = do what the fuck you want to and lol at my code)
*/

#include "SparseMatrix.hpp"
#include <sstream>
#include <string>
#include <fstream>

using std::string;

int main(void)
{
	SparseMatrix<int> aMatrix;

	// from somebody I know:
	std::ifstream infile("Himmel.txt");
	string line = "Fubar";
	while (infile.good()) {
		while (line.size() > 4 && line[0] != '=') std::getline(infile, line); // We're in a new Land, yay
		std::getline(infile, line); // get first line of current Land
		/*SparseMatrix currentLand(100000, 100000);*/
		SparseMatrix<int> currentLand;
		while (line.size() > 2 && line[0] != '=') { // Now we extract stuff
			int row, col, val;
			std::stringstream number(line);
			number >> row;
			number.get(); // remove comma
			number >> col;
			for (int i = 0; i < 4; i++) number.get(); // remove arrow and both spaces
			number >> val;
			currentLand.addValue(row, col, val);
			if (infile.good()) getline(infile, line);
			else break;
		}
		aMatrix += currentLand;
	}

	aMatrix.outputElementsHigherThan(19);
	return 0; 
}

