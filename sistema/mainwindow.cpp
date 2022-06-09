#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include "cmath"

using namespace std;

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

double math(double m)
{
    double rnd, F=0;
    rnd = rand()%16+1;
    F= 1 - exp(-1/m*rnd);
    return F*m;
}

void MainWindow::on_pushButton_clicked()
{
    double time_profitE = 0,time_profitB = 0, time_costE = 0, time_costB = 0;
    int conditionE=0, conditionB=0, kol_work=0; //profit-работа, cost-простой; Ni - текущий день;
    //condition 0-начало дня, 1-простой, 2-работа (работает машина), 3-починка (машину чинят)
    double time_work1B= 0,time_work2B= 0, time_work1E= 0, time_work2E= 0;
    double sum2B = 0, sum1B = 0, sum3B=0, sum2E = 0, sum1E = 0, sum3E=0, sumBothB=0, sumBothE; //сумма времени по состояниям: н) sum2B-сумма (2)-работы(см выше) бульдозера
    double SUMEB, SUMW, ClearPrice;
    int conditionW=0; //рабочие, condition 0-свободен, 1-занят


    //перенос из первой таблицы, матем ожидание машин
    double math_E = ui->doubleSpinBox_E->value();
    double math_B = ui->doubleSpinBox_B->value();
    //перенос из второй таблицы, матем ожид рабочих
    double math_3E = ui->doubleSpinBox_3E->value();
    double math_6E = ui->doubleSpinBox_6E->value();
    double math_2E = ui->doubleSpinBox_2E->value();
    double math_6B = ui->doubleSpinBox_6B->value();
    double math_2B = ui->doubleSpinBox_2B->value();
    //перенос из третьей таблицы, доход и убытки
    double profitE = ui->doubleSpinBox_profitE->value();
    double profitB = ui->doubleSpinBox_profitB->value();
    double costE = ui->doubleSpinBox_costE->value();
    double costB = ui->doubleSpinBox_costB->value();
    //перенос из четвертой таблицы,заплата
    double salary3 = ui->doubleSpinBox_salary3->value();
    double salary6 = ui->doubleSpinBox_salary6->value();
    double salBoth = ui->doubleSpinBox_salBoth->value();
    double smena = ui->doubleSpinBox_smena->value();

    double S;
    if (ui->radioButton->isChecked()) //если выбираем одного рабочего(6 разряд слесаря)
    {
         kol_work = 1;
    }
    if (ui->radioButton_2->isChecked()) //слесари работают вдвоем
    {
        kol_work = 2;
    }
    int N=ui->spinBox_N->value();
    for (int Ni=0; Ni<=N; Ni++) // цикл от 0 до н дней
    {
        while (S <smena) //сумма всех работ за день не превышает 16 часов
        {
    if (conditionB == 0)
    {
        time_profitB = math(math_B);
        conditionB = 2;
    }
   else if (conditionE == 0)
    {
        time_profitE = math(math_E);
        conditionE = 2;
    }
    if (conditionB == 2)
    {
        conditionB = 1;
    }
   else if (conditionE == 2)
    {
        conditionE = 1;
    }
    if (conditionE == 1) //поломка экскаватора
    {
        if (kol_work == 2 && conditionW == 0)
        {
            time_costE = math(math_2E);
            conditionW = 1;
            time_work2E = time_costE;
            conditionE= 3;
        }
        else if (kol_work == 1 && conditionW == 0)
        {
            time_costE = math(math_6E);
            conditionW = 1;
            time_work1E = time_costE;
            conditionE= 3;
        }

    }

    if (conditionB == 1) //поломка бульдозера
    {
        if (kol_work == 2 && conditionW == 0)
        {
            time_costB = math(math_2B);
            conditionW = 1;
            time_work2B = time_costB;
            conditionB= 3;
        }
        else if (kol_work == 1 && conditionW == 0)
        {
            time_costB = math(math_6B);
            conditionW = 1;
            time_work1B = time_costB;
            conditionB= 3;
        }
    }
    if (conditionE == 3) //время работы после починки E
    {
        conditionE = 2;
        time_profitE = math(math_E);
        conditionW = 0;
    }
    if (conditionB == 3) //время работы после починки B
    {
        conditionB = 2;
        time_profitB = math(math_B);
        conditionW = 0;
    }
        if (conditionB == 2)
        {
            sum2B = sum2B + time_profitB;
        }
        else if (conditionB == 1)
        {
            sum1B = sum1B + time_costB;
        }
        else if (conditionB == 3 && kol_work == 2)
        {
            sumBothB = sumBothB + time_work2B;
        }
        else if (conditionB == 3 && kol_work == 1)
        {
            sum3B = sum3B + time_work1B;
        }

        //E
        if (conditionE == 2)
        {
            sum2E = sum2E + time_profitE;
        }
        else if (conditionE == 1)
        {
            sum1E = sum1E + time_costE;
        }
        else if (conditionE == 3 && kol_work == 2)
        {
            sumBothE = sumBothE + time_work2E;
        }
        else if (conditionE == 3 && kol_work == 1)
        {
            sum3E = sum3E + time_work1E;
        }
        S =  sum2B+sum1B+sum3B+sum2E+sum1E+sum3E+sumBothB+sumBothE; //считаем сумму часов работ за день (иногда больше чем 16 дает, не знаю почему)

        }//end while
        if (kol_work == 2) {
        SUMEB = SUMEB + sum2E*profitE +sum2B*profitB - sum1E*costE +sum1B*costB; //считаем конечную сумму, доходов и убытков от машин- бульдозра и экскаватора
        SUMW = SUMW + (sumBothE*salBoth+time_work2B*salary6 +time_work2E*salary6+time_work2E*salary3); //зарпалата рабочих за все  время
        ClearPrice =  (SUMEB - SUMW);
        }
        else if (kol_work == 1) {
        SUMEB =SUMEB+ (sum2E*profitE +sum2B*profitB - sum1E*costE +sum1B*costB);
        SUMW = SUMW+(time_work1B * salary6 +time_work1E*salary6);
        ClearPrice =  (SUMEB - SUMW);
        }

    }


    QString Str = QString::number(SUMEB, 'g', 10);
    ui->label_out->setText(Str);

    QString Str1 = QString::number(SUMW, 'g', 10);
    ui->label_out2->setText(Str1);


    QString Str2 = QString::number(ClearPrice,'g', 10);
    ui->label_out3->setText(Str2);
}













