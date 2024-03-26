########################################
1.创建一个build文件夹，在里面cmake ..
2.在build下 make -j4
3.在build下 ./CsI_array run.mac G4程序开始运行
4.G4程序运行完成后（运行过程中也可以），在build文件夹下会出现一个Results.txt，
里面存放着原始数据
5.在build下打开root程序，输入 .x test.cpp
6.这时候会出现2个数据文件 Coincidence.txt 和 Info.txt，分别是筛选数据 和 x1,y1,z1,x2,y2,z2,Energy

修改root，用test.cpp修改
########################################
