#include "funkcijos.h"

int main()
{

	Klase_ klase{};

	klase.IntervaloNustatymas(1, 2);                                                          
	klase.paklausimas("Kuri faila norite nuskaityti?");

	int numeris;
	numeris = klase.get_input();                                                  // pasirenkame faila nuskaitymui

	klase.IntervaloNustatymas(1, 100);                                                        
	klase.Tikrinimas("Ar norite, jog butu isrinkti visi URL link'ai?");                      //Bei leidziame pasirinkti ar jis nori, kad buti isrinkti URL linkai


	try {
		MAPw Zodziai = Skaitymas(klase, numeris);
		MAPw::iterator it = Zodziai.begin();

		if (it->second.size() == 0) throw std::runtime_error("Teksto failas yra tuscias");
		bool empty = true;

		std::ofstream out("Rezultatai.txt");
		int maxWordLimit = 0;
		for (auto& m : Zodziai) { // surasti koks yra max zodzio pasikartojimas
			m.second.erase(m.second.begin());
			if (m.second.size() > maxWordLimit) {
				maxWordLimit = m.second.size();
			}
		}
		for (int a = 2; a <= maxWordLimit; ++a) {
		
			for (const auto& x : Zodziai)
			{
				if (x.second.size() == a) {
					empty = false;
					out << "Zodis |" << x.first + " \t\t\t" << "| buvo pakartotas " << x.second.size()<< " kartus(-u) eilutese: ";
					std::cout << "Zodis |" << x.first + " \t\t\t" << "| buvo pakartotas " << x.second.size() << " kartus(-u) eilutese: ";
					for (const auto& a : x.second) {
						out << a << " ";
						cout << a << " ";
					}
					out << endl;
					cout << endl;
				}
				
			}
			
		}
		if (empty) {
			cout << std::string(55, '=') << endl;
			cout << "Nera zodziu atitinkanciu reikalavimus" << endl;
		}

		if (klase.TikrinimasTiesa()) {                              

			cout << std::string(55, '=') << endl;
			cout << "\t\tURLS:" << endl;
			cout << std::string(55, '=') << endl;

			out << std::string(55, '=') << endl;
			out << "\t\tURLS:" << endl;
			out << std::string(55, '=') << endl;

			vector<string> URLS = RastiURLS(numeris);
			if (URLS.empty()) {
				cout << "Tekste url adresu nera" << endl;
			}
			else {
				for (const auto& url : URLS)
				{
					cout << url << endl;
					out << url << endl;
				}
			}
			cout << std::string(55, '=') << endl;
			out << std::string(55, '=') << endl;

		}

	}
	catch (const std::runtime_error& e) {
		cout << e.what() << endl;
	}
	

}
