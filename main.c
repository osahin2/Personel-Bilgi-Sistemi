#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
typedef struct
{
    char Isim[100];
    long int TCKimlikNo;
    long int Telefon;
    char Eposta[100];
    char Adres[100];
}Personel;
Personel perE[10];
void KayitEkle();
void Listele();
void Duzenle();
void TCKayitBul();
void IsimKayitBul();
void KayitSil();
int sayac=0;

int main()
{
    setlocale(LC_ALL, "Turkish");
    int secim;
    do
    {
        printf("1. Kayit Ekle\n");
        printf("2. Personel Listele\n");
        printf("3. Kaydi Düzenle\n");
        printf("4. Tc Kimlik No ile Kayit Bul\n");
        printf("5. Isim ile Kayit Bul\n");
        printf("6. Kayit Sil\n");
        printf("0. Cikis\n");
        scanf("%d",&secim);

        switch(secim)
        {
            case 1: KayitEkle();break;
            case 2: Listele();break;
            case 3: Duzenle();break;
            case 4: TCKayitBul();break;
            case 5: IsimKayitBul();break;
            case 6: KayitSil();break;
            case 0: exit(0);break;
        }
    }while(secim<=6 && secim>=0);


    return 0;
}
void KayitEkle()
{
    FILE *fp;
    fp=fopen("Personel.txt","wb+");
    printf("Personel Isim:\n");
    scanf("%s",perE[sayac].Isim);
    fflush(stdin);
    printf("Personel Tc Kimlik No:\n");
    scanf("%ld",&perE[sayac].TCKimlikNo);
    fflush(stdin);
    printf("Personel Telefon:\n");
    scanf("%ld",&perE[sayac].Telefon);
    fflush(stdin);
    printf("Personel Eposta:\n");
    scanf("%s",perE[sayac].Eposta);
    fflush(stdin);
    printf("Personel Adres:\n");
    scanf("%s",perE[sayac].Adres);
    fflush(stdin);
    fwrite(&perE,sizeof(perE),1,fp);
    sayac++;
    fclose(fp);
}
void Listele()
{
    FILE *fp;
    fp=fopen("Personel.txt","r");
    Personel perL;
    while(fread(&perL,sizeof(perL),1,fp)!=0)
    {
        printf("%s \n%ld \n%ld \n%s \n%s",perL.Isim,perL.TCKimlikNo,perL.Telefon,perL.Eposta,perL.Adres);
    }
    fclose(fp);
}
void Duzenle()
{
    FILE *fp,*fp2;
    fp=fopen("Personel.txt","r");
    fp2=fopen("Personel1.txt","w");
    char secim1;
    char Aranan[100];
    Personel perD;
    printf("Düzenlenecek Personelin Adini Giriniz.");
    scanf("%s",Aranan);
        while(fread(&perD,sizeof(perD),1,fp)==1)
    {
        if(strcmp(Aranan,perD.Isim)==0)
        {
            printf("Yeni Bilgiler:\n");
            printf("Ýsim:\n");
            scanf("%s",perD.Isim);
            printf("TC:\n");
            scanf("%ld",&perD.TCKimlikNo);
            printf("Telefon:\n");
            scanf("%ld",&perD.Telefon);
            printf("Eposta:\n");
            scanf("%s",perD.Eposta);
            printf("Adres:\n");
            scanf("%s",perD.Adres);

        }
        fwrite(&perD,sizeof(perD),1,fp2);
    }
    fclose(fp);
    fclose(fp2);
    remove("Personel.txt");
    rename("Personel1.txt","Personel.txt");
}
void TCKayitBul()
{
    long int GirilenTc;
    Personel PerTc;
    FILE *fp;
    fp=fopen("Personel.txt","r");
    printf("Aranacak TC yi Giriniz:\n");
    scanf("%ld",&GirilenTc);
    while(fread(&PerTc,sizeof(PerTc),1,fp)==1)
    {
        if(GirilenTc==PerTc.TCKimlikNo)
        {
            printf("Bilgiler:\n");
            printf("%s \n%ld \n%ld \n%s \n%s",PerTc.Isim,PerTc.TCKimlikNo,PerTc.Telefon,PerTc.Eposta,PerTc.Adres);
        }
    }
    fclose(fp);
}
void IsimKayitBul()
{
    char GirilenIsim[15];
    Personel PerI;
    FILE *fp;
    fp=fopen("Personel.txt","r");
    printf("Aranacak Isimi Giriniz:\n");
    scanf("%s",GirilenIsim);
    while(fread(&PerI,sizeof(PerI),1,fp)==1)
    {
        if(strcmp(GirilenIsim,PerI.Isim)==0)
        {
            printf("Aranan Personelin Bilgileri:\n");
            printf("%s \n%ld \n%ld \n%s \n%s",PerI.Isim,PerI.TCKimlikNo,PerI.Telefon,PerI.Eposta,PerI.Adres);
        }
    }
    fclose(fp);
}
void KayitSil()
{
    char secim1;
    do
    {
        FILE *fp,*fp2;
        fp=fopen("Personel.txt","r");
        fp2=fopen("Personel1.txt","w");
        long int SilinenTc;
        Personel PerS;
        int kontrol=0;

        printf("Kaydi silinecek  Personelin TC'sini Giriniz:\n");
        scanf("%ld",&SilinenTc);
        while(fread(&PerS,sizeof(PerS),1,fp)==1)
        {
            if(SilinenTc==PerS.TCKimlikNo)
                kontrol++;
            else
                fwrite(&PerS,sizeof(PerS),1,fp2);
        }
        fclose(fp);
        fclose(fp2);
        remove("Personel.txt");
        rename("Personel1.txt","Personel.txt");

        if(kontrol!=0)
        {
            printf("Kayit Basariyla Silindi.\n");
            printf("Baska Kayit Silmek Istiyor musunuz?<y-Evet/n-Hayir>\n");
            scanf("%s",secim1);

        }
        else
        {
            printf("Kayit Bulunamadi!\n");
            break;
        }



    }while(secim1=='y' || secim1=='Y');
}

