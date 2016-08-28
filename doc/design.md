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

//ToDo.
	