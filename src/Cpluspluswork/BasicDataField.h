#ifndef BASICDATA_H
#define BASICDATA_H
#include<QSql>
#include<QSqlRecord>
#include<QTime>
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
    Ticket_BeginStation_Id,
    Ticket_EndStation_Id
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
    TrainStation_Number,
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
#endif
