# Google Test library is included into this project (in /lib) instead of downloading it directly in compilation due to problems with GOOGLETEST_VERSION label (see general CmakeLists.txt).

# Not tested in Linux, only in Windows due to lack of time (I tried to avoid external libraries like boost in spite of the code optimization).  

# Tests (/tst) and main program (/src) are in separated folders.