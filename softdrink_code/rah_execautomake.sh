
# apt-get install autoconf automake gcc

# config.ac is already there , preferably as read-only. 
# Therefore, following should work   

autoreconf -i
automake --add-missing
./configure
make

# make dist



# sudo make install 
# sudo make uninstall



