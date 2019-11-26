#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

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

int main()
{
    string dir = string("..\\sm_doc_set");
    vector<string> files = vector<string>();
    int nWordSequence=6;
    getdir(dir,files);

    for (const auto & file : files) {
        ifstream myfile;
        myfile.open(dir + "\\" + file);

        string word;
        vector<string> contents = vector<string>();
        if (myfile.is_open()) {
            while (myfile >> word) {
                contents.push_back(word);
                if(contents.size()==nWordSequence){
                    string sequence;
                    for (int j = 0; j < nWordSequence; j++){
                        sequence += contents.at(j);
                    }
                    cout<<sequence<<endl;
                    rotate(contents.begin(),contents.begin()+1,contents.end());
                    contents.erase(contents.end());
                }
            }
            /*for (int i = 0; i < contents.size() - nWordSequence; i++) {
                string sequence;
                for (int j = 0; j < nWordSequence; j++) {
                    sequence += contents.at(i + j);
                }
                cout << sequence << endl;
            }*/
        }
    }
    return 0;
}