#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <filesystem>

bool compare_files(const std::string& p1, const std::string& p2)
{
    std::ifstream f1(p1);
    std::ifstream f2(p2);
  
    if (f1.fail() || f2.fail())
        return false;
    
    std::string l_line, r_line; 
   
    while(!f1.eof() || !f2.eof())
    {
        if(f1.eof() || f2.eof())
            return false;

        std::getline(f1,l_line);
        std::getline(f2,r_line);

        if(l_line != r_line)
        {
            //printf("\n\"%s\" != \"%s\"\n",l_line.c_str(),r_line.c_str()); 
            return false;
        }
    }
      
    return true;
}
    

void get_files(std::set<std::string> &out, const std::string &directory)
{

    for (const auto & entry : std::filesystem::directory_iterator(directory))
    {   
        std::string path(entry.path());
        out.insert(path.substr(path.find_last_of('/')+1));
    }
}

void testing(std::set<std::string>& files,std::string& i_dir, std::string& o_dir)
{
    int i = 0;
    for(auto it = files.begin(); it != files.end();it++)
    {
        i++;
        printf("TEST[%i], FILENAME[%s] - ",i,it->c_str());
        std::string cmd = "../GameClub " + i_dir + "/" +*it + " > tmp_result_test.txt";
        system(cmd.c_str());

        if(compare_files(o_dir + "/" + *it,"tmp_result_test.txt"))
            printf("OK\n");
        else
            printf("NO\n");

    }
    system("rm tmp_result_test.txt");
}

int main(int argc, char*argv[])
{
    if(argc != 3)
    {
        printf("<program> <inputs test dir> <outputs test dir>\n");
        return 1;
    }

    std::string path_input = argv[1];
    std::string path_output = argv[2];
   
    
    std::set<std::string> inputs;
    std::set<std::string> outputs;

    get_files(inputs,path_input);
    get_files(outputs,path_output);

    std::set<std::string> intersect;
    std::set_intersection(inputs.begin(),inputs.end(),
                          outputs.begin(),outputs.end(),
                          std::inserter(intersect,intersect.begin()));

    testing(intersect,path_input,path_output);


    return 0;

}
