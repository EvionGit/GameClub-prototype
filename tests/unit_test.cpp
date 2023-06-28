#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <filesystem>

/* compares content of two files */
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
            return false;
        }
    }
      
    return true;
}
   
/* get all files in dir */
void get_files(std::set<std::string> &out, const std::string &directory)
{

    for (const auto & entry : std::filesystem::directory_iterator(directory))
    {   
        std::string path(entry.path().string());

#ifdef _WIN32
        out.insert(path.substr(path.find_last_of('\\') + 1));
#else
        out.insert(path.substr(path.find_last_of('/') + 1));
#endif
    }
}


/* for each file execute GameClub prog and check results with OUTPUTS files */
void testing(std::set<std::string>& files,std::string& exe_dir ,std::string& i_dir, std::string& o_dir)
{
    if (files.empty())
        return;

    int i = 0;

    std::string rm_cmd; //delete tmp file
    std::string run_cmd; //run program
    std::string out_file; //output check file
    for(auto it = files.begin(); it != files.end();it++)
    {
        i++;
        printf("TEST[%i], FILENAME[%s] - ", i, it->c_str());

#ifdef _WIN32
        run_cmd = exe_dir + " " + i_dir + "\\" + *it + " > tmp_result_test.txt";
        rm_cmd = "del tmp_result_test.txt";
        out_file = o_dir + "\\" + *it;
#else
        run_cmd = exe_dir + " " + i_dir + "/" + *it + " > tmp_result_test.txt";
        rm_cmd = "rm tmp_result_test.txt";
        out_file = o_dir + "/" + *it;
#endif 

        /* run GameClub.exe and create tmp file with results */
        system(run_cmd.c_str());


        /* compare results */
        if(compare_files(out_file,"tmp_result_test.txt"))
            printf("OK\n");
        else
            printf("NO\n");

    }

    system(rm_cmd.c_str());
}

int main(int argc, char*argv[])
{
    if(argc != 4)
    {
        printf("<program> <GameClub.exe PATH> <INPUT TEST DIR> <OUTPUT TEST DIR>\n");
        return 1;
    }

    std::string exe_dir = argv[1];
    std::string path_input = argv[2];
    std::string path_output = argv[3];
   
    
    std::set<std::string> inputs;
    std::set<std::string> outputs;

    get_files(inputs,path_input);
    get_files(outputs,path_output);

    std::set<std::string> intersect;
    std::set_intersection(inputs.begin(),inputs.end(),
                          outputs.begin(),outputs.end(),
                          std::inserter(intersect,intersect.begin()));

    testing(intersect,exe_dir,path_input,path_output);


    return 0;

}
