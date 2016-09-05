#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtGui>
#include<QtSql/QSqlQuery>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit2->setEchoMode(QLineEdit::Password);//密码设置为不可见
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logButton_clicked()//用户点击登录按钮
{
    if(ui->comboBox->currentText()=="Passenger")//身份为乘客
    {

        if ()//在数据库中查到了该用户名,开始检测密码是否正确
        {

            if(password!=ui->lineEdit2->text().toInt())//密码错误，发出警告信息
            {
                QMessage::warning(this,tr("登录失败！"),tr("密码错误"),QMessageBox::Close);
            }
            else//用户名和密码都正确
            {
                accept();
                this->close();
                User user1(ui->lineEdit1);
            }
        }
        else//用户名不存在，发出警告
        {
            QMessage::warning(this,tr("登录失败！"),tr("用户名不存在"),QMessageBox::Close);
        }
    }
    else//身份为管理员
    {
        if(ui->lineEdit1->text()=="Admin"&&ui->lineEdit2->text()=="123456")
        {
            accept();
        }
        else
            QMessage::warning(this,tr("登录失败！"),tr("用户名或密码错误"),QMessageBox::Close);
    }
    ui->lineEdit1->clear();//清空用户名输入框
    ui->lineEdit2->clear();//清空密码输入框
    ui->lineEdit1->setFocus();//将光标转到用户名输入框
}

void MainWindow::on_newButton_clicked()//用户点击注册按钮
{
    QSqlQuery query;
    QSqlQuery query1;
    query1.prepare("select * from passengers where paName=?");
    query1.addBindValue(ui->lineEdit1->text());
    query1.exec();
    if(query1.next())//用户名已被注册，发出警告信息
    {
        QMessageBox::warning(this,tr("注册失败！"),tr("该用户名已被注册"),QMessageBox::Close);
    }
    else
    {
        query.prepare("insert into passengers values(?,?)");
        query.addBindValue(ui->lineEdit1->text());
        query.addBindValue(ui->lineEdit2->text().toInt());
        query.exec();
    }
    ui->lineEdit1->clear();
    ui->lineEdit2->clear();
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}
