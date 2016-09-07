#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtGui>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QSqlRecord>
#include<QMessageBox>
#include"User.h"
#include"Manager.h"
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
    if(ui->typeBox->currentText()=="Passenger")//身份为乘客
    {
        QSqlTableModel user;
        user.setTable("users");
        user.setFilter("username = "+ui->usernameEdit->text());
        user.select();

        if (user.rowCount()==1)//在数据库中查到了该用户名,开始检测密码是否正确
        {

            if(user.record(0).value("password").toString()!=ui->passwordEdit->text())//密码错误，发出警告信息
            {
                QMessage::warning(this,tr("登录失败！"),tr("密码错误"),QMessageBox::Close);
            }
            else//用户名和密码都正确
            {
                handler=new User(user.record(0));
                accept();
                this->close();

            }
        }
        else//用户名不存在，发出警告
        {
            QMessage::warning(this,tr("登录失败！"),tr("用户名不存在"),QMessageBox::Close);
        }
    }
    else//身份为管理员
    {
        QSqlTableModel manager;
        manager.setTable("managers");
        manager.setFilter("username = "+ui->usernameEdit->text());
        manager.select();

        if(manager.rowCount()==1)
        {
            if(manager.record(0).value("password").toString()==ui->passwordEdit->text())
            {

                handler=new Manager(manager.record(0));
                accept();
                this->close();

            }
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
    if(ui->typeBox->currentText()=="Passenger")

   {
        QSqlQuery query;
        QSqlQuery query1;
        query1.prepare("select * from users where username=?");
        query1.addBindValue(ui->usernameEdit->text());
        query1.exec();
        if(query1.next())//用户名已被注册，发出警告信息
        {
            QMessageBox::warning(this,tr("注册失败！"),tr("该用户名已被注册"),QMessageBox::Close);
        }
        else
        {
            query.prepare("insert into users values(?,?)");
            query.addBindValue(ui->usernameEdit->text());
            query.addBindValue(ui->passwordEdit->text());
            query.exec();
        }
            ui->passwordEdit->clear();
            ui->usernameEdit->clear();
    }
    else
    {
        QMessageBox::warning(this,tr("注册失败"),tr("无法注册管理员账号"),QMessageBox::Close);
    }
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}
