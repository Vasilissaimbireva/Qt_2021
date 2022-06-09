#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "windows.h"
#include <math.h>
#include <QMessageBox>

using namespace std;
static QString str;
static QString out_gamma;
static QString out;
static QString abc("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
static int n=33;

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



void MainWindow::on_pushButton_3_clicked()
{
    QWidget::close();
}


void MainWindow::on_pushButton_clicked() //зашифровка
{

        int m=0;

        QString info = ui->lineEdit_in->text();//считываем сообщение

        QString gamma = ui->lineEdit_gamma->text();//считываем ключ - гамму
        if (info.length()%gamma.length()==0)
        {
            m=info.length()/gamma.length();
        }
        else if (info.length()%gamma.length()!=0)
        {
            m=ceil(info.length()/gamma.length())+1;
        }

      // выводим код сообщения

        for (int i = 0; i < info.length(); ++i)
        {
            for (int j = 0; j < abc.length(); ++j)
            {
                if (info[i] == abc[j])
                {
                    if (j>10)
                    {
                    out.push_back(QString::number(j));

                    break;}

                    else {
                        out.push_back('0');
                        out.push_back(QString::number(j));

                        break;
                    }
                    }
                else if (info[i]==' ')
                  {
                      out.push_back(' ');
                      break;
                  }
                }
            }


        ui->lineEdit_inf->setText(out);


         int g=0;
         while (g<m)
         {
         for (int k = 0; k < gamma.length(); ++k)
         {

             for (int q = 0; q <abc.length(); ++q)
             {
                 if (gamma[k] == abc[q])
                 {
                     if (q>10)
                    {
                    out_gamma.push_back(QString::number(q));

                     break;
                     }

                     else {
                     out_gamma.push_back('0');
                     out_gamma.push_back(QString::number(q));
                     break;
                 }
                    }
             }
        }
         g++;
         }

         ui->lineEdit_gam->setText(out_gamma);

                // вывод в out 1 (зашифровка)

                 for (int k = 0; k < out_gamma.length(); k+=2)
                 {
                 for (int i = 0; i < out.length(); i+=2)
                 { if (k==i)
                     {
                        int asd = out[i].digitValue();
                        int asd1 = out[i+1].digitValue();
                        int asd2 = out_gamma[k].digitValue();
                        int asd3 = out_gamma[k+1].digitValue();
                        int a= ((asd*10+asd1)+(asd2*10+asd3))%n;

                        if (a>10)
                        {
                        str.push_back(QString::number(a));

                        break;
                        }

                        else {
                        str.push_back('0');
                        str.push_back(QString::number(a));
                        break;

                            }}}
                 }
                  ui->lineEdit_out1->setText(str);

                   // вывод в out 3 (буквы зашифровка)
                    QString str3;
                    for (int i = 0; i < str.length(); i+=2)
                    {
                        int asd = str[i].digitValue();
                        int asd1 = str[i+1].digitValue();

                        int a= (asd*10+asd1);
                    for (int j = 0; j < abc.length(); ++j)

                        { if (a==j)

                           str3.push_back(abc[j]);

                           }
                    }
                     ui->lineEdit_out3->setText(str3);

}


void MainWindow::on_pushButton_2_clicked() //расщифровка
{
    // вывод в out 2 (расшифровка)
    QString str1;
     for (int i = 0; i < str.length(); i+=2)
    {
      for (int k = 0; k < out_gamma.length(); k+=2)
    { if (k==i)
        {
           int asd = str[i].digitValue();
           int asd1 = str[i+1].digitValue();
           int asd2 = out_gamma[k].digitValue();
           int asd3 = out_gamma[k+1].digitValue();
           int a= ((asd*10+asd1)+n-(asd2*10+asd3))%n;

           if (a>10)
          {
          str1.push_back(QString::number(a));

           break;
           }
           else {
           str1.push_back('0');
           str1.push_back(QString::number(a));
           break;
       }
               }}}
     ui->lineEdit_out2->setText(str1);


       // вывод в out 4 (буквы расшифровка)
        QString str4;
        for (int i = 0; i < str1.length(); i+=2)
        {
            int asd = str1[i].digitValue();
            int asd1 = str1[i+1].digitValue();

            int a= (asd*10+asd1);
        for (int j = 0; j < abc.length(); ++j)

            { if (a==j)

               str4.push_back(abc[j]);

               }
        }
         ui->lineEdit_out4->setText(str4);
}

