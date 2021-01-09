
#pragma once
#include "klase.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <exception>
#include <clocale>
#include <regex>
#include <locale>
#include <codecvt>

using std::vector;
using std::map;

typedef unsigned int uint;
typedef map<string, vector<uint>> MAPw;                     //Naudojame std::map duomenims saugoti


bool ArSarase(MAPw& mapOfZodiss, string& val);
void Didinimas(MAPw& Zodziai, string& zodis, uint& index);
void PasalintiURLS(string& eil);
void IsvalytiString(string& eil);
vector<string> RastiURLS(int);
void IsrinktiURL(string, vector<string>&);
MAPw Skaitymas(Klase_&, int);

bool ArSarase(MAPw& mapOfZodiss, string& val)
{
	MAPw::iterator it = mapOfZodiss.begin();
	while (it != mapOfZodiss.end())
	{
		if (it->first == val)
			return true;
		++it;
	}
	return false;
}


void Didinimas(MAPw& Zodziai, string& zodis, uint& index) {
	MAPw::iterator it = Zodziai.begin();
	while (it != Zodziai.end())
	{
		if (it->first == zodis && !std::count(it->second.begin(), it->second.end(), index)) { 
			it->second.push_back(index);
			break;
		}

		++it;
	}
}

void IsvalytiString(string& eil) {
	std::transform(eil.begin(), eil.end(), eil.begin(), ::tolower);
	std::regex reg("\\W");
	eil = std::regex_replace(eil, reg, " ");

}

void PasalintiURLS(string& eil) {
	std::regex reg("((http|https):\\/\\/)?(www\\.)?(\\w+\\.(com|org|lt)){1}");
	eil = std::regex_replace(eil, reg, " ");
}


void IsrinktiURL(string eil, vector<string>& URLS) {
	try {
		std::regex reg("((http|https):\\/\\/)?(www\\.)?(\\w+\\.(com|org|lt)){1}");
		std::sregex_iterator next(eil.begin(), eil.end(), reg);
		std::sregex_iterator end;
		while (next != end) {
			std::smatch match = *next;
			if (match.str() != "")
				URLS.push_back(match.str());
			next++;
		}
	}
	catch (std::regex_error& e) {
		cout << e.what() << endl;
	}
}

vector<string> RastiURLS(int numeris) {

	std::ifstream failas(std::to_string(numeris) + "-failas.txt");;
	vector<string> URLS;
	string eil;
	for (uint i = 0; !failas.eof(); ++i) {
		std::getline(failas, eil, '\n');
		IsrinktiURL(eil, URLS);
	}
	return URLS;
}


MAPw Skaitymas(Klase_& klase, int numeris) {


	std::ifstream in;
	in.open(std::to_string(numeris) + "-failas.txt");                               //atsidarom pasirinkta faila

	if (in.fail()) throw std::runtime_error("Toks failas siame aplanke neegzistuoja."); //jei nera failo      //jeigu toks failas neegzistuoja
	cout << "\nFailo " << std::to_string(numeris) + "-failas.txt" << " sudetis:\n\n";
	cout << std::string(55, '=') << endl;
	MAPw Zodziai;
	string eil;
	for (uint i = 0; !in.eof(); ++i) {
		std::getline(in, eil, '\n');                                                   
		if (klase.TikrinimasTiesa()) PasalintiURLS(eil);                                 
		IsvalytiString(eil);                                                                

		std::stringstream ss(eil);
		string zodis;
		while (ss >> zodis) {
			if (!ArSarase(Zodziai, zodis)) {                                          
				vector<uint> init{ 0 };
				Zodziai.insert(MAPw::value_type(zodis, init));
			}
			else {
				Didinimas(Zodziai, zodis, i);
			}
		}
		eil.clear();
	}
	return Zodziai;
}
