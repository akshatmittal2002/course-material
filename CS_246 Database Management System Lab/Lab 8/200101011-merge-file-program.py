import os

source = "C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 8/database-07-mar-2022/course-wise-students-list/"
des = open("C:/Users/mitta/Desktop/Documents/CS_246 DBMS/Lab 8/database-07-mar-2022/merged-students-list.csv",'w')

# Note: change the address of source and des location according to your system otherwise merged csv will not be generated.

for dirname in os.scandir(source):
    if dirname.is_dir():
        for filename in os.scandir(dirname.path):
            if filename.is_file():
                f = open(filename,'r')
                while(1):
                    c = f.read(1)
                    if not c:
                        break
                    if(c != ','):
                        des.write(c)
                    else:
                        des.write(',')
                        des.write(os.path.basename(filename).split('.')[0])
                        des.write(',')
                        while(1):
                            c = f.read(1)
                            if(c == '\n'):
                                des.write('\n')
                                break
                            des.write(c)
