#ifndef DUGUM_HPP
#define DUGUM_HPP

#include <iostream>

using namespace std;

class Dugum{
	private:
		string deger;
		Dugum * sonraki;
	public:
		void degeriDegistir(string yeniDeger);
		string degeriVer();
		void sonrakiniDegistir(Dugum* yeniSonraki);
		Dugum* sonrakiniVer();
};

#endif