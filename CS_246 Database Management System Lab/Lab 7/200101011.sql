-- Task 1
create database if not exists assignment07;
use assignment07;

-- -------------------------------------------------------------------------------------------------------
-- Task 2.1
delimiter ||
create function join_year_func( roll_no char(10) )
returns int deterministic
begin
	declare one_two int;
    set one_two = substring(roll_no,1,2);
    set one_two = concat('20',one_two);
	return one_two;
end; ||
delimiter ;

-- -------------------------------------------------------------------------------------------------------
-- Task 2.2
delimiter ||
create function join_prog_func( roll_no char(10) )
returns char(10) deterministic
begin
	declare three_four char(10);
    set three_four = substring(roll_no,3,2);
    if(three_four = '01')
    then
		return 'B.Tech';
    else
		if(three_four = '02')
		then
			return 'B.Des';
		else
			return NULL;
		end if;
    end if;
end; ||
delimiter ;

-- -------------------------------------------------------------------------------------------------------
-- Task 2.3
delimiter ||
create function join_dept_func( roll_no char(10) )
returns char(10) deterministic
begin
	declare five_six char(10);
    set five_six = substring(roll_no,5,2);
    case
		when five_six = '01' then return 'CSE';
        when five_six = '02' then return 'ECE';
        when five_six = '03' then return 'ME';
        when five_six = '04' then return 'CE';
        when five_six = '05' then return 'DD';
        when five_six = '06' then return 'BSBE';
        when five_six = '07' then return 'CL';
        when five_six = '08' then return 'EEE';
        when five_six = '21' then return 'EPH';
        when five_six = '22' then return 'CST';
        when five_six = '23' then return 'M&C';
        else return NULL;
	end case;
end; ||
delimiter ;

-- -------------------------------------------------------------------------------------------------------
-- Task 3
create table if not exists hss_electives(
	roll_number char(10),
    sname char(70) not null,
    cid char(10) not null,
    cname char(70) not null,
    primary key(roll_number)
);

-- -------------------------------------------------------------------------------------------------------
-- Task 4
create table if not exists student_details(
	roll_number char(10),
    sname char(70) not null,
    joined_year int not null,
    joined_program char(10) not null,
    joined_dept char(10) not null,
    primary key(roll_number)
);

-- -------------------------------------------------------------------------------------------------------
-- Task 5
delimiter ||
create trigger insert_student_details
after insert
on hss_electives
for each row
begin
	insert into student_details(roll_number,sname,joined_year,joined_program,joined_dept)
    values (
		new.roll_number,
        new.sname,
        join_year_func(new.roll_number),
        join_prog_func(new.roll_number),
        join_dept_func(new.roll_number)
        );
end; ||
delimiter ;

-- -------------------------------------------------------------------------------------------------------
-- Task 6
load data local infile "C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 7/HSS_ELECTIVE_ALLOCATION_2018_BATCH.csv"
into table hss_electives
fields terminated by '#'
lines terminated by '\n'
ignore 4 lines;

-- -------------------------------------------------------------------------------------------------------
-- Task 7.1
insert into hss_electives(roll_number,sname,cid,cname)
values ('AB0101011','Xyz Abc','HS123','Game Theory And Economics'); -- Instance 1 : Since joined_year is integer data type but we are
-- getting 'AB' on parsing roll number which is not valid, hence row will not be inserted.
insert into hss_electives(roll_number,sname,cid,cname)
values ('','Abc Xyz','HS123','Game Theory And Economics'); -- Instance 2 : Since joined_year is integer data type but we are
-- getting '' on parsing roll number which is not valid, hence row will not be inserted.

-- -------------------------------------------------------------------------------------------------------
-- Task 7.2
insert into hss_electives(roll_number,sname,cid,cname)
values ('200309011','Xyz Abc','HS123','Game Theory And Economics'); -- Instance 1 : In the given roll number program code = '03',
-- but this code is invalid, hence row will not be inserted generating error via join_prog_func.
insert into hss_electives(roll_number,sname,cid,cname)
values ('18','Abc Xyz','HS123','Game Theory And Economics'); -- Instance 2 : In the given roll number program code = null,
-- hence row will not be inserted generating error via join_prog_func.

-- -------------------------------------------------------------------------------------------------------
-- Task 7.3
insert into hss_electives(roll_number,sname,cid,cname)
values ('200109011','Xyz Abc','HS123','Game Theory And Economics'); -- Instance 1 : In the given roll number dept code = '09',
-- but this code is invalid, hence row will not be inserted generating error via join_prog_func.
insert into hss_electives(roll_number,sname,cid,cname)
values ('1802','Abc Xyz','HS123','Game Theory And Economics'); -- Instance 2 : In the given roll number dept code = null,
-- hence row will not be inserted generating error via join_prog_func.

-- -------------------------------------------------------------------------------------------------------
-- Task 7.4
insert into hss_electives(roll_number,sname,cid,cname)
values ('200101011','Xyz Abc',null,'Game Theory And Economics'); -- Instance 1 : Since column cid is null but table has not null
-- constraint on this column, this row will not be inserted into hss_electives.
insert into hss_electives(roll_number,sname,cid,cname)
values ('180205009','Abc Xyz','HS123','Game Theory And Economics'); -- Instance 2 : Since column roll_number is primary key and
-- roll_number = '180205009' already exists in table, this row will not be inserted into hss_electives.

-- -------------------------------------------------------------------------------------------------------
-- Task 8
delimiter ||
create trigger update_student_details
after update
on hss_electives
for each row
begin
	update student_details
    set
		roll_number = new.roll_number,
        sname = new.sname,
        joined_year = join_year_func(new.roll_number),
        joined_program = join_prog_func(new.roll_number),
        joined_dept = join_dept_func(new.roll_number)
	where roll_number = old.roll_number;
end; ||
delimiter ;

-- -------------------------------------------------------------------------------------------------------
-- Task 9
delimiter ||
create trigger delete_student_details
after delete
on hss_electives
for each row
begin
	delete from student_details
    where roll_number = old.roll_number;
end; ||
delimiter ;