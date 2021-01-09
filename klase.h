#pragma once
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

class Klase_ {
private:
	int IntervaloPradzia_;
	int IntervaloPabaiga_;
	char c_;
	int input_;
public:
	Klase_(int a = 2, int b = 100, char c = 'n', int input = 2) : IntervaloPradzia_(a), IntervaloPabaiga_(b), c_(c), input_(input) {}

	int IntervaloPradzia() const { return IntervaloPradzia_; }
	int IntervaloPabaiga() const { return IntervaloPabaiga_; }
	char get_c() const { return c_; }
	char get_input() const { return input_; }

	void IntervaloNustatymas(int a, int b);
	void paklausimas(string text);
	void Tikrinimas(string text);
	bool TikrinimasTiesa();
};

void Klase_::IntervaloNustatymas(int a, int b) {
	IntervaloPradzia_ = a;
	IntervaloPabaiga_ = b;
}
void Klase_::paklausimas(string text) {
	cout << text + "(" << IntervaloPradzia() << "-" << IntervaloPabaiga() << ")" << endl;
	int input;
	while (!(cin >> input) || IntervaloPradzia() > input || input > IntervaloPabaiga()) {
		std::cout << "Netinkamas ivesties formatas. Iveskite is naujo: " << endl;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	input_ = input;
}
void Klase_::Tikrinimas(string text) {
	cout << text + "(y/n)" << endl;
	char c;
	if (cin >> c) c_ = std::tolower(c);
}
bool Klase_::TikrinimasTiesa() {
	return get_c() == 'y';
}
