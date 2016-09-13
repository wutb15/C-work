#Design of the work

##Design of the view

- We will use the QMainwindow's structure as our mainwindow's structure.This means our mainwindow will contain a menubar,a centralWidget,a statusbar,and a Toolbar.


##Design of the class
- class handler（记录使用者类，派生出user 与mananger 两个子类 ）

```
{
	enum class Handlertype
	{
		user,
		manager,
	
	}
	class Handler
	{
		protected:
			QString	username;
			QString password;
			QSqlRecord* record;
		public:
			QString getusername(),
			QString getpassword(),
			void    setusername(Qstring src),
			void    setpassword(Qstring src),
			virtual ~Handler();
			Handler()
			virtual QSqlRecord toSqlRecord(),
			virtual void       load(QSqlRecord& src);	

	}
	
	class User:public Handler
	{
		protected:
			int personalprofile_id;
			QString extrainformation;
		public:
			User(QSqlRecord &src);
		
		
	} 

	class Manager:public Handler
	{
		public:
			Mananger(QSqlRecord&src);
			~Manager();
		
	}


}

```

- class basicdata(记录一些基本数据类，派生出profile,train,station,以及trainstation,用于操作与单个显示，大规模显示查询结果利用QSqlTableModel 与QSqlRelationalTableModel )

```
enum class BasicDataType
{
    Train,
    Profile,
    Station,
    TrainStation,
    Ticket
};
//这里的类只用做显示不能更改，更改只能通过qsqltable;
class BasicData
{
public:
    BasicData(){}
    virtual ~BasicData(){delete _record;}
    virtual void load(QSqlRecord&src)=0;
    QSqlRecord toSqlRecord();

protected:
    QSqlRecord* _record;
};

class TrainStation;
class Train:public BasicData
{
public:
    Train(QSqlRecord& src);
    void load(QSqlRecord& src);
    QList<TrainStation*> getstations();
    TrainStation* getstation(int number);
    int getindex(int station_id);
    QString gettrainnumber()const；
    SeatType getseattype()const；
    SpeedType getspeedtype()const；
    ~Train();
 private:
    QString trainnumber;
    SeatType seattype;
    SpeedType speedtype;
    QList<TrainStation*> trainstations;

};


class Station:public BasicData
{
public:
    Station(QSqlRecord& src);
    void load(QSqlRecord& src);
    int getid()const；
    QString getname()const；
    QString getprovince()const；
private:
    int id;
    QString name;
    QString province;

};
class Ticket:public BasicData
{
public:
    Ticket(QSqlRecord& src);
    void load(QSqlRecord& src);
    Profile getProfile();
    int getid()const；
    int getseatnumber() const；
    QString gettrainnumber() const；
    QString getusername()const；


 private:
    int id;
    int profile_id;
    int seatnumber;
    QString trainnumber;
    int beginnumber;
    int endnumber;
    QString username;

};

class TrainStation:public BasicData
{
public:
    TrainStation(QSqlRecord& src);
    void load(QSqlRecord& src);
    QString gettrainnumber()const{return trainnumber;}
    QTime   getstarttime()const{return starttime;}
    QTime	getarrivetime()const{return arrivetime;}
    int 	getmiles()const{return miles;}
    int 	getbookednumber()const{return bookednumber;}
    int		getstation_id()const{return station_id;}
    Station* getstation();
private:
    int id;
    QString trainnumber;
    QTime starttime;
    QTime arrivetime;
    Station* _station;
    int station_id;
    int miles;
    int bookednumber;

};

class Profile:public BasicData
{
public:
    Profile(QSqlRecord& src);
    void load(QSqlRecord& src);
    QString getsex()const；
    int 	getid()const；
    QString getname()const；
    QString getcardid()const；
    QString getphone()const；
    QString getusername()const；
 private:
    int id;
    QString sex;
    QString name;
    QString cardid;
    QString phone;
    QString username;

};

//还有枚举类来记录变量域，方便sql查询

enum class ProfileField
{
    Profile_Id,
    Profile_Sex,
    Profile_Name,
    Profile_Cardid,
    Profile_Phone,
    Profile_Username
};

enum class StationField
{
    Station_Id,
    Station_Name,
    Station_Province
};

enum class TicketField
{
    Ticket_Id,
    Ticket_Profile_Id,
    Ticket_Seatnumber,
    Ticket_Trainnumber,
    Ticket_Beginnumber,
    Ticket_Endnumber,
    Ticket_Username
};
enum class TrainField
{
    Train_Number,
    Train_SeatType,
    Train_SpeedType
};

enum class TrainStationField
{
    TrainStation_Id,
    TrainStation_TrainNumber,
    TrainStation_StartTime,
    TrainStation_ArriveTime,
    TrainStation_Station_Id,
    TrainStation_Miles,
    TrainStation_BookedNumber//被预定的票数
};

enum class UserField
{
    User_UserName,
    User_Password,
    User_Money,
    User_Extrainformation
};

enum class ManagerField
{
    Manager_UserName,
    Manager_Password,
};
	
```

##QT界面控制
###Form 类(用于更改基本数据)

```
class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);

private:
    virtual void addItem()=0;//执行增加元素的作用
    virtual void deleteItem()=0;//执行删减元素的作用
    virtual void createMap()=0;//创建表与数据库对应关系
    virtual void createContents()=0;//创建表的内容
    virtual void createTable()=0;//创建和链接表;



protected:
    Ui::Form ui;
    QDataWidgetMapper* mapper;
    QSqlRelationalTableModel* tableModel;
    void on_addButton_clicked();
    void on_deleteButton_clicked();
};

class ProfileForm : public Form
{
    Q_OBJECT
public:
    explicit ProfileForm(const QString& username,int id,QWidget* parent=0);
private:
    void addItem();
    void deleteItem();


    void createContents();
    void createMap();
    void createTable();


    const QString& _username;


    QLabel* usernameLabel;
    QLineEdit* usernameEdit;

    QLabel* nameLabel;
    QLineEdit* nameEdit;

    QLabel* sexLabel;
    QComboBox* sexCombo;

    QLabel* phoneLabel;
    QLineEdit* phoneEdit;

    QLabel* cardIdLabel;
    QLineEdit* cardIdEdit;

};

class TrainForm : public Form
{
    Q_OBJECT
public:
    TrainForm(const QString& Trainnumber ,QWidget* parent);
private:
    void addItem();
    void deleteItem();


    void createContents();
    void createMap();
    void createTable();

    QLabel* trainnumberLabel;
    QLineEdit* trainnumberEdit;

    QComboBox* seatCombo;
    QLabel*  seatLabel;

    QComboBox* speedCombo;
    QLabel*  speedLabel;

    QStringListModel* seatType;
    QStringListModel* speedType;



};

class TrainStationForm : public Form
{
public:
    TrainStationForm(int id,QWidget* parent);
private:
    void addItem();
    void deleteItem();


    void createContents();
    void createMap();
    void createTable();

    QLabel* trainnumberLabel;
    QComboBox* trainnumberCombo;

    QLabel* starttimeLabel;
    QTimeEdit* starttimeEdit;//editable

    QLabel* arrivetimeLabel;
    QTimeEdit* arrivetimeEdit;//editable

    QLabel* stationLabel;
    QComboBox* stationCombo;

    QLabel* milesLabel;
    QSpinBox* milesEdit;//editable

    QLabel* bookedLabel;
    QSpinBox* bookedEdit;//editable



};

```

###用于显示的类
 - mainwindow(登陆界面)
   - managerview

   - userview
		- searchview
			- seatview
				- bookview
		- password
        
		- charge
        
		- profileview	

	
	
 




##Design of the Database

- We will use the sqlite
- We will use the QsqlTableModel and QsqlrelationalTableModel to do all the job.

```sqlite
TABLE users {
	username TEXT PRIMARY KEY NOT NULL,
	password TEXT NOT NULL,
	money    REAL DEFAULT,
	extrainformation TEXT,
}

TABLE profiles{
	id INT PRIMARY KEY NOT NULL AUTOINCREMENT,
	sex		 TEXT NOT NULL,
	name     TEXT NOT NULL,	
	cardid	 TEXT NOT NULL,
	phone  	 TEXT NOT NULL,
	username TEXT NOT NULL,
	FOREIGN KEY(username) REFERENCES users(username)
}

TABLE managers{
	username TEXT PRIMARY KEY  NOT NULL,
	password VARCHAR(40) NOT NULL,
}

TABLE trains{
	trainnumber TEXT PRIMARY KEY NOT NULL,
	seattype INT NOT NULL,(0 是坐铺 ，1 是卧铺)
	speedtype INT NOT NULL,(0 至3分别代表 普快，特快，动车，高铁) 
	
}

TABLE trainstations{

	id INT PRIMARY KEY NOT NULL AUTOINCREMENT,
	trainnumber TEXT NOT NULL,
	starttime   TEXT NOT NULL,
	arrivetime  TEXT NOT NULL,
	station_id  INT  NOT NULL,
	miles		INT  NOT NULL,
	booknumber  INT  DEFAULT 0;
	FOREIGN KEY(trainnumber) REFERENCES trains(trainnumber)
	FOREIGN KEY(station_id)	 REFERENCES stations(id)
	
}

TABLE stations{
	id INT PRIMARY KRY NOT NULL AUTOINCREMENT,
	name TEXT NOT NULL,
	province  TEXT NOT NULL,
}

TABLE tickets{
	id INT PRIMARY KEY NOT NULL AUTOINCREMENT,
	profile_id INT NOT NULL,
	seatnumber INT NOT NULL,
	trainnumber INT NOT NULL,
	beginnumber	INT NOT NULL,
	endnumber   INT NOT NULL,
	FOREIGN KEY(trainnumber) REFERENCES trains(trainnumber)
	FOREIGN KEY(profile_id)		 REFERENCES profile(id)	
	
}

```

//ToDo.
	