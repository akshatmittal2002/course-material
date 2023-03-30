-- Task 1
create database if not exists assignment06;
use assignment06;

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 2.1
create table if not exists course(
	cid char(10),
    cname char(70),
    l int,
    t int,
    p int,
    c int,
    primary key(cid)
);

-- Task 2.2
create table if not exists course_coordinator(
	cid char(10),
    cstart char(20),
    cend char(20),
    gsubmission char(20),
    coordinator char(50),
    exam_date char(40),
    primary key(cid)
);

-- Task 2.3
create table if not exists course_eligibility(
	cid char(10) not null,
    program char(70),
    batch_year char(10),
    batch_month char(10),
    eligibility char(50)
);

-- Task 2.4
create table if not exists course_instructor(
	cid char(10),
    instructor char(50)
);

-- Task 2.5
create table if not exists faculty(
	dept char(50),
    instructor char(50),
    primary key(dept,instructor)
);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 3.1
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 6/database-14-feb-2022/course.csv'
into table course
fields terminated by '#'
lines terminated by '\n';

-- Task 3.2
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 6/database-14-feb-2022/course_coordinator.csv'
into table course_coordinator
fields terminated by '#'
lines terminated by '\n';

-- Task 3.3
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 6/database-14-feb-2022/course_eligibility.csv'
into table course_eligibility
fields terminated by '#'
lines terminated by '\n';

-- Task 3.4
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 6/database-14-feb-2022/course_instructor.csv'
into table course_instructor
fields terminated by '#'
lines terminated by '\n';

-- Task 3.5
load data local infile 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 6/database-14-feb-2022/faculty.csv'
into table faculty
fields terminated by '#'
lines terminated by '\n';

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.1
-- Nested Query
select cname, num as number_of_eligible_programs
from
	(select c.cid,c.cname,count(ce.cid) as num
     from course as c
     left outer join course_eligibility as ce
     on c.cid = ce.cid
     group by c.cid) as temp
where cid = ANY (select cid from course);

-- Correlated Query
select c.cname,
	(select count(*)
     from course_eligibility as ce
	 where ce.cid = c.cid) as number_of_eligible_programs
from course as c;

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.2
create table if not exists temp2 as
	(select cid,cname,instructor,count(*) as num
     from course
     natural join course_instructor
     group by cid);

-- Nested Query
select c.cid,c.cname,ci.instructor
from course as c
natural join course_instructor as ci
where c.cid in 
	(select cid
	 from temp2
	 where (num >= ALL
		(select distinct num 
		 from temp2)));

-- Correlated Query
select c.cid,c.cname,ci.instructor
from course as c
natural join course_instructor as ci
where exists 
	(select cid
	 from temp2
	 where (num >= ALL
		(select distinct num 
		 from temp2))
	 and temp2.cid = c.cid);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.3
-- Nested Query
select distinct c.cname,f.dept
from course as c
natural join course_instructor as ci
natural join faculty as f
where c.cid in
	(select cid
     from course
     where (((cid not like "%H")
     and (C <> (2*L+2*T+P)))
     or ((cid like "%H")
     and (C <> ((2*L+2*T+P)/2)))));

-- Correlated Query
select distinct c.cname,f.dept
from course as c
natural join course_instructor as ci
natural join faculty as f
where exists
	(select cid
     from course as c1
     where (((c1.cid not like "%H")
     and (C <> (2*L+2*T+P)))
     or ((c1.cid like "%H")
     and (C <> ((2*L+2*T+P)/2))))
     and c1.cid = c.cid);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.4
-- Nested Query
select c.cname,cc.coordinator
from course as c
natural join course_coordinator as cc
where (c.cid,cc.coordinator) not in
	(select cid,instructor
     from course_instructor);

-- Correlated Query
select c.cname,cc.coordinator
from course as c
natural join course_coordinator as cc
where not exists
	(select *
     from course_instructor as ci
     where ci.cid = c.cid
     and cc.coordinator = ci.instructor);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.5
-- Nested Query
select cname,gsubmission
from
	(select c.cid,c.cname,cc.gsubmission
     from course as c
     join course_coordinator as cc
     on c.cid = cc.cid) as temp
where cid = ANY (select cid from course);

-- Correlated Query
select cname,
	(select cc.gsubmission
     from course_coordinator as cc
     where cc.cid = c.cid) as gsubmission
from course as c;

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.6
-- Nested Query
select c.cname,cc.exam_date
from course as c
natural join course_coordinator as cc
where c.cid not in
	(select cid
     from course
     where cid like "%H");

-- Correlated Query
select cname,
	(select exam_date
     from course_coordinator as cc
     where cc.cid = c.cid) as exam_date
from course as c
where not exists
	(select cid
     from course
     where cid like "%H"
     and course.cid = c.cid);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.7
create table if not exists temp7 as
	(select c.cid, c.cname, count(ce.cid) as num
	 from course as c
	 left outer join course_eligibility as ce
	 on c.cid = ce.cid
	 group by c.cid);

-- Nested Query
select c.cid, c.cname, ci.instructor
from course as c
natural join course_instructor as ci
where cid in
	(select cid
     from temp7
     where temp7.num >= 10);

-- Correlated Query
select 
	(select c.cid
     from course as c
     where c.cid = ci.cid) as cid,
     (select c.cname
     from course as c
     where c.cid = ci.cid) as cname, ci.instructor
from course_instructor as ci
where exists
	(select cid
     from temp7
     where temp7.num >= 10
     and temp7.cid = ci.cid);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.8
-- Nested Query
select instructor,dept,cid
from
	(select *
     from faculty as f
     natural join course_instructor as ci) as temp
where cid = ANY (select cid from course);

-- Correlated Query
select ci.instructor, f.dept, ci.cid
from course_instructor AS ci, faculty as f
where exists
    (select *
     from faculty as f1
     where f1.instructor = f.instructor
     and f1.instructor = ci.instructor);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 4.9
-- Nested Query
select *
from faculty as f
where ((f.instructor) not in 
	(select ci.instructor
	 from course_instructor as ci))
order by dept;

-- Correlated Query
select *
from faculty as f
where not exists 
	(select *
	 from course_instructor as ci
     where ci.instructor = f.instructor)
order by dept;

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.1
create view view1 as
	select cname, num as number_of_eligible_programs
	from
		(select c.cid,c.cname,count(ce.cid) as num
		 from course as c
		 left outer join course_eligibility as ce
		 on c.cid = ce.cid
		 group by c.cid) as temp
	where cid = ANY (select cid from course);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.2
create view view2 as
	select c.cid,c.cname,ci.instructor
	from course as c
	natural join course_instructor as ci
	where c.cid in 
		(select cid
		 from temp2
		 where (num >= ALL
			(select distinct num 
			 from temp2)));

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.3
create view view3 as
	select distinct c.cname,f.dept
	from course as c
	natural join course_instructor as ci
	natural join faculty as f
	where c.cid in
		(select cid
		 from course
		 where (((cid not like "%H")
		 and (C <> (2*L+2*T+P)))
		 or ((cid like "%H")
		 and (C <> ((2*L+2*T+P)/2)))));

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.4
create view view4 as
	select c.cname,cc.coordinator
	from course as c
	natural join course_coordinator as cc
	where (c.cid,cc.coordinator) not in
		(select cid,instructor
		 from course_instructor);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.5
create view view5 as
	select cname,gsubmission
	from
		(select c.cid,c.cname,cc.gsubmission
		 from course as c
		 join course_coordinator as cc
		 on c.cid = cc.cid) as temp
	where cid = ANY (select cid from course);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.6
create view view6 as
	select c.cname,cc.exam_date
	from course as c
	natural join course_coordinator as cc
	where c.cid not in
		(select cid
		 from course
		 where cid like "%H");

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.7
create view view7 as
	select c.cid, c.cname, ci.instructor
	from course as c
	natural join course_instructor as ci
	where cid in
		(select cid
		 from temp7
		 where temp7.num >= 10);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.8
create view view8 as
	select instructor,dept,cid
	from
		(select *
		 from faculty as f
		 natural join course_instructor as ci) as temp
	where cid = ANY (select cid from course);

-- ---------------------------------------------------------------------------------------------------------------------------
-- Task 5.9
create view view9 as
	select *
	from faculty as f
	where ((f.instructor) not in 
		(select ci.instructor
		 from course_instructor as ci))
	order by dept;