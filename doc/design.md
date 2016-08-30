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


##Design of the Model
- The user Model
- The manager Model
- The train Model




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
    number		INT,
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
	