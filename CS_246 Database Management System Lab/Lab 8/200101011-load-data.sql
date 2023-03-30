create database if not exists assignment08;
use assignment08;

create table if not exists ett(
	cid char(10),
    exam_date date,
    start_time time,
    end_time time
);

create table if not exists cc(
	cid char(10) primary key,
    credits int
);

create table if not exists cwsl(
	serial_number int,
    cid char(10),
    roll_number char(10),
    stud_name char(50),
    stud_email char(30),
    primary key(cid,roll_number)
);

load data local infile "C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 8/database-07-mar-2022/exam-time-table.csv"
into table ett
fields terminated by ','
lines terminated by '\n';

load data local infile "C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 8/database-07-mar-2022/course-credits.csv"
into table cc
fields terminated by ','
lines terminated by '\n';

-- Before running the next sql query, do run the pyhton program to generate merged sql file having list of all students.
-- Ensure to change the locations as well according to your system.
-- Please also look into python file as there also the loactions need to be altered.

load data local infile "C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 8/database-07-mar-2022/merged-students-list.csv"
into table cwsl
character set latin1
fields terminated by ','
lines terminated by '\n';