#Design of the work

##Design of the view

- We will use the QMainwindow's structure as our mainwindow's structure.This means our mainwindow will contain a menubar,a centralWidget,a statusbar,and a Toolbar.

- The desgin of every part of the main window:
	- Menubar:We will use the menubar as a navigationbar.We will separate the Actions in three kinds: 
		- "before logining in"(referred as "Bmode" below) , 
		- "after logining in(Normal user)"(referred as "Nmode" below),
		- "after logining in(Manager)"(referred as "Mmode" below);<br>
	Only one kind of Actions will be enabled at a time.The Actions are designed to choose view.

	- Central Widget:This place contains the main parts of our project.In Bmode, we have two choices, " Sign in" view and "Sign Out" view, both consisting of Labels,  lineEditors and ConfirmButton .<br>
In Nmode,we can choose "Profile view" and "Book view".
In Mmode , we can choose "Manager view" ,where we can search ,insert ,delete the information of the trains.


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
			QString	username,
			QString password,
			Handlertype type,
			
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
			Profile* personalprofile;
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
	class BasicData
	{
		public:
			void load(QSqlRecord src);
			QSqlRecord toQSqlRecord();
		protected:
			
	}
	class Profile: public basicdata
	{
		protected:
			int id;
			QString sex;
			QString name;
			QString cardid;
			QString phone;
			QString username;
		public:
			void load(QSqlRecord src);
			QSqlRecord toQSqlRecord();
			Profile(QSqlRecord src);
	}
	class Train: public BasicData
	{
		protected:
			QString trainnumber;
			int seattype;
			int speedtype;
		public:
			void load(QSqlRecord src);
			QSqlRecord toQSqlRecord();
			Train(QSqlRecord src);
			
			
	}
	class Station:public BasicData
	{
		protected:
			int id;
			QString name;
			QString province;
	}
	class TrainStation:public BasicData
		{
			protected:
				QTime arrivetime;
				QTime starttiem;
				int   id;
				int   number;
				QString trainnumber;
				int station_id;
			public:
				void load(QSqlRecord src);
				QSqlRecord toQSqlRecord();
				Train(QSqlRecord src);
		}
	class Ticket:public BasicData
	{
		protected:
			int id;
			int profile_id;
			int seatnumber;
			int beginstation_id;
			int endstation_id;
		public:
			void load(QSqlRecord src);
			QSqlRecord toQSqlRecord();
			Train(QSqlRecord src);
			
			
	}

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
    number		INT  NOT NULL ,//表示这个站在这趟车上的位次，从零开始
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
	beginstation_id INT NOT NULL,
	endstation_id	INT NOT NULL,
	FOREIGN KEY(beginstation_id) REFERENCES trainstations(id)
	FOREIGN KEY(endstation_id)	 REFERENCES trainstations(id)
	FOREIGN KEY(profile_id)		 REFERENCES profile(id)	
	
}

```

//ToDo.
	