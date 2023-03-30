CREATE DATABASE IF NOT EXISTS assignment03;
USE assignment03;

-- NOTE: Paths used for loading data into tables from various files are relative to my system. Please update them accordingly.

# Task 1

CREATE TABLE IF NOT EXISTS course(`Course No` CHAR(10),
								  `Course Title` CHAR(100) NOT NULL,
								  `L` INT NOT NULL,
                                  `T` INT NOT NULL,
                                  `P` INT NOT NULL,
                                  `C` INT NOT NULL,
                                  `Type Of Course` CHAR(100) NOT NULL,
                                  PRIMARY KEY(`Course No`));

# Task 2

LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/courses.csv'
INTO TABLE course
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

# Task 3

CREATE TABLE IF NOT EXISTS course_offered_to(`Course No` CHAR(10),
										   `Type Of Course` CHAR(100) NOT NULL,
                                           `Offered To` VARCHAR(150) NOT NULL,
                                           PRIMARY KEY(`Course No`),
                                           FOREIGN KEY(`Course No`) references course(`Course No`) ON DELETE CASCADE ON UPDATE CASCADE);

# Task 4

LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/courses-offered-to.csv'
INTO TABLE course_offered_to
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

# Task 5

CREATE TABLE IF NOT EXISTS course_exam_slot(`Course No` CHAR(10),
										   `Exam Slot` CHAR(5),
                                           `Exam Date and Time` CHAR(100),
                                           PRIMARY KEY(`Course No`),
                                           FOREIGN KEY(`Course No`) references course(`Course No`) ON DELETE CASCADE ON UPDATE CASCADE);

# Task 6

LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/courses-exam-slots.csv'
INTO TABLE course_exam_slot
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

# Task 7

CREATE TABLE IF NOT EXISTS faculty(`Faculty ID` INT,
								   `Department Name` CHAR(10) NOT NULL,
                                   `Faculty Name` VARCHAR(150) NOT NULL,
                                   PRIMARY KEY(`Faculty ID`));

# Task 8

LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/bt.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/ce.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/ch.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/cl.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/cs.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/da.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/dd.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/dm.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/ee.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/en.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/hs.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/ifst.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/ls.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/ma.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/me.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/nt.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/ph.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/ra.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';
LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty/rt.csv'
INTO TABLE faculty
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';

# Task 9

CREATE TABLE IF NOT EXISTS faculty_course_allotment(`Course No` CHAR(10),
												  `Department Name` CHAR(10) NOT NULL,
                                                  `Faculty ID` INT,
                                                  PRIMARY KEY(`Course No`,`Faculty ID`),
                                                  FOREIGN KEY(`Course No`) references course(`Course No`) ON DELETE CASCADE ON UPDATE CASCADE,
                                                  FOREIGN KEY(`Faculty ID`) references faculty(`Faculty ID`) ON DELETE CASCADE ON UPDATE CASCADE);

# Task 10
-- NOTE: Their is a entry "BD" in line 430 of "faculty-course-allotment.csv" file corresponding to "Facluty ID" and hence, this row will not be
-- accepted as valid record. Further, no such entry is present in the 19 files of faculty directory and hence while inserting this row, foreign
-- key constraint will be violated and this row will not be inserted.

LOAD DATA LOCAL INFILE 'C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 3/database-24-jan-2022/faculty-course-allotment.csv'
INTO TABLE faculty_course_allotment
FIELDS TERMINATED BY '#'
LINES TERMINATED BY '\n';