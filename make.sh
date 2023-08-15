#make clean
make config=debug system=linux --jobs=4 VersaEditor
#make config=release system=linux --jobs=16 VersaEditor
./run.sh
