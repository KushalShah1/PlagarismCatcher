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

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    string dir = string("..\\med_doc_set");
    vector<string> files = vector<string>();
    int nWordSequence=6;
    getdir(dir,files);
    files.erase(files.begin(),files.begin()+2);
    HashTable cheaters(files.size()*2000);

    int **similarities = new int*[files.size()];
    for(int i = 0; i < files.size(); ++i) {
        similarities[i] = new int[files.size()];
    }
    for(int i=0;i<files.size();i++){
        for(int j=0;j<files.size();j++){
            similarities[i][j]=0;
        }
    }


    string *contents= new string[nWordSequence];
    for (int fileIndex=0;fileIndex<files.size();fileIndex++) {
        ifstream myfile;
        myfile.open(dir + "\\" + files[fileIndex]);

        string word;

        int insertIndex=0;
        int currentReadIndex=0;
        string sequence="";
        if(myfile.is_open()) {
            while (myfile >> word) {
                contents[insertIndex] = word;
                insertIndex = (insertIndex + 1) % nWordSequence;

                currentReadIndex = (insertIndex + 1) % nWordSequence;
                sequence = "";
                for (int i = 0; i < nWordSequence; i++) {
                    sequence += contents[currentReadIndex];
                    currentReadIndex = (currentReadIndex + 1) % nWordSequence;
                }
                vector<int> collisions = cheaters.insert(sequence, fileIndex);
                if(collisions.size()>1) {
                    for (int x:collisions) {
                        similarities[fileIndex][x]++;
                    }
                }
            }
        }
    }
    vector<Worst> topCheaters;
    for(int i=0;i<files.size();i++){
        for(int j=0;j<i;j++){
            if(similarities[i][j]>400)
                topCheaters.push_back({files.at(i),files.at(j),similarities[i][j]});
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
    delete[](contents);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    return 0;
}