-- Task 1
create database if not exists assignment04;
use assignment04;

-- Task 2
create table if not exists hss_electives(
	roll_number char(10),
	sname char(50) not null,
	cid char(10) not null,
	cname char(70) not null,
	primary key(roll_number)
);

-- Task 3
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 4/database-31-jan-2022/HSS_ELECTIVE_ALLOCATION_2018_BATCH.csv'
into table hss_electives
fields terminated by '#'
lines terminated by '\n'
ignore 4 lines;

-- Task 4
-- 4.1
insert into hss_electives(roll_number,sname,cid,cname)
values(180101058,'Pranav Gupta','HS 236','Sociological Perspectives on Modernity');
/* The above SQL statement will generate an error message since we are trying to insert duplicate value of roll number( which is a
primary key) into table and hence SQL will not allow this. */

-- 4.2
insert into hss_electives(roll_number,sname,cid,cname)
values(null,'Pranav Gupta','HS 236','Sociological Perspectives on Modernity');
/* The above SQL statement will generate an error message since we are trying to insert a null value into a column which is primary key
and hence SQL will not allow this. */

-- 4.3
insert into hss_electives(roll_number,sname,cid,cname)
values(180101058,null,'HS 236','Sociological Perspectives on Modernity');
/* The above SQL statement will generate an error message since we are trying to a null value into a column having 'not null'
constraint and hence SQL will not allow this. */

-- 4.4
insert into hss_electives(roll_number,sname,cid,cname)
values(180101058,'Pranav Gupta',null,'Sociological Perspectives on Modernity');
/* The above SQL statement will generate an error message since we are trying to a null value into a column having 'not null'
constraint and hence SQL will not allow this. */

-- 4.5
insert into hss_electives(roll_number,sname,cid,cname)
values(180101058,'Pranav Gupta','HS 236',null);
/* The above SQL statement will generate an error message since we are trying to a null value into a column having 'not null'
constraint and hence SQL will not allow this. */

-- Task 5
-- 5.1
update hss_electives set roll_number=null where roll_number=180123047;
/* The above SQL statement will generate an error message since we are trying to update a null value in the column roll_number (which is
primary key) but this is not possible and hence SQL will not allow this. */

-- 5.2
update hss_electives set roll_number=180123045 where roll_number=180123046;
/* The above SQL statement will generate an error message since we are trying to update a duplicate value in the column roll_number (which
is primary key) but this is not possible and hence SQL will not allow this. */

-- 5.3
update hss_electives set sname=null;
/* The above SQL statement will generate an error message since we are trying to update a null value in the column which has not null
constraint but this is not possible and hence SQL will not allow this. */

-- 5.4
update hss_electives set cid=null where cid='HS 211';
/* The above SQL statement will generate an error message since we are trying to update a null value in the column which has not null
constraint but this is not possible and hence SQL will not allow this. */

-- 5.5
update hss_electives set cname=null where cid='HS 245';
/* The above SQL statement will generate an error message since we are trying to update a null value in the column which has not null
constraint but this is not possible and hence SQL will not allow this. */

-- Task 6
-- 6.1
delete from hss_electives
where cid='HS 225';

-- 6.2
delete from hss_electives
where sname like '%Ajay%';
/* Please note:
1. If we run task 6.1 and 6.2 individually, 119 and 5 rows will be deleted respectively.
2. If we run task 6.1 and 6.2 in the order, first 119 and then 4 rows will be deleted.
*/

-- Task 7
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 4/database-31-jan-2022/HS225.csv'
into table hss_electives
fields terminated by '#'
lines terminated by '\n';

load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 4/database-31-jan-2022/ajay.csv'
into table hss_electives
fields terminated by '#'
lines terminated by '\n';

-- Task 8
show warnings;
/*
Note:	I am first loading the HS225.csv file and then ajay.csv file.
CASE 1:
		If we will run task 7 after running task 6 (both parts), there will be ony no warnings for HS225.csv file while 1 warning for
        ajay.csv file, i.e., "1062 Duplicate entry '180107005' for key 'hss_electives.PRIMARY'". This warning is coming because we are
        trying to insert a duplicate value into primary key for roll_number 180107005 which is not allowed.
CASE 2:
		If we will run task 7 directly after loading file (i.e., task 3), there will be 119 warnings for HS225.csv file and
        5 warnings for ajay.csv file. This is because all of the new entries are already present in the table and due to primary key
        constraint, we can not add them again.

The entry with roll_number 180107005 is present in both files.
Now, when we load from 'HS 225.csv' and 'ajay.csv' one after the other, this entry has already been added from 'HS225.csv'.
Due to primary key constraint, we can not add this again.
*/

-- Task 9
-- 9.1
alter table hss_electives drop primary key;

-- 9.2
insert into hss_electives(roll_number,sname,cid,cname)
values(180123001,'Aditi Bihade','HS 225','Inventing the Truth: The Art and Craft of Autobiography');

-- 9.3
alter table hss_electives add constraint xyz primary key(roll_number);
/*
Error code: 1062. Duplicate entry '180123001' for key 'hss_electives.PRIMARY'
Since, we have a duplicate value in the column roll_number, we can not add a primary key constraint onto it.
To do so, we have to delete one of this duplicate entry first.
*/

-- 9.4
insert into hss_electives(roll_number,sname,cid,cname)
values(180123001,'Aditi Bihade','HS 225','Inventing the Truth: The Art and Craft of Autobiography');
-- Since, dropping of primary key was unsuccessful, this record of 'Aditi Bihade' has been added again resulting in 3 duplicate entries.
-- Total records will be 659 now.

-- Task 10
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 4/database-31-jan-2022/old-hss-electives-allotment.csv'
into table hss_electives
fields terminated by ','
lines terminated by '\n'
ignore 1 lines;

-- Task 11
-- 11.1
select cid
from hss_electives;

-- 11.2
select *
from hss_electives
where (roll_number like '1_0101___')
or (roll_number like '1_0123___');

-- 11.3
select *
from hss_electives
where (roll_number like '1_0123___')
and (cname='Sociological Perspectives on Modernity');

-- 11.4
select distinct cid,cname
from hss_electives;

-- 11.5
select distinct cid,cname
from hss_electives
order by cname desc;

-- 11.6
select sname
from hss_electives
where cname='Human Resource Management'
order by sname,roll_number;