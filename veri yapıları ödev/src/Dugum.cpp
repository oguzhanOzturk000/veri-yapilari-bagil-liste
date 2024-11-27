/**
* Dugum.cpp
* Bağıl Liste veri yapısının düğümünün kaynak dosyası
* 1. Eğitim B grubu
* 1. Ödev
* 27.11.2024
* Oğuzhan Öztürk oguzhan.ozturk15@ogr.sakarya.edu.tr
*/

#include <iostream>
#include "Dugum.hpp"

using namespace std;

void Dugum::degeriDegistir(string yeniDeger){
	deger = yeniDeger;
}
void Dugum::sonrakiniDegistir(Dugum* yeniSonraki){
	sonraki = yeniSonraki;
}
string Dugum::degeriVer(){
	return deger;
}
Dugum* Dugum::sonrakiniVer(){
	return sonraki;
}
