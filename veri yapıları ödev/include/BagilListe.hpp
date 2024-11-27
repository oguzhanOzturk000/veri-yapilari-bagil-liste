#ifndef BAGILLISTE_HPP
#define BAGILLISTE_HPP

#include <iostream>
#include "Dugum.hpp"

using namespace std;

class BagilListe{
	private:
		Dugum* listeBasi;
		int uzunluk;
	public:
		BagilListe();
		void ekle(string eklenecekDeger);
		bool bosMu();
		Dugum* listeBasiniVer();
		Dugum* siradakiniVer(int sira);
		Dugum* sonuncuyuVer();
		void hepsiniTemizle();
};
#endif