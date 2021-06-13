#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfile.h>
#include <qdir.h>
#include <windows.h>

int pstI = 0;
int pstT = 0;
int lenghtI = 0;
int lenghtT = 0;
QStringList ingilizceListe;
QStringList turkceListe;

void ingilizceList(){
    QFile  fileIngilizce("english.txt");
    fileIngilizce.open(QFile::ReadOnly);
    QTextStream in(&fileIngilizce);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ingilizceListe.append(line);
        lenghtI ++;
    }
}

void turkceList(){
    QFile  fileTurkce("turkce.txt");
    fileTurkce.open(QFile::ReadOnly);
    QTextStream in(&fileTurkce);
    while (!in.atEnd()) {
        QString line = in.readLine();
        turkceListe.append(line);
        lenghtT ++ ;
    }
}

QString ingilizce(int i){
    if(lenghtI == i ){
        MessageBoxA(0,"Ingilizce kelimeler bitti!" ,"UYARI!", MB_ICONWARNING);
        pstI = -1;
        return 0;
    }
    return(ingilizceListe[i]);
}

QString turkce(int i){
    if(lenghtT == i ){
        MessageBoxA(0,"Turkce kelimeler bitti!" ,"UYARI!", MB_ICONWARNING);
        pstT = -1;
        return 0;
    }
    return(turkceListe[i]);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ingilizceList();
    turkceList();
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

bool ctrl(QString x){
    if(x == "")
    {
        MessageBoxA(0,"KELIME GIRIS ALANI BOS OLAMAZ!" ,"UYARI!", MB_ICONWARNING);
        return false;
    }
    else{
        return true;
    }
}

void MainWindow::on_kelimeGiris_clicked()
{
    if(ctrl(ui->kelimeGirisLine->text())){
        QString kelime;
        QString turkce;
        QString ingilizce;
        kelime = ui->kelimeGirisLine->text();
        QStringList list = kelime.split(":");
        ingilizce = list[0];
        turkce = list[1];
        QFile fileIngilizce("english.txt");
        fileIngilizce.open(QFile::Append);
        QTextStream yazIngilizce(&fileIngilizce);
        yazIngilizce << ingilizce + "\n";
        fileIngilizce.close();
        QFile fileTurkce("turkce.txt");
        fileTurkce.open(QFile::Append);
        QTextStream yazTurkce(&fileTurkce);
        yazTurkce << turkce + "\n";
        fileTurkce.close();
        MessageBoxA(0,"Kelimeler eklendi" ,"Bilgi!", MB_ICONINFORMATION);
        ui->kelimeGirisLine->clear();
        lenghtI = 0;
        lenghtT = 0;
        turkceListe.clear();
        ingilizceListe.clear();
        turkceList();
        ingilizceList();
    }
}

void MainWindow::on_ingilizceYaz_clicked()
{
    ui->ingilizceKelime->appendPlainText(ingilizce(pstI));
    pstI++;
}

void MainWindow::on_turkceYaz_clicked()
{
    ui->turkceKelime->appendPlainText(turkce(pstT));
    pstT++;
}

void MainWindow::on_temizle_clicked()
{
    ui->ingilizceKelime->clear();
    ui->turkceKelime->clear();
    pstI = 0;
    pstT = 0;
}
