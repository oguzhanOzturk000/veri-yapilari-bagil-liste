/**
* Test.cpp
* Programın çalışacağı dosya
* 1. Eğitim B grubu
* 1. Ödev
* 27.11.2024
* Oğuzhan Öztürk oguzhan.ozturk15@ogr.sakarya.edu.tr
*/

#include <iostream>
#include <fstream>
#include <string>
#include "BagilListe.hpp"
using namespace std;

string dnaPath = "C:\\B231210071\\src\\Dna.txt"; // "Dna.txt" dosyasının adresi
string islemlerPath = "C:\\B231210071\\src\\islemler.txt"; // "Islemler.txt" dosyasının adresi
BagilListe* liste = new BagilListe; // Dna.txt'deki verilerin kaydedileceği bağıl listenin tanımlanması
BagilListe* otoIslemListesi = new BagilListe; // Islemler.txt'deki verilerin kaydedileceği bağıl listenin tanımlanması

void dnadanListeyeKaydet(){
	//"Dna.txt" dosyasındaki verileri okuyup bağıl listeye kaydetme
	string dosyadan;
	fstream OkunacakDosya;
	OkunacakDosya.open(dnaPath , ios::in);
	if (!OkunacakDosya.is_open()) {
		cout << "Dna.txt dosyasi acilirken hata meydana geldi" << endl;
		return;
	}
	int i = 0;
	//while döngüsü ve getline fonksiyonu sayesinde her bir satırı "liste" değişkenine kaydediyoruz ve ekrana yazıyoruz
	while(getline(OkunacakDosya, dosyadan)){		
		liste->ekle(dosyadan);
	}
	OkunacakDosya.close(); // Dosyayla şimdilik işimiz bittiği için kapattık
}
void listedenDnayaYaz(){
	//Yeni kromozomlar Dna.txt dosyasına da ekleniyor
	ofstream dosyam(dnaPath, ios::trunc);
	if (!dosyam.is_open()) {
		cout << "Dna.txt dosyasi açilirken hata meydana geldi" << endl;
		return;
	}
	Dugum* d = liste->siradakiniVer(0);
	while(d!=NULL){
		dosyam << d->degeriVer() << endl;
		d= d->sonrakiniVer();
	}
	dosyam.close();
}
void caprazlama(int ilkKromozom, int ikinciKromozom){
	string a1 , a2 , b1 ,b2;
	string str1 = liste->siradakiniVer(ilkKromozom)->degeriVer();
	string str2 = liste->siradakiniVer(ikinciKromozom)->degeriVer();
	int ilkUzunluk = str1.length();
	int ikinciUzunluk = str2.length();
	//Satır uzunluğunun çift veya tek olmasına göre değişen işlemler
	//Tekse ortadaki harf çaprazlamaya dahil edilmez
	if(ilkUzunluk%2==0){
		a1 = str1.substr(0 , ilkUzunluk/2);
		a2 = str1.substr(ilkUzunluk/2 ,ilkUzunluk/2);
	}else{
		a1 = str1.substr(0, ilkUzunluk/2);
		a2 = str1.substr(ilkUzunluk/2+1 , ilkUzunluk/2);
	}
	if(ikinciUzunluk%2==0){
		b1 = str2.substr(0 , ikinciUzunluk/2);
		b2 = str2.substr(ikinciUzunluk/2 ,ikinciUzunluk/2);
	}else{
		b1 = str2.substr(0, ikinciUzunluk/2);
		b2 = str2.substr(ikinciUzunluk/2+1 , ikinciUzunluk/2);
	}
	
	//İşlemler sonrası oluşan yeni kromozomlar bağıl listenin sonuna ekleniyor
	liste->ekle(a1+b2);
	liste->ekle(a2+b1);
	
	listedenDnayaYaz();
}
	
void mutasyon(int kromozom, int gen){
	
	Dugum * n = liste->siradakiniVer(kromozom);
	string ilkHal = n->degeriVer();
	string yeniDeger = n->degeriVer();
	yeniDeger.replace(gen,1,"X"); // Seçilen kromzomun seçilen geninin "X" ile değiştirilmesi
	
	//Mutasyon geçirmiş kromozomun yeni hali düğümde güncellenir
	n->degeriDegistir(yeniDeger);
	
	//Dosya güncellenir
	listedenDnayaYaz();
	
}

void otomatikIslemler(){ // Islem.txt dosyası düzgün formatlanmamışsa hata verir
	
	
	Dugum * n = otoIslemListesi->siradakiniVer(0); ///Liste başı olan düğüm döngüye girmek üzere geçici bir değişkene atanır
	//Son düğüme kadar dönecek bir döngü
	while(n!=NULL){
		string str, islemTuru;
		int ilkSayi, ikinciSayi;
		str = n->degeriVer();
		string tmp1, tmp2;
		tmp1 = str.at(2); // Satırın 3. karakteri işlemdeki ilk kromozomu belirler
		tmp2 = str.at(4); // Satırın 5. karakteri işlemdeki geni ya da ikinci kromozomu belirler
		islemTuru = str.at(0); // Satırıın ilk karakteri işlem türünü belirtir
		ilkSayi = stoi(tmp1); // string'ler int'e dönüştürülür
		ikinciSayi = stoi(tmp2);
		if(islemTuru=="C"){ // Çaprazlama işlemi seçildiyse ilk ve ikinci sayı ilk ve ikinci kromozom olarak fonksiyona verilerek çağırılır
			caprazlama(ilkSayi,ikinciSayi);
		}else if(islemTuru=="M"){ // Mutasyon işlemi seçildiyse ilk ve ikinci sayı kromzom ve gen olarak fonksiyona verilerek çağırılır
			mutasyon(ilkSayi,ikinciSayi);
		}
		n=n->sonrakiniVer(); // Döngünün ilerlemesini sağlar
	}
	//İşlemlerin tamamlandığını belirtir
	cout<<endl<<"Otomatik islemler tamamlandi";
	cin.get();
}



void ekranaTumunuYazListe(){
	int s = 0;
	Dugum * n = liste->siradakiniVer(0);
	while(n!=NULL){
		cout << s << "- " << n->degeriVer() << endl ; 
		n= n->sonrakiniVer();
		s++;
	}
}

void ekranaYaz(){
	Dugum * n = liste->siradakiniVer(0);
	int siraUzunluk, e;
	e=0;
	string sira ,ilkHarf , harfK;
	while(n!=NULL){
		sira= n->degeriVer();
		siraUzunluk = sira.length();
		ilkHarf=sira.at(0);
		for(int y = 0; y<siraUzunluk; y++){
			harfK = sira.at(siraUzunluk-1-y);
			int sonuc = harfK.compare(ilkHarf);
			if(sonuc<0){
				cout <<endl<< e << "- "<< harfK;
				break;
			}else if(y+1==siraUzunluk){
				cout << endl<< e << "- " << ilkHarf;
			}
		}
		e++;
		n= n->sonrakiniVer();
		
	}
	cin.get();
}

int main(){
	int secim;
	string str0;
	fstream okunanDosya;
	cout<<"----------- HOSGELDINIZ! -----------" << endl << endl;
	
	dnadanListeyeKaydet();
	cout << "----------- Dna.txt dekiler listeye gecirildi -----------" <<endl << endl;
	
	
	//Kullanıcı çıkış işlemini temsil eden 5 rakamını girmediği sürece dönmeye devam edecek olan döngü
	do{
		system("CLS");
		//İlk döngüden sonra listedekilerin yazılması işlemi
		int b= 0;
		ekranaTumunuYazListe();
		
		
		//Kullanıcıdan switch case ile yapılacak işlemi seçmesi istenir 
		cout<<endl<<"----------- Islemler -----------"<< endl;
		cout<<"1-Caprazlama"<< endl;
		cout<<"2-Mutasyon" << endl;
		cout<<"3-Otamatik Islemler" << endl;
		cout<<"4-Tum Satirlari Ekrana Yaz"<< endl;
		cout<<"5-Cikis" << endl;
		cout << endl<<"Yapilacak Islem Seciniz: ";
		cin>>secim;
		switch(secim){
			case 1:
				int ilkKromozom, ikinciKromozom;
				cout << endl << "Caprazlanacak ilk kromzomu seciniz: ";
				cin>> ilkKromozom;
				cout << endl << "Caprazlanacak ikinci kromozomu seciniz: ";
				cin>> ikinciKromozom;
				//Kullanıcıdan istenilen değişkenler alındıktan sonra fonksiyonda yerine yazılır fonksiyon bitince döngü yeniden çalışır ve Dna.txt'nin yeni hali ekrana verilir
				caprazlama(ilkKromozom,ikinciKromozom);
			break;
			case 2:
				int kromozom, gen;
				cout << endl << "Mutasyona ugrayacak kromozomu seciniz: ";
				cin>> kromozom;
				cout << endl << "Mutasyona ugrayacak geni secin: ";
				cin>> gen;
				//Kullanıcıdan istenilen değişkenler alındıktan sonra fonksiyonda yerine yazılır fonksiyon bitince döngü yeniden çalışır ve Dna.txt'nin yeni hali ekrana verilir
				mutasyon(kromozom,gen);
			break;
			case 3:
				system("CLS");
				cout << "Otomatik islemleri sectiniz" ;
				//Yapılacak islemlerin anlaşılması için dosya açılır içerisindeli veriler while döngüsünde otoIslemListesi'ne kaydedilir
				
				okunanDosya.open(islemlerPath , ios::in);
				if (!okunanDosya.is_open()) {
					cout << "Islemler.txt dosyasi acilirken hata meydana geldi" << endl;
					break;
				}
				
				cout<<endl<< endl << "---------Yapilacak islemler---------" << endl<< endl;
				while(getline(okunanDosya, str0)){
					cout <<endl<< str0 << endl;
					otoIslemListesi->ekle(str0);
				}
				//İşlem bitince dosya kapatılır
				okunanDosya.close();
				//Fonksiyon çağrılır içine bir metot göndermeye gerek yoktu çünkü yapılacak işlemler otoIslemListesi'ne kaydedilmiştir
				otomatikIslemler();
				//Ekrana yazılanlar görünemeden geçmemesi için kullanıcı bi şey girince ilerlenir
				cout << endl<< "Devam etmek icin enter'a basin"<<endl;
				cin.get();
			break;
			case 4:
				system("CLS");
				cout<< "Ekrana yazmayi sectiniz" <<endl;
				//Fonksiyon çağrılır
				ekranaYaz();
				//Ekrana yazılanlar görünemeden geçmemesi için kullanıcı bi şey girince ilerlenir
				cout <<endl<< "Devam etmek icin enter'a basin"<<endl;
				cin.get();
			break;
			case 5:
			break;
			default: 
			break;
		}

	}while(secim!=5);


	//Listelerden çöp kalmaması için siliyoruz.
	liste->hepsiniTemizle();
	otoIslemListesi->hepsiniTemizle();
	return 0;
}