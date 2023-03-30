-- Task 1
create database if not exists assignment05;
use assignment05;

-- Task 2
create table if not exists course(
	cid char(10),
    cname char(70),
    l int,
    t int,
    p int,
    c int,
    primary key(cid)
);

create table if not exists course_coordinator(
	cid char(10),
    cstart char(20),
    cend char(20),
    gsubmission char(20),
    coordinator char(50),
    exam_date char(40),
    primary key(cid)
);

create table if not exists course_eligibility(
	cid char(10) not null,
    program char(70),
    batch_year char(10),
    batch_month char(10),
    eligibility char(50)
);

create table if not exists course_instructor(
	cid char(10),
    instructor char(50)
);

create table if not exists faculty(
	dept char(50),
    instructor char(50),
    primary key(dept,instructor)
);

-- Task 3
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 5/database-07-jan-2022/course.csv'
into table course
fields terminated by '#'
lines terminated by '\n';
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 5/database-07-jan-2022/course_coordinator.csv'
into table course_coordinator
fields terminated by '#'
lines terminated by '\n';
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 5/database-07-jan-2022/course_eligibility.csv'
into table course_eligibility
fields terminated by '#'
lines terminated by '\n';
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 5/database-07-jan-2022/course_instructor.csv'
into table course_instructor
fields terminated by '#'
lines terminated by '\n';
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 5/database-07-jan-2022/faculty.csv'
into table faculty
fields terminated by '#'
lines terminated by '\n';

-- Task 4.1
select course.cname, count(course_eligibility.cid) as number_of_eligible_programs
from course, course_eligibility
where course.cid = course_eligibility.cid
group by course_eligibility.cid;

-- Task 4.2
create table if not exists temp1
as (select cid,cname,instructor,count(*) as num
from course
natural join course_instructor
group by cid);

select cid,cname,instructor
from course
natural join course_instructor
where (cid)
in (select cid
from temp1
where (num = (select max(num) from temp1)));

-- Task 4.3
create table if not exists temp2
as (select *
from course
where (((cid not like "%H") and (C <> (2*L+2*T+P)))
or ((cid like "%H") and (C <> ((2*L+2*T+P)/2)))));

select distinct cname,dept
from course
natural join course_instructor
natural join faculty
natural join temp2;

-- Task 4.4
select cname,coordinator
from course
natural join course_coordinator
where ((cid,coordinator)
not in (select * from course_instructor));

-- Task 4.5
select cname,gsubmission
from course
natural join course_coordinator;

-- Task 4.6
select cname,exam_date
from course
natural join course_coordinator
where cid not like "%H";

-- Task 4.7
create table if not exists temp3
as (select course.cid as cid, course.cname as cname, count(course_eligibility.cid) as number_of_eligible_programs
from course, course_eligibility
where course.cid = course_eligibility.cid
group by course_eligibility.cid);

select cid, cname, instructor
from course
natural join course_instructor
natural join temp3
where temp3.number_of_eligible_programs >= 10;

-- Task 4.8
select instructor,dept,cid
from faculty
natural join course_instructor;

-- Task 4.9
select *
from faculty
where ((instructor)
not in (select instructor from course_instructor))
order by dept;