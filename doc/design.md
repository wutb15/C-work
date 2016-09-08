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
			void booktickets(Profile* profile,int begin_id,int end_id);
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
	
```

##QT界面控制//Qmainwindow的函数

private:

	- enum Mode mode;
	- Handler* handler;
	
	- createSignInpanel()创建登陆界面
	- deleteLoginpanel()//之后的delete就不重复了
	- createSignuppanel()//注册界面
	- createNavigationbar()
	- createProfielpanel()//显示用户个人信息界面
	- createTrainspanel()//显示列车信息，包括沿途车站，Mmode下调用；
	- createSearchTicketspanel()//显示搜索车票界面，包括一个搜索框与结果显示框
	- createTicketpanel()/显示票界面
	- clearView()/清空CentralWidget显示界面

	QSqlRelationalTableModel* TrainModel;
	QSqlRelationalTableModel* ProfileModel;
	QWidget* Profilepanel;
	...
	
private slots:

	- //Mmode 下默认station不变
	- showTrains();
	- editTrains();
	- addTrains();
	- //Nmode
	- editProfile();
	- addProfile();
	- bookTickets();
	- showSignIn();
	- showSignUp();
	- showProfile();
	- showTickets();
	
	
 




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
	