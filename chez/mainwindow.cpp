#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "windows.h"
#include <math.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    close();
}


void MainWindow::on_pushButton_clicked()
{
    QString ABC("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");

    QString info = ui->lineEdit_in->text();//сообщение
    QString out;
    QString out2;
    QString ABCk;
    QString str;

    int k= ui->spinBox->value();
    int m=ABC.length()-k;


 //афлавит со сдвигом к
    for (int g=0; g<ABC.length();g++)
    { if (g>=ABC.length()-k)
        {
         ABCk.push_back(ABC[abs(g-m)]);
        }
        else{
        ABCk.push_back(ABC[g+k]);
        }
    }

    ui->label_ABC->setText(ABCk);

    for (int f=0;f<ABC.length();f++)
    {
        str.push_back(ABC[f]);
    }
    ui->label_ABC_2->setText(str);
 //проверка на корректность
    for (auto c1: info) //auto любой формат (форматы как инт, чар)
    {
        bool flag = 0;
        for (auto c: ABC)
        {
            if (c == c1)
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            QMessageBox::warning(this,"Ошибка","Не правильные символы");
       }
    }

        //через вайл вывод шифра
        int g=0;
        while (g<info.length())
        {
        for (int i = 0; i < ABC.length(); ++i)
        {

            for (int q = 0; q <ABCk.length(); ++q)
            {
                if (i==q)
                {
                    if (info[g] == ABC[i])
                   {
                   out.push_back(ABCk[i]);


       }}}}
        g++;
        }
        ui->label_out->setText(out);

//расшифровываем
        int p=0;
        while (p<out.length())
        {
        for (int i = 0; i < ABCk.length(); ++i)
        {

            for (int q = 0; q <ABC.length(); ++q)
            {
                if (i==q)
                {
                    if (out[p] == ABCk[i])
                   {
                   out2.push_back(ABC[i]);


       }}}}
        p++;
        }
        ui->label_out2->setText(out2);
}

