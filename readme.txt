Purpose of the program:
The purpose of the program is to check a set of documents for similarities and return a list in order of the pairs of files 
that have over 200 matching n-word sequences. Our program limits the output to the top 25 most plagarised file pairs.

Partners:
Kushal Shah- KHS722
Jay Chaudhari- JC79858

File Names:
main.cpp, HashTable.cpp, HashTable.h, makefile

How to use it:
1. Open linux command window
2. Type ‘module load gcc’
3. Unzip the folder and navigate to it
4. Type ‘make’
5. Run the resulting file with "./plagarismCatcher PATH/TO/FILE CHUNKSIZE" make sure the the path does not have / at the end.

What works:
Successfully sorts pairs of plagiarized documents in order for small, medium, and big sets
Better results with a higher n-word sequence.

What doesn’t work:
Nothing

Bugs:
None