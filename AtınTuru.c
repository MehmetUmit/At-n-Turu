#include <stdio.h>

//Tahtanın boyutu
#define B_SIZE 8

//Global değişkenlerin tanımlanması
//Mevcut konumu tutan değişkenler(Satır -> R Sütun -> C)
int currentR,currentC;

//Adımların sayılarını tutan değişken
int board[B_SIZE][B_SIZE] = {0};

//Erişilebilirlik sayılarını tutan değişken
int accessibility[B_SIZE][B_SIZE];

//Atın yapabileceği hamleleri tutan değişkenler
int movR[] = {-2,-2,-1,1,2,2,1,-1};
int movC[] = {-1,1,2,2,1,-1,-2,-2};

//Fonksiyonların prototipleri
int calculateAccessibility(int R,int C);
void calculateAllAccessibility();
void nextMov();

int main(void){
    int i,j;

    //Bütün erişilebilirliklerin hesaplanması
    calculateAllAccessibility();

    //Erişilebilirliğin yazdırılması
    printf("****Erisilebilirlik****\n");
    for(i = 0;i < B_SIZE;i++){
        for(j = 0;j < B_SIZE;j++){
            printf("%d ",accessibility[i][j]);
        }
        printf("\n");
    }
    
	//Başlangıç konumunun girilmesi
    printf("Baslangic konumunu giriniz (Satir-Sutun)(0-7) :");
    scanf("%d %d",&currentR,&currentC);
    
	//Başlangıç konumunun atanması
    board[currentR][currentC] = 1;
    for(i = 2;i <= 64;i++){
        nextMov();
        calculateAllAccessibility();
        board[currentR][currentC] = i;

    }
    printf("\n");
    
	//Tahtanın yazdırılması
    for(i = 0;i < B_SIZE;i++){
        for(j = 0;j < B_SIZE;j++){
            printf("%d\t",board[i][j]);
        }
        printf("\n\n\n");
    }
    return 0;
}

//Atın mevcut konumunu değiştirmeye yarayan fonksiyonun tanımlanması
void nextMov(){
    int i,minA = 9,nextR,nextC;
    
	//Bütün gidebileceği yerlere bakılır (8 durum var)
    for(i = 0;i < 8;i++){
        //Atın gidebileceği konumlar tahtanın içerisindeyse ve gidebileceği konuma daha önce uğramadıysa 
        if(currentR + movR[i] < B_SIZE && currentR + movR[i] >= 0 && currentC + movC[i] < B_SIZE && currentC + movC[i] >= 0 && board[currentR +movR[i]][currentC +movC[i]] == 0){
            //Gidebileceği konumunun erişilebilirliği minA dan küçükse minA nın yerine geçer
            if(accessibility[currentR + movR[i]][currentC + movC[i]] < minA ){
                minA = accessibility[currentR + movR[i]][currentC + movC[i]];
                //Gidebileceği yerin satır ve sütunu , daha düşük erişilebilirliği olan bir hamle olabileceğinden değişkende tutulur 
                nextR = currentR + movR[i];
                nextC = currentC + movC[i];
           }  
        }
    }
    //Atın konumu değiştirilir
    currentR = nextR;
    currentC = nextC;

}

//Bütün erişilebilirlikleri hesaplayan fonksiyonun tanımlanması
void calculateAllAccessibility(){
    int i,j;
    //Erişilebilirliğin hesaplanması
    for(i = 0;i < B_SIZE;i++){
        for(j = 0;j < B_SIZE;j++){
            //Eğer tahtanın belirtilen konumuna daha önce uğramışsa  bir sonraki değere bak
            if(board[i][j] > 0)
                continue;
            //Değilse belirtilen değerin erişilebilirliğini, erişilebilirliğini hesaplayan fonksiyona konumunu gönder ve hesapla
            else
                accessibility[i][j] = calculateAccessibility(i,j);
        }
    }
}

//Gönderilen konuma göre erişilebilirliği hesaplayan fonksiyonun tanımlanması
int calculateAccessibility(int R,int C){
    int i,count = 0;
    //Alınan konumdan yapılabilecek 8 hamleye bakılır
    for(i = 0;i < 8;i++){
        //Hamle tahtanın içindeyse ve hamlenin yapılacağı konuma at uğramamışsa erişilebilirlik sayıcını 1 arttır
        if(R + movR[i] < B_SIZE && R + movR[i] >= 0 && C + movC[i] < B_SIZE && C + movC[i] >= 0 && board[R + movR[i]][C + movC[i]] == 0){
            count ++;

        }
    }
    return count;

}