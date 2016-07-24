#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;


class CFileList
{
  vector<dirent>list;


   CFileList (string path);

};


CFileList::CFileList (string path)
{
   struct dirent *dirp;
   DIR *dp = opendir (dir.c_str()); 
   if (! dp)
      {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while (dirp = readdir(dp)) 
              {
               list.push_back (dirp);

               //files.push_back(string(dirp->d_name));
              }

    closedir(dp);

};


/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
   struct dirent *dirp;
   DIR *dp = opendir (dir.c_str()); 
   if (! dp)
      {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while (dirp = readdir(dp)) 
              {
               files.push_back(string(dirp->d_name));
              }

    closedir(dp);
    return 0;
}

int main()
{
    string dir = string(".");
    vector<string> files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        cout << files[i] << endl;
    }
    return 0;
}