This project contains 3 different code files:1- e_shop.c(main program),2- e_shop.h(header, its where i prepare everything for my shop), 
3-arxeio_make.mak(this basically makes our executable file at ubuntu)

arxeio_make.mak: We assign our compiler and its flags, then declare our main program and the header added to it when creating the executable file, 
lastly we clean any files created during the process and not needed after

e_shop.h: First we make it so we dont take this file multiple times with our first two commands(if the e_shop.h doesnt exist it defines it otherwise it skips the following code), 
we include libraries used later and create constant, then we create we structs our shop, orders and shop items, lastly we have two functions which will be defined later

e_shop.c: First we include our header(he is essencial here), we define the previous fuctions 1)initialise_shop which creates the initial state of our shop and 2) process_order which
goes through the shop searching for the requested item and acts based on what we have on our code, then in main we create pipes and using fork we create childs, after using a for 
and our process_order fuction we process all our orders with parent(we do have a wait for our children to finish their work), and then theres nothing left but the prints.

For more details on each command the code contains comments. 

When it prints the final stats some values are weird regarding the orders made, there might have been a mistake when the initial values were given im not sure to be honest because
most of them appear correct

In order to execute it you need to pull it in ubuntu terminal (git pull) and maybe merge , then use make -f arxeio_make.mak and it should propably be ready to run using ./e_shop
