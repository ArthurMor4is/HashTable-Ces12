#include <gtest/gtest.h>
#include "hash.h"
#include "hashfunctions.h"
#include <fstream>
#include <sstream>
#include <string>

TEST(Lab1Hash, AddOneElement){
    int collisons; int isthere;
    
    Hash *H = new Hash(29,hashdiv29);
    
    // before inserting, it must be empty
    isthere = H->contains("abc",collisons);
    EXPECT_EQ(0,isthere);
    EXPECT_EQ(0,collisons);
    EXPECT_EQ(0,H->worst_case());
    
    collisons = H->add("abc");
    EXPECT_EQ(0,collisons); // if it was empty, there could be no collisions
    EXPECT_EQ(1,H->worst_case());
    
    // check if inserted element is really there.
    isthere = H->contains("abc",collisons);
    EXPECT_EQ(1,isthere);
    EXPECT_EQ(1,collisons); // 1 element, 1 collision to find it
    // note that sum of chars of abd is just 1 + sum(abc)
    // so this would check the next bucket
    isthere = H->contains("abd",collisons);
    EXPECT_EQ(0,isthere);
    EXPECT_EQ(0,collisons);
    // node that we just changed the order, the sum must be the same
    isthere = H->contains("cab",collisons);
    EXPECT_EQ(0,isthere);
    EXPECT_EQ(1,collisons); // this queue has 1 element
    
         
    delete H;
      
}// AddOneElement


TEST(AuxLab1Hash, HashValueIsInsideVector){
    
    int tsize=29;
    Hash *H = new Hash(tsize,hashdiv29);
    
    int hval;
    hval = H->hash("abc");
    EXPECT_LE(hval, tsize);
    EXPECT_GE(hval, 0);
    
    // generate different strings and
    // check if hashvalue is not out of vector bounds
    std::string str = "a";
    char c = 'a';
    for (int i=0; i < 40 ; i++) {
        hval = H->hash(str);
        EXPECT_LE(hval, tsize);
        EXPECT_GE(hval, 0);
        str += c; c++; // adds another char to str
    }
    
    delete H;
}//HashValueIsInsideVector


TEST(Lab1Hash, Add4Elements){
    int collisons; int isthere;
    
    Hash *H = new Hash(29,hashdiv29);
    
    // 3 elements in the same bucket, 1 element in a different bucket
    collisons = H->add("abc");
    EXPECT_EQ(0,collisons); // if it was empty, there could be no collisions
    EXPECT_EQ(1,H->worst_case());
    collisons = H->add("abd"); // different bucket
    EXPECT_EQ(0,collisons); // different bucket, there could be no collisions
    EXPECT_EQ(1,H->worst_case()); // one element on each bucket
    collisons = H->add("bca"); // same bucket
    EXPECT_EQ(1,collisons); // bucket already had 1 element
    EXPECT_EQ(2,H->worst_case());
    collisons = H->add("cab"); // same bucket
    EXPECT_EQ(2,collisons); // bucket already had 2 elements
    EXPECT_EQ(3,H->worst_case()); // now  bucket has 3 elements
    
    
    // the number of collisons depend on the order elements were inserted in the bucket
    // check if inserted element is really there.
    isthere = H->contains("abc",collisons);
    EXPECT_EQ(1,isthere);
    EXPECT_EQ(3,collisons); // the first element inserted is at 3rd place in the list
    // node that we just changed the order, the sum must be the same
    isthere = H->contains("bca",collisons);
    EXPECT_EQ(1,isthere);
    EXPECT_EQ(2,collisons);// the 2nd element inserted is at 2nd place in the list
    // node that we just changed the order, the sum must be the same
    isthere = H->contains("cab",collisons);
    EXPECT_EQ(1,isthere);// the 3rd element inserted is at 1st place in the list
    EXPECT_EQ(1,collisons);
    
    // node that sum of chars of abd is just 1 + sum(abc)
    isthere = H->contains("abd",collisons);
    EXPECT_EQ(1,isthere);
    EXPECT_EQ(1,collisons);
         
    delete H;
      
}// Add4Elements


/*
 * reads of file of strings and adds the strings to the Hash H
 */
int HashFile(Hash* H,std::string filename) {
    std::ifstream infile(filename);
    
    int readlines = 0;
    std::string line;
    while (std::getline(infile, line)) {
        H->add(line);
        readlines++;
    }
    infile.close();
    return readlines;
}

std::string getDataDir() { return "../data/"; }


TEST(Lab1Hash, AddFileRandom){
    
    std::string datadir = getDataDir();
    
    int collisons; int isthere; int readlines;
    Hash *H = new Hash(29,hashdiv29);
    readlines = HashFile(H,datadir+"random.txt");
    EXPECT_EQ(700, readlines);
    EXPECT_EQ(42, H->worst_case());
    isthere = H->contains("Paris",collisons);
    EXPECT_EQ(1,isthere);
    EXPECT_EQ(23,collisons);
    isthere = H->contains("thy",collisons);
    EXPECT_EQ(1,isthere);
    EXPECT_EQ(3,collisons);
    isthere = H->contains("ITA",collisons);
    EXPECT_EQ(0,isthere);
    EXPECT_EQ(19,collisons);   
    delete H;
    
    
} //  AddFile

TEST(Lab1Hash, AddFilelength8){
    
    std::string datadir = getDataDir();
    
    int collisons; int isthere; int readlines;
    Hash *H = new Hash(29,hashdiv29);
    readlines = HashFile(H,datadir+"length8.txt");
    EXPECT_EQ(700, readlines);
    EXPECT_EQ(34, H->worst_case());
    isthere = H->contains("sidewalk",collisons);
    EXPECT_EQ(1,isthere);
    EXPECT_EQ(27,collisons);
    isthere = H->contains("epilogue",collisons);
    EXPECT_EQ(1,isthere);
    EXPECT_EQ(18,collisons);
    isthere = H->contains("ITA",collisons);
    EXPECT_EQ(0,isthere);
    EXPECT_EQ(20,collisons);   
    delete H;    
    
} //  AddFile



