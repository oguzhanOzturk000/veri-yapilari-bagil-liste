/**
* BagilListe.cpp
* Bağıl liste fonksiyonlarının olduğu kaynak dosyası
* 1. Eğitim B grubu
* 1. Ödev
* 27.11.2024
* Oğuzhan Öztürk oguzhan.ozturk15@ogr.sakarya.edu.tr
*/

#include <iostream>
#include "BagilListe.hpp"
using namespace std;

BagilListe::BagilListe(){
	uzunluk=0;
	listeBasi=NULL;
}
void BagilListe::ekle(string eklenecekDeger){
	if(bosMu()){
		Dugum* yeniDugum = new Dugum;
		yeniDugum->degeriDegistir(eklenecekDeger);
		yeniDugum->sonrakiniDegistir(NULL);
		listeBasi=yeniDugum;
		uzunluk++;
	}else{
		Dugum* yeniDugum = new Dugum;
		Dugum * sonuncu = sonuncuyuVer();
		sonuncu->sonrakiniDegistir(yeniDugum);
		yeniDugum->sonrakiniDegistir(NULL);
		yeniDugum->degeriDegistir(eklenecekDeger);
		uzunluk++;
	}
}
Dugum* BagilListe::sonuncuyuVer(){
	Dugum* n = listeBasi;
	while(n->sonrakiniVer() != NULL){
		n=n->sonrakiniVer();
	}
	return n;
}
bool BagilListe::bosMu(){
	if(uzunluk == 0){
		return 1;
	}else{
		return 0;
	}
}
Dugum* BagilListe::siradakiniVer(int sira){
	Dugum * d = listeBasi;
	for(int i=0; i<sira ; i++){
		d= d->sonrakiniVer();
	}
	return d;
}

void BagilListe::hepsiniTemizle(){
	Dugum * gecici;
	Dugum * gosterici = listeBasi;
	while(gosterici!=NULL){
		gecici = gosterici->sonrakiniVer();
		delete gosterici;
		gosterici=gecici;
	}
}