//Programda, her koşulda 251 tabanında çalıştığımıza lütfen dikkat edin !!!
#include "secret.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include "bitmap_image.hpp"
using namespace std;
int yedek;
int subline; //alicagim yedek class'a ait bir degisken olmamali
int width,height;
//Satır sayısını alıyoruz ve next toplam satır sayımızı veriyor.

void secret::satirsayisi(){
    ifstream openFile("pikseller.txt");
    string line;
    next = 0;
    while (getline(openFile, line)) {
    if (line.empty()) continue;
    istringstream iss(line);
    next = 1+next;
  }
  subline = next;
}


void secret::sayigir(){
    ifstream file("pikseller.txt");
    satirsayisi();
    semagir();
    for(p = 0; p < next; p++){
	getline(file, girdi); //Herbir R G B değerini alıyorum ve işleme sokuyorum
	fonksyonata();
	paydahesapla();
	paydasec();
	fonksyonbul();
	}}


//Kullanıcıdan şemayı aldım SEMA(SEMAX,SEMAY)
void secret::semagir(){

	//cout << endl << "Semayı girin (kullanicilar,dagitilacaklar)" << endl << " Kullanicilar:\t";
	//cin >> semax;
	//cout << endl << "Dagitacilaklar:\t";
	//cin >> semay;
	semax = 6;
	semay = 3;
	yedek = semay;
   // cout << endl << "Goruntunun Genisligini girin" <<endl;
    //cin >> width;
    //cout << "Goruntunun Yuksekligini girin" <<endl;
    //cin >> height;
    cout<<endl;
}


//Sır paylaşımı alg. gereği fonksyon atamamızı yapıyoruz. Her bir piksele ayrı ayrı fonksyon ataması oluyor.
void secret::fonksyonata(){
    i = 0;
    random = new int[semay-1];
    for(i=0;i<semay-1;i++){
        random[i] = rand() % 4; // 251 e gore mod aldigimizda 12 8 icin mesela goruntu bozuluyor.
    }
}


//Basitce us alma bloğu
int secret::usal(int sayi,int ussu){
    usalsonuc = 1;
    for(int i=1;i<=ussu;i++){
            usalsonuc=usalsonuc*sayi;}
        return usalsonuc;
}


//Kaç kişi varsa o kadar payda(pay) hesaplanıyor.Ardından payda yani hangi kişilere dağıtılacağı seçilecek.
void secret::paydahesapla(){
    i = 0,toplam = 0;
    value = atoi(girdi.c_str());
    partition = new int[semax-1];
    for(i=0;i<semax;i++){
            toplam = 0;
            for(j=0;j<semay-1;j++){
                toplam = toplam+random[j]*usal(i+1,j+1) ;
            }
        partition[i] = (toplam+value) % 251;	//251 e göre mod aldım çünkü çakışmaları önlemem gerekiyor.
    }
}


//Aşağıda hangi kişilere hangi payda(pay) degerlerinin dağıtılacağı seçiliyor. Rastgele secim yaptırıyorum.
void secret::paydasec(){
    selectedpartition = new int [semay];

        for(i =0;i<semay;i++){
	        rastgele = rand() %semax+1;
	            if(i>0){
		            for(j=0;j<i;j++){
		                if(selectedpartition[j]==rastgele) {j = -1; rastgele = rand() %semax+1;}
		            }
		            selectedpartition[i]=rastgele;
	            }
	            else selectedpartition[i] = rastgele;
	        }
    }


//Lagrange İnterpolasyondan çıkan sonuç double ise integer'a çeviriyorum.251 tabanında çalıştığıma dikkat edin !
void secret::oylemi(double interpolasyon){
                            while(1) {
	                            if((interpolasyon-(int)interpolasyon) != 0) {
	                            		pay = pay+251; interpolasyon = (pay/payda);
	                            }
	                            
	                            else {
	                            		interpolasyonint = (int)interpolasyon;
	                            		break;
	                            }
	                        }
                    	}

//Kullanıcıların alacağı yeni piksel değerleri aşağıda hesaplanıp .txt yazılacak.
void secret::fonksyonbul(){

        //Interpolasyon islemine baslaniyor
		//Asagidaki ic ice bulunan for dongusunu daha rahat kavramak icin Lagrange Interpolasyonuna goz atin.

        for(i = 0; i < semay; i++){
	        ofstream dosya;
	        payda = 1, pay = 1; //Interpolasyonda matematiksel olarak pay ve payda

	        for(j = 0; j < semay; j++){
	            if( selectedpartition[i] != selectedpartition[j] ) {
	                pay = -selectedpartition[j] * pay;
	                payda = ( selectedpartition[i] - selectedpartition[j] ) * payda;
	                interpolasyon = ( pay / payda );
	                tut = selectedpartition[i];
	            }
        	}
        	//KONTROL çıkan değerin double olması ihtimaline karşı kontrol ettiriyorum.Double ise integer'a çeviriyorum.
	        //Basina (int) koy diye dusunurseniz hata edersiniz cunku , den sonraki kisim bizim icin oldukca onemli
	        oylemi(interpolasyon);

	        results = ((interpolasyonint * partition[tut-1]) % 251);   //Dağıtacağım piksellerim
	        //interpolasyonun sonucu negatif ise asagidaki isleme sokuyoruz.
	        if((results < 0)){
	        	results = results + 251;
	        }
	        else {
	        	results = ( ( interpolasyonint * partition[tut-1] ) % 251 );
	        }

	        string Result;
	        stringstream convert;
	        convert << i;
	        Result = convert.str();

	        //1.txt 2.txt 3.txt ...
	        filename = Result + ".txt";
	        dosya.open(filename.c_str(), ios::out | ios::binary| ios::app);
	        dosya << results << endl;
        }
}


void pixel::translate(){

    //totaline
    ifstream openFilet("pikseller.txt");
    string linet;

	    while (getline(openFilet, linet)) {
		    if (linet.empty()) continue;

		    istringstream iss(linet);

		    nextt = 1 + nextt;

	  	}

  	rgbarray = new int[nextt];


	//translate

		for(pt = 0; pt < yedek; pt++){
			string Resultt;
			stringstream convertt;
			convertt << pt;
		    Resultt = convertt.str();
			openfilename = Resultt+".txt";

			//Assignment
			it = 0;
			ifstream openFile1t(openfilename.c_str());
			string line1t;

				while (getline(openFile1t, line1t)) {
					if (line1t.empty()) continue;
					istringstream iss(line1t);
					valuet = atoi(line1t.c_str());
					rgbarray[it]  = valuet;
					it++;
				}

		    //11.txt 22.txt 33.txt ...
		    filenamet = Resultt + Resultt +".txt";
		    ofstream txtt;
		    txtt.open(filenamet.c_str(), ios::out | ios::app);
		    it = 0;
		    jt = 0;

		        for (it = 0; it < nextt; ++it)
		        {

		            if(jt == 1 || jt == 0){
		                txtt<<rgbarray[it] << " ";
		                jt++;
		            }
		            else if (jt == 2){
		                txtt<<rgbarray[it];
		                jt++;
		            }
		            else if(jt == 3){
		                txtt<<endl;
		                jt=0;
		                it = it-1;
		            }
		        }
		}
	imagetranslate();
}


void pixel::del(){
    it =0;
    for(it=0;it<yedek;it++){
        string Resulttde;
        stringstream converttde;
        converttde << it;
        Resulttde = converttde.str();

        openfilenamede = Resulttde +".txt";
        remove(openfilenamede.c_str());
        openfilenamede = Resulttde + Resulttde +".txt";
        remove(openfilenamede.c_str());
    }
}

void pixel::imagetranslate(){
    subline = subline/3;
    pt = 0;
	    for(pt=0; pt<yedek; pt++){
	        string Resultti;
	        stringstream convertti;
	        convertti << pt;
	        Resultti = convertti.str();
	        openfilenamei = "./"+ Resultti +".txt";
	    	FILE *imagee;
	    	imagee = fopen(openfilenamei.c_str(), "r");

	   		unsigned char image11[subline][3];

	    	for (i=0; fscanf (imagee, "%d %d %d", &r, &g, &b) == 3; ++i) {
	        	image11[i][0] = r;
	        	image11[i][1] = g;
	       		image11[i][2] = b;
	    	}

			fclose(imagee);


		    bitmap_image image(512,512);   //1.si yukseklik 2.si genislik
		               image_drawer draw(image);
						int k = 0;
		                for (unsigned int d = 0; d < image.width(); ++d)
		               {
		                  for (unsigned int m = 0; m < image.height(); ++m)
		                  {
		                  		image.set_pixel(d,m,image11[k][0],image11[k][1],image11[k][2]);
		                    k++;

		                  }
		               }
		               openfilenamei = Resultti+".bmp";
		               image.save_image(openfilenamei.c_str());
		}

	del();
	cout<<"Finish"<<endl;
}


