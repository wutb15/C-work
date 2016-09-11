#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtGui>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QSqlRecord>
#include<QMessageBox>
#include<QtDebug>
#include"userview.h"
#include"Manager.h"
#include"User.h"
#include"Handle.h"
#include"managerview.h"
#include"Manager.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);//密码设置为不可见
    ui->typeBox->insertItem(0,"Passenger");
    ui->typeBox->insertItem(1,"Admin");
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
        QString filter= QString("username = '")+ui->usernameEdit->text()+QString("'");
        user.setFilter(filter);
        user.select();

        if (user.rowCount()==1)//在数据库中查到了该用户名,开始检测密码是否正确
        {

            if(user.record(0).value("password").toString()!=ui->passwordEdit->text())//密码错误，发出警告信息
            {
                QMessageBox::warning(this,tr("failure"),tr("password wrong or username doesn't exist"),QMessageBox::Close);
            }
            else//用户名和密码都正确
            {

                this->handler=new User(user.record(0));
                UserView userview1(dynamic_cast<User*>(this->handler),this);
                this->close();

                userview1.exec();


            }
        }
        else//用户名不存在，发出警告
        {
            QMessageBox::warning(this,tr("failure"),tr("username doesn't exist "),QMessageBox::Close);
        }
    }
    else//身份为管理员
    {
        QSqlTableModel manager;
        manager.setTable("managers");
        QString filter= QString("username = '")+ui->usernameEdit->text()+QString("'");
        manager.setFilter(filter);
        manager.setFilter(filter);
        manager.select();

        if(manager.rowCount()==1)
        {
            if(manager.record(0).value("password").toString()==ui->passwordEdit->text())
            {

                this->handler=new Manager(manager.record(0));
                ManagerView managerview1(dynamic_cast<Manager*>(handler));
                this->close();
                managerview1.exec();

            }
        }
        else
            QMessageBox::warning(this,tr("failure"),tr("password or username wrong"),QMessageBox::Close);
    }
    ui->usernameEdit->clear();//清空用户名输入框
    ui->passwordEdit->clear();//清空密码输入框
    ui->usernameEdit->setFocus();//将光标转到用户名输入框
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
            QMessageBox::warning(this,tr("failure"),tr("username exists"),QMessageBox::Close);
        }
        else
        {
            query.prepare("INSERT INTO users (username,password)"
                          "VALUES(?,?)");
            query.addBindValue(ui->usernameEdit->text());
            query.addBindValue(ui->passwordEdit->text());
            query.exec();
            QSqlTableModel user;
            user.setTable("users");
            this->handler=new User(user.record(0));
            UserView userview1(dynamic_cast<User*>(this->handler));
            this->close();
            userview1.exec();
        }
            ui->passwordEdit->clear();
            ui->usernameEdit->clear();
    }
    else
    {
        QMessageBox::warning(this,tr("failure "),tr("can't register an admin account. "),QMessageBox::Close);
    }
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}
