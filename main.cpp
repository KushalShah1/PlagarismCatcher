#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "HashTable.h"
#include <chrono>

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

struct Worst{
    string filename1;
    string filename2;
    int data;
};
bool compareWorstCheaters(const Worst &a, const Worst &b ){
    return a.data > b.data;
}

int main(int argc, char *argv[])
{
    string dir = string(argv[1]);
    //string dir = string("../med_doc_set");

    vector<string> files = vector<string>();
    int nWordSequence=stoi(argv[2]);
    //int nWordSequence=20;

    getdir(dir,files);
    files.erase(files.begin(),files.begin()+2);//deletes "." and ".."
    HashTable cheaters(524287);//Big prime number

    int **similarities = new int*[files.size()];
    for(int i = 0; i < files.size(); ++i) {
        similarities[i] = new int[files.size()];
        for(int j=0;j<files.size();j++){
            similarities[i][j]=0;
        }
    }


    for (int fileIndex=0;fileIndex<files.size();fileIndex++) {
        ifstream myfile;
        myfile.open(dir + "\\" + files.at(fileIndex));

        string word;

        int insertIndex=0;
        int currentReadIndex=0;
        string sequence="";
        if(myfile.is_open()) {
            string *contents= new string[nWordSequence];

            while (myfile >> word) {
                contents[insertIndex] = word;
                currentReadIndex = (insertIndex+nWordSequence) % nWordSequence;
                insertIndex = (insertIndex + 1) % nWordSequence;

                sequence = "";
                int tempIndex=currentReadIndex;
                for (int i = 0; i < nWordSequence; i++) {
                    sequence += contents[tempIndex];
                    tempIndex = (tempIndex + 1) % nWordSequence;
                }
                vector<int> collisions = cheaters.insert(sequence, fileIndex);
                collisions.erase( unique( collisions.begin(), collisions.end() ), collisions.end() );
                if(collisions.size()>0) {
                    for (int x:collisions) {
                        similarities[fileIndex][x]++;
                    }
                }
            }
            delete[](contents);

        }
    }
    vector<Worst> topCheaters;
    for(int i=0;i<files.size();i++){
        for(int j=0;j<i;j++){
            if(similarities[i][j]>200) {
                topCheaters.push_back({files.at(i), files.at(j), similarities[i][j]});
            }
        }
    }

    std::sort(topCheaters.begin(), topCheaters.end(), compareWorstCheaters);

    for(int i=0;i<topCheaters.size();i++){
        cout<<topCheaters.at(i).data<<" : "<<topCheaters.at(i).filename1<<", "<<topCheaters.at(i).filename2<<endl;
    }



    for(int i = 0; i < files.size(); ++i) {
        delete []similarities[i];
    }
    delete [] similarities;
    return 0;
}